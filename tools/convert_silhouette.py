#!/usr/bin/env python3
"""
Convert SilhouettesLarge.png and SilhouettesMedium.png into a combined sprite sheet.

Output:
  - Silhouettes.gbapal     (GBA palette, 16 colors, 32 bytes — shared by both)
  - Silhouettes.4bpp       (combined 4bpp tile data)

Combined sheet layout (each silhouette is split into 64x64 left + 32x64 right):
  Tiles   0-63:  Large  left  (64x64)
  Tiles  64-95:  Large  right (32x64)
  Tiles  96-159: Medium left  (64x64)
  Tiles 160-191: Medium right (32x64)
"""

import struct
import os
from PIL import Image


def image_to_4bpp(img):
    """Convert a PIL Image (mode P, indexed) to raw 4bpp tile data."""
    w, h = img.size
    assert w % 8 == 0 and h % 8 == 0, f"Image dimensions must be multiples of 8, got {w}x{h}"
    pixels = img.load()
    tiles_per_row = w // 8
    tiles_per_col = h // 8
    data = bytearray()

    for ty in range(tiles_per_col):
        for tx in range(tiles_per_row):
            for row in range(8):
                for col in range(0, 8, 2):
                    px_left = pixels[tx * 8 + col, ty * 8 + row] & 0x0F
                    px_right = pixels[tx * 8 + col + 1, ty * 8 + row] & 0x0F
                    byte_val = (px_right << 4) | px_left
                    data.append(byte_val)

    return bytes(data)


def make_gba_palette(img, num_colors=16):
    """Create a GBA palette from a PIL image, padded to num_colors."""
    pal = img.getpalette()
    if pal is None:
        raise ValueError("Image has no palette")
    actual_colors = len(pal) // 3
    gba_pal = bytearray()
    for i in range(num_colors):
        if i < actual_colors:
            r = pal[i * 3 + 0]
            g = pal[i * 3 + 1]
            b = pal[i * 3 + 2]
        else:
            r, g, b = 0, 0, 0
        gba_r = (r >> 3) & 0x1F
        gba_g = (g >> 3) & 0x1F
        gba_b = (b >> 3) & 0x1F
        color = (gba_b << 10) | (gba_g << 5) | gba_r
        gba_pal.extend(struct.pack('<H', color))
    return bytes(gba_pal)


def split_4bpp_left_right(tile_data, src_w, src_h, split_x):
    """Split 4bpp tile data into left (split_x wide) and right remainder."""
    assert split_x % 8 == 0
    tiles_per_row = src_w // 8
    left_tiles_per_row = split_x // 8
    tiles_per_col = src_h // 8
    tile_size = 32

    left_data = bytearray()
    right_data = bytearray()

    for ty in range(tiles_per_col):
        for tx in range(tiles_per_row):
            offset = (ty * tiles_per_row + tx) * tile_size
            tile = tile_data[offset:offset + tile_size]
            if tx < left_tiles_per_row:
                left_data.extend(tile)
            else:
                right_data.extend(tile)

    return bytes(left_data), bytes(right_data)


def convert_to_indexed(img, reference_img=None, target_colors=2):
    """Convert RGBA/RGB image to indexed P mode with target_colors.
    If reference_img is provided, map pixels to match its palette."""
    if img.mode == 'P' and reference_img is None:
        return img

    if reference_img is not None and reference_img.mode == 'P':
        # Map pixels to reference palette: find closest color
        ref_pal = reference_img.getpalette()
        ref_colors = [(ref_pal[i*3], ref_pal[i*3+1], ref_pal[i*3+2]) for i in range(target_colors)]
        result = img.convert('RGB')
        pixels = result.load()
        w, h = result.size
        out = Image.new('P', (w, h), 0)
        out_pixels = out.load()
        for y in range(h):
            for x in range(w):
                r, g, b = pixels[x, y]
                best_idx = 0
                best_dist = float('inf')
                for i, (rr, gg, bb) in enumerate(ref_colors):
                    dist = (r-rr)**2 + (g-gg)**2 + (b-bb)**2
                    if dist < best_dist:
                        best_dist = dist
                        best_idx = i
                out_pixels[x, y] = best_idx
        out.putpalette(reference_img.getpalette())
        return out

    img_p = img.quantize(colors=target_colors, method=Image.Quantize.FASTOCTREE)
    return img_p


def pad_image(img, target_w, target_h, fill_index=0):
    """Pad an indexed image to target_w x target_h with fill_index."""
    w, h = img.size
    if w >= target_w and h >= target_h:
        return img
    padded = Image.new('P', (target_w, target_h), fill_index)
    padded.paste(img, (0, 0))
    # Copy palette from original
    if img.getpalette():
        padded.putpalette(img.getpalette())
    return padded


def process_silhouette(path, split_x=64, reference_img=None):
    """Load, convert, pad, and split a silhouette image. Returns (img, left_data, right_data)."""
    img = Image.open(path)
    print(f"  Loaded: {img.size} mode={img.mode}")

    # Convert RGBA to indexed if needed
    if img.mode != 'P':
        img = convert_to_indexed(img, reference_img=reference_img)
        print(f"  Converted to: {img.size} mode={img.mode}")

    # Pad to multiple of 8 in width, and to at least 96 wide for clean 64+32 split
    w, h = img.size
    padded_w = max(w, 96)
    padded_h = max(h, 64)
    # Round up to multiples of 8
    padded_w = ((padded_w + 7) // 8) * 8
    padded_h = ((padded_h + 7) // 8) * 8
    img = pad_image(img, padded_w, padded_h)
    print(f"  Padded to: {img.size}")

    # Convert to 4bpp tiles
    tile_data = image_to_4bpp(img)
    print(f"  Tiles: {len(tile_data)} bytes ({len(tile_data) // 32} tiles)")

    # Split into left and right
    left_data, right_data = split_4bpp_left_right(tile_data, img.size[0], img.size[1], split_x)
    print(f"  Left: {len(left_data)} bytes ({len(left_data) // 32} tiles), Right: {len(right_data)} bytes ({len(right_data) // 32} tiles)")

    return img, left_data, right_data


def process_silhouette_small(path, reference_img=None, target_w=None, target_h=None):
    """Load, convert, and tile a silhouette into a single OAM sprite.
    If target_w/target_h are set, crop/pad to that size (must be multiples of 8)."""
    img = Image.open(path)
    print(f"  Loaded: {img.size} mode={img.mode}")

    if img.mode != 'P':
        img = convert_to_indexed(img, reference_img=reference_img)
        print(f"  Converted to: {img.size} mode={img.mode}")

    if target_w and target_h:
        # Crop or pad to exact target size
        img = img.crop((0, 0, min(img.size[0], target_w), min(img.size[1], target_h)))
        img = pad_image(img, target_w, target_h)
        print(f"  Cropped/padded to: {img.size}")
    else:
        w, h = img.size
        padded_w = ((w + 7) // 8) * 8
        padded_h = ((h + 7) // 8) * 8
        img = pad_image(img, padded_w, padded_h)
        print(f"  Padded to: {img.size}")

    tile_data = image_to_4bpp(img)
    print(f"  Tiles: {len(tile_data)} bytes ({len(tile_data) // 32} tiles)")

    return img, tile_data


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    gfx_dir = os.path.join(script_dir, '..', 'graphics', 'title_screen')

    # Skip if outputs are already up to date
    input_files = [
        os.path.join(gfx_dir, 'SilhouettesLarge.png'),
        os.path.join(gfx_dir, 'SilhouettesMedium.png'),
        os.path.join(gfx_dir, 'SilhouettesSmall.png'),
        os.path.join(gfx_dir, 'SalamenceSilhouette.png'),
        os.path.join(gfx_dir, 'SilhouettesTiny.png'),
    ]
    output_files = [
        os.path.join(gfx_dir, 'Silhouettes.gbapal'),
        os.path.join(gfx_dir, 'Silhouettes.4bpp'),
    ]
    all_exist = all(os.path.exists(f) for f in input_files + output_files)
    if all_exist:
        newest_in = max(os.path.getmtime(f) for f in input_files)
        oldest_out = min(os.path.getmtime(f) for f in output_files)
        if oldest_out > newest_in:
            print("Silhouette tiles up to date, skipping.")
            return

    # Process Large silhouette
    print("Processing SilhouettesLarge.png:")
    large_img, large_left, large_right = process_silhouette(
        os.path.join(gfx_dir, 'SilhouettesLarge.png'))

    # Process Medium silhouette (using Large palette as reference)
    print("Processing SilhouettesMedium.png:")
    medium_img, medium_left, medium_right = process_silhouette(
        os.path.join(gfx_dir, 'SilhouettesMedium.png'), reference_img=large_img)

    # Process Small silhouette (using Large palette as reference)
    print("Processing SilhouettesSmall.png:")
    small_img, small_tiles = process_silhouette_small(
        os.path.join(gfx_dir, 'SilhouettesSmall.png'), reference_img=large_img)

    # Process Salamence silhouette (crop to 64x64, pad to 64x64 for OAM)
    print("Processing SalamenceSilhouette.png:")
    salamence_img, salamence_tiles = process_silhouette_small(
        os.path.join(gfx_dir, 'SalamenceSilhouette.png'), reference_img=large_img,
        target_w=64, target_h=64)

    # Process Tiny silhouette (32x32, single OAM sprite)
    print("Processing SilhouettesTiny.png:")
    tiny_img, tiny_tiles = process_silhouette_small(
        os.path.join(gfx_dir, 'SilhouettesTiny.png'), reference_img=large_img)

    # Generate shared palette from the large image
    pal_data = make_gba_palette(large_img, 16)
    pal_path = os.path.join(gfx_dir, 'Silhouettes.gbapal')
    with open(pal_path, 'wb') as f:
        f.write(pal_data)
    print(f"\nWrote palette: {pal_path} ({len(pal_data)} bytes)")

    # Combine all into one sprite sheet
    combined = bytearray()
    combined.extend(large_left)    # Tiles 0-63:   Large  left  (64 tiles)
    combined.extend(large_right)   # Tiles 64-95:  Large  right (32 tiles)
    combined.extend(medium_left)   # Tiles 96-159: Medium left  (64 tiles)
    combined.extend(medium_right)  # Tiles 160-191:Medium right (32 tiles)
    combined.extend(small_tiles)   # Tiles 192-207:Small        (16 tiles)
    combined.extend(salamence_tiles) # Tiles 208-271:Salamence   (64 tiles)
    combined.extend(tiny_tiles)     # Tiles 272-287:Tiny         (16 tiles)

    combined_path = os.path.join(gfx_dir, 'Silhouettes.4bpp')
    with open(combined_path, 'wb') as f:
        f.write(combined)
    total_tiles = len(combined) // 32
    print(f"Wrote combined sheet: {combined_path} ({len(combined)} bytes, {total_tiles} tiles)")
    print(f"  Large  left={len(large_left)//32} right={len(large_right)//32} -> tiles 0-{(len(large_left)+len(large_right))//32-1}")
    offset = (len(large_left) + len(large_right)) // 32
    print(f"  Medium left={len(medium_left)//32} right={len(medium_right)//32} -> tiles {offset}-{offset+(len(medium_left)+len(medium_right))//32-1}")
    offset += (len(medium_left) + len(medium_right)) // 32
    print(f"  Small  tiles={len(small_tiles)//32} -> tiles {offset}-{offset+len(small_tiles)//32-1}")
    offset += len(small_tiles) // 32
    print(f"  Salamence tiles={len(salamence_tiles)//32} -> tiles {offset}-{offset+len(salamence_tiles)//32-1}")
    offset += len(salamence_tiles) // 32
    print(f"  Tiny     tiles={len(tiny_tiles)//32} -> tiles {offset}-{offset+len(tiny_tiles)//32-1}")


if __name__ == '__main__':
    main()

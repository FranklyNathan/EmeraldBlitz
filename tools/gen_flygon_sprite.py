import struct
import sys
import os

TILE_SIZE = 32  # bytes per 8x8 4bpp tile
IMG_W_TILES = 16  # 128/8
IMG_H_TILES = 20  # 160/8

def get_tile(bg_data, tile_col, tile_row):
    idx = (tile_row * IMG_W_TILES + tile_col) * TILE_SIZE
    return bg_data[idx:idx+TILE_SIZE]

with open('graphics/title_screen/titleflygon.4bpp', 'rb') as f:
    bg_tiles = f.read()

sprites = [
    (0,  0,  8, 8),   # 64x64 top-left
    (8,  0,  8, 8),   # 64x64 top-right
    (0,  8,  8, 8),   # 64x64 middle-left
    (8,  8,  8, 8),   # 64x64 middle-right
    (0,  16, 8, 4),   # 64x32 bottom-left
    (8,  16, 8, 4),   # 64x32 bottom-right
]

sprite_data = bytearray()
sprite_info = []

for sx, sy, sw, sh in sprites:
    offset = len(sprite_data)
    num_tiles = sw * sh
    for row in range(sh):
        for col in range(sw):
            tile = get_tile(bg_tiles, sx + col, sy + row)
            sprite_data.extend(tile)
    sprite_info.append((offset, num_tiles))

with open('graphics/title_screen/titleflygon_obj.4bpp', 'wb') as f:
    f.write(sprite_data)

print("Total sprite data: %d bytes (%d tiles)" % (len(sprite_data), len(sprite_data)//TILE_SIZE))

for i, (sx, sy, sw, sh) in enumerate(sprites):
    offset, num_tiles = sprite_info[i]
    tile_num = offset // TILE_SIZE
    print("Sprite %d: pos=(%d,%d) %dx%d tiles=%d tileNum=%d" % (i, sx*8, sy*8, sw*8, sh*8, num_tiles, tile_num))

#include "global.h"
#include "gba/gba.h"
#include "main.h"
#include "overworld.h"
#include "sprite.h"
#include "event_data.h"
#include "constants/flags.h"
#include "b_to_accel_hint.h"

#define B_TO_ACCEL_HINT_TILE_TAG   0xC0A3
#define B_TO_ACCEL_HINT_PAL_TAG    0xC0A4
#define B_TO_ACCEL_HINT_X_0        (-32)
#define B_TO_ACCEL_HINT_X_F        16
#define B_TO_ACCEL_HINT_Y          92
#define B_TO_ACCEL_HINT_HOLD_TIME  100

#define sHide  data[0]
#define sTimer data[1]

static const u8 sBToAccelHintGfx[] = INCBIN_U8("graphics/misc/b_to_accel.4bpp");
static const u16 sBToAccelHintPalette[] = INCBIN_U16("graphics/battle_interface/ability_pop_up.gbapal");

static const struct SpriteSheet sSpriteSheet_BToAccelHint =
{
    sBToAccelHintGfx, sizeof(sBToAccelHintGfx), B_TO_ACCEL_HINT_TILE_TAG
};

static const struct SpritePalette sSpritePalette_BToAccelHint =
{
    sBToAccelHintPalette, B_TO_ACCEL_HINT_PAL_TAG
};

static const struct OamData sOamData_BToAccelHint =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static void SpriteCB_BToAccelHint(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_BToAccelHint =
{
    .tileTag = B_TO_ACCEL_HINT_TILE_TAG,
    .paletteTag = B_TO_ACCEL_HINT_PAL_TAG,
    .oam = &sOamData_BToAccelHint,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_BToAccelHint,
};

static u8 sBToAccelHintSpriteId;

static bool32 IsBToAccelHintSprite(u8 spriteId)
{
    return spriteId < MAX_SPRITES
        && gSprites[spriteId].inUse
        && gSprites[spriteId].template == &sSpriteTemplate_BToAccelHint;
}

static void DestroyBToAccelHintGfx(struct Sprite *sprite)
{
    FreeSpriteTilesByTag(B_TO_ACCEL_HINT_TILE_TAG);
    FreeSpritePaletteByTag(B_TO_ACCEL_HINT_PAL_TAG);
    DestroySprite(sprite);
    sBToAccelHintSpriteId = MAX_SPRITES;
}

static void SpriteCB_BToAccelHint(struct Sprite *sprite)
{
    if (gMain.callback2 != CB2_Overworld)
    {
        DestroyBToAccelHintGfx(sprite);
        return;
    }

    if (sprite->sHide)
    {
        if (sprite->x != B_TO_ACCEL_HINT_X_0)
            sprite->x -= 2;

        if (sprite->x <= B_TO_ACCEL_HINT_X_0)
            DestroyBToAccelHintGfx(sprite);
    }
    else
    {
        if (sprite->x != B_TO_ACCEL_HINT_X_F)
            sprite->x += 2;
        else if (sprite->sTimer++ >= B_TO_ACCEL_HINT_HOLD_TIME)
            sprite->sHide = TRUE;
    }
}

void TryToShowBToAccelHint(void)
{
    if (FlagGet(FLAG_B_TO_ACCEL_HINT_SHOWN) == FALSE)
    {
        FlagSet(FLAG_B_TO_ACCEL_HINT_SHOWN);

        LoadSpritePalette(&sSpritePalette_BToAccelHint);
        if (GetSpriteTileStartByTag(B_TO_ACCEL_HINT_TILE_TAG) == 0xFFFF)
            LoadSpriteSheet(&sSpriteSheet_BToAccelHint);

        if (!IsBToAccelHintSprite(sBToAccelHintSpriteId))
        {
            sBToAccelHintSpriteId = CreateSprite(&sSpriteTemplate_BToAccelHint, B_TO_ACCEL_HINT_X_0, B_TO_ACCEL_HINT_Y, 5);
            if (sBToAccelHintSpriteId != MAX_SPRITES)
            {
                gSprites[sBToAccelHintSpriteId].sHide = FALSE;
                gSprites[sBToAccelHintSpriteId].sTimer = 0;
            }
        }
    }
}

void TryToHideBToAccelHint(void)
{
    if (IsBToAccelHintSprite(sBToAccelHintSpriteId))
        gSprites[sBToAccelHintSpriteId].sHide = TRUE;
}
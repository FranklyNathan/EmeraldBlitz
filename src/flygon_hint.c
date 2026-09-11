#include "global.h"
#include "gba/gba.h"
#include "main.h"
#include "overworld.h"
#include "sprite.h"
#include "event_data.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "flygon_hint.h"

#define L_FLY_HINT_TILE_TAG   0xC0A1
#define L_FLY_HINT_PAL_TAG    0xC0A2
#define L_FLY_HINT_X_0        (-32)
#define L_FLY_HINT_X_F        16
#define L_FLY_HINT_Y          92
#define L_FLY_HINT_HOLD_TIME  100

#define sHide  data[0]
#define sTimer data[1]

static const u8 sLFlyHintGfx[] = INCBIN_U8("graphics/misc/l_to_fly.4bpp");
static const u16 sLFlyHintPalette[] = INCBIN_U16("graphics/battle_interface/ability_pop_up.gbapal");

static const struct SpriteSheet sSpriteSheet_LFlyHint =
{
    sLFlyHintGfx, sizeof(sLFlyHintGfx), L_FLY_HINT_TILE_TAG
};

static const struct SpritePalette sSpritePalette_LFlyHint =
{
    sLFlyHintPalette, L_FLY_HINT_PAL_TAG
};

static const struct OamData sOamData_LFlyHint =
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

static void SpriteCB_LFlyHint(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_LFlyHint =
{
    .tileTag = L_FLY_HINT_TILE_TAG,
    .paletteTag = L_FLY_HINT_PAL_TAG,
    .oam = &sOamData_LFlyHint,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_LFlyHint,
};

static u8 sLFlyHintSpriteId;

static bool32 IsLFlyHintSprite(u8 spriteId)
{
    return spriteId < MAX_SPRITES
        && gSprites[spriteId].inUse
        && gSprites[spriteId].template == &sSpriteTemplate_LFlyHint;
}

static void DestroyLFlyHintGfx(struct Sprite *sprite)
{
    FreeSpriteTilesByTag(L_FLY_HINT_TILE_TAG);
    FreeSpritePaletteByTag(L_FLY_HINT_PAL_TAG);
    DestroySprite(sprite);
    sLFlyHintSpriteId = MAX_SPRITES;
}

static void SpriteCB_LFlyHint(struct Sprite *sprite)
{
    if (gMain.callback2 != CB2_Overworld)
    {
        DestroyLFlyHintGfx(sprite);
        return;
    }

    if (sprite->sHide)
    {
        if (sprite->x != L_FLY_HINT_X_0)
            sprite->x -= 2;

        if (sprite->x <= L_FLY_HINT_X_0)
            DestroyLFlyHintGfx(sprite);
    }
    else
    {
        if (sprite->x != L_FLY_HINT_X_F)
            sprite->x += 2;
        else if (sprite->sTimer++ >= L_FLY_HINT_HOLD_TIME)
            sprite->sHide = TRUE;
    }
}

void TryToShowLFlyHint(void)
{
    if (VarGet(VAR_BADGE_COUNT) >= 1
     && FlagGet(FLAG_B_TO_ACCEL_HINT_SHOWN) == TRUE
     && FlagGet(FLAG_L_FLY_HINT_SHOWN) == FALSE)
    {
        FlagSet(FLAG_L_FLY_HINT_SHOWN);

        LoadSpritePalette(&sSpritePalette_LFlyHint);
        if (GetSpriteTileStartByTag(L_FLY_HINT_TILE_TAG) == 0xFFFF)
            LoadSpriteSheet(&sSpriteSheet_LFlyHint);

        if (!IsLFlyHintSprite(sLFlyHintSpriteId))
        {
            sLFlyHintSpriteId = CreateSprite(&sSpriteTemplate_LFlyHint, L_FLY_HINT_X_0, L_FLY_HINT_Y, 5);
            if (sLFlyHintSpriteId != MAX_SPRITES)
            {
                gSprites[sLFlyHintSpriteId].sHide = FALSE;
                gSprites[sLFlyHintSpriteId].sTimer = 0;
            }
        }
    }
}

void TryToHideLFlyHint(void)
{
    if (IsLFlyHintSprite(sLFlyHintSpriteId))
        gSprites[sLFlyHintSpriteId].sHide = TRUE;
}
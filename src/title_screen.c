#include "global.h"
#include "battle.h"
#include "title_screen.h"
#include "sprite.h"
#include "gba/m4a_internal.h"
#include "clear_save_data_menu.h"
#include "decompress.h"
#include "event_data.h"
#include "intro.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "palette.h"
#include "reset_rtc_screen.h"
#include "berry_fix_program.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "scanline_effect.h"
#include "gpu_regs.h"
#include "trig.h"
#include "graphics.h"
#include "random.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum {
    TAG_VERSION = 1000,
    TAG_PRESS_START_COPYRIGHT,
    TAG_LOGO_SHINE,
    TAG_SILHOUETTE,
};

// Tile offsets are in OAM tile units (32 bytes); each 64x64 8bpp sprite consumes 128 units.
#define VERSION_BANNER_MIDDLE_TILEOFFSET 128
#define VERSION_BANNER_RIGHT_TILEOFFSET 256
#define VERSION_BANNER_LEFT_X 81
#define VERSION_BANNER_MIDDLE_X 145
#define VERSION_BANNER_RIGHT_X 209
#define VERSION_BANNER_Y 18
#define VERSION_BANNER_Y_GOAL 77
#define START_BANNER_X 133
#define SILHOUETTE_CHILD_X_OFFSET 48

#define CLEAR_SAVE_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_UP)
#define RESET_RTC_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_LEFT)
#define BERRY_UPDATE_BUTTON_COMBO (B_BUTTON | SELECT_BUTTON)
#define A_B_START_SELECT (A_BUTTON | B_BUTTON | START_BUTTON | SELECT_BUTTON)

static void MainCB2(void);
static void Task_TitleScreenPhase1(u8);
static void Task_TitleScreenPhase2(u8);
static void Task_TitleScreenPhase3(u8);
static void CB2_GoToMainMenu(void);
static void CB2_GoToClearSaveDataScreen(void);
static void CB2_GoToResetRtcScreen(void);
static void CB2_GoToBerryFixScreen(void);
static void CB2_GoToCopyrightScreen(void);
static void UpdateLegendaryMarkingColor(u8);

static void SpriteCB_VersionBannerLeft(struct Sprite *sprite);
static void SpriteCB_VersionBannerSegment(struct Sprite *sprite);
static void SpriteCB_PressStartCopyrightBanner(struct Sprite *sprite);
static void SpriteCB_PokemonLogoShine(struct Sprite *sprite);

// const rom data
static const u16 sUnusedUnknownPal[] = INCBIN_U16("graphics/title_screen/unused.gbapal");

static const u32 sTitleScreenRayquazaGfx[] = INCBIN_U32("graphics/title_screen/rayquaza.4bpp.smol");
static const u32 sTitleScreenRayquazaTilemap[] = INCBIN_U32("graphics/title_screen/rayquaza.bin.smolTM");
static const u32 sTitleScreenSilhouetteGfx[] = INCBIN_U32("graphics/title_screen/Silhouettes.4bpp.smol");
static const u32 sTitleScreenLogoShineGfx[] = INCBIN_U32("graphics/title_screen/logo_shine.4bpp.smol");
static const u32 sTitleScreenCloudsGfx[] = INCBIN_U32("graphics/title_screen/clouds.4bpp.smol");



// Used to blend "Emerald Version" as it passes over over the Pokémon banner.
// Also used by the intro to blend the Game Freak name/logo in and out as they appear and disappear
const u16 gTitleScreenAlphaBlend[64] =
{
    BLDALPHA_BLEND(16, 0),
    BLDALPHA_BLEND(16, 1),
    BLDALPHA_BLEND(16, 2),
    BLDALPHA_BLEND(16, 3),
    BLDALPHA_BLEND(16, 4),
    BLDALPHA_BLEND(16, 5),
    BLDALPHA_BLEND(16, 6),
    BLDALPHA_BLEND(16, 7),
    BLDALPHA_BLEND(16, 8),
    BLDALPHA_BLEND(16, 9),
    BLDALPHA_BLEND(16, 10),
    BLDALPHA_BLEND(16, 11),
    BLDALPHA_BLEND(16, 12),
    BLDALPHA_BLEND(16, 13),
    BLDALPHA_BLEND(16, 14),
    BLDALPHA_BLEND(16, 15),
    BLDALPHA_BLEND(15, 16),
    BLDALPHA_BLEND(14, 16),
    BLDALPHA_BLEND(13, 16),
    BLDALPHA_BLEND(12, 16),
    BLDALPHA_BLEND(11, 16),
    BLDALPHA_BLEND(10, 16),
    BLDALPHA_BLEND(9, 16),
    BLDALPHA_BLEND(8, 16),
    BLDALPHA_BLEND(7, 16),
    BLDALPHA_BLEND(6, 16),
    BLDALPHA_BLEND(5, 16),
    BLDALPHA_BLEND(4, 16),
    BLDALPHA_BLEND(3, 16),
    BLDALPHA_BLEND(2, 16),
    BLDALPHA_BLEND(1, 16),
    BLDALPHA_BLEND(0, 16),
    [32 ... 63] = BLDALPHA_BLEND(0, 16)
};

static const struct OamData sVersionBannerLeftOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sVersionBannerMiddleOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sVersionBannerRightOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_8BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sVersionBannerLeftAnimSequence[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END,
};

static const union AnimCmd sVersionBannerMiddleAnimSequence[] =
{
    ANIMCMD_FRAME(VERSION_BANNER_MIDDLE_TILEOFFSET, 30),
    ANIMCMD_END,
};

static const union AnimCmd sVersionBannerRightAnimSequence[] =
{
    ANIMCMD_FRAME(VERSION_BANNER_RIGHT_TILEOFFSET, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sVersionBannerLeftAnimTable[] =
{
    sVersionBannerLeftAnimSequence,
};

static const union AnimCmd *const sVersionBannerMiddleAnimTable[] =
{
    sVersionBannerMiddleAnimSequence,
};

static const union AnimCmd *const sVersionBannerRightAnimTable[] =
{
    sVersionBannerRightAnimSequence,
};

static const struct SpriteTemplate sVersionBannerLeftSpriteTemplate =
{
    .tileTag = TAG_VERSION,
    .paletteTag = TAG_VERSION,
    .oam = &sVersionBannerLeftOamData,
    .anims = sVersionBannerLeftAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_VersionBannerLeft,
};

static const struct SpriteTemplate sVersionBannerMiddleSpriteTemplate =
{
    .tileTag = TAG_VERSION,
    .paletteTag = TAG_VERSION,
    .oam = &sVersionBannerMiddleOamData,
    .anims = sVersionBannerMiddleAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_VersionBannerSegment,
};

static const struct SpriteTemplate sVersionBannerRightSpriteTemplate =
{
    .tileTag = TAG_VERSION,
    .paletteTag = TAG_VERSION,
    .oam = &sVersionBannerRightOamData,
    .anims = sVersionBannerRightAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_VersionBannerSegment,
};

static const struct CompressedSpriteSheet sSpriteSheet_EmeraldVersion[] =
{
    {
        .data = gTitleScreenEmeraldVersionGfx,
        .size = 0x3000, // 3 * (64x64 px @ 8bpp)
        .tag = TAG_VERSION
    },
    {},
};

static const struct OamData sOamData_CopyrightBanner =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sAnim_PressStart_0[] =
{
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_PressStart_1[] =
{
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_PressStart_2[] =
{
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_PressStart_3[] =
{
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_PressStart_4[] =
{
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_Copyright_0[] =
{
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_Copyright_1[] =
{
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_Copyright_2[] =
{
    ANIMCMD_FRAME(29, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_Copyright_3[] =
{
    ANIMCMD_FRAME(33, 4),
    ANIMCMD_END,
};
static const union AnimCmd sAnim_Copyright_4[] =
{
    ANIMCMD_FRAME(37, 4),
    ANIMCMD_END,
};

// The "Press Start" and copyright graphics are each 5 32x8 segments long
#define NUM_PRESS_START_FRAMES 5
#define NUM_COPYRIGHT_FRAMES 5

static const union AnimCmd *const sStartCopyrightBannerAnimTable[NUM_PRESS_START_FRAMES + NUM_COPYRIGHT_FRAMES] =
{
    sAnim_PressStart_0,
    sAnim_PressStart_1,
    sAnim_PressStart_2,
    sAnim_PressStart_3,
    sAnim_PressStart_4,
    [NUM_PRESS_START_FRAMES] =
    sAnim_Copyright_0,
    sAnim_Copyright_1,
    sAnim_Copyright_2,
    sAnim_Copyright_3,
    sAnim_Copyright_4,
};

static const struct SpriteTemplate sStartCopyrightBannerSpriteTemplate =
{
    .tileTag = TAG_PRESS_START_COPYRIGHT,
    .paletteTag = TAG_PRESS_START_COPYRIGHT,
    .oam = &sOamData_CopyrightBanner,
    .anims = sStartCopyrightBannerAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PressStartCopyrightBanner,
};

static const struct CompressedSpriteSheet sSpriteSheet_PressStart[] =
{
    {
        .data = gTitleScreenPressStartGfx,
        .size = 0x520,
        .tag = TAG_PRESS_START_COPYRIGHT
    },
    {},
};

static const struct SpritePalette sSpritePalette_PressStart[] =
{
    {
        .data = gTitleScreenPressStartPal,
        .tag = TAG_PRESS_START_COPYRIGHT
    },
    {},
};

static const struct OamData sPokemonLogoShineOamData =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sPokemonLogoShineAnimSequence[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sPokemonLogoShineAnimTable[] =
{
    sPokemonLogoShineAnimSequence,
};

static const struct SpriteTemplate sPokemonLogoShineSpriteTemplate =
{
    .tileTag = TAG_LOGO_SHINE,
    .paletteTag = TAG_PRESS_START_COPYRIGHT,
    .oam = &sPokemonLogoShineOamData,
    .anims = sPokemonLogoShineAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokemonLogoShine,
};

static const struct CompressedSpriteSheet sPokemonLogoShineSpriteSheet[] =
{
    {
        .data = sTitleScreenLogoShineGfx,
        .size = 0x800,
        .tag = TAG_LOGO_SHINE
    },
    {},
};

// Task data for the main title screen tasks (Task_TitleScreenPhase#)
#define tCounter    data[0]
#define tSkipToNext data[1]
#define tPointless  data[2] // Incremented but never used to do anything.
#define tBg2Y       data[3]
#define tBg1Y       data[4]

// Sprite data for sVersionBannerLeftSpriteTemplate / sVersionBannerMiddleSpriteTemplate / sVersionBannerRightSpriteTemplate
#define sAlphaBlendIdx data[0]
#define sParentTaskId  data[1]

static void SpriteCB_VersionBannerLeft(struct Sprite *sprite)
{
    if (gTasks[sprite->sParentTaskId].tSkipToNext)
    {
        sprite->oam.objMode = ST_OAM_OBJ_NORMAL;
        sprite->y = VERSION_BANNER_Y_GOAL;
    }
    else
    {
        if (sprite->y != VERSION_BANNER_Y_GOAL)
            sprite->y++;
        if (sprite->sAlphaBlendIdx != 0)
            sprite->sAlphaBlendIdx--;
        SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[sprite->sAlphaBlendIdx]);
    }
}

static void SpriteCB_VersionBannerSegment(struct Sprite *sprite)
{
    if (gTasks[sprite->sParentTaskId].tSkipToNext)
    {
        sprite->oam.objMode = ST_OAM_OBJ_NORMAL;
        sprite->y = VERSION_BANNER_Y_GOAL;
    }
    else
    {
        if (sprite->y != VERSION_BANNER_Y_GOAL)
            sprite->y++;
    }
}

// Sprite data for SpriteCB_PressStartCopyrightBanner
#define sAnimate data[0]
#define sTimer   data[1]

static void SpriteCB_PressStartCopyrightBanner(struct Sprite *sprite)
{
    if (sprite->sAnimate == TRUE)
    {
        // Alternate between hidden and shown every 16th frame
        if (++sprite->sTimer & 16)
            sprite->invisible = FALSE;
        else
            sprite->invisible = TRUE;
    }
    else
    {
        sprite->invisible = FALSE;
    }
}

static void CreatePressStartBanner(s16 x, s16 y)
{
    u8 i;
    u8 spriteId;

    x -= 64;
    for (i = 0; i < NUM_PRESS_START_FRAMES; i++, x += 32)
    {
        spriteId = CreateSprite(&sStartCopyrightBannerSpriteTemplate, x, y, 0);
        StartSpriteAnim(&gSprites[spriteId], i);
        gSprites[spriteId].sAnimate = TRUE;
    }
}

static void CreateCopyrightBanner(s16 x, s16 y)
{
    u8 i;
    u8 spriteId;

    x -= 64;
    for (i = 0; i < NUM_COPYRIGHT_FRAMES; i++, x += 32)
    {
        spriteId = CreateSprite(&sStartCopyrightBannerSpriteTemplate, x, y, 0);
        StartSpriteAnim(&gSprites[spriteId], i + NUM_PRESS_START_FRAMES);
    }
}

// Silhouette sprite data
static const struct OamData sSilhouetteLeftOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sSilhouetteRightOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSilhouetteLeftAnimCmd[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END,
};

static const union AnimCmd sSilhouetteRightAnimCmd[] =
{
    ANIMCMD_FRAME(64, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sSilhouetteLeftAnimTable[] =
{
    sSilhouetteLeftAnimCmd,
};

static const union AnimCmd *const sSilhouetteRightAnimTable[] =
{
    sSilhouetteRightAnimCmd,
};

static const union AnimCmd sSilhouetteMedLeftAnimCmd[] =
{
    ANIMCMD_FRAME(96, 30),
    ANIMCMD_END,
};

static const union AnimCmd sSilhouetteMedRightAnimCmd[] =
{
    ANIMCMD_FRAME(160, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sSilhouetteMedLeftAnimTable[] =
{
    sSilhouetteMedLeftAnimCmd,
};

static const union AnimCmd *const sSilhouetteMedRightAnimTable[] =
{
    sSilhouetteMedRightAnimCmd,
};

static const union AnimCmd sSilhouetteSalamenceAnimCmd[] =
{
    ANIMCMD_FRAME(224, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sSilhouetteSalamenceAnimTable[] =
{
    sSilhouetteSalamenceAnimCmd,
};

static const union AnimCmd sSilhouetteTinyAnimCmd[] =
{
    ANIMCMD_FRAME(288, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sSilhouetteTinyAnimTable[] =
{
    sSilhouetteTinyAnimCmd,
};

#define sChildSpriteId data[0]
#define sPauseTimer   data[2]
#define sIsActive     data[3]
#define sSpeedFlag    data[4]
#define sBaseY        data[6]
#define sFirstFlight  data[7]

// Random pause between 120-300 frames
#define SILHOUETTE_MIN_PAUSE 120
#define SILHOUETTE_PAUSE_RANGE 300
#define SILHOUETTE_START_VARIANCE 22

static u16 GetSilhouettePause(void)
{
    return SILHOUETTE_MIN_PAUSE + (Random() % SILHOUETTE_PAUSE_RANGE);
}

// 80% chance of half speed, 20% full speed. Set once per flight.
// First flight is always half speed if sFirstFlight is set.
static void MaybeSetHalfSpeed(struct Sprite *sprite)
{
    if (sprite->sFirstFlight)
    {
        sprite->sSpeedFlag = 1;
        sprite->sFirstFlight = FALSE;
    }
    else if ((Random() % 5) != 0) // 4/5 = 80%
        sprite->sSpeedFlag = 1;
    else
        sprite->sSpeedFlag = 0;
}

// Returns TRUE if sprite should skip this frame (half speed mode)
static u8 IsHalfSpeedSkipped(struct Sprite *sprite)
{
    if (sprite->sSpeedFlag)
        return (++sprite->data[5] & 1);
    return FALSE;
}

static s16 SilhouetteRandOffset(void)
{
    return (Random() % (SILHOUETTE_START_VARIANCE * 2 + 1)) - SILHOUETTE_START_VARIANCE;
}

// Large silhouette: flies bottom-left to top-right
static void SpriteCB_SilhouetteFly(struct Sprite *sprite)
{
    struct Sprite *child = &gSprites[sprite->sChildSpriteId];

    if (sprite->sPauseTimer != 0)
    {
        sprite->sPauseTimer--;
        return;
    }

    if (sprite->invisible)
    {
        sprite->invisible = FALSE;
        child->invisible = FALSE;
        MaybeSetHalfSpeed(sprite);
    }

    if (IsHalfSpeedSkipped(sprite))
        return;

    sprite->x += 3;
    sprite->y -= 1;

    child->x = sprite->x + SILHOUETTE_CHILD_X_OFFSET;
    child->y = sprite->y;

    if (sprite->x > DISPLAY_WIDTH + 96 || sprite->y < -64)
    {
        s16 ox = SilhouetteRandOffset();
        s16 oy = SilhouetteRandOffset();
        sprite->sPauseTimer = GetSilhouettePause();
        sprite->x = -26 + ox;
        sprite->y = DISPLAY_HEIGHT + 32 + oy;
        child->x = sprite->x + SILHOUETTE_CHILD_X_OFFSET;
        child->y = sprite->y;
        sprite->invisible = TRUE;
        child->invisible = TRUE;
    }
}

static void SpriteCB_SilhouetteSmallFly(struct Sprite *sprite);

static const struct SpriteTemplate sSilhouetteLeftSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteLeftOamData,
    .anims = sSilhouetteLeftAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SilhouetteFly,
};

static const struct SpriteTemplate sSilhouetteRightSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteRightOamData,
    .anims = sSilhouetteRightAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// Medium silhouette: flies bottom-right to top-left
static void SpriteCB_SilhouetteMedFly(struct Sprite *sprite)
{
    struct Sprite *child = &gSprites[sprite->sChildSpriteId];

    if (sprite->sPauseTimer != 0)
    {
        sprite->sPauseTimer--;
        return;
    }

    if (sprite->invisible)
    {
        sprite->invisible = FALSE;
        child->invisible = FALSE;
        MaybeSetHalfSpeed(sprite);
    }

    if (IsHalfSpeedSkipped(sprite))
        return;

    sprite->x -= 3;
    sprite->y -= 1;

    child->x = sprite->x + 48;
    child->y = sprite->y;

    if (sprite->x < -96 || sprite->y < -64)
    {
        s16 ox = SilhouetteRandOffset();
        s16 oy = SilhouetteRandOffset();
        sprite->sPauseTimer = GetSilhouettePause();
        sprite->x = DISPLAY_WIDTH + 46 + ox;
        sprite->y = DISPLAY_HEIGHT + 32 + oy;
        child->x = sprite->x + 48;
        child->y = sprite->y;
        sprite->invisible = TRUE;
        child->invisible = TRUE;
    }
}

static const struct SpriteTemplate sSilhouetteMedLeftSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteLeftOamData,
    .anims = sSilhouetteMedLeftAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SilhouetteMedFly,
};

static const struct SpriteTemplate sSilhouetteMedRightSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteRightOamData,
    .anims = sSilhouetteMedRightAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// Small silhouette: flies left to right, starts high
static const struct OamData sSilhouetteSmallOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSilhouetteSmallAnimCmd[] =
{
    ANIMCMD_FRAME(192, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sSilhouetteSmallAnimTable[] =
{
    sSilhouetteSmallAnimCmd,
};

static const struct SpriteTemplate sSilhouetteSmallSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteSmallOamData,
    .anims = sSilhouetteSmallAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SilhouetteSmallFly,
};

// data[7]: companion delay countdown only (0 = no delay active)
#define sCompanionDelay  data[7]

static void SpriteCB_SilhouetteSmallFly(struct Sprite *sprite)
{
    if (sprite->sPauseTimer != 0)
    {
        sprite->sPauseTimer--;
        return;
    }

    if (sprite->invisible)
    {
        sprite->invisible = FALSE;
        MaybeSetHalfSpeed(sprite);

        // 10% chance to spawn a companion (only if still in lower half of screen)
        if (!(sprite->sCompanionDelay & 0x80) && sprite->y > DISPLAY_HEIGHT / 2 && (Random() % 10) == 0)
            sprite->sCompanionDelay = 127; // start 127-frame countdown (~2s)
    }

    // Countdown and spawn companion exactly once
    if (sprite->sCompanionDelay > 0 && sprite->sCompanionDelay < 0x80)
    {
        sprite->sCompanionDelay--;
        if (sprite->sCompanionDelay == 0)
        {
            u8 compId = CreateSprite(&sSilhouetteSmallSpriteTemplate, sprite->x, sprite->y + 60, 0);
            gSprites[compId].oam.paletteNum = sprite->oam.paletteNum;
            gSprites[compId].sBaseY = sprite->y + 60;
            gSprites[compId].sSpeedFlag = !sprite->sSpeedFlag; // opposite speed
            gSprites[compId].sFirstFlight = FALSE;
            gSprites[compId].sCompanionDelay = 0x80; // permanently blocked
            gSprites[compId].sPauseTimer = 0;
            gSprites[compId].invisible = TRUE;
            sprite->sCompanionDelay = 0x80; // parent also permanently blocked
        }
    }

    if (IsHalfSpeedSkipped(sprite))
        return;

    sprite->x += 4;
    sprite->y -= 1;

    if (sprite->x > DISPLAY_WIDTH + 64)
    {
        sprite->sPauseTimer = GetSilhouettePause();
        sprite->x = -64;
        sprite->y = sprite->sBaseY + SilhouetteRandOffset();
        sprite->invisible = TRUE;
    }
}

// Salamence silhouette: rare, flies left to right

static const struct OamData sSilhouetteSalamenceOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static void SpriteCB_SilhouetteSalamenceFly(struct Sprite *sprite)
{
    if (sprite->sIsActive)
    {
        if (IsHalfSpeedSkipped(sprite))
            return;

        sprite->x -= 4;
        sprite->y -= 1;

        if (sprite->x < -64)
        {
            sprite->sIsActive = FALSE;
            sprite->sPauseTimer = GetSilhouettePause();
            sprite->x = DISPLAY_WIDTH + 64;
            sprite->y = 72 + SilhouetteRandOffset();
        }
    }
    else
    {
        if (sprite->sPauseTimer != 0)
        {
            sprite->sPauseTimer--;
        }
        else
        {
            // Odds to appear
            if ((Random() % 12) == 0)
            {
                sprite->sIsActive = TRUE;
                sprite->x = DISPLAY_WIDTH + 64;
                sprite->y = 72 + SilhouetteRandOffset();
                MaybeSetHalfSpeed(sprite);
            }
            else
            {
                sprite->sPauseTimer = GetSilhouettePause();
            }
        }
    }
}

static const struct SpriteTemplate sSilhouetteSalamenceSpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteSalamenceOamData,
    .anims = sSilhouetteSalamenceAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SilhouetteSalamenceFly,
};

// Tiny silhouette: flies right to left, always starts on a slight delay
static const struct OamData sSilhouetteTinyOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 3,
    .paletteNum = 0,
    .affineParam = 0,
};

static void SpriteCB_SilhouetteTinyFly(struct Sprite *sprite)
{
    if (sprite->sPauseTimer != 0)
    {
        sprite->sPauseTimer--;
        return;
    }

    if (sprite->invisible)
    {
        sprite->invisible = FALSE;
        MaybeSetHalfSpeed(sprite);
    }

    if (IsHalfSpeedSkipped(sprite))
        return;

    sprite->x -= 4;
    sprite->y -= 1;

    if (sprite->x < -32)
    {
        sprite->sPauseTimer = GetSilhouettePause();
        sprite->x = DISPLAY_WIDTH + 32;
        sprite->y = 50 + SilhouetteRandOffset();
        sprite->invisible = TRUE;
    }
}

static const struct SpriteTemplate sSilhouetteTinySpriteTemplate =
{
    .tileTag = TAG_SILHOUETTE,
    .paletteTag = TAG_SILHOUETTE,
    .oam = &sSilhouetteTinyOamData,
    .anims = sSilhouetteTinyAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SilhouetteTinyFly,
};

static const struct CompressedSpriteSheet sSpriteSheet_Silhouette[] =
{
    { .data = sTitleScreenSilhouetteGfx, .size = 0x2600, .tag = TAG_SILHOUETTE },
    {},
};

static const struct SpritePalette sSpritePalette_Silhouette[] =
{
    { .data = gTitleScreenSilhouettePal, .tag = TAG_SILHOUETTE },
    {},
};

// Tinted palettes simulating atmospheric transparency.
// Color 1 blended 50% toward sky blue, then tinted progressively bluer for smaller sprites.
// Large=no tint, Medium=slight, Salamence=moderate, Small=strong, Tiny=strongest
#define SILHOUETTE_PAL_BASE 3

static const u16 sSilhouetteTintedPalettes[][16] =
{
    // Level 0: Small #2 (bottom start) — darker blue-grey
    {0x0000, RGB(9, 10, 16), [2 ... 15] = 0x0000},
    // Level 1: Small #1, Salamence, Tiny — lighter blue-grey
    {0x0000, RGB(10, 11, 18), [2 ... 15] = 0x0000},
    // Level 2: Medium — lightest blue-grey
    {0x0000, RGB(11, 12, 19), [2 ... 15] = 0x0000},
};

static void CreateSilhouetteSprites(void)
{
    u8 leftId, rightId, smallId;
    s16 ox, oy;
    u8 i;

    LoadCompressedSpriteSheet(&sSpriteSheet_Silhouette[0]);
    LoadSpritePalette(&sSpritePalette_Silhouette[0]);

    // Load tinted palettes into fixed OBJ palette slots
    for (i = 0; i < ARRAY_COUNT(sSilhouetteTintedPalettes); i++)
    {
        LoadPalette(sSilhouetteTintedPalettes[i], OBJ_PLTT_ID(SILHOUETTE_PAL_BASE + i), PLTT_SIZE_4BPP);
    }

    // Small silhouette #1: flies left to right from high up
    smallId = CreateSprite(&sSilhouetteSmallSpriteTemplate, -64, 40 + SilhouetteRandOffset(), 0);
    gSprites[smallId].oam.paletteNum = SILHOUETTE_PAL_BASE + 1;
    gSprites[smallId].sBaseY = 40;
    gSprites[smallId].sFirstFlight = 1;
    gSprites[smallId].sPauseTimer = 110;
    gSprites[smallId].invisible = TRUE;

    // Small silhouette #2: flies left to right from bottom (former large position)
    oy = SilhouetteRandOffset();
    smallId = CreateSprite(&sSilhouetteSmallSpriteTemplate, -64, DISPLAY_HEIGHT + 32 + oy, 0);
    gSprites[smallId].oam.paletteNum = SILHOUETTE_PAL_BASE + 0;
    gSprites[smallId].sBaseY = DISPLAY_HEIGHT + 32;
    gSprites[smallId].sFirstFlight = 1;
    gSprites[smallId].sPauseTimer = 20;
    gSprites[smallId].invisible = TRUE;

    // Medium silhouette: flies bottom-right to top-left (launches immediately)
    ox = SilhouetteRandOffset();
    oy = SilhouetteRandOffset();
    leftId = CreateSprite(&sSilhouetteMedLeftSpriteTemplate, DISPLAY_WIDTH + 46 + ox, DISPLAY_HEIGHT + 32 + oy, 0);
    gSprites[leftId].oam.paletteNum = SILHOUETTE_PAL_BASE + 2;
    gSprites[leftId].sPauseTimer = 0;

    rightId = CreateSprite(&sSilhouetteMedRightSpriteTemplate, DISPLAY_WIDTH + 46 + ox + 48, DISPLAY_HEIGHT + 32 + oy, 0);
    gSprites[rightId].oam.paletteNum = SILHOUETTE_PAL_BASE + 2;

    gSprites[leftId].sChildSpriteId = rightId;

    // Salamence silhouette: rare
    smallId = CreateSprite(&sSilhouetteSalamenceSpriteTemplate, -64, 30, 0);
    gSprites[smallId].oam.paletteNum = SILHOUETTE_PAL_BASE + 1;
    gSprites[smallId].sPauseTimer = 20;

    // Tiny silhouette
    smallId = CreateSprite(&sSilhouetteTinySpriteTemplate, DISPLAY_WIDTH + 32, 50, 0);
    gSprites[smallId].oam.paletteNum = SILHOUETTE_PAL_BASE + 1;
    gSprites[smallId].sFirstFlight = 1;
    gSprites[smallId].sPauseTimer = 50;
    gSprites[smallId].invisible = TRUE;
}

#undef sChildSpriteId
#undef sPauseTimer
#undef sIsActive
#undef sSpeedFlag
#undef sBaseY
#undef sFirstFlight
#undef sCompanionDelay
#undef sAnimate
#undef sTimer

// Defines for SpriteCB_PokemonLogoShine
enum {
    SHINE_MODE_SINGLE_NO_BG_COLOR,
    SHINE_MODE_DOUBLE,
    SHINE_MODE_SINGLE,
};

#define SHINE_SPEED  4

#define sMode     data[0]
#define sBgColor  data[1]

static void SpriteCB_PokemonLogoShine(struct Sprite *sprite)
{
    if (sprite->x < DISPLAY_WIDTH + 32)
    {
        // In any mode except SHINE_MODE_SINGLE_NO_BG_COLOR the background
        // color will change, in addition to the shine sprite moving.
        if (sprite->sMode != SHINE_MODE_SINGLE_NO_BG_COLOR)
        {
            u16 backgroundColor;

            if (sprite->x < DISPLAY_WIDTH / 2)
            {
                // Brighten background color
                if (sprite->sBgColor < 31)
                    sprite->sBgColor++;
                if (sprite->sBgColor < 31)
                    sprite->sBgColor++;
            }
            else
            {
                // Darken background color
                if (sprite->sBgColor != 0)
                    sprite->sBgColor--;
                if (sprite->sBgColor != 0)
                    sprite->sBgColor--;
            }

            backgroundColor = _RGB(sprite->sBgColor, sprite->sBgColor, sprite->sBgColor);

            gPlttBufferFaded[0] = backgroundColor;
        }

        sprite->x += SHINE_SPEED;
    }
    else
    {
        // Sprite has moved fully offscreen
        gPlttBufferFaded[0] = RGB_BLACK;
        DestroySprite(sprite);
    }
}

static void SpriteCB_PokemonLogoShine_Fast(struct Sprite *sprite)
{
    if (sprite->x < DISPLAY_WIDTH + 32)
        sprite->x += SHINE_SPEED * 2;
    else
        DestroySprite(sprite);
}

static void StartPokemonLogoShine(u8 mode)
{
    u8 spriteId;

    switch (mode)
    {
    case SHINE_MODE_SINGLE_NO_BG_COLOR:
    case SHINE_MODE_SINGLE:
        // Create one regular shine sprite.
        // If mode is SHINE_MODE_SINGLE it will also change the background color.
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        gSprites[spriteId].sMode = mode;
        break;
    case SHINE_MODE_DOUBLE:
        // Create an invisible sprite with mode set to update the background color
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        gSprites[spriteId].sMode = mode;
        gSprites[spriteId].invisible = TRUE;

        // Create two faster shine sprites
        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, 0, 68, 0);
        gSprites[spriteId].callback = SpriteCB_PokemonLogoShine_Fast;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

        spriteId = CreateSprite(&sPokemonLogoShineSpriteTemplate, -80, 68, 0);
        gSprites[spriteId].callback = SpriteCB_PokemonLogoShine_Fast;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        break;
    }
}

#undef sMode
#undef sBgColor

static void VBlankCB(void)
{
    ScanlineEffect_InitHBlankDmaTransfer();
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    SetGpuReg(REG_OFFSET_BG1VOFS, gBattle_BG1_Y);
}

void CB2_InitTitleScreen(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        *((u16 *)PLTT) = RGB_WHITE;
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetPaletteFade();
        gMain.state = 1;
        break;
    case 1:
        // bg2
        DecompressDataWithHeaderVram(gTitleScreenPokemonLogoGfx, (void *)(BG_CHAR_ADDR(0)));
        DecompressDataWithHeaderVram(gTitleScreenPokemonLogoTilemap, (void *)(BG_SCREEN_ADDR(9)));
        LoadPalette(gTitleScreenBgPalettes, BG_PLTT_ID(0), 15 * PLTT_SIZE_4BPP);
        // bg0
        DecompressDataWithHeaderVram(sTitleScreenRayquazaGfx, (void *)(BG_CHAR_ADDR(2)));
        DecompressDataWithHeaderVram(sTitleScreenRayquazaTilemap, (void *)(BG_SCREEN_ADDR(26)));
        // bg1
        DecompressDataWithHeaderVram(sTitleScreenCloudsGfx, (void *)(BG_CHAR_ADDR(3)));
        DecompressDataWithHeaderVram(gTitleScreenCloudsTilemap, (void *)(BG_SCREEN_ADDR(27)));
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 9;
        LoadCompressedSpriteSheet(&sSpriteSheet_EmeraldVersion[0]);
        LoadCompressedSpriteSheet(&sSpriteSheet_PressStart[0]);
        LoadCompressedSpriteSheet(&sPokemonLogoShineSpriteSheet[0]);
        LoadPalette(gTitleScreenEmeraldVersionPal, OBJ_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadSpritePalette(&sSpritePalette_PressStart[0]);
        gMain.state = 2;
        break;
    case 2:
    {
        u8 taskId = CreateTask(Task_TitleScreenPhase1, 0);

        gTasks[taskId].tCounter = 256;
        gTasks[taskId].tSkipToNext = FALSE;
        gTasks[taskId].tPointless = -16;
        gTasks[taskId].tBg2Y = -31;
        gMain.state = 3;
        break;
    }
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 1, 16, 0, RGB_WHITEALPHA);
        SetVBlankCallback(VBlankCB);
        gMain.state = 4;
        break;
    case 4:
        PanFadeAndZoomScreen(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 0x100, 0);
        SetGpuReg(REG_OFFSET_BG2X_L, -37 * 256);
        SetGpuReg(REG_OFFSET_BG2X_H, -1);
        SetGpuReg(REG_OFFSET_BG2Y_L, -31 * 256);
        SetGpuReg(REG_OFFSET_BG2Y_H, -1);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_ALL);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_LIGHTEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 12);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(26) | BGCNT_16COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(3) | BGCNT_SCREENBASE(27) | BGCNT_16COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(9) | BGCNT_256COLOR | BGCNT_AFF256x256);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG2_ON
                                    | DISPCNT_OBJ_ON
                                    | DISPCNT_WIN0_ON
                                    | DISPCNT_OBJWIN_ON);
        m4aSongNumStart(MUS_TITLE);
        gMain.state = 5;
        break;
    case 5:
        if (!UpdatePaletteFade())
        {
            StartPokemonLogoShine(SHINE_MODE_SINGLE_NO_BG_COLOR);
            ScanlineEffect_InitWave(0, DISPLAY_HEIGHT, 4, 4, 0, SCANLINE_EFFECT_REG_BG1HOFS, TRUE);
            SetMainCallback2(MainCB2);
        }
        break;
    }
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

// Shine the Pokémon logo two more times, and fade in the version banner
static void Task_TitleScreenPhase1(u8 taskId)
{
    // Skip to next phase when A, B, Start, or Select is pressed
    if (JOY_NEW(A_B_START_SELECT) || gTasks[taskId].tSkipToNext)
    {
        gTasks[taskId].tSkipToNext = TRUE;
        gTasks[taskId].tCounter = 0;
    }

    if (gTasks[taskId].tCounter != 0)
    {
        u16 frameNum = gTasks[taskId].tCounter;
        if (frameNum == 176)
            StartPokemonLogoShine(SHINE_MODE_DOUBLE);
        else if (frameNum == 64)
            StartPokemonLogoShine(SHINE_MODE_SINGLE);

        gTasks[taskId].tCounter--;
    }
    else
    {
        u8 spriteId;

        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG2_ON | DISPCNT_OBJ_ON);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
        SetGpuReg(REG_OFFSET_BLDY, 0);

        // Create left third of version banner
        spriteId = CreateSprite(&sVersionBannerLeftSpriteTemplate, VERSION_BANNER_LEFT_X, VERSION_BANNER_Y, 0);
        gSprites[spriteId].sAlphaBlendIdx = ARRAY_COUNT(gTitleScreenAlphaBlend);
        gSprites[spriteId].sParentTaskId = taskId;

        // Create middle third of version banner
        spriteId = CreateSprite(&sVersionBannerMiddleSpriteTemplate, VERSION_BANNER_MIDDLE_X, VERSION_BANNER_Y, 0);
        gSprites[spriteId].sParentTaskId = taskId;

        // Create right third of version banner
        spriteId = CreateSprite(&sVersionBannerRightSpriteTemplate, VERSION_BANNER_RIGHT_X, VERSION_BANNER_Y, 0);
        gSprites[spriteId].sParentTaskId = taskId;

        gTasks[taskId].tCounter = 144;
        gTasks[taskId].func = Task_TitleScreenPhase2;
    }
}

#undef sParentTaskId
#undef sAlphaBlendIdx

// Create "Press Start" and copyright banners, and slide Pokémon logo up
static void Task_TitleScreenPhase2(u8 taskId)
{
    u32 yPos;

    // Skip to next phase when A, B, Start, or Select is pressed
    if (JOY_NEW(A_B_START_SELECT) || gTasks[taskId].tSkipToNext)
    {
        gTasks[taskId].tSkipToNext = TRUE;
        gTasks[taskId].tCounter = 0;
    }

    if (gTasks[taskId].tCounter != 0)
    {
        gTasks[taskId].tCounter--;
    }
    else
    {
        gTasks[taskId].tSkipToNext = TRUE;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BD);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(6, 15));
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1
                                    | DISPCNT_OBJ_1D_MAP
                                    | DISPCNT_BG0_ON
                                    | DISPCNT_BG1_ON
                                    | DISPCNT_BG2_ON
                                    | DISPCNT_OBJ_ON);
        CreatePressStartBanner(START_BANNER_X, 127);
        CreateCopyrightBanner(125, 154);
        CreateSilhouetteSprites();
        gTasks[taskId].tBg1Y = 0;
        gTasks[taskId].func = Task_TitleScreenPhase3;
    }

    if (!(gTasks[taskId].tCounter & 3) && gTasks[taskId].tPointless != 0)
        gTasks[taskId].tPointless++;
    if (!(gTasks[taskId].tCounter & 1) && gTasks[taskId].tBg2Y != -1)
        gTasks[taskId].tBg2Y++;

    // Slide Pokémon logo up
    yPos = gTasks[taskId].tBg2Y * 256;
    SetGpuReg(REG_OFFSET_BG2Y_L, yPos);
    SetGpuReg(REG_OFFSET_BG2Y_H, yPos / 0x10000);

    gTasks[taskId].data[5] = 15; // Unused
    gTasks[taskId].data[6] = 6;  // Unused
}

// Show Rayquaza silhouette and process main title screen input
static void Task_TitleScreenPhase3(u8 taskId)
{
    if (JOY_NEW(A_BUTTON) || JOY_NEW(START_BUTTON))
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
        SetMainCallback2(CB2_GoToMainMenu);
    }
    else if (JOY_HELD(CLEAR_SAVE_BUTTON_COMBO) == CLEAR_SAVE_BUTTON_COMBO)
    {
        SetMainCallback2(CB2_GoToClearSaveDataScreen);
    }
    else if (JOY_HELD(RESET_RTC_BUTTON_COMBO) == RESET_RTC_BUTTON_COMBO
      && CanResetRTC() == TRUE)
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        SetMainCallback2(CB2_GoToResetRtcScreen);
    }
    else if (JOY_HELD(BERRY_UPDATE_BUTTON_COMBO) == BERRY_UPDATE_BUTTON_COMBO)
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        SetMainCallback2(CB2_GoToBerryFixScreen);
    }
    else
    {
        SetGpuReg(REG_OFFSET_BG2X_L, -37 * 256);
        SetGpuReg(REG_OFFSET_BG2X_H, -1);
        SetGpuReg(REG_OFFSET_BG2Y_L, -1 * 256);
        SetGpuReg(REG_OFFSET_BG2Y_H, -1);
        if (++gTasks[taskId].tCounter & 1)
        {
            gTasks[taskId].tBg1Y++;
            gBattle_BG1_Y = gTasks[taskId].tBg1Y / 2;
            gBattle_BG1_X = 0;
        }
        //UpdateLegendaryMarkingColor(gTasks[taskId].tCounter);
        if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
            SetMainCallback2(CB2_GoToCopyrightScreen);
        }
    }
}

static void CB2_GoToMainMenu(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitMainMenu);
}

static void CB2_GoToCopyrightScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitCopyrightScreenAfterTitleScreen);
}

static void CB2_GoToClearSaveDataScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitClearSaveDataScreen);
}

static void CB2_GoToResetRtcScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitResetRtcScreen);
}

static void CB2_GoToBerryFixScreen(void)
{
    if (!UpdatePaletteFade())
    {
        m4aMPlayAllStop();
        SetMainCallback2(CB2_InitBerryFixProgram);
    }
}

static void UpdateLegendaryMarkingColor(u8 frameNum)
{
    if ((frameNum % 4) == 0) // Change color every 4th frame
    {
        s32 intensity = Cos(frameNum, 128) + 128;
        s32 r = 31 - ((intensity * 32 - intensity) / 256);
        s32 g = 31 - (intensity * 22 / 256);
        s32 b = 12;

        u16 color = RGB(r, g, b);
        LoadPalette(&color, BG_PLTT_ID(14) + 15, sizeof(color));
   }
}

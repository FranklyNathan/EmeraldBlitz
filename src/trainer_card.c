#include "global.h"
#include "scanline_effect.h"
#include "palette.h"
#include "task.h"
#include "main.h"
#include "window.h"
#include "malloc.h"
#include "link.h"
#include "bg.h"
#include "sound.h"
#include "frontier_pass.h"
#include "overworld.h"
#include "menu.h"
#include "text.h"
#include "event_data.h"
#include "easy_chat.h"
#include "money.h"
#include "strings.h"
#include "string_util.h"
#include "trainer_card.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "pokedex.h"
#include "pokemon_icon.h"
#include "data.h"
#include "graphics.h"
#include "battle_setup.h"
#include "trainer_pokemon_sprites.h"
#include "constants/event_objects.h"
#include "contest_util.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "constants/songs.h"
#include "constants/game_stat.h"
#include "constants/battle_frontier.h"
#include "constants/rgb.h"
#include "constants/trainers.h"
#include "constants/union_room.h"

const u16 *GetPlayerObjectEventPaletteData(u8 gender);

extern const u8 gText_BeatChampion[];

enum {
    WIN_MSG,
    WIN_CARD_TEXT,
    WIN_TRAINER_PIC,
};

struct TrainerCardData
{
    u8 mainState;
    u8 printState;
    u8 gfxLoadState;
    u8 bgPalLoadState;
    u8 flipDrawState;
    bool8 isLink;
    u8 timeColonBlinkTimer;
    bool8 timeColonInvisible;
    bool8 onBack;
    bool8 allowDMACopy;
    bool8 hasPokedex;
    bool8 hasHofResult;
    bool8 hasLinkResults;
    bool8 hasBattleTowerWins;
    bool8 unused_E;
    bool8 unused_F;
    bool8 hasTrades;
    u8 badgeCount[NUM_BADGES];
    u8 currentPalIndex;
    u8 easyChatProfile[TRAINER_CARD_PROFILE_LENGTH][13];
    u8 textPlayersCard[70];
    u8 textHofTime[70];
    u8 textLinkBattleType[140];
    u8 textLinkBattleWins[70];
    u8 textLinkBattleLosses[140];
    u8 textNumTrades[140];
    u8 textBerryCrushPts[140];
    u8 textUnionRoomStats[70];
    u8 textNumLinkPokeblocks[70];
    u8 textNumLinkContests[70];
    u8 textBattleFacilityStat[70];
    u8 winNames[12][32];
    u8 winTimes[12][32];
    u8 championSpriteIds[2];
    s16 championSpritesX;
    u8 winSpriteIds[12][2];
    u16 monIconPal[16 * PARTY_SIZE];
    s8 flipBlendY;
    bool8 timeColonNeedDraw;
    u8 cardType;
    bool8 isHoenn;
    u16 blendColor;
    MainCallback callback2;
    struct TrainerCard trainerCard;
    u16 frontTilemap[600];
    u16 backTilemap[600];
    u16 bgTilemap[600];
    u8 badgeTiles[0x80 * NUM_BADGES];
    u8 stickerTiles[0x200];
    u8 cardTiles[0x2300];
    u16 cardTilemapBuffer[0x1000];
    u16 bgTilemapBuffer[0x1000];
    u16 cardTop;
    u8 language;
};

// EWRAM
EWRAM_DATA struct TrainerCard gTrainerCards[4] = {0};
EWRAM_DATA static struct TrainerCardData *sData = NULL;

//this file's functions
static void VblankCb_TrainerCard(void);
static void HblankCb_TrainerCard(void);
static void BlinkTimeColon(void);
static void CB2_TrainerCard(void);
static void CloseTrainerCard(u8 task);
static bool8 PrintAllOnCardFront(void);
static void DrawTrainerCardWindow(u8);
static void CreateTrainerCardTrainerPic(void);
static void DrawCardScreenBackground(u16 *);
static void DrawCardFrontOrBack(u16 *);
static void DrawStarsAndBadgesOnCard(void);
static void PrintTimeOnCard(void);
static void FlipTrainerCard(void);
static bool8 IsCardFlipTaskActive(void);
static bool8 LoadCardGfx(void);
static void CB2_InitTrainerCard(void);
static u32 GetCappedGameStat(u8 statId, u32 maxValue);
static bool8 HasAllFrontierSymbols(void);
static u8 GetRubyTrainerStars(struct TrainerCard *);
static u16 GetCaughtMonsCount(void);
static void SetPlayerCardData(struct TrainerCard *, u8);
static void TrainerCard_GenerateCardForPlayer(struct TrainerCard *);
static u8 VersionToCardType(u8);
static void SetDataFromTrainerCard(void);
static void InitGpuRegs(void);
static void ResetGpuRegs(void);
static void UpdateTrainerCardPalette(void);
static void InitBgsAndWindows(void);
static void SetTrainerCardCb2(void);
static void SetUpTrainerCardTask(void);
static void InitTrainerCardData(void);
static u8 GetSetCardType(void);
static void PrintNameOnCardFront(void);
static void PrintIdOnCard(void);
static void PrintMoneyOnCard(void);
static void PrintDeathsOnCard(void);
static void PrintProfilePhraseOnCard(void);
static bool8 PrintAllOnCardBack(void);
static void PrintNameOnCardBack(void);
static void PrintWinRecords(void);
static void PrintStickersOnCard(void);
static void BufferTextsVarsForCardPage2(void);
static void BufferNameForCardBack(void);
static void BufferWinRecords(void);
static void LoadStickerGfx(void);
static u8 SetCardBgsAndPals(void);
static void DrawCardBackStats(void);
static void Task_DoCardFlipTask(u8);
static bool8 Task_BeginCardFlip(struct Task *task);
static bool8 Task_AnimateCardFlipDown(struct Task *task);
static bool8 Task_DrawFlippedCardSide(struct Task *task);
static bool8 Task_SetCardFlipped(struct Task *task);
static bool8 Task_AnimateCardFlipUp(struct Task *task);
static bool8 Task_EndCardFlip(struct Task *task);
static void UpdateCardFlipRegs(u16);
static void LoadMonIconGfx(void);
u16 FacilityClassToGraphicsId(u8 facilityClass);
static u16 GetTrainerOverworldGraphicsId(u16 trainerId);
static void CreateWinRecordSprites(void);
static void DestroyWinRecordSprites(void);

static const u32 sTrainerCardStickers_Gfx[]      = INCBIN_U32("graphics/trainer_card/frlg/stickers.4bpp.smol");
static const u16 sUnused_Pal[]                   = INCBIN_U16("graphics/trainer_card/unused.gbapal");
static const u16 sHoennTrainerCardBronze_Pal[]   = INCBIN_U16("graphics/trainer_card/bronze.gbapal");
static const u16 sKantoTrainerCardGreen_Pal[]    = INCBIN_U16("graphics/trainer_card/frlg/green.gbapal");
static const u16 sHoennTrainerCardCopper_Pal[]   = INCBIN_U16("graphics/trainer_card/copper.gbapal");
static const u16 sKantoTrainerCardBronze_Pal[]   = INCBIN_U16("graphics/trainer_card/frlg/bronze.gbapal");
static const u16 sHoennTrainerCardSilver_Pal[]   = INCBIN_U16("graphics/trainer_card/silver.gbapal");
static const u16 sKantoTrainerCardSilver_Pal[]   = INCBIN_U16("graphics/trainer_card/frlg/silver.gbapal");
static const u16 sHoennTrainerCardGold_Pal[]     = INCBIN_U16("graphics/trainer_card/gold.gbapal");
static const u16 sKantoTrainerCardGold_Pal[]     = INCBIN_U16("graphics/trainer_card/frlg/gold.gbapal");
static const u16 sHoennTrainerCardFemaleBg_Pal[] = INCBIN_U16("graphics/trainer_card/female_bg.gbapal");
static const u16 sKantoTrainerCardFemaleBg_Pal[] = INCBIN_U16("graphics/trainer_card/frlg/female_bg.gbapal");
static const u16 sHoennTrainerCardBadges_Pal[]   = INCBIN_U16("graphics/trainer_card/badges.gbapal");
static const u16 sKantoTrainerCardBadges_Pal[]   = INCBIN_U16("graphics/trainer_card/frlg/badges.gbapal");
static const u16 sTrainerCardStar_Pal[]          = INCBIN_U16("graphics/trainer_card/star.gbapal");
static const u16 sTrainerCardSticker1_Pal[]      = INCBIN_U16("graphics/trainer_card/frlg/stickers1.gbapal");
static const u16 sTrainerCardSticker2_Pal[]      = INCBIN_U16("graphics/trainer_card/frlg/stickers2.gbapal");
static const u16 sTrainerCardSticker3_Pal[]      = INCBIN_U16("graphics/trainer_card/frlg/stickers3.gbapal");
static const u16 sTrainerCardSticker4_Pal[]      = INCBIN_U16("graphics/trainer_card/frlg/stickers4.gbapal");
static const u32 sHoennTrainerCardBadges_Gfx[]   = INCBIN_U32("graphics/trainer_card/badges.4bpp.smol");
static const u32 sKantoTrainerCardBadges_Gfx[]   = INCBIN_U32("graphics/trainer_card/frlg/badges.4bpp.smol");

static const struct BgTemplate sTrainerCardBgTemplates[4] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 27,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 192
    },
};

static const struct WindowTemplate sTrainerCardWindowTemplates[] =
{
    [WIN_MSG] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x253,
    },
    [WIN_CARD_TEXT] = {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 28,
        .height = 18,
        .paletteNum = 15,
        .baseBlock = 0x1,
    },
    [WIN_TRAINER_PIC] = {
        .bg = 3,
        .tilemapLeft = 19,
        .tilemapTop = 5,
        .width = 9,
        .height = 10,
        .paletteNum = 8,
        .baseBlock = 0x150,
    },
    DUMMY_WIN_TEMPLATE
};

static const u16 *const sHoennTrainerCardPals[] =
{
    gHoennTrainerCardGreen_Pal,  // Default (0 stars)
    sHoennTrainerCardCopper_Pal, // 2 stars
    sHoennTrainerCardBronze_Pal, // 1 star
    sHoennTrainerCardSilver_Pal, // 3 stars
    sHoennTrainerCardGold_Pal,   // 4 stars
};

static const u16 *const sKantoTrainerCardPals[] =
{
    gKantoTrainerCardBlue_Pal,   // Default (0 stars)
    sKantoTrainerCardGreen_Pal,  // 1 star
    sKantoTrainerCardBronze_Pal, // 2 stars
    sKantoTrainerCardSilver_Pal, // 3 stars
    sKantoTrainerCardGold_Pal,   // 4 stars
};

static const u8 sTrainerCardTextColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};
static const u8 sTrainerCardGoldTextColors[] = {TEXT_COLOR_TRANSPARENT, 15, TEXT_COLOR_LIGHT_BLUE};
static const u8 sTrainerCardLossTextColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED, TEXT_COLOR_LIGHT_RED};
static const u8 sTimeColonInvisibleTextColors[6] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_TRANSPARENT};

static const u8 sTrainerPicOffset[2][GENDER_COUNT][2] =
{
    // Kanto
    {
        [MALE]   = {13, 4},
        [FEMALE] = {13, 4}
    },
    // Hoenn
    {
        [MALE]   = {1, 0},
        [FEMALE] = {1, 0}
    },
};

static const u8 sTrainerPicFacilityClass[][GENDER_COUNT] =
{
    [CARD_TYPE_FRLG] =
    {
        [MALE]   = FACILITY_CLASS_RED,
        [FEMALE] = FACILITY_CLASS_LEAF
    },
    [CARD_TYPE_RS] =
    {
        [MALE]   = FACILITY_CLASS_RS_BRENDAN,
        [FEMALE] = FACILITY_CLASS_RS_MAY
    },
    [CARD_TYPE_EMERALD] =
    {
        [MALE]   = FACILITY_CLASS_BRENDAN,
        [FEMALE] = FACILITY_CLASS_MAY
    }
};

static bool8 (*const sTrainerCardFlipTasks[])(struct Task *) =
{
    Task_BeginCardFlip,
    Task_AnimateCardFlipDown,
    Task_DrawFlippedCardSide,
    Task_SetCardFlipped,
    Task_AnimateCardFlipUp,
    Task_EndCardFlip,
};

static void VblankCb_TrainerCard(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    BlinkTimeColon();
    if (sData->allowDMACopy)
        DmaCopy16(3, &gScanlineEffectRegBuffers[0], &gScanlineEffectRegBuffers[1], 0x140);
}

static void HblankCb_TrainerCard(void)
{
    u16 backup;
    u16 bgVOffset;

    backup = REG_IME;
    REG_IME = 0;
    bgVOffset = gScanlineEffectRegBuffers[1][REG_VCOUNT & 0xFF];
    REG_BG0VOFS = bgVOffset;
    REG_IME = backup;
}

static void CB2_TrainerCard(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void CloseTrainerCard(u8 taskId)
{
    DestroyWinRecordSprites();
    SetMainCallback2(sData->callback2);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sData);
    DestroyTask(taskId);
}

// States for Task_TrainerCard. Skips the initial states, which are done once in order
#define STATE_HANDLE_INPUT_FRONT  10
#define STATE_HANDLE_INPUT_BACK   11
#define STATE_WAIT_FLIP_TO_BACK   12
#define STATE_WAIT_FLIP_TO_FRONT  13
#define STATE_CLOSE_CARD          14
#define STATE_WAIT_LINK_PARTNER   15
#define STATE_CLOSE_CARD_LINK     16

static void Task_TrainerCard(u8 taskId)
{
    switch (sData->mainState)
    {
    // Draw card initially
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            FillWindowPixelBuffer(WIN_CARD_TEXT, PIXEL_FILL(0));
            sData->mainState++;
        }
        break;
    case 1:
        if (PrintAllOnCardFront())
            sData->mainState++;
        break;
    case 2:
        DrawTrainerCardWindow(WIN_CARD_TEXT);
        sData->mainState++;
        break;
    case 3:
        FillWindowPixelBuffer(WIN_TRAINER_PIC, PIXEL_FILL(0));
        CreateTrainerCardTrainerPic();
        DrawTrainerCardWindow(WIN_TRAINER_PIC);
        sData->mainState++;
        break;
    case 4:
        DrawCardScreenBackground(sData->bgTilemap);
        sData->mainState++;
        break;
    case 5:
        DrawCardFrontOrBack(sData->frontTilemap);
        sData->mainState++;
        break;
    case 6:
        DrawStarsAndBadgesOnCard();
        sData->mainState++;
        break;
    // Fade in
    case 7:
        if (gWirelessCommType == 1 && gReceivedRemoteLinkPlayers == TRUE)
        {
            LoadWirelessStatusIndicatorSpriteGfx();
            CreateWirelessStatusIndicatorSprite(DISPLAY_WIDTH - 10, DISPLAY_HEIGHT - 10);
        }
        BlendPalettes(PALETTES_ALL, 16, sData->blendColor);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, sData->blendColor);
        SetVBlankCallback(VblankCb_TrainerCard);
        sData->mainState++;
        break;
    case 8:
        if (!UpdatePaletteFade() && !IsDma3ManagerBusyWithBgCopy())
        {
            PlaySE(SE_RG_CARD_OPEN);
            sData->mainState = STATE_HANDLE_INPUT_FRONT;
        }
        break;
    case 9:
        if (!IsSEPlaying())
            sData->mainState++;
        break;
    case STATE_HANDLE_INPUT_FRONT:
        // Blink the : in play time
        if (!gReceivedRemoteLinkPlayers && sData->timeColonNeedDraw)
        {
            PrintTimeOnCard();
            DrawTrainerCardWindow(WIN_CARD_TEXT);
            sData->timeColonNeedDraw = FALSE;
        }
        if (JOY_NEW(A_BUTTON))
        {
            FlipTrainerCard();
            PlaySE(SE_RG_CARD_FLIP);
            sData->mainState = STATE_WAIT_FLIP_TO_BACK;
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            if (sData->isHoenn) // Only apply to Hoenn cards as per request
            {
                PlaySE(SE_SELECT);
                if (sData->currentPalIndex == 0)
                    sData->currentPalIndex = ARRAY_COUNT(sHoennTrainerCardPals) - 1;
                else
                    sData->currentPalIndex--;
                UpdateTrainerCardPalette();
            }
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (sData->isHoenn) // Only apply to Hoenn cards as per request
            {
                PlaySE(SE_SELECT);
                sData->currentPalIndex++;
                if (sData->currentPalIndex >= ARRAY_COUNT(sHoennTrainerCardPals))
                    sData->currentPalIndex = 0;
                UpdateTrainerCardPalette();
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            if (gReceivedRemoteLinkPlayers && sData->isLink && InUnionRoom() == TRUE)
            {
                sData->mainState = STATE_WAIT_LINK_PARTNER;
            }
            else
            {
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, sData->blendColor);
                sData->mainState = STATE_CLOSE_CARD;
            }
        }
        break;
    case STATE_WAIT_FLIP_TO_BACK:
        if (IsCardFlipTaskActive() && Overworld_IsRecvQueueAtMax() != TRUE)
        {
            PlaySE(SE_RG_CARD_OPEN);
            sData->mainState = STATE_HANDLE_INPUT_BACK;
        }
        break;
    case STATE_HANDLE_INPUT_BACK:
        if (JOY_NEW(DPAD_LEFT))
        {
            if (sData->isHoenn) // Only apply to Hoenn cards as per request
            {
                PlaySE(SE_SELECT);
                if (sData->currentPalIndex == 0)
                    sData->currentPalIndex = ARRAY_COUNT(sHoennTrainerCardPals) - 1;
                else
                    sData->currentPalIndex--;
                UpdateTrainerCardPalette();
            }
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (sData->isHoenn) // Only apply to Hoenn cards as per request
            {
                PlaySE(SE_SELECT);
                sData->currentPalIndex++;
                if (sData->currentPalIndex >= ARRAY_COUNT(sHoennTrainerCardPals))
                    sData->currentPalIndex = 0;
                UpdateTrainerCardPalette();
            }
        }
        else if (JOY_NEW(A_BUTTON))
        {
           if (gReceivedRemoteLinkPlayers && sData->isLink && InUnionRoom() == TRUE)
           {
               sData->mainState = STATE_WAIT_LINK_PARTNER;
           }
           else
           {
               BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, sData->blendColor);
               sData->mainState = STATE_CLOSE_CARD;
           }
        }
        break;
    case STATE_WAIT_LINK_PARTNER:
        SetCloseLinkCallback();
        DrawDialogueFrame(WIN_MSG, TRUE);
        AddTextPrinterParameterized(WIN_MSG, FONT_NORMAL, gText_WaitingTrainerFinishReading, 0, 1, 255, 0);
        CopyWindowToVram(WIN_MSG, COPYWIN_FULL);
        sData->mainState = STATE_CLOSE_CARD_LINK;
        break;
    case STATE_CLOSE_CARD_LINK:
        if (!gReceivedRemoteLinkPlayers)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, sData->blendColor);
            sData->mainState = STATE_CLOSE_CARD;
        }
        break;
    case STATE_CLOSE_CARD:
        if (!UpdatePaletteFade())
            CloseTrainerCard(taskId);
        break;
    case STATE_WAIT_FLIP_TO_FRONT:
        if (IsCardFlipTaskActive() && Overworld_IsRecvQueueAtMax() != TRUE)
        {
            sData->mainState = STATE_HANDLE_INPUT_FRONT;
            PlaySE(SE_RG_CARD_OPEN);
        }
        break;
   }
}

static void UpdateTrainerCardPalette(void)
{
    const u16 *palettes;
    if (sData->cardType == CARD_TYPE_FRLG)
        palettes = sKantoTrainerCardPals[sData->currentPalIndex];
    else // CARD_TYPE_RS or CARD_TYPE_EMERALD
        palettes = sHoennTrainerCardPals[sData->currentPalIndex];

    LoadPalette(palettes, BG_PLTT_ID(0), 3 * PLTT_SIZE_4BPP);

    if (!sData->onBack)
        DrawStarsAndBadgesOnCard(); // Redraw front-side elements (stars/badges)
    else
        DrawCardBackStats(); // Ensure back-side elements (stickers) or empty space is maintained

    CopyBgTilemapBufferToVram(3); 
}

static bool8 LoadCardGfx(void)
{
    switch (sData->gfxLoadState)
    {
    case 0:
        if (sData->cardType != CARD_TYPE_FRLG)
            DecompressDataWithHeaderWram(gHoennTrainerCardBg_Tilemap, sData->bgTilemap);
        else
            DecompressDataWithHeaderWram(gKantoTrainerCardBg_Tilemap, sData->bgTilemap);
        break;
    case 1:
        if (sData->cardType != CARD_TYPE_FRLG)
            DecompressDataWithHeaderWram(gHoennTrainerCardBack_Tilemap, sData->backTilemap);
        else
            DecompressDataWithHeaderWram(gKantoTrainerCardBack_Tilemap, sData->backTilemap);
        break;
    case 2:
        if (!sData->isLink)
        {
            if (sData->cardType != CARD_TYPE_FRLG)
                DecompressDataWithHeaderWram(gHoennTrainerCardFront_Tilemap, sData->frontTilemap);
            else
                DecompressDataWithHeaderWram(gKantoTrainerCardFront_Tilemap, sData->frontTilemap);
        }
        else
        {
            if (sData->cardType != CARD_TYPE_FRLG)
                DecompressDataWithHeaderWram(gHoennTrainerCardFrontLink_Tilemap, sData->frontTilemap);
            else
                DecompressDataWithHeaderWram(gKantoTrainerCardFrontLink_Tilemap, sData->frontTilemap);
        }
        break;
    case 3:
        if (sData->cardType != CARD_TYPE_FRLG)
            DecompressDataWithHeaderWram(sHoennTrainerCardBadges_Gfx, sData->badgeTiles);
        else
            DecompressDataWithHeaderWram(sKantoTrainerCardBadges_Gfx, sData->badgeTiles);
        break;
    case 4:
        if (sData->cardType != CARD_TYPE_FRLG)
            DecompressDataWithHeaderWram(gHoennTrainerCard_Gfx, sData->cardTiles);
        else
            DecompressDataWithHeaderWram(gKantoTrainerCard_Gfx, sData->cardTiles);
        break;
    case 5:
        if (sData->cardType == CARD_TYPE_FRLG)
            DecompressDataWithHeaderWram(sTrainerCardStickers_Gfx, sData->stickerTiles);
        break;
    default:
        sData->gfxLoadState = 0;
        return TRUE;
    }
    sData->gfxLoadState++;
    return FALSE;
}

static void CB2_InitTrainerCard(void)
{
    switch (gMain.state)
    {
    case 0:
        ResetGpuRegs();
        SetUpTrainerCardTask();
        gMain.state++;
        break;
    case 1:
        DmaClear32(3, (void *)OAM, OAM_SIZE);
        gMain.state++;
        break;
    case 2:
        if (!sData->blendColor)
            DmaClear16(3, (void *)PLTT, PLTT_SIZE);
        gMain.state++;
        break;
    case 3:
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        gMain.state++;
    case 4:
        InitBgsAndWindows();
        gMain.state++;
        break;
    case 5:
        LoadMonIconGfx();
        gMain.state++;
        break;
    case 6:
        if (LoadCardGfx() == TRUE)
            gMain.state++;
        break;
    case 7:
        LoadStickerGfx();
        gMain.state++;
        break;
    case 8:
        InitGpuRegs();
        gMain.state++;
        break;
    case 9:
        BufferTextsVarsForCardPage2();
        gMain.state++;
        break;
    case 10:
        if (SetCardBgsAndPals() == TRUE)
            gMain.state++;
        break;
    default:
        SetTrainerCardCb2();
        break;
    }
}

static u32 GetCappedGameStat(u8 statId, u32 maxValue)
{
    u32 statValue = GetGameStat(statId);

    return min(maxValue, statValue);
}

static bool8 HasAllFrontierSymbols(void)
{
    u8 i;
    for (i = 0; i < NUM_FRONTIER_FACILITIES; i++)
    {
        if (!FlagGet(FLAG_SYS_TOWER_SILVER + 2 * i) || !FlagGet(FLAG_SYS_TOWER_GOLD + 2 * i))
            return FALSE;
    }
    return TRUE;
}

u32 CountPlayerTrainerStars(void)
{
    u8 stars = 0;

    if (GetGameStat(GAME_STAT_ENTERED_HOF))
        stars++;
    if (HasAllHoennMons())
        stars++;
    if (CountPlayerMuseumPaintings() >= CONTEST_CATEGORIES_COUNT)
        stars++;
    if (HasAllFrontierSymbols())
        stars++;

    return stars;
}

static u8 GetRubyTrainerStars(struct TrainerCard *trainerCard)
{
    u8 stars = 0;

    if (trainerCard->hofDebutHours || trainerCard->hofDebutMinutes || trainerCard->hofDebutSeconds)
        stars++;
    if (trainerCard->caughtAllHoenn)
        stars++;
    if (trainerCard->battleTowerStraightWins > 49)
        stars++;
    if (trainerCard->hasAllPaintings)
        stars++;

    return stars;
}

static void SetPlayerCardData(struct TrainerCard *trainerCard, u8 cardType)
{
    u32 playTime;
    u8 i;

    trainerCard->gender = gSaveBlock2Ptr->playerGender;
    trainerCard->playTimeHours = gSaveBlock2Ptr->playTimeHours;
    trainerCard->playTimeMinutes = gSaveBlock2Ptr->playTimeMinutes;

    playTime = GetGameStat(GAME_STAT_FIRST_HOF_PLAY_TIME);
    if (!GetGameStat(GAME_STAT_ENTERED_HOF))
        playTime = 0;

    trainerCard->hofDebutHours = playTime >> 16;
    trainerCard->hofDebutMinutes = (playTime >> 8) & 0xFF;
    trainerCard->hofDebutSeconds = playTime & 0xFF;
    if ((playTime >> 16) > 999)
    {
        trainerCard->hofDebutHours = 999;
        trainerCard->hofDebutMinutes = 59;
        trainerCard->hofDebutSeconds = 59;
    }

    trainerCard->hasPokedex = FlagGet(FLAG_SYS_POKEDEX_GET);
    trainerCard->caughtAllHoenn = HasAllHoennMons();
    trainerCard->caughtMonsCount = GetCaughtMonsCount();

    trainerCard->trainerId = (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];

    trainerCard->linkBattleWins = GetCappedGameStat(GAME_STAT_LINK_BATTLE_WINS, 9999);
    trainerCard->linkBattleLosses = GetCappedGameStat(GAME_STAT_LINK_BATTLE_LOSSES, 9999);

    trainerCard->pokemonTrades = GetCappedGameStat(GAME_STAT_POKEMON_TRADES, 0xFFFF);

    trainerCard->money = GetMoney(&gSaveBlock1Ptr->money);

    trainerCard->winsCount = gSaveBlock2Ptr->trainerCardWinsCount;
    for (i = 0; i < 13; i++)
        trainerCard->wins[i] = gSaveBlock2Ptr->trainerCardWins[i];

    for (i = 0; i < TRAINER_CARD_PROFILE_LENGTH; i++)
        trainerCard->easyChatProfile[i] = gSaveBlock1Ptr->easyChatProfile[i];

    StringCopy(trainerCard->playerName, gSaveBlock2Ptr->playerName);

    switch (cardType)
    {
    case CARD_TYPE_EMERALD:
        trainerCard->battleTowerWins = 0;
        trainerCard->battleTowerStraightWins = 0;
    // Seems like GF got CARD_TYPE_FRLG and CARD_TYPE_RS wrong.
    case CARD_TYPE_FRLG:
        trainerCard->contestsWithFriends = GetCappedGameStat(GAME_STAT_WON_LINK_CONTEST, 999);
        trainerCard->pokeblocksWithFriends = GetCappedGameStat(GAME_STAT_POKEBLOCKS_WITH_FRIENDS, 0xFFFF);
        if (CountPlayerMuseumPaintings() >= CONTEST_CATEGORIES_COUNT)
            trainerCard->hasAllPaintings = TRUE;
        trainerCard->stars = GetRubyTrainerStars(trainerCard);
        break;
    case CARD_TYPE_RS:
        trainerCard->battleTowerWins = 0;
        trainerCard->battleTowerStraightWins = 0;
        trainerCard->contestsWithFriends = 0;
        trainerCard->pokeblocksWithFriends = 0;
        trainerCard->hasAllPaintings = 0;
        trainerCard->stars = 0;
        break;
    }
}

static void TrainerCard_GenerateCardForPlayer(struct TrainerCard *trainerCard)
{
    memset(trainerCard, 0, sizeof(struct TrainerCard));
    trainerCard->version = GAME_VERSION;
    SetPlayerCardData(trainerCard, CARD_TYPE_EMERALD);
    trainerCard->hasAllFrontierSymbols = HasAllFrontierSymbols();
    trainerCard->frontierBP = gSaveBlock2Ptr->frontier.cardBattlePoints;
    if (trainerCard->hasAllFrontierSymbols)
        trainerCard->stars++;

    if (trainerCard->gender == FEMALE)
        trainerCard->unionRoomClass = gUnionRoomFacilityClasses[(trainerCard->trainerId % NUM_UNION_ROOM_CLASSES) + NUM_UNION_ROOM_CLASSES];
    else
        trainerCard->unionRoomClass = gUnionRoomFacilityClasses[trainerCard->trainerId % NUM_UNION_ROOM_CLASSES];
}

void TrainerCard_GenerateCardForLinkPlayer(struct TrainerCard *trainerCard)
{
    memset(trainerCard, 0, 0x60);
    trainerCard->version = GAME_VERSION;
    SetPlayerCardData(trainerCard, CARD_TYPE_EMERALD);
    trainerCard->linkHasAllFrontierSymbols = HasAllFrontierSymbols();
    *((u16 *)&trainerCard->linkPoints.frontier) = gSaveBlock2Ptr->frontier.cardBattlePoints;
    if (trainerCard->linkHasAllFrontierSymbols)
        trainerCard->stars++;

    if (trainerCard->gender == FEMALE)
        trainerCard->unionRoomClass = gUnionRoomFacilityClasses[(trainerCard->trainerId % NUM_UNION_ROOM_CLASSES) + NUM_UNION_ROOM_CLASSES];
    else
        trainerCard->unionRoomClass = gUnionRoomFacilityClasses[trainerCard->trainerId % NUM_UNION_ROOM_CLASSES];
}

void CopyTrainerCardData(struct TrainerCard *dst, struct TrainerCard *src, u8 gameVersion)
{
    memset(dst, 0, sizeof(struct TrainerCard));
    dst->version = gameVersion;

    switch (VersionToCardType(gameVersion))
    {
    case CARD_TYPE_FRLG:
        memcpy(dst, src, 0x60);
        break;
    case CARD_TYPE_RS:
        memcpy(dst, src, 0x38);
        break;
    case CARD_TYPE_EMERALD:
        memcpy(dst, src, 0x60);
        dst->linkPoints.frontier = 0;
        dst->hasAllFrontierSymbols = src->linkHasAllFrontierSymbols;
        dst->frontierBP = *((u16 *)&src->linkPoints.frontier);
        break;
    }
}

static void SetDataFromTrainerCard(void)
{
    u8 i;
    u32 badgeFlag;

    sData->hasPokedex = FALSE;
    sData->hasHofResult = FALSE;
    sData->hasLinkResults = FALSE;
    sData->hasBattleTowerWins = FALSE;
    sData->unused_E = FALSE;
    sData->unused_F = FALSE;
    sData->hasTrades = FALSE;
    memset(sData->badgeCount, 0, sizeof(sData->badgeCount));
    if (sData->trainerCard.hasPokedex)
        sData->hasPokedex++;

    if (sData->trainerCard.hofDebutHours
     || sData->trainerCard.hofDebutMinutes
     || sData->trainerCard.hofDebutSeconds)
        sData->hasHofResult++;

    if (sData->trainerCard.linkBattleWins || sData->trainerCard.linkBattleLosses)
        sData->hasLinkResults++;
    if (sData->trainerCard.pokemonTrades)
        sData->hasTrades++;
    if (sData->trainerCard.battleTowerWins || sData->trainerCard.battleTowerStraightWins)
        sData->hasBattleTowerWins++;

    for (i = 0, badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++, i++)
    {
        if (FlagGet(badgeFlag))
            sData->badgeCount[i]++;
    }
}

static void InitGpuRegs(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ);
    SetGpuReg(REG_OFFSET_WIN0V, DISPLAY_HEIGHT);
    SetGpuReg(REG_OFFSET_WIN0H, DISPLAY_WIDTH);
    if (gReceivedRemoteLinkPlayers)
        EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_HBLANK | INTR_FLAG_VCOUNT | INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    else
        EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_HBLANK);
}

static void UpdateCardFlipRegs(u16 cardTop)
{
    s8 blendY = (cardTop + 40) / 10;

    if (blendY <= 4)
        blendY = 0;
    sData->flipBlendY = blendY;
    SetGpuReg(REG_OFFSET_BLDY, sData->flipBlendY);
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(sData->cardTop, DISPLAY_HEIGHT - sData->cardTop));
}

static void ResetGpuRegs(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
}

static void InitBgsAndWindows(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sTrainerCardBgTemplates, ARRAY_COUNT(sTrainerCardBgTemplates));
    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    ChangeBgX(2, 0, BG_COORD_SET);
    ChangeBgY(2, 0, BG_COORD_SET);
    ChangeBgX(3, 0, BG_COORD_SET);
    ChangeBgY(3, 0, BG_COORD_SET);
    InitWindows(sTrainerCardWindowTemplates);
    DeactivateAllTextPrinters();
    LoadMessageBoxAndBorderGfx();
}

static void SetTrainerCardCb2(void)
{
    SetMainCallback2(CB2_TrainerCard);
}

static void SetUpTrainerCardTask(void)
{
    ResetTasks();
    ScanlineEffect_Stop();
    CreateTask(Task_TrainerCard, 0);
    InitTrainerCardData();
    SetDataFromTrainerCard();
}

static bool8 PrintAllOnCardFront(void)
{
    switch (sData->printState)
    {
    case 0:
        PrintNameOnCardFront();
        break;
    case 1:
        PrintIdOnCard();
        break;
    case 2:
        PrintMoneyOnCard();
        break;
    case 3:
        PrintDeathsOnCard();
        break;
    case 4:
        PrintTimeOnCard();
        break;
    case 5:
        PrintProfilePhraseOnCard();
        break;
    default:
        sData->printState = 0;
        return TRUE;
    }
    sData->printState++;
    return FALSE;
}

static bool8 PrintAllOnCardBack(void)
{
    switch (sData->printState)
    {
    case 0:
        PrintNameOnCardBack();
        break;
    case 1:
        PrintWinRecords();
        break;
    case 7:
        break;
    default:
        sData->printState = 0;
        return TRUE;
    }
    sData->printState++;
    return FALSE;
}

static void BufferTextsVarsForCardPage2(void)
{
    BufferNameForCardBack();
    BufferWinRecords();
}

static void PrintNameOnCardFront(void)
{
    u8 buffer[32];
    u8 *txtPtr;
    txtPtr = StringCopy(buffer, gText_TrainerCardName);
    StringCopy(txtPtr, sData->trainerCard.playerName);
    ConvertInternationalString(txtPtr, sData->language);
    if (sData->cardType == CARD_TYPE_FRLG)
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 20, 28, sTrainerCardTextColors, TEXT_SKIP_DRAW, buffer);
    else
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 16, 33, sTrainerCardTextColors, TEXT_SKIP_DRAW, buffer);
}

static void PrintIdOnCard(void)
{
    u8 buffer[32];
    u8 *txtPtr;
    s32 xPos;
    u32 top;
    txtPtr = StringCopy(buffer, gText_TrainerCardIDNo);
    ConvertIntToDecimalStringN(txtPtr, sData->trainerCard.trainerId, STR_CONV_MODE_LEADING_ZEROS, 5);
    if (sData->cardType == CARD_TYPE_FRLG)
    {
        xPos = GetStringCenterAlignXOffset(FONT_NORMAL, buffer, 80) + 132;
        top = 9;
    }
    else
    {
        xPos = GetStringCenterAlignXOffset(FONT_NORMAL, buffer, 96) + 120;
        top = 9;
    }

    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, xPos, top, sTrainerCardTextColors, TEXT_SKIP_DRAW, buffer);
}

static void PrintMoneyOnCard(void)
{
    s32 xOffset;
    u8 top;

    if (!sData->isHoenn)
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 20, 56, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_TrainerCardMoney);
    else
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 16, 57, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_TrainerCardMoney);

    ConvertIntToDecimalStringN(gStringVar1, sData->trainerCard.money, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_PokedollarVar1);
    if (!sData->isHoenn)
    {
        xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 144);
        top = 56;
    }
    else
    {
        xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 128);
        top = 57;
    }
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, xOffset, top, sTrainerCardTextColors, TEXT_SKIP_DRAW, gStringVar4);
}

static u16 GetCaughtMonsCount(void)
{
    if (IsNationalPokedexEnabled())
        return GetNationalPokedexCount(FLAG_GET_CAUGHT);
    else
        return GetHoennPokedexCount(FLAG_GET_CAUGHT);
}

static void PrintDeathsOnCard(void)
{
    s32 xOffset;
    u8 top;

    if (!sData->isHoenn)
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 20, 72, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_SavingFaints);
    else
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 16, 73, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_SavingFaints);

    ConvertIntToDecimalStringN(gStringVar4, gSaveBlock1Ptr->playerFaintCounter, STR_CONV_MODE_LEFT_ALIGN, 5);

    if (!sData->isHoenn)
    {
        xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 144);
        top = 72;
    }
    else
    {
        xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 128);
        top = 73;
    }
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, xOffset, top, sTrainerCardTextColors, TEXT_SKIP_DRAW, gStringVar4);
}

static const u8 *const sTimeColonTextColors[] = {sTrainerCardTextColors, sTimeColonInvisibleTextColors};

static void PrintTimeOnCard(void)
{
    u16 hours;
    u16 minutes;
    u16 seconds = 0;
    s32 width;
    u32 x, y, totalWidth;

    if (!sData->isHoenn)
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 20, 88, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_TrainerCardTime);
    else
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 16, 89, sTrainerCardTextColors, TEXT_SKIP_DRAW, gText_TrainerCardTime);

    if (sData->isLink)
    {
        hours = sData->trainerCard.playTimeHours;
        minutes = sData->trainerCard.playTimeMinutes;
        // Link trainer cards do not transmit seconds, so it defaults to 0.
    }
    else
    {
        hours = gSaveBlock2Ptr->playTimeHours;
        minutes = gSaveBlock2Ptr->playTimeMinutes;
        seconds = gSaveBlock2Ptr->playTimeSeconds;
    }

    if (hours > 999)
        hours = 999;
    if (minutes > 59)
        minutes = 59;
    if (seconds > 59)
        seconds = 59;
    width = GetStringWidth(FONT_NORMAL, gText_Colon2, 0);

    if (!sData->isHoenn)
    {
        x = 144;
        y = 88;
    }
    else
    {
        x = 128;
        y = 89;
    }
    totalWidth = width + 30 + width + 12;
    x -= totalWidth;

    FillWindowPixelRect(WIN_CARD_TEXT, PIXEL_FILL(0), x, y, totalWidth, 15);
    ConvertIntToDecimalStringN(gStringVar4, hours, STR_CONV_MODE_RIGHT_ALIGN, 3);
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, x, y, sTrainerCardTextColors, TEXT_SKIP_DRAW, gStringVar4);
    x += 18;
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, x, y, sTimeColonTextColors[sData->timeColonInvisible], TEXT_SKIP_DRAW, gText_Colon2);
    x += width;
    ConvertIntToDecimalStringN(gStringVar4, minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, x, y, sTrainerCardTextColors, TEXT_SKIP_DRAW, gStringVar4);
    x += 12;
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, x, y, sTimeColonTextColors[sData->timeColonInvisible], TEXT_SKIP_DRAW, gText_Colon2);
    x += width;
    ConvertIntToDecimalStringN(gStringVar4, seconds, STR_CONV_MODE_LEADING_ZEROS, 2);
    AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, x, y, sTrainerCardTextColors, TEXT_SKIP_DRAW, gStringVar4);
}

static void PrintProfilePhraseOnCard(void)
{
    static const u8 yOffsetsLine1[] = {113, 104};
    static const u8 yOffsetsLine2[] = {129, 120};

    if (sData->isLink)
    {
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 8, yOffsetsLine1[sData->isHoenn], sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->easyChatProfile[0]);
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, GetStringWidth(FONT_NORMAL, sData->easyChatProfile[0], 0) + 14, yOffsetsLine1[sData->isHoenn], sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->easyChatProfile[1]);
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 8, yOffsetsLine2[sData->isHoenn], sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->easyChatProfile[2]);
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, GetStringWidth(FONT_NORMAL, sData->easyChatProfile[2], 0) + 14, yOffsetsLine2[sData->isHoenn], sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->easyChatProfile[3]);
    }
}

static void BufferNameForCardBack(void)
{
    StringCopy(sData->textPlayersCard, sData->trainerCard.playerName);
    ConvertInternationalString(sData->textPlayersCard, sData->language);

    if (sData->trainerCard.winsCount > 12)
    {
        u8 *str = sData->textHofTime;
        str = ConvertIntToDecimalStringN(str, sData->trainerCard.wins[12].hours, STR_CONV_MODE_LEFT_ALIGN, 3);
        *str++ = CHAR_COLON;
        str = ConvertIntToDecimalStringN(str, sData->trainerCard.wins[12].minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
        *str++ = CHAR_COLON;
        ConvertIntToDecimalStringN(str, sData->trainerCard.wins[12].seconds, STR_CONV_MODE_LEADING_ZEROS, 2);

        if (sData->trainerCard.wins[12].trainerId & 0x8000)
            StringCopy(sData->textPlayersCard, COMPOUND_STRING("TRAINER CARD"));
        else
            StringCopy(sData->textPlayersCard, COMPOUND_STRING("BLITZ CHAMPION!     "));
    }
    else if (sData->cardType != CARD_TYPE_FRLG)
    {
        StringCopy(gStringVar1, sData->textPlayersCard);
        StringExpandPlaceholders(sData->textPlayersCard, gText_Var1sTrainerCard);
    }
}

static void PrintNameOnCardBack(void)
{
    if (sData->trainerCard.winsCount > 12)
    {
        u32 textWidth = GetStringWidth(FONT_NORMAL, sData->textPlayersCard, 0);

        if (sData->trainerCard.wins[12].trainerId & 0x8000)
        {
            s32 timeX = GetStringRightAlignXOffset(FONT_NORMAL, sData->textHofTime, 198); // 18px left of before
            s32 leftMiniX = timeX - 22;             // minis keep their pre-shift position
            s32 textX = leftMiniX - textWidth - 26; // 18px clear of the minis

            AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, textX, 9, sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->textPlayersCard);
            AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, timeX, 9, sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->textHofTime);
            sData->championSpritesX = leftMiniX - 16;
        }
        else
        {
            u32 timeWidth = GetStringWidth(FONT_NORMAL, sData->textHofTime, 0);
            u32 totalWidth = textWidth + 40 + timeWidth;
            s32 startX = ((224 - totalWidth) / 2) - 12;

            AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, startX, 9, sTrainerCardGoldTextColors, TEXT_SKIP_DRAW, sData->textPlayersCard);
            AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, startX + textWidth + 40, 9, sTrainerCardGoldTextColors, TEXT_SKIP_DRAW, sData->textHofTime);
            sData->championSpritesX = startX + textWidth + 4;
        }
    }
    else if (!sData->isHoenn)
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, 136, 9, sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->textPlayersCard);
    else
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, GetStringRightAlignXOffset(FONT_NORMAL, sData->textPlayersCard, 216), 9, sTrainerCardTextColors, TEXT_SKIP_DRAW, sData->textPlayersCard);
}

static void BufferWinRecords(void)
{
    u32 i;
    for (i = 0; i < sData->trainerCard.winsCount && i < 12; i++)
    {
        StringCopy(sData->winNames[i], GetTrainerNameFromId(sData->trainerCard.wins[i].trainerId & 0x7FFF));
        ConvertInternationalString(sData->winNames[i], sData->language);

        u8 *str = sData->winTimes[i];
        str = ConvertIntToDecimalStringN(str, sData->trainerCard.wins[i].hours, STR_CONV_MODE_LEFT_ALIGN, 3);
        *str++ = CHAR_COLON;
        str = ConvertIntToDecimalStringN(str, sData->trainerCard.wins[i].minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
        *str++ = CHAR_COLON;
        ConvertIntToDecimalStringN(str, sData->trainerCard.wins[i].seconds, STR_CONV_MODE_LEADING_ZEROS, 2);
    }
}

static void PrintWinRecords(void)
{
    u32 i;
    u32 x, y;
    for (i = 0; i < sData->trainerCard.winsCount && i < 12; i++)
    {
        if (i < 6)
        {
            x = 8;
            y = i * 16 + 33;
        }
        else
        {
            x = 104;
            y = (i - 6) * 16 + 33;
        }
        // Name text removed to be replaced by overworld sprite

        const u8 *colors = (sData->trainerCard.wins[i].trainerId & 0x8000) ? sTrainerCardLossTextColors : sTrainerCardTextColors;
        u32 timeX = x + 80 - GetStringWidth(FONT_NORMAL, sData->winTimes[i], 0);
        AddTextPrinterParameterized3(WIN_CARD_TEXT, FONT_NORMAL, timeX, y, colors, TEXT_SKIP_DRAW, sData->winTimes[i]);
    }
}

static u16 GetTrainerOverworldGraphicsId(u16 trainerId)
{
    u8 picIndex = GetTrainerPicFromId(trainerId);
    u32 i;

    // Map unique bosses to their overworld sprites by comparing against known trainer IDs.
    // This avoids dependency on missing TRAINER_PIC_ or FACILITY_CLASS_ constants.
    if (picIndex == GetTrainerPicFromId(TRAINER_ROXANNE_1)) return OBJ_EVENT_GFX_ROXANNE;
    if (picIndex == GetTrainerPicFromId(TRAINER_VIOLA_1)) return OBJ_EVENT_GFX_VIOLA;
    if (picIndex == GetTrainerPicFromId(TRAINER_BRAWLY_1)) return OBJ_EVENT_GFX_BRAWLY;
    if (picIndex == GetTrainerPicFromId(TRAINER_WATTSON_1)) return OBJ_EVENT_GFX_WATTSON;
    if (picIndex == GetTrainerPicFromId(TRAINER_FLANNERY_1)) return OBJ_EVENT_GFX_FLANNERY;
    if (picIndex == GetTrainerPicFromId(TRAINER_NORMAN_1)) return OBJ_EVENT_GFX_NORMAN;
    if (picIndex == GetTrainerPicFromId(TRAINER_WINONA_1)) return OBJ_EVENT_GFX_WINONA;
    if (picIndex == GetTrainerPicFromId(TRAINER_TATE_AND_LIZA_1)) return OBJ_EVENT_GFX_TATE;
    if (picIndex == GetTrainerPicFromId(TRAINER_JUAN_1)) return OBJ_EVENT_GFX_JUAN;
    if (picIndex == GetTrainerPicFromId(TRAINER_ARCHIE)) return OBJ_EVENT_GFX_ARCHIE;
    if (picIndex == GetTrainerPicFromId(TRAINER_MAXIE_MAGMA_HIDEOUT)) return OBJ_EVENT_GFX_MAXIE;

    if (picIndex == GetTrainerPicFromId(TRAINER_SIDNEY)) return OBJ_EVENT_GFX_SIDNEY;
    if (picIndex == GetTrainerPicFromId(TRAINER_PHOEBE)) return OBJ_EVENT_GFX_PHOEBE;
    if (picIndex == GetTrainerPicFromId(TRAINER_GLACIA)) return OBJ_EVENT_GFX_GLACIA;
    if (picIndex == GetTrainerPicFromId(TRAINER_DRAKE)) return OBJ_EVENT_GFX_DRAKE;

    if (picIndex == GetTrainerPicFromId(TRAINER_WALLACE)) return OBJ_EVENT_GFX_WALLACE;
    if (picIndex == GetTrainerPicFromId(TRAINER_STEVEN)) return OBJ_EVENT_GFX_STEVEN;
    if (picIndex == GetTrainerPicFromId(TRAINER_WALLY)) return OBJ_EVENT_GFX_WALLY;

    // Frontier Brains
    if (picIndex == GetTrainerPicFromId(TRAINER_NOLAND)) return OBJ_EVENT_GFX_NOLAND;
    if (picIndex == GetTrainerPicFromId(TRAINER_GRETA)) return OBJ_EVENT_GFX_GRETA;
    if (picIndex == GetTrainerPicFromId(TRAINER_TUCKER)) return OBJ_EVENT_GFX_TUCKER;
    if (picIndex == GetTrainerPicFromId(TRAINER_LUCY)) return OBJ_EVENT_GFX_LUCY;
    if (picIndex == GetTrainerPicFromId(TRAINER_SPENSER)) return OBJ_EVENT_GFX_SPENSER;
    if (picIndex == GetTrainerPicFromId(TRAINER_ANABEL)) return OBJ_EVENT_GFX_ANABEL;
    if (picIndex == GetTrainerPicFromId(TRAINER_BRANDON)) return OBJ_EVENT_GFX_BRANDON;

    // Search for the facility class that uses this front pic
    for (i = 0; i < 255; i++)
    {
        // If the palette is already loaded and is a generic NPC palette,
        // we need to ensure it's not greyed out by a previous operation.
        if (gFacilityClassToPicIndex[i] == picIndex)
            return FacilityClassToGraphicsId(i);
    }

    return OBJ_EVENT_GFX_YOUNGSTER;
}

static u8 AllocateAndGreyOutPalette(u8 spriteId, u32 winRecordIndex, u32 spriteIndexInRecord)
{
    u8 oldPalNum = gSprites[spriteId].oam.paletteNum;
    u8 newPalTag = OBJ_EVENT_PAL_TAG_DYNAMIC_GREY_START + (winRecordIndex * 2) + spriteIndexInRecord;
    u8 newPalNum = AllocSpritePalette(newPalTag);

    if (newPalNum == 0xFF) // Failed to allocate
        return 0xFF;

    // Copy original colors from the buffer to the new slot
    u16 *oldPalPtr = &gPlttBufferUnfaded[OBJ_PLTT_ID(oldPalNum)];
    u16 *newPalPtrUnfaded = &gPlttBufferUnfaded[OBJ_PLTT_ID(newPalNum)];
    u16 *newPalPtrFaded = &gPlttBufferFaded[OBJ_PLTT_ID(newPalNum)];
    s32 i;

    for (i = 0; i < 16; i++)
    {
        u32 r, g, b, grey;
        u16 color = oldPalPtr[i];
        r = GET_R(color);
        g = GET_G(color);
        b = GET_B(color);
        grey = (r * 30 + g * 59 + b * 11) / 100;
        color = RGB(grey, grey, grey);
        newPalPtrUnfaded[i] = color;
        newPalPtrFaded[i] = color;
    }
    return newPalNum;
}

static void CreateWinRecordSprites(void)
{
    u32 i;
    s16 x, y;
    u16 trainerId;
    u8 picIndex;
    u16 leftGfx, rightGfx;
    u8 spriteIdLeft, spriteIdRight;
    u8 greyPalNum;
    bool8 isPair;
    bool8 foughtLeft;

    for (i = 0; i < sData->trainerCard.winsCount && i < 12; i++)
    {
        if (i < 6)
        {
            x = 32;
            y = i * 16 + 41;
        }
        else
        {
            x = 128;
            y = (i - 6) * 16 + 41;
        }

        trainerId = sData->trainerCard.wins[i].trainerId & 0x7FFF;
        picIndex = GetTrainerPicFromId(trainerId);
        isPair = FALSE;
        foughtLeft = FALSE;

        if (picIndex == GetTrainerPicFromId(TRAINER_ROXANNE_1) || picIndex == GetTrainerPicFromId(TRAINER_VIOLA_1))
        {
            leftGfx = OBJ_EVENT_GFX_ROXANNE;
            rightGfx = OBJ_EVENT_GFX_VIOLA;
            foughtLeft = (picIndex == GetTrainerPicFromId(TRAINER_ROXANNE_1));
            isPair = TRUE;
        }
        else if (picIndex == GetTrainerPicFromId(TRAINER_SIDNEY) || picIndex == GetTrainerPicFromId(TRAINER_SPENSER))
        {
            leftGfx = OBJ_EVENT_GFX_SIDNEY;
            rightGfx = OBJ_EVENT_GFX_SPENSER;
            foughtLeft = (picIndex == GetTrainerPicFromId(TRAINER_SIDNEY));
            isPair = TRUE;
        }
        else if (picIndex == GetTrainerPicFromId(TRAINER_PHOEBE) || picIndex == GetTrainerPicFromId(TRAINER_LUCY))
        {
            leftGfx = OBJ_EVENT_GFX_PHOEBE;
            rightGfx = OBJ_EVENT_GFX_LUCY;
            foughtLeft = (picIndex == GetTrainerPicFromId(TRAINER_PHOEBE));
            isPair = TRUE;
        }
        else if (picIndex == GetTrainerPicFromId(TRAINER_GLACIA) || picIndex == GetTrainerPicFromId(TRAINER_TUCKER))
        {
            leftGfx = OBJ_EVENT_GFX_GLACIA;
            rightGfx = OBJ_EVENT_GFX_TUCKER;
            foughtLeft = (picIndex == GetTrainerPicFromId(TRAINER_GLACIA));
            isPair = TRUE;
        }
        else if (picIndex == GetTrainerPicFromId(TRAINER_DRAKE) || picIndex == GetTrainerPicFromId(TRAINER_BRANDON))
        {
            leftGfx = OBJ_EVENT_GFX_DRAKE;
            rightGfx = OBJ_EVENT_GFX_BRANDON;
            foughtLeft = (picIndex == GetTrainerPicFromId(TRAINER_DRAKE));
            isPair = TRUE;
        }

        if (isPair)
        {
            spriteIdLeft = CreateObjectGraphicsSprite(leftGfx, SpriteCallbackDummy, x, y, 0);
            spriteIdRight = CreateObjectGraphicsSprite(rightGfx, SpriteCallbackDummy, x + 16, y, 0);
            sData->winSpriteIds[i][0] = spriteIdLeft;
            sData->winSpriteIds[i][1] = spriteIdRight;
            StartSpriteAnim(&gSprites[spriteIdLeft], 0);
            StartSpriteAnim(&gSprites[spriteIdRight], 0);

            if (foughtLeft)
            {
                greyPalNum = AllocateAndGreyOutPalette(spriteIdRight, i, 1);
                if (greyPalNum != 0xFF)
                    gSprites[spriteIdRight].oam.paletteNum = greyPalNum;
            }
            else
            {
                greyPalNum = AllocateAndGreyOutPalette(spriteIdLeft, i, 0);
                if (greyPalNum != 0xFF)
                    gSprites[spriteIdLeft].oam.paletteNum = greyPalNum;
            }
        }
        else
        {
            spriteIdLeft = CreateObjectGraphicsSprite(GetTrainerOverworldGraphicsId(trainerId), SpriteCallbackDummy, x, y, 0);
            sData->winSpriteIds[i][0] = spriteIdLeft;
            StartSpriteAnim(&gSprites[spriteIdLeft], 0); // Face South

            // Initialize the second sprite ID to SPRITE_NONE for non-paired trainers
            sData->winSpriteIds[i][1] = SPRITE_NONE;

            if (picIndex == GetTrainerPicFromId(TRAINER_TATE_AND_LIZA_1))
            {
                sData->winSpriteIds[i][1] = CreateObjectGraphicsSprite(OBJ_EVENT_GFX_LIZA, SpriteCallbackDummy, x + 16, y, 0);
                StartSpriteAnim(&gSprites[sData->winSpriteIds[i][1]], 0);
            }
            else if (picIndex == GetTrainerPicFromId(TRAINER_JUAN_1))
            {
                sData->winSpriteIds[i][1] = CreateObjectGraphicsSprite(OBJ_EVENT_GFX_WALLACE, SpriteCallbackDummy, x + 16, y, 0);
                StartSpriteAnim(&gSprites[sData->winSpriteIds[i][1]], 0);
            }
        }

        // Grey out sprites if the record is a loss
        if (sData->trainerCard.wins[i].trainerId & 0x8000)
        {
            greyPalNum = AllocateAndGreyOutPalette(sData->winSpriteIds[i][0], i, 0);
            if (greyPalNum != 0xFF)
                gSprites[sData->winSpriteIds[i][0]].oam.paletteNum = greyPalNum;

            if (sData->winSpriteIds[i][1] != SPRITE_NONE)
            {
                greyPalNum = AllocateAndGreyOutPalette(sData->winSpriteIds[i][1], i, 1);
                if (greyPalNum != 0xFF)
                    gSprites[sData->winSpriteIds[i][1]].oam.paletteNum = greyPalNum;
            }
        }
    }

    if (sData->trainerCard.winsCount > 12)
    {
        u16 trainerId = sData->trainerCard.wins[12].trainerId & 0x7FFF;
        u8 picIndex = GetTrainerPicFromId(trainerId);
        u8 greyPalNum;
        s16 x = sData->championSpritesX + 16;
        s16 y = 17;

        sData->championSpriteIds[0] = CreateObjectGraphicsSprite(OBJ_EVENT_GFX_STEVEN, SpriteCallbackDummy, x, y, 0);
        sData->championSpriteIds[1] = CreateObjectGraphicsSprite(OBJ_EVENT_GFX_WALLY, SpriteCallbackDummy, x + 16, y, 0);
        StartSpriteAnim(&gSprites[sData->championSpriteIds[0]], 0);
        StartSpriteAnim(&gSprites[sData->championSpriteIds[1]], 0);

        if (picIndex == GetTrainerPicFromId(TRAINER_STEVEN))
        {
            greyPalNum = AllocateAndGreyOutPalette(sData->championSpriteIds[1], 12, 1);
            if (greyPalNum != 0xFF)
                gSprites[sData->championSpriteIds[1]].oam.paletteNum = greyPalNum;
        }
        else
        {
            greyPalNum = AllocateAndGreyOutPalette(sData->championSpriteIds[0], 12, 0);
            if (greyPalNum != 0xFF)
                gSprites[sData->championSpriteIds[0]].oam.paletteNum = greyPalNum;
        }
    }
}

static void DestroyWinRecordSprites(void)
{
    u32 i;

    for (i = 0; i < 12; i++)
    {
        // Free the dynamically allocated grey palettes
        if (sData->winSpriteIds[i][0] != SPRITE_NONE)
        {
            DestroySprite(&gSprites[sData->winSpriteIds[i][0]]);
            sData->winSpriteIds[i][0] = SPRITE_NONE;
            FreeSpritePaletteByTag(OBJ_EVENT_PAL_TAG_DYNAMIC_GREY_START + (i * 2));
        }
        if (sData->winSpriteIds[i][1] != SPRITE_NONE)
        {
            DestroySprite(&gSprites[sData->winSpriteIds[i][1]]);
            sData->winSpriteIds[i][1] = SPRITE_NONE;
            FreeSpritePaletteByTag(OBJ_EVENT_PAL_TAG_DYNAMIC_GREY_START + (i * 2) + 1);
        }
    }

    if (sData->championSpriteIds[0] != SPRITE_NONE)
    {
        DestroySprite(&gSprites[sData->championSpriteIds[0]]);
        sData->championSpriteIds[0] = SPRITE_NONE;
        FreeSpritePaletteByTag(OBJ_EVENT_PAL_TAG_DYNAMIC_GREY_START + (12 * 2));
    }
    if (sData->championSpriteIds[1] != SPRITE_NONE)
    {
        DestroySprite(&gSprites[sData->championSpriteIds[1]]);
        sData->championSpriteIds[1] = SPRITE_NONE;
        FreeSpritePaletteByTag(OBJ_EVENT_PAL_TAG_DYNAMIC_GREY_START + (12 * 2) + 1);
    }
}

static void LoadMonIconGfx(void)
{
    u8 i;

    CpuSet(gMonIconPalettes, sData->monIconPal, 0x60);
    switch (sData->trainerCard.monIconTint)
    {
    case MON_ICON_TINT_NORMAL:
        break;
    case MON_ICON_TINT_BLACK:
        TintPalette_CustomTone(sData->monIconPal, 96, 0, 0, 0);
        break;
    case MON_ICON_TINT_PINK:
        TintPalette_CustomTone(sData->monIconPal, 96, 500, 330, 310);
        break;
    case MON_ICON_TINT_SEPIA:
        TintPalette_SepiaTone(sData->monIconPal, 96);
        break;
    }
    LoadPalette(sData->monIconPal, BG_PLTT_ID(5), 6 * PLTT_SIZE_4BPP);

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sData->trainerCard.monSpecies[i])
            LoadBgTiles(3, GetMonIconTiles(sData->trainerCard.monSpecies[i], 0), 512, 16 * i + 32);
    }
}

static void PrintStickersOnCard(void)
{
    u8 i;
    u8 paletteSlots[4] = {11, 12, 13, 14};

    if (sData->cardType == CARD_TYPE_FRLG && sData->trainerCard.shouldDrawStickers == TRUE)
    {
        for (i = 0; i < TRAINER_CARD_STICKER_TYPES; i++)
        {
            u8 sticker = sData->trainerCard.stickers[i];
            if (sData->trainerCard.stickers[i])
                WriteSequenceToBgTilemapBuffer(3, i * 4 + 320, i * 3 + 2, 2, 2, 2, paletteSlots[sticker - 1], 1);
        }
    }
}

static void LoadStickerGfx(void)
{
    LoadPalette(sTrainerCardSticker1_Pal, BG_PLTT_ID(11), PLTT_SIZE_4BPP);
    LoadPalette(sTrainerCardSticker2_Pal, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
    LoadPalette(sTrainerCardSticker3_Pal, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
    LoadPalette(sTrainerCardSticker4_Pal, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
    LoadBgTiles(3, sData->stickerTiles, 1024, 128);
}

static void DrawTrainerCardWindow(u8 windowId)
{
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static u8 SetCardBgsAndPals(void)
{
    switch (sData->bgPalLoadState)
    {
    case 0:
        LoadBgTiles(3, sData->badgeTiles, ARRAY_COUNT(sData->badgeTiles), 0);
        break;
    case 1:
        LoadBgTiles(0, sData->cardTiles, 0x1800, 0);
        break;
    case 2:
        if (sData->cardType != CARD_TYPE_FRLG)
        {
            sData->currentPalIndex = sData->trainerCard.stars; // Initialize palette index
            LoadPalette(sHoennTrainerCardPals[sData->trainerCard.stars], BG_PLTT_ID(0), 3 * PLTT_SIZE_4BPP);
            LoadPalette(sHoennTrainerCardBadges_Pal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
            if (sData->trainerCard.gender != MALE)
                LoadPalette(sHoennTrainerCardFemaleBg_Pal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        else
        {
            sData->currentPalIndex = sData->trainerCard.stars; // Initialize palette index
            LoadPalette(sKantoTrainerCardPals[sData->trainerCard.stars], BG_PLTT_ID(0), 3 * PLTT_SIZE_4BPP);
            LoadPalette(sKantoTrainerCardBadges_Pal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
            if (sData->trainerCard.gender != MALE)
                LoadPalette(sKantoTrainerCardFemaleBg_Pal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        LoadPalette(sTrainerCardStar_Pal, BG_PLTT_ID(4), PLTT_SIZE_4BPP);
        // Explicitly load Gold colors into indices 15 and 14 of the text palette (Palette 15)
        gPlttBufferUnfaded[BG_PLTT_ID(15) + 15] = RGB_BLACK;
        break;
    case 3:
        SetBgTilemapBuffer(0, sData->cardTilemapBuffer);
        SetBgTilemapBuffer(2, sData->bgTilemapBuffer);
        break;
    case 4:
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 32, 32);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 32);
        FillBgTilemapBufferRect_Palette0(3, 0, 0, 0, 32, 32);
    default:
        return 1;
    }
    sData->bgPalLoadState++;
    return 0;
}

static void DrawCardScreenBackground(u16 *ptr)
{
    s16 i, j;
    u16 *dst = sData->bgTilemapBuffer;

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (j < 30)
                dst[32 * i + j] = ptr[30 * i + j];
            else
                dst[32 * i + j] = ptr[0];
        }
    }
    CopyBgTilemapBufferToVram(2);
}

static void DrawCardFrontOrBack(u16 *ptr)
{
    s16 i, j;
    u16 *dst = sData->cardTilemapBuffer;

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (j < 30)
                dst[32 * i + j] = ptr[30 * i + j];
            else
                dst[32 * i + j] = ptr[0];
        }
    }
    CopyBgTilemapBufferToVram(0);
}

static void DrawStarsAndBadgesOnCard(void)
{
    static const u8 yOffsets[] = {7, 7};

    s16 i, x;
    u16 tileNum = 192;
    u8 palNum = 3;

    FillBgTilemapBufferRect(3, 143, 15, yOffsets[sData->isHoenn], sData->trainerCard.stars, 1, 4);
    if (!sData->isLink)
    {
        x = 4;
        for (i = 0; i < NUM_BADGES; i++, tileNum += 2, x += 3)
        {
            if (sData->badgeCount[i])
            {
                FillBgTilemapBufferRect(3, tileNum, x, 15, 1, 1, palNum);
                FillBgTilemapBufferRect(3, tileNum + 1, x + 1, 15, 1, 1, palNum);
                FillBgTilemapBufferRect(3, tileNum + 16, x, 16, 1, 1, palNum);
                FillBgTilemapBufferRect(3, tileNum + 17, x + 1, 16, 1, 1, palNum);
            }
        }
    }
    CopyBgTilemapBufferToVram(3);
}

static void DrawCardBackStats(void)
{
    // Disabled to prevent overlap with the new win records list.
    if (sData->cardType == CARD_TYPE_FRLG && sData->trainerCard.shouldDrawStickers == TRUE)
    {
        PrintStickersOnCard();
    }
    CopyBgTilemapBufferToVram(3);
}

static void BlinkTimeColon(void)
{
    if (++sData->timeColonBlinkTimer > 60)
    {
        sData->timeColonBlinkTimer = 0;
        sData->timeColonInvisible ^= 1;
        sData->timeColonNeedDraw = TRUE;
    }
}

u8 GetTrainerCardStars(u8 cardId)
{
    struct TrainerCard *trainerCards = gTrainerCards;
    return trainerCards[cardId].stars;
}

#define tFlipState data[0]
#define tCardTop   data[1]

static void FlipTrainerCard(void)
{
    u8 taskId = CreateTask(Task_DoCardFlipTask, 0);
    Task_DoCardFlipTask(taskId);
    SetHBlankCallback(HblankCb_TrainerCard);
}

static bool8 IsCardFlipTaskActive(void)
{
    if (FindTaskIdByFunc(Task_DoCardFlipTask) == TASK_NONE)
        return TRUE;
    else
        return FALSE;
}

void ClearTrainerCardWins(void)
{
    u32 i;

    gSaveBlock2Ptr->trainerCardWinsCount = 0;
    for (i = 0; i < ARRAY_COUNT(gSaveBlock2Ptr->trainerCardWins); i++)
    {
        gSaveBlock2Ptr->trainerCardWins[i].trainerId = 0;
        gSaveBlock2Ptr->trainerCardWins[i].hours = 0;
        gSaveBlock2Ptr->trainerCardWins[i].minutes = 0;
        gSaveBlock2Ptr->trainerCardWins[i].seconds = 0;
    }
}

void RecordTrainerCardWin(struct ScriptContext *ctx)
{
    u16 trainerId = VarGet(VAR_0x8004);
    u32 i;

    // If this trainer was previously recorded as a loss, update it to a win.
    for (i = 0; i < gSaveBlock2Ptr->trainerCardWinsCount; i++)
    {
        if ((gSaveBlock2Ptr->trainerCardWins[i].trainerId & 0x7FFF) == trainerId)
        {
            gSaveBlock2Ptr->trainerCardWins[i].trainerId = trainerId; // Remove loss bit
            gSaveBlock2Ptr->trainerCardWins[i].hours = gSaveBlock2Ptr->playTimeHours;
            gSaveBlock2Ptr->trainerCardWins[i].minutes = gSaveBlock2Ptr->playTimeMinutes;
            gSaveBlock2Ptr->trainerCardWins[i].seconds = gSaveBlock2Ptr->playTimeSeconds;
            return;
        }
    }

    if (gSaveBlock2Ptr->trainerCardWinsCount < 13)
    {
        i = gSaveBlock2Ptr->trainerCardWinsCount;
        gSaveBlock2Ptr->trainerCardWins[i].trainerId = trainerId;
        gSaveBlock2Ptr->trainerCardWins[i].hours = gSaveBlock2Ptr->playTimeHours;
        gSaveBlock2Ptr->trainerCardWins[i].minutes = gSaveBlock2Ptr->playTimeMinutes;
        gSaveBlock2Ptr->trainerCardWins[i].seconds = gSaveBlock2Ptr->playTimeSeconds;
        gSaveBlock2Ptr->trainerCardWinsCount++;
    }
}

void RecordTrainerCardLoss(u16 trainerId)
{
    u32 i;
    for (i = 0; i < gSaveBlock2Ptr->trainerCardWinsCount; i++)
    {
        if ((gSaveBlock2Ptr->trainerCardWins[i].trainerId & 0x7FFF) == trainerId)
            return; // Already in the list (as win or loss)
    }

    if (gSaveBlock2Ptr->trainerCardWinsCount < 12
        || (gSaveBlock2Ptr->trainerCardWinsCount == 12
            && (trainerId == TRAINER_STEVEN || trainerId == TRAINER_WALLY)))
    {
        u8 count = gSaveBlock2Ptr->trainerCardWinsCount;
        gSaveBlock2Ptr->trainerCardWins[count].trainerId = trainerId | 0x8000;
        // Use challenge time if available (for boss trainers), otherwise use current time
        if (HasBossChallengeTime())
        {
            gSaveBlock2Ptr->trainerCardWins[count].hours = GetBossChallengeHours();
            gSaveBlock2Ptr->trainerCardWins[count].minutes = GetBossChallengeMinutes();
            gSaveBlock2Ptr->trainerCardWins[count].seconds = GetBossChallengeSeconds();
        }
        else
        {
            gSaveBlock2Ptr->trainerCardWins[count].hours = gSaveBlock2Ptr->playTimeHours;
            gSaveBlock2Ptr->trainerCardWins[count].minutes = gSaveBlock2Ptr->playTimeMinutes;
            gSaveBlock2Ptr->trainerCardWins[count].seconds = gSaveBlock2Ptr->playTimeSeconds;
        }
        gSaveBlock2Ptr->trainerCardWinsCount++;
    }
}

static void Task_DoCardFlipTask(u8 taskId)
{
    while(sTrainerCardFlipTasks[gTasks[taskId].tFlipState](&gTasks[taskId]))
        ;
}

static bool8 Task_BeginCardFlip(struct Task *task)
{
    u32 i;

    HideBg(1);
    HideBg(3);
    DestroyWinRecordSprites();
    ScanlineEffect_Stop();
    ScanlineEffect_Clear();
    for (i = 0; i < DISPLAY_HEIGHT; i++)
        gScanlineEffectRegBuffers[1][i] = 0;
    task->tFlipState++;
    return FALSE;
}

// Note: Cannot be DISPLAY_HEIGHT / 2, or cardHeight will be 0
#define CARD_FLIP_Y ((DISPLAY_HEIGHT / 2) - 3)

static bool8 Task_AnimateCardFlipDown(struct Task *task)
{
    u32 cardHeight, r5, r10, cardTop, r6, var_24, cardBottom, var;
    s16 i;

    sData->allowDMACopy = FALSE;
    if (task->tCardTop >= CARD_FLIP_Y)
        task->tCardTop = CARD_FLIP_Y;
    else
        task->tCardTop += 7;

    sData->cardTop = task->tCardTop;
    UpdateCardFlipRegs(task->tCardTop);

    cardTop = task->tCardTop;
    cardBottom = DISPLAY_HEIGHT - cardTop;
    cardHeight = cardBottom - cardTop;
    r6 = -cardTop << 16;
    r5 = (DISPLAY_HEIGHT << 16) / cardHeight;
    r5 -= 1 << 16;
    var_24 = r6;
    var_24 += r5 * cardHeight;
    r10 = r5 / cardHeight;
    r5 *= 2;

    for (i = 0; i < cardTop; i++)
        gScanlineEffectRegBuffers[0][i] = -i;
    for (; i < (s16)cardBottom; i++)
    {
        var = r6 >> 16;
        r6 += r5;
        r5 -= r10;
        gScanlineEffectRegBuffers[0][i] = var;
    }
    var = var_24 >> 16;
    for (; i < DISPLAY_HEIGHT; i++)
        gScanlineEffectRegBuffers[0][i] = var;

    sData->allowDMACopy = TRUE;
    if (task->tCardTop >= CARD_FLIP_Y)
        task->tFlipState++;

    return FALSE;
}

static bool8 Task_DrawFlippedCardSide(struct Task *task)
{
    sData->allowDMACopy = FALSE;
    if (Overworld_IsRecvQueueAtMax() == TRUE)
        return FALSE;

    do
    {
        switch (sData->flipDrawState)
        {
        case 0:
            FillWindowPixelBuffer(WIN_CARD_TEXT, PIXEL_FILL(0));
            FillBgTilemapBufferRect_Palette0(3, 0, 0, 0, 0x20, 0x20);
            break;
        case 1:
            if (!sData->onBack)
            {
                if (!PrintAllOnCardBack())
                    return FALSE;
            }
            else
            {
                if (!PrintAllOnCardFront())
                    return FALSE;
            }
            break;
        case 2:
            if (!sData->onBack)
            {
                DrawCardFrontOrBack(sData->backTilemap);
                CreateWinRecordSprites();
            }
            else
            {
                DrawTrainerCardWindow(WIN_CARD_TEXT);
            }
            break;
        case 3:
            if (!sData->onBack)
                DrawCardBackStats();
            else
                FillWindowPixelBuffer(WIN_TRAINER_PIC, PIXEL_FILL(0));
            break;
        case 4:
            if (sData->onBack)
                CreateTrainerCardTrainerPic();
            break;
        default:
            task->tFlipState++;
            sData->allowDMACopy = TRUE;
            sData->flipDrawState = 0;
            return FALSE;
        }
        sData->flipDrawState++;
    } while (gReceivedRemoteLinkPlayers == 0);

    return FALSE;
}

static bool8 Task_SetCardFlipped(struct Task *task)
{
    sData->allowDMACopy = FALSE;

    // If on back of card, draw front of card because its being flipped
    if (sData->onBack)
    {
        DrawTrainerCardWindow(WIN_TRAINER_PIC);
        DestroyWinRecordSprites();
        DrawCardScreenBackground(sData->bgTilemap);
        DrawCardFrontOrBack(sData->frontTilemap);
        DrawStarsAndBadgesOnCard();
    }
    DrawTrainerCardWindow(WIN_CARD_TEXT);
    sData->onBack ^= 1;
    task->tFlipState++;
    sData->allowDMACopy = TRUE;
    PlaySE(SE_RG_CARD_FLIPPING);
    return FALSE;
}

static bool8 Task_AnimateCardFlipUp(struct Task *task)
{
    u32 cardHeight, r5, r10, cardTop, r6, var_24, cardBottom, var;
    s16 i;

    sData->allowDMACopy = FALSE;
    if (task->tCardTop <= 5)
        task->tCardTop = 0;
    else
        task->tCardTop -= 5;

    sData->cardTop = task->tCardTop;
    UpdateCardFlipRegs(task->tCardTop);

    cardTop = task->tCardTop;
    cardBottom = DISPLAY_HEIGHT - cardTop;
    cardHeight = cardBottom - cardTop;
    r6 = -cardTop << 16;
    r5 = (DISPLAY_HEIGHT << 16) / cardHeight;
    r5 -= 1 << 16;
    var_24 = r6;
    var_24 += r5 * cardHeight;
    r10 = r5 / cardHeight;
    r5 /= 2;

    for (i = 0; i < cardTop; i++)
        gScanlineEffectRegBuffers[0][i] = -i;
    for (; i < (s16)cardBottom; i++)
    {
        var = r6 >> 16;
        r6 += r5;
        r5 += r10;
        gScanlineEffectRegBuffers[0][i] = var;
    }
    var = var_24 >> 16;
    for (; i < DISPLAY_HEIGHT; i++)
        gScanlineEffectRegBuffers[0][i] = var;

    sData->allowDMACopy = TRUE;
    if (task->tCardTop <= 0)
        task->tFlipState++;

    return FALSE;
}

static bool8 Task_EndCardFlip(struct Task *task)
{
    ShowBg(1);
    ShowBg(3);
    SetHBlankCallback(NULL);
    DestroyTask(FindTaskIdByFunc(Task_DoCardFlipTask));
    return FALSE;
}

void ShowPlayerTrainerCard(void (*callback)(void))
{
    sData = AllocZeroed(sizeof(*sData));
    sData->callback2 = callback;
    if (callback == CB2_ReshowFrontierPass)
        sData->blendColor = RGB_WHITE;
    else
        sData->blendColor = RGB_BLACK;

    if (InUnionRoom() == TRUE)
        sData->isLink = TRUE;
    else
        sData->isLink = FALSE;

    sData->language = GAME_LANGUAGE;
    TrainerCard_GenerateCardForPlayer(&sData->trainerCard);
    SetMainCallback2(CB2_InitTrainerCard);
}

void ShowTrainerCardInLink(u8 cardId, void (*callback)(void))
{
    sData = AllocZeroed(sizeof(*sData));
    sData->callback2 = callback;
    sData->isLink = TRUE;
    sData->trainerCard = gTrainerCards[cardId];
    sData->language = gLinkPlayers[cardId].language;
    SetMainCallback2(CB2_InitTrainerCard);
}

static void InitTrainerCardData(void)
{
    u8 i;

    sData->mainState = 0;
    sData->timeColonBlinkTimer = gSaveBlock2Ptr->playTimeVBlanks;
    sData->timeColonInvisible = FALSE;
    sData->onBack = FALSE;
    sData->flipBlendY = 0;
    sData->cardType = GetSetCardType();
    sData->championSpriteIds[0] = SPRITE_NONE;
    sData->championSpriteIds[1] = SPRITE_NONE;
    for (i = 0; i < 12; i++)
    {
        sData->winSpriteIds[i][0] = SPRITE_NONE;
        sData->winSpriteIds[i][1] = SPRITE_NONE;
    }
    for (i = 0; i < TRAINER_CARD_PROFILE_LENGTH; i++)
        CopyEasyChatWord(sData->easyChatProfile[i], sData->trainerCard.easyChatProfile[i]);
}

static u8 GetSetCardType(void)
{
    if (sData == NULL)
    {
        if (gGameVersion == VERSION_FIRE_RED || gGameVersion == VERSION_LEAF_GREEN)
            return CARD_TYPE_FRLG;
        else if (gGameVersion == VERSION_EMERALD)
            return CARD_TYPE_EMERALD;
        else
            return CARD_TYPE_RS;
    }
    else
    {
        if (sData->trainerCard.version == VERSION_FIRE_RED || sData->trainerCard.version == VERSION_LEAF_GREEN)
        {
            sData->isHoenn = FALSE;
            return CARD_TYPE_FRLG;
        }
        else if (sData->trainerCard.version == VERSION_EMERALD)
        {
            sData->isHoenn = TRUE;
            return CARD_TYPE_EMERALD;
        }
        else
        {
            sData->isHoenn = TRUE;
            return CARD_TYPE_RS;
        }
    }
}

static u8 VersionToCardType(u8 version)
{
    if (version == VERSION_FIRE_RED || version == VERSION_LEAF_GREEN)
        return CARD_TYPE_FRLG;
    else if (version == VERSION_EMERALD)
        return CARD_TYPE_EMERALD;
    else
        return CARD_TYPE_RS;
}

static void CreateTrainerCardTrainerPic(void)
{
    if (InUnionRoom() == TRUE && gReceivedRemoteLinkPlayers == 1)
    {
        CreateTrainerCardTrainerPicSprite(FacilityClassToPicIndex(sData->trainerCard.unionRoomClass),
                    TRUE,
                    sTrainerPicOffset[sData->isHoenn][sData->trainerCard.gender][0],
                    sTrainerPicOffset[sData->isHoenn][sData->trainerCard.gender][1],
                    8,
                    WIN_TRAINER_PIC);
    }
    else
    {
        CreateTrainerCardTrainerPicSprite(FacilityClassToPicIndex(sTrainerPicFacilityClass[sData->cardType][sData->trainerCard.gender]),
                    TRUE,
                    sTrainerPicOffset[sData->isHoenn][sData->trainerCard.gender][0],
                    sTrainerPicOffset[sData->isHoenn][sData->trainerCard.gender][1],
                    8,
                    WIN_TRAINER_PIC);
    }
    
    // Load player's chosen palette if viewing player's own card
    if (!sData->isLink)
    {
        const u16 *palette = GetPlayerObjectEventPaletteData(sData->trainerCard.gender);
        if (palette != NULL)
        {
            LoadPalette(palette, BG_PLTT_ID(8), PLTT_SIZE_4BPP);
        }
    }
}

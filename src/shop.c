#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "list_menu.h"
#include "pokemon.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "move.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_icon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "text_window.h"
#include "constants/maps.h"
#include "tv.h"
#include "constants/decorations.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/metatile_behaviors.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define TAG_SCROLL_ARROW   2100
#define TAG_ITEM_ICON_BASE 9110 // immune to time blending

#define MAX_ITEMS_SHOWN 8
#define SHOP_MENU_PALETTE_ID 12

extern const u16 *GetPlayerObjectEventPaletteData(u8 gender);

enum {
    WIN_BUY_SELL_QUIT,
    WIN_BUY_QUIT,
};

enum {
    WIN_MONEY,
    WIN_ITEM_LIST,
    WIN_ITEM_DESCRIPTION,
    WIN_QUANTITY_IN_BAG,
    WIN_QUANTITY_PRICE,
    WIN_MESSAGE,
};

enum {
    COLORID_NORMAL,      // Item descriptions, quantity in bag, and quantity/price
    COLORID_ITEM_LIST,   // The text in the item list, and the cursor normally
    COLORID_GRAY_CURSOR, // When the cursor has selected an item to purchase
};

enum {
    MART_TYPE_NORMAL,
    MART_TYPE_DECOR,
    MART_TYPE_DECOR2,
};

// shop view window NPC info enum
enum
{
    OBJ_EVENT_ID,
    X_COORD,
    Y_COORD,
    ANIM_NUM,
    LAYER_TYPE
};

struct MartInfo
{
    void (*callback)(void);
    const struct MenuAction *menuActions;
    const u16 *itemList;
    const u16 *priceList;
    u16 itemCount;
    u8 windowId;
    u8 martType;
};

struct ShopData
{
    u16 tilemapBuffers[4][0x400];
    u32 totalCost;
    u16 itemsShowed;
    u16 selectedRow;
    u16 scrollOffset;
    u16 maxQuantity;
    u8 scrollIndicatorsTaskId;
    u8 iconSlot;
    u8 itemSpriteIds[2];
    u8 pokemonIconSpriteIds[10];
    s16 viewportObjects[OBJECT_EVENTS_COUNT][5];
};

static EWRAM_DATA struct MartInfo sMartInfo = {0};
static EWRAM_DATA struct ShopData *sShopData = NULL;
static u16 sScottTmItemList[7]; // 5 TMs + INVERT + ITEM_NONE
static u16 sScottTmPriceList[7]; // 5 TM prices + INVERT price + 0
static const u16 sScottTmPool[] = {
    ITEM_TM_SEED_BOMB,
    ITEM_TM_GIGA_DRAIN,
    ITEM_TM_FIRE_PUNCH,
    ITEM_TM_FLAMETHROWER,
    ITEM_TM_THUNDER_PUNCH,
    ITEM_TM_THUNDERBOLT,
    ITEM_TM_ICE_PUNCH,
    ITEM_TM_ICE_BEAM,
    ITEM_TM_BRICK_BREAK,
    ITEM_TM_FOCUS_BLAST,
    ITEM_TM_X_SCISSOR,
    ITEM_TM_BUG_BUZZ,
    ITEM_TM_ROCK_SLIDE,
    ITEM_TM_POWER_GEM,
    ITEM_TM_DRAGON_CLAW,
    ITEM_TM_DRAGON_PULSE,
    ITEM_TM_IRON_TAIL,
    ITEM_TM_FLASH_CANNON,
    ITEM_TM_PLAY_ROUGH,
    ITEM_TM_DAZZLING_GLEAM,
    ITEM_TM_EARTHQUAKE,
    ITEM_TM_SCORCHING_SANDS,
    ITEM_TM_SHADOW_CLAW,
    ITEM_TM_SHADOW_BALL,
    ITEM_TM_ZEN_HEADBUTT,
    ITEM_TM_PSYCHIC,
    ITEM_TM_RETURN,
    ITEM_TM_HYPER_VOICE,
    ITEM_TM_POISON_JAB,
    ITEM_TM_SLUDGE_BOMB,
    ITEM_TM_CRUNCH,
    ITEM_TM_DARK_PULSE,
    ITEM_TM_FLIP_TURN,
    ITEM_TM_SCALD,
    ITEM_TM_DUAL_WINGBEAT,
    ITEM_TM_AIR_SLASH,
    ITEM_NONE
};

static bool8 sIsScottTmShop = FALSE;
static bool8 sScottTmPurchased[5]; // Track which of the 5 current TMs are purchased
static EWRAM_DATA u8 sScottTmPurchasedCount = 0; // Track total TMs purchased for price reduction
static bool8 sScottTmInvertPurchased = FALSE; // Track if Invert was purchased
static EWRAM_DATA struct ListMenuItem *sListMenuItems = NULL;

// Special item ID for Scott's TM shop option
#define ITEM_SCOTT_TM_INVERT  0xFFFD

// Partner TM pairs for Invert option
static const u16 sScottTmPartners[][2] = {
    {ITEM_TM_SEED_BOMB, ITEM_TM_GIGA_DRAIN},
    {ITEM_TM_FIRE_PUNCH, ITEM_TM_FLAMETHROWER},
    {ITEM_TM_THUNDER_PUNCH, ITEM_TM_THUNDERBOLT},
    {ITEM_TM_ICE_PUNCH, ITEM_TM_ICE_BEAM},
    {ITEM_TM_BRICK_BREAK, ITEM_TM_FOCUS_BLAST},
    {ITEM_TM_X_SCISSOR, ITEM_TM_BUG_BUZZ},
    {ITEM_TM_ROCK_SLIDE, ITEM_TM_POWER_GEM},
    {ITEM_TM_DRAGON_CLAW, ITEM_TM_DRAGON_PULSE},
    {ITEM_TM_IRON_TAIL, ITEM_TM_FLASH_CANNON},
    {ITEM_TM_PLAY_ROUGH, ITEM_TM_DAZZLING_GLEAM},
    {ITEM_TM_EARTHQUAKE, ITEM_TM_SCORCHING_SANDS},
    {ITEM_TM_SHADOW_CLAW, ITEM_TM_SHADOW_BALL},
    {ITEM_TM_ZEN_HEADBUTT, ITEM_TM_PSYCHIC},
    {ITEM_TM_RETURN, ITEM_TM_HYPER_VOICE},
    {ITEM_TM_POISON_JAB, ITEM_TM_SLUDGE_BOMB},
    {ITEM_TM_CRUNCH, ITEM_TM_DARK_PULSE},
    {ITEM_TM_FLIP_TURN, ITEM_TM_SCALD},
    {ITEM_TM_DUAL_WINGBEAT, ITEM_TM_AIR_SLASH},
};
static EWRAM_DATA u8 (*sItemNames)[ITEM_NAME_LENGTH + 2] = {0};
static EWRAM_DATA u8 sPurchaseHistoryId = 0;
EWRAM_DATA struct ItemSlot gMartPurchaseHistory[SMARTSHOPPER_NUM_ITEMS] = {0};

static void Task_ShopMenu(u8 taskId);
static void Task_HandleShopMenuQuit(u8 taskId);
static void CB2_InitBuyMenu(void);
static void PrepareScottTmShopInventory(void);
static u16 GetMartItemPrice(u16 itemId);
static void Task_GoToBuyOrSellMenu(u8 taskId);
static void BuyMenuFreeMemory(void);
static u16 GetScottTmPartner(u16 tmId);
static void ScottTmInvert(u8 taskId);
static void MapPostLoadHook_ReturnToShopMenu(void);
static void Task_ReturnToShopMenu(u8 taskId);
static void ShowShopMenuAfterExitingBuyOrSellMenu(u8 taskId);
static void BuyMenuDrawGraphics(void);
static void BuyMenuAddScrollIndicatorArrows(void);
static void Task_BuyMenu(u8 taskId);
static void BuyMenuBuildListMenuTemplate(void);
static void BuyMenuInitBgs(void);
static void BuyMenuInitWindows(void);
static void BuyMenuDecompressBgGraphics(void);
static void BuyMenuSetListEntry(struct ListMenuItem *, u16, u8 *);
static void BuyMenuAddItemIcon(u16, u8);
static void BuyMenuRemoveItemIcon(u16, u8);
static void BuyMenuPrint(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet);
static void BuyMenuDrawMapGraphics(void);
static void BuyMenuCopyMenuBgToBg1TilemapBuffer(void);
static void CreateShopPokemonIconSprites(u16 itemId);
static void BuyMenuCollectObjectEventData(void);
static void BuyMenuDrawObjectEvents(void);
static void BuyMenuDrawMapBg(void);
static bool8 BuyMenuCheckForOverlapWithMenuBg(int, int);
static void BuyMenuDrawMapMetatile(s16, s16, const u16 *, u8);
static void BuyMenuDrawMapMetatileLayer(u16 *dest, s16 offset1, s16 offset2, const u16 *src);
static bool8 BuyMenuCheckIfObjectEventOverlapsMenuBg(s16 *);
static void ExitBuyMenu(u8 taskId);
static void Task_ExitBuyMenu(u8 taskId);
static void BuyMenuTryMakePurchase(u8 taskId);
static void BuyMenuReturnToItemList(u8 taskId);
static void Task_BuyHowManyDialogueInit(u8 taskId);
static void BuyMenuConfirmPurchase(u8 taskId);
static void BuyMenuPrintItemQuantityAndPrice(u8 taskId);
static void Task_BuyHowManyDialogueHandleInput(u8 taskId);
static void BuyMenuSubtractMoney(u8 taskId);
static void RecordItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterDecorationPurchase(u8 taskId);
static void Task_HandleShopMenuBuy(u8 taskId);
static void Task_HandleShopMenuSell(u8 taskId);
static void BuyMenuPrintItemDescriptionAndShowItemIcon(s32 item, bool8 onInit, struct ListMenu *list);
static void BuyMenuPrintPriceInList(u8 windowId, u32 itemId, u8 y);

static const struct YesNoFuncTable sShopPurchaseYesNoFuncs =
{
    BuyMenuTryMakePurchase,
    BuyMenuReturnToItemList
};

static const struct MenuAction sShopMenuActions_BuySellQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopSell, {.void_u8=Task_HandleShopMenuSell} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct MenuAction sShopMenuActions_BuyQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct WindowTemplate sShopMenuWindowTemplates[] =
{
    [WIN_BUY_SELL_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    },
    // Separate shop menu window for decorations, which can't be sold
    [WIN_BUY_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    }
};

static const struct ListMenuTemplate sShopBuyMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = BuyMenuPrintItemDescriptionAndShowItemIcon,
    .itemPrintFunc = BuyMenuPrintPriceInList,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_ITEM_LIST,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_MULTIPLE_SCROLL_DPAD,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW,
    .textNarrowWidth = 84,
};

static const struct BgTemplate sShopBuyMenuBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct WindowTemplate sShopBuyMenuWindowTemplates[] =
{
    [WIN_MONEY] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x001E,
    },
    [WIN_ITEM_LIST] = {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 2,
        .width = 15,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 0x0032,
    },
    [WIN_ITEM_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0122,
    },
    [WIN_QUANTITY_IN_BAG] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 11,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0176,
    },
    [WIN_QUANTITY_PRICE] = {
        .bg = 0,
        .tilemapLeft = 18,
        .tilemapTop = 11,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x018E,
    },
    [WIN_MESSAGE] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x01A2,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sShopBuyMenuYesNoWindowTemplates =
{
    .bg = 0,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x020E,
};

static const u8 sShopBuyMenuTextColors[][3] =
{
    [COLORID_NORMAL]      = {1, 2, 3},
    [COLORID_ITEM_LIST]   = {0, 2, 3},
    [COLORID_GRAY_CURSOR] = {0, 3, 2},
};

static u8 CreateShopMenu(u8 martType)
{
    int numMenuItems;

    LockPlayerFieldControls();
    sMartInfo.martType = martType;

    if (martType == MART_TYPE_NORMAL)
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuyQuit, ARRAY_COUNT(sShopMenuActions_BuyQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuyQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuyQuit);
    }
    else
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuyQuit, ARRAY_COUNT(sShopMenuActions_BuyQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuyQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuyQuit);
    }

    SetStandardWindowBorderStyle(sMartInfo.windowId, FALSE);
    PrintMenuTable(sMartInfo.windowId, numMenuItems, sMartInfo.menuActions);
    InitMenuInUpperLeftCornerNormal(sMartInfo.windowId, numMenuItems, 0);
    PutWindowTilemap(sMartInfo.windowId);
    CopyWindowToVram(sMartInfo.windowId, COPYWIN_MAP);

    return CreateTask(Task_ShopMenu, 8);
}

static void SetShopMenuCallback(void (*callback)(void))
{
    sMartInfo.callback = callback;
}

static void SetShopItemsForSale(const u16 *items)
{
    u16 i = 0;

    sMartInfo.itemList = items;
    sMartInfo.priceList = NULL;
    sMartInfo.itemCount = 0;

    // Read items until ITEM_NONE / DECOR_NONE is reached
    while (sMartInfo.itemList[i])
    {
        sMartInfo.itemCount++;
        i++;
    }
}

static void PrepareScottTmShopInventory(void)
{
    u16 poolItems[ARRAY_COUNT(sScottTmPool)] = {0};
    u16 poolSize = 0;
    u16 i;

    for (i = 0; sScottTmPool[i] != ITEM_NONE; i++)
        poolItems[poolSize++] = sScottTmPool[i];

    // Select 5 random TMs
    for (i = 0; i < 5; i++)
    {
        u16 chosenIndex = Random() % poolSize;
        u16 j;
        sScottTmItemList[i] = poolItems[chosenIndex];
        for (j = chosenIndex; j < poolSize - 1; j++)
            poolItems[j] = poolItems[j + 1];
        poolSize--;
    }
    // Assign initial prices for TMs (all 4000). These are effectively dummy values for TMs
    // because GetMartItemPrice will calculate the actual dynamic price.
    for (i = 0; i < 5; i++)
        sScottTmPriceList[i] = 4000;

    // Add Invert option after the 5 TMs
    sScottTmItemList[5] = ITEM_SCOTT_TM_INVERT;
    sScottTmItemList[6] = ITEM_NONE;
    sScottTmPriceList[5] = 4000; // Invert fixed price
    sScottTmPriceList[6] = 0;
}

static u16 GetMartItemPrice(u16 itemId)
{
    u16 i;

    // If this is Scott's TM shop, calculate dynamic prices
    if (sIsScottTmShop)
    {
        // Handle special options first
        if (itemId == ITEM_SCOTT_TM_INVERT)
            return 4000; // Fixed price for Invert

        // Handle TMs
        for (i = 0; i < 5; i++) // Iterate over the 5 TM slots
        {
            if (sScottTmItemList[i] == itemId)
            {
                // If TM is already purchased, it effectively costs 0 (will show as Sold Out)
                if (sScottTmPurchased[i])
                    return 0;

                // Calculate dynamic price based on number of TMs already purchased
                switch (sScottTmPurchasedCount)
                {
                    case 0: return 4000;
                    case 1: return 2000;
                    case 2: return 1000;
                    case 3: return 500;
                    case 4: return 250;
                    case 5:
                    default: return 4000; // Should not happen, but a safe default
                }
            }
        }
    }

    // Original logic for non-Scott's shop items or items not found in Scott's list
    if (sMartInfo.priceList != NULL)
    {
        for (i = 0; i < sMartInfo.itemCount; i++)
        {
            if (sMartInfo.itemList[i] == itemId)
                return sMartInfo.priceList[i];
        }
    }

    return GetItemPrice(itemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT);
}

static u16 GetScottTmPartner(u16 tmId)
{
    u16 i;
    for (i = 0; i < ARRAY_COUNT(sScottTmPartners); i++)
    {
        if (sScottTmPartners[i][0] == tmId)
            return sScottTmPartners[i][1];
        if (sScottTmPartners[i][1] == tmId)
            return sScottTmPartners[i][0];
    }
    return ITEM_NONE;
}

static void ScottTmInvert(u8 taskId)
{
    u16 i;
    // Subtract money
    RemoveMoney(&gSaveBlock1Ptr->money, sShopData->totalCost);
    PlaySE(SE_SHOP);
    PrintMoneyAmountInMoneyBox(WIN_MONEY, GetMoney(&gSaveBlock1Ptr->money), 0);

    // Swap each TM with its partner
    for (i = 0; i < 5; i++)
    {
        u16 partner = GetScottTmPartner(sScottTmItemList[i]);
        if (partner != ITEM_NONE)
            sScottTmItemList[i] = partner;
    }

    // Update the shop's item list pointer to reflect changes
    SetShopItemsForSale(sScottTmItemList);

    // Restore the Scott TM price table so the custom prices remain in the shop
    sMartInfo.priceList = sScottTmPriceList;
    // If the buy menu's list arrays exist, update their entries so the
    // displayed list reflects the inverted items immediately.
    if (sListMenuItems != NULL && sItemNames != NULL)
    {
        u16 k;
        for (k = 0; k < sMartInfo.itemCount; k++)
            BuyMenuSetListEntry(&sListMenuItems[k], sMartInfo.itemList[k], sItemNames[k]);
        StringCopy(sItemNames[k], gText_Cancel2);
        sListMenuItems[k].name = sItemNames[k];
        sListMenuItems[k].id = LIST_CANCEL;
    }

    // sScottTmPurchasedCount (price tier) is NOT reset as per requirements.
    // Mark Invert as purchased for this session.
    sScottTmInvertPurchased = TRUE;

    // Return to item list
    BuyMenuReturnToItemList(taskId);
}

static void Task_ShopMenu(u8 taskId)
{
    s8 inputCode = Menu_ProcessInputNoWrap();
    switch (inputCode)
    {
    case MENU_NOTHING_CHOSEN:
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        Task_HandleShopMenuQuit(taskId);
        break;
    default:
        sMartInfo.menuActions[inputCode].func.void_u8(taskId);
        break;
    }
}

#define tItemCount  data[1]
#define tItemId     data[5]
#define tListTaskId data[7]
#define tCallbackHi data[8]
#define tCallbackLo data[9]

static void Task_HandleShopMenuBuy(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tCallbackHi = (u32)CB2_InitBuyMenu >> 16;
    tCallbackLo = (u32)CB2_InitBuyMenu;
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

static void Task_HandleShopMenuSell(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tCallbackHi = (u32)CB2_GoToSellMenu >> 16;
    tCallbackLo = (u32)CB2_GoToSellMenu;
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

void CB2_ExitSellMenu(void)
{
    gFieldCallback = MapPostLoadHook_ReturnToShopMenu;
    SetMainCallback2(CB2_ReturnToField);
}

static void Task_HandleShopMenuQuit(u8 taskId)
{
    ClearStdWindowAndFrameToTransparent(sMartInfo.windowId, 2); // Incorrect use, making it not copy it to vram.
    RemoveWindow(sMartInfo.windowId);
    TryPutSmartShopperOnAir();
    UnlockPlayerFieldControls();
    DestroyTask(taskId);

    if (sMartInfo.callback)
        sMartInfo.callback();
}

static void Task_GoToBuyOrSellMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2((MainCallback)((u16)tCallbackHi << 16 | (u16)tCallbackLo));
    }
}

static void MapPostLoadHook_ReturnToShopMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_ReturnToShopMenu, 8);
}

static void Task_ReturnToShopMenu(u8 taskId)
{
    if (IsWeatherNotFadingIn() == TRUE)
    {
        if (sMartInfo.martType == MART_TYPE_DECOR2)
            DisplayItemMessageOnField(taskId, gText_CanIHelpWithAnythingElse, ShowShopMenuAfterExitingBuyOrSellMenu);
        else
            DisplayItemMessageOnField(taskId, gText_AnythingElseICanHelp, ShowShopMenuAfterExitingBuyOrSellMenu);
    }
}

static void ShowShopMenuAfterExitingBuyOrSellMenu(u8 taskId)
{
    CreateShopMenu(sMartInfo.martType);
    DestroyTask(taskId);
}

static void CB2_BuyMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_BuyMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitBuyMenu(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        CpuFastFill(0, (void *)OAM, OAM_SIZE);
        ScanlineEffect_Stop();
        ResetTempTileDataBuffers();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        ClearScheduledBgCopiesToVram();
        sShopData = AllocZeroed(sizeof(struct ShopData));
        sShopData->scrollIndicatorsTaskId = TASK_NONE;
        sShopData->itemSpriteIds[0] = SPRITE_NONE;
        sShopData->itemSpriteIds[1] = SPRITE_NONE;
    memset(sShopData->pokemonIconSpriteIds, SPRITE_NONE, sizeof(sShopData->pokemonIconSpriteIds));
        BuyMenuBuildListMenuTemplate();
        BuyMenuInitBgs();
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(3, 0, 0, 0, 0x20, 0x20);
        BuyMenuInitWindows();
        BuyMenuDecompressBgGraphics();
        gMain.state++;
        break;
    case 1:
        if (!FreeTempTileDataBuffersIfPossible())
            gMain.state++;
        break;
    default:
        BuyMenuDrawGraphics();
        BuyMenuAddScrollIndicatorArrows();
        taskId = CreateTask(Task_BuyMenu, 8);
        gTasks[taskId].tListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_BuyMenu);
        SetMainCallback2(CB2_BuyMenu);
        break;
    }
}

static void BuyMenuFreeMemory(void)
{
    Free(sShopData);
    Free(sListMenuItems);
    memset(sShopData->pokemonIconSpriteIds, SPRITE_NONE, sizeof(sShopData->pokemonIconSpriteIds));
    Free(sItemNames);
    FreeAllWindowBuffers();
}

static void BuyMenuBuildListMenuTemplate(void)
{
    u16 i;

    sListMenuItems = Alloc((sMartInfo.itemCount + 1) * sizeof(*sListMenuItems));
    sItemNames = Alloc((sMartInfo.itemCount + 1) * sizeof(*sItemNames));
    for (i = 0; i < sMartInfo.itemCount; i++)
        BuyMenuSetListEntry(&sListMenuItems[i], sMartInfo.itemList[i], sItemNames[i]);

    StringCopy(sItemNames[i], gText_Cancel2);
    sListMenuItems[i].name = sItemNames[i];
    sListMenuItems[i].id = LIST_CANCEL;

    gMultiuseListMenuTemplate = sShopBuyMenuListTemplate;
    gMultiuseListMenuTemplate.items = sListMenuItems;
    gMultiuseListMenuTemplate.totalItems = sMartInfo.itemCount + 1;
    if (gMultiuseListMenuTemplate.totalItems > MAX_ITEMS_SHOWN)
        gMultiuseListMenuTemplate.maxShowed = MAX_ITEMS_SHOWN;
    else
        gMultiuseListMenuTemplate.maxShowed = gMultiuseListMenuTemplate.totalItems;

    sShopData->itemsShowed = gMultiuseListMenuTemplate.maxShowed;
}

static void BuyMenuSetListEntry(struct ListMenuItem *menuItem, u16 item, u8 *name)
{
    if (sMartInfo.martType == MART_TYPE_NORMAL)
    {
        if (item == ITEM_SCOTT_TM_INVERT)
            StringCopy(name, gText_Invert);
        else
            CopyItemName(item, name);
    }
    else
        StringCopy(name, gDecorations[item].name);

    menuItem->name = name;
    menuItem->id = item;
}

static void BuyMenuPrintItemDescriptionAndShowItemIcon(s32 item, bool8 onInit, struct ListMenu *list)
{
    const u8 *description;
    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    if (item != LIST_CANCEL)
        BuyMenuAddItemIcon(item, sShopData->iconSlot);
    else
        BuyMenuAddItemIcon(ITEM_LIST_END, sShopData->iconSlot);

    BuyMenuRemoveItemIcon(item, sShopData->iconSlot ^ 1);
    sShopData->iconSlot ^= 1;
    if (item != LIST_CANCEL)
    {
        if (sMartInfo.martType == MART_TYPE_NORMAL)
        {
            if (item == ITEM_SCOTT_TM_INVERT)
                description = gText_InvertDescription;
            else
                description = GetItemDescription(item);
        }
        else
            description = gDecorations[item].description;
    }
    else
    {
        description = gText_QuitShopping;
        if (VarGet(VAR_POWER_TM_CLERK) == 1)
        {
            u8 i;
            for (i = 0; i < 10; i++)
            {
                if (sShopData->pokemonIconSpriteIds[i] != SPRITE_NONE)
                    FreeAndDestroyMonIconSprite(&gSprites[sShopData->pokemonIconSpriteIds[i]]);
            }
        }
    }

    FillWindowPixelBuffer(WIN_ITEM_DESCRIPTION, PIXEL_FILL(0));
    // If the TM clerk feature is enabled, clear any existing mini icons when
    // hovering non-pokemon-item entries (Invert/Cancel) so the
    // description text doesn't overlap leftover sprites.
    if (VarGet(VAR_POWER_TM_CLERK) == 1)
    {
        if (item == LIST_CANCEL || item == ITEM_SCOTT_TM_INVERT)
        {
            u8 i;
            for (i = 0; i < 10; i++)
            {
                if (sShopData->pokemonIconSpriteIds[i] != SPRITE_NONE)
                    FreeAndDestroyMonIconSprite(&gSprites[sShopData->pokemonIconSpriteIds[i]]);
                sShopData->pokemonIconSpriteIds[i] = SPRITE_NONE;
            }
        }
    }
    if (VarGet(VAR_POWER_TM_CLERK) == 1 && item != LIST_CANCEL && item != ITEM_SCOTT_TM_INVERT)
    {
        CreateShopPokemonIconSprites(item);
        CopyWindowToVram(WIN_ITEM_DESCRIPTION, COPYWIN_GFX);
    }
    else
    {
        BuyMenuPrint(WIN_ITEM_DESCRIPTION, description, 3, 1, 0, COLORID_NORMAL);
    }
}

static void BuyMenuPrintPriceInList(u8 windowId, u32 itemId, u8 y)
{
    u8 x;

    if (itemId != LIST_CANCEL)
    {
        if (sMartInfo.martType == MART_TYPE_NORMAL)
        {
            u32 price;
            if (FlagGet(FLAG_FREE_SHOP))
                price = 0;
            else
                price = GetMartItemPrice(itemId);

            ConvertIntToDecimalStringN(
                gStringVar1,
                price,
                STR_CONV_MODE_LEFT_ALIGN,
                6);
        }
        else
        {
            ConvertIntToDecimalStringN(
                gStringVar1,
                gDecorations[itemId].price,
                STR_CONV_MODE_LEFT_ALIGN,
                6);
        }

        // Check if this is Scott's TM shop and if the TM has been purchased
        if (sIsScottTmShop)
        {
            u16 i;
            // Check for purchased TMs
            for (i = 0; i < 5; i++)
            {
                if (sScottTmItemList[i] == itemId && sScottTmPurchased[i])
                {
                    StringCopy(gStringVar4, gText_Purchased);
                    x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
                    AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
                    return;
                }
            }
            // Check if Invert has been purchased
            if (itemId == ITEM_SCOTT_TM_INVERT && sScottTmInvertPurchased)
            {
                StringCopy(gStringVar4, gText_Purchased);
                x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
                AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
                return;
            }
        }
        if (GetItemImportance(itemId) && (CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1)))
            StringCopy(gStringVar4, gText_SoldOut);
        else
            StringExpandPlaceholders(gStringVar4, gText_PokedollarVar1);
        x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
        AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
    }
}

static void CreateShopPokemonIconSprites(u16 itemId)
{
    LoadMonIconPalettes();

    u32 i, j;
    u8 spriteId;
    u8 count = 0;
    u16 move = ItemIdToBattleMoveId(itemId); // This is correct
    struct Pokemon tempMon;

    for (i = 0; i < 10; i++)
    {
        if (sShopData->pokemonIconSpriteIds[i] != SPRITE_NONE)
            FreeAndDestroyMonIconSprite(&gSprites[sShopData->pokemonIconSpriteIds[i]]);
        sShopData->pokemonIconSpriteIds[i] = SPRITE_NONE;
    }

    // Check party Pokemon first
    for (i = 0; i < gPlayerPartyCount && count < 10; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        u16 hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
        if (species != SPECIES_NONE && hp != 0 && CanLearnTeachableMove(species, move))
        {
            u16 x = 16 + (count % 4) * 24;
            u16 y = 112 + (count / 4) * 24;
            u32 personality = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY);
            spriteId = CreateMonIcon(species, SpriteCallbackDummy, x, y, 4, personality);
            sShopData->pokemonIconSpriteIds[count] = spriteId;
            count++;
        }
    }

    // Check PC boxes if we haven't reached 10 yet
    for (i = 0; i < TOTAL_BOXES_COUNT && count < 10; i++)
    {
        for (j = 0; j < IN_BOX_COUNT && count < 10; j++)
        {
            u16 species = GetBoxMonDataAt(i, j, MON_DATA_SPECIES);
            if (species != SPECIES_NONE)
            {
                BoxMonAtToMon(i, j, &tempMon);
                u16 hp = GetMonData(&tempMon, MON_DATA_HP);
                if (hp != 0 && CanLearnTeachableMove(species, move))
                {
                    u16 x = 16 + (count % 4) * 24;
                    u16 y = 112 + (count / 4) * 24;
                    u32 personality = GetMonData(&tempMon, MON_DATA_PERSONALITY);
                    spriteId = CreateMonIcon(species, SpriteCallbackDummy, x, y, 4, personality);
                    sShopData->pokemonIconSpriteIds[count] = spriteId;
                    count++;
                }
            }
        }
    }
}

static void BuyMenuAddScrollIndicatorArrows(void)
{
    if (sShopData->scrollIndicatorsTaskId == TASK_NONE && sMartInfo.itemCount + 1 > MAX_ITEMS_SHOWN)
    {
        sShopData->scrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            172,
            12,
            148,
            sMartInfo.itemCount - (MAX_ITEMS_SHOWN - 1),
            TAG_SCROLL_ARROW,
            TAG_SCROLL_ARROW,
            &sShopData->scrollOffset);
    }
}

static void BuyMenuRemoveScrollIndicatorArrows(void)
{
    if (sShopData->scrollIndicatorsTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sShopData->scrollIndicatorsTaskId);
        sShopData->scrollIndicatorsTaskId = TASK_NONE;
    }
}

static void BuyMenuPrintCursor(u8 scrollIndicatorsTaskId, u8 colorSet)
{
    u8 y = ListMenuGetYCoordForPrintingArrowCursor(scrollIndicatorsTaskId);
    BuyMenuPrint(WIN_ITEM_LIST, gText_SelectorArrow2, 0, y, 0, colorSet);
}

static void BuyMenuAddItemIcon(u16 item, u8 iconSlot)
{
    u8 spriteId;
    u8 *spriteIdPtr = &sShopData->itemSpriteIds[iconSlot];
    if (*spriteIdPtr != SPRITE_NONE)
        return;

    if (sMartInfo.martType == MART_TYPE_NORMAL || item == ITEM_LIST_END)
    {
        u16 iconItem = item;
        // Map special Scott TM shop options to actual items for icons
        if (item == ITEM_SCOTT_TM_INVERT)
            iconItem = ITEM_GIMMIGHOUL_COIN;

        spriteId = AddItemIconSprite(iconSlot + TAG_ITEM_ICON_BASE, iconSlot + TAG_ITEM_ICON_BASE, iconItem);
        if (spriteId != MAX_SPRITES)
        {
            *spriteIdPtr = spriteId;
            gSprites[spriteId].x2 = 24;
            gSprites[spriteId].y2 = 88;
        }
    }
    else
    {
        spriteId = AddDecorationIconObject(item, 20, 84, 1, iconSlot + TAG_ITEM_ICON_BASE, iconSlot + TAG_ITEM_ICON_BASE);
        if (spriteId != MAX_SPRITES)
            *spriteIdPtr = spriteId;
    }
}

static void BuyMenuRemoveItemIcon(u16 item, u8 iconSlot)
{
    u8 *spriteIdPtr = &sShopData->itemSpriteIds[iconSlot];
    if (*spriteIdPtr == SPRITE_NONE)
        return;

    FreeSpriteTilesByTag(iconSlot + TAG_ITEM_ICON_BASE);
    FreeSpritePaletteByTag(iconSlot + TAG_ITEM_ICON_BASE);
    DestroySprite(&gSprites[*spriteIdPtr]);
    *spriteIdPtr = SPRITE_NONE;
}

static void BuyMenuInitBgs(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sShopBuyMenuBgTemplates, ARRAY_COUNT(sShopBuyMenuBgTemplates));
    SetBgTilemapBuffer(1, sShopData->tilemapBuffers[1]);
    SetBgTilemapBuffer(2, sShopData->tilemapBuffers[3]);
    SetBgTilemapBuffer(3, sShopData->tilemapBuffers[2]);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void BuyMenuDecompressBgGraphics(void)
{
    DecompressAndCopyTileDataToVram(1, gShopMenu_Gfx, 0x3A0, 0x3E3, 0);
    DecompressDataWithHeaderWram(gShopMenu_Tilemap, sShopData->tilemapBuffers[0]);
    LoadPalette(gShopMenu_Pal, BG_PLTT_ID(SHOP_MENU_PALETTE_ID), PLTT_SIZE_4BPP);
}

static void BuyMenuInitWindows(void)
{
    InitWindows(sShopBuyMenuWindowTemplates);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(WIN_MONEY, 1, BG_PLTT_ID(13));
    LoadMessageBoxGfx(WIN_MONEY, 0xA, BG_PLTT_ID(14));
    PutWindowTilemap(WIN_MONEY);
    if (VarGet(VAR_POWER_TM_CLERK) == 1)
    {
        struct WindowTemplate template = {
            .bg = 0,
            .tilemapLeft = 1,
            .tilemapTop = 13,
            .width = 12,
            .height = 6,
            .paletteNum = 15,
            .baseBlock = 0x122,
        };
        AddWindow(&template);
    }
    PutWindowTilemap(WIN_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_DESCRIPTION);
}

static void BuyMenuPrint(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet)
{
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, x, y, 0, 0, sShopBuyMenuTextColors[colorSet], speed, text);
}

static void BuyMenuDisplayMessage(u8 taskId, const u8 *text, TaskFunc callback)
{
    DisplayMessageAndContinueTask(taskId, WIN_MESSAGE, 10, 14, FONT_NORMAL, GetPlayerTextSpeedDelay(), text, callback);
    ScheduleBgCopyTilemapToVram(0);
}

static void BuyMenuDrawGraphics(void)
{
    BuyMenuDrawMapGraphics();
    BuyMenuCopyMenuBgToBg1TilemapBuffer();
    AddMoneyLabelObject(19, 11);
    PrintMoneyAmountInMoneyBoxWithBorder(WIN_MONEY, 1, 13, GetMoney(&gSaveBlock1Ptr->money));
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);
    ScheduleBgCopyTilemapToVram(3);
}

static void BuyMenuDrawMapGraphics(void)
{
    BuyMenuCollectObjectEventData();
    BuyMenuDrawObjectEvents();
    BuyMenuDrawMapBg();
}

static void BuyMenuDrawMapBg(void)
{
    s16 i, j;
    s16 x, y;
    const struct MapLayout *mapLayout;
    u16 metatile;
    u8 metatileLayerType;

    mapLayout = gMapHeader.mapLayout;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    x -= 4;
    y -= 4;

    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 15; i++)
        {
            metatile = MapGridGetMetatileIdAt(x + i, y + j);
            if (BuyMenuCheckForOverlapWithMenuBg(i, j) == TRUE)
                metatileLayerType = MapGridGetMetatileLayerTypeAt(x + i, y + j);
            else
                metatileLayerType = METATILE_LAYER_TYPE_COVERED;

            if (metatile < NUM_METATILES_IN_PRIMARY)
                BuyMenuDrawMapMetatile(i, j, mapLayout->primaryTileset->metatiles + metatile * NUM_TILES_PER_METATILE, metatileLayerType);
            else
                BuyMenuDrawMapMetatile(i, j, mapLayout->secondaryTileset->metatiles + ((metatile - NUM_METATILES_IN_PRIMARY) * NUM_TILES_PER_METATILE), metatileLayerType);
        }
    }
}

static void BuyMenuDrawMapMetatile(s16 x, s16 y, const u16 *src, u8 metatileLayerType)
{
    u16 offset1 = x * 2;
    u16 offset2 = y * 64;

    switch (metatileLayerType)
    {
    case METATILE_LAYER_TYPE_NORMAL:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[3], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[1], offset1, offset2, src + 4);
        break;
    case METATILE_LAYER_TYPE_COVERED:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[2], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[3], offset1, offset2, src + 4);
        break;
    case METATILE_LAYER_TYPE_SPLIT:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[2], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[1], offset1, offset2, src + 4);
        break;
    }
}

static void BuyMenuDrawMapMetatileLayer(u16 *dest, s16 offset1, s16 offset2, const u16 *src)
{
    // This function draws a whole 2x2 metatile.
    dest[offset1 + offset2] = src[0]; // top left
    dest[offset1 + offset2 + 1] = src[1]; // top right
    dest[offset1 + offset2 + 32] = src[2]; // bottom left
    dest[offset1 + offset2 + 33] = src[3]; // bottom right
}

static void BuyMenuCollectObjectEventData(void)
{
    s16 facingX;
    s16 facingY;
    u8 y;
    u8 x;
    u8 numObjects = 0;

    GetXYCoordsOneStepInFrontOfPlayer(&facingX, &facingY);

    for (y = 0; y < OBJECT_EVENTS_COUNT; y++)
        sShopData->viewportObjects[y][OBJ_EVENT_ID] = OBJECT_EVENTS_COUNT;

    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 7; x++)
        {
            u8 objEventId = GetObjectEventIdByXY(facingX - 4 + x, facingY - 2 + y);

            // skip if invalid or an overworld pokemon that is not following the player
            if (objEventId != OBJECT_EVENTS_COUNT && !(gObjectEvents[objEventId].active && gObjectEvents[objEventId].graphicsId & OBJ_EVENT_MON && gObjectEvents[objEventId].localId != OBJ_EVENT_ID_FOLLOWER))
            {
                sShopData->viewportObjects[numObjects][OBJ_EVENT_ID] = objEventId;
                sShopData->viewportObjects[numObjects][X_COORD] = x;
                sShopData->viewportObjects[numObjects][Y_COORD] = y;
                sShopData->viewportObjects[numObjects][LAYER_TYPE] = MapGridGetMetatileLayerTypeAt(facingX - 4 + x, facingY - 2 + y);

                switch (gObjectEvents[objEventId].facingDirection)
                {
                case DIR_SOUTH:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_SOUTH;
                    break;
                case DIR_NORTH:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_NORTH;
                    break;
                case DIR_WEST:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_WEST;
                    break;
                case DIR_EAST:
                default:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_EAST;
                    break;
                }
                numObjects++;
            }
        }
    }
}

static void BuyMenuDrawObjectEvents(void)
{
    u8 i;
    u8 spriteId;
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    u8 weatherTemp = gWeatherPtr->palProcessingState;

    // This function runs during fadeout, so the weather palette processing state must be temporarily changed,
    // so that time-blending will work properly
    if (weatherTemp == WEATHER_PAL_STATE_SCREEN_FADING_OUT)
        gWeatherPtr->palProcessingState = WEATHER_PAL_STATE_IDLE;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (sShopData->viewportObjects[i][OBJ_EVENT_ID] == OBJECT_EVENTS_COUNT)
            continue;

        u8 objEventId = sShopData->viewportObjects[i][OBJ_EVENT_ID];
        u16 graphicsId = gObjectEvents[objEventId].graphicsId;

        if (objEventId == gPlayerAvatar.objectEventId)
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
                graphicsId = OBJ_EVENT_GFX_BRENDAN_NORMAL;
            else
                graphicsId = OBJ_EVENT_GFX_MAY_NORMAL;
        }

        graphicsInfo = GetObjectEventGraphicsInfo(graphicsId);

        spriteId = CreateObjectGraphicsSprite(
            graphicsId,
            SpriteCallbackDummy,
            (u16)sShopData->viewportObjects[i][X_COORD] * 16 + 8,
            (u16)sShopData->viewportObjects[i][Y_COORD] * 16 + 48 - graphicsInfo->height / 2,
            2);

        if (objEventId == gPlayerAvatar.objectEventId)
        {
            const u16 *palette = GetPlayerObjectEventPaletteData(gSaveBlock2Ptr->playerGender);
            if (palette != NULL)
            {
                LoadPalette(palette, OBJ_PLTT_ID(gSprites[spriteId].oam.paletteNum), PLTT_SIZE_4BPP);
                UpdateSpritePaletteWithWeather(gSprites[spriteId].oam.paletteNum, FALSE);
            }
        }

        if (BuyMenuCheckIfObjectEventOverlapsMenuBg(sShopData->viewportObjects[i]) == TRUE)
        {
            gSprites[spriteId].subspriteTableNum = 4;
            gSprites[spriteId].subspriteMode = SUBSPRITES_ON;
        }

        StartSpriteAnim(&gSprites[spriteId], sShopData->viewportObjects[i][ANIM_NUM]);
    }

    gWeatherPtr->palProcessingState = weatherTemp; // restore weather state
    CpuFastCopy(gPlttBufferFaded + 16*16, gPlttBufferUnfaded + 16*16, PLTT_BUFFER_SIZE);
}

static bool8 BuyMenuCheckIfObjectEventOverlapsMenuBg(s16 *object)
{
    if (!BuyMenuCheckForOverlapWithMenuBg(object[X_COORD], object[Y_COORD] + 2) && object[LAYER_TYPE] != METATILE_LAYER_TYPE_COVERED)
        return TRUE;
    else
        return FALSE;
}

static void BuyMenuCopyMenuBgToBg1TilemapBuffer(void)
{
    s16 i;
    u16 *dest = sShopData->tilemapBuffers[1];
    const u16 *src = sShopData->tilemapBuffers[0];

    for (i = 0; i < 1024; i++)
    {
        if (src[i] != 0)
            dest[i] = src[i] + ((SHOP_MENU_PALETTE_ID << 12) | 0x3E3);
    }
}

static bool8 BuyMenuCheckForOverlapWithMenuBg(int x, int y)
{
    const u16 *metatile = sShopData->tilemapBuffers[0];
    int offset1 = x * 2;
    int offset2 = y * 64;

    if (metatile[offset2 + offset1] == 0 &&
        metatile[offset2 + offset1 + 32] == 0 &&
        metatile[offset2 + offset1 + 1] == 0 &&
        metatile[offset2 + offset1 + 33] == 0)
        return TRUE;

    return FALSE;
}

static void Task_BuyMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        s32 itemId = ListMenu_ProcessInput(tListTaskId);
        ListMenuGetScrollAndRow(tListTaskId, &sShopData->scrollOffset, &sShopData->selectedRow);

        switch (itemId)
        {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_SELECT);
            ExitBuyMenu(taskId);
            break;
        default:
            PlaySE(SE_SELECT);
            tItemId = itemId;
            ClearWindowTilemap(WIN_ITEM_DESCRIPTION);
            BuyMenuRemoveScrollIndicatorArrows();
            BuyMenuPrintCursor(tListTaskId, COLORID_GRAY_CURSOR);

            if (sMartInfo.martType == MART_TYPE_NORMAL)
            {
                sShopData->totalCost = FlagGet(FLAG_FREE_SHOP) ? 0 : GetMartItemPrice(itemId);
            }
            else
                sShopData->totalCost = gDecorations[itemId].price;

            // Handle special Scott TM shop options
            if (sIsScottTmShop && itemId == ITEM_SCOTT_TM_INVERT)
            {
                if (sScottTmInvertPurchased)
                    BuyMenuDisplayMessage(taskId, gText_ThatItemIsSoldOut, BuyMenuReturnToItemList);
                else if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sShopData->totalCost))
                    BuyMenuDisplayMessage(taskId, gText_YouDontHaveMoney, BuyMenuReturnToItemList);
                else
                {
                    ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);
                    StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);
                    tItemCount = 1; // Invert is always a single purchase
                    BuyMenuDisplayMessage(taskId, gStringVar4, ScottTmInvert);
                }
            }
            // For TMs and other normal items in Scott's shop
            else if (GetItemImportance(itemId) && (CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1)))
                BuyMenuDisplayMessage(taskId, gText_ThatItemIsSoldOut, BuyMenuReturnToItemList);
            else if (sIsScottTmShop) // Check for TMs in Scott's shop (not Invert, not "important" item already checked)
            {
                u16 i;
                for (i = 0; i < 5; i++)
                {
                    if (sScottTmItemList[i] == itemId && sScottTmPurchased[i])
                    {
                        BuyMenuDisplayMessage(taskId, gText_ThatItemIsSoldOut, BuyMenuReturnToItemList);
                        break;
                    }
                }
                if (i < 5) { // Item was found and sold out
                    // Message already displayed, just return.
                } else if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sShopData->totalCost))
                {
                    BuyMenuDisplayMessage(taskId, gText_YouDontHaveMoney, BuyMenuReturnToItemList);
                }
                else // If not sold out and has money (it's a purchasable TM)
                {
                    // For Scott's TMs, always assume quantity 1 and go to confirm purchase
                    CopyItemName(itemId, gStringVar1);
                    ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);
                    StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);
                    tItemCount = 1; // Always buy 1 TM
                    if (FlagGet(FLAG_FREE_SHOP))
                        sShopData->totalCost = 0;
                    BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                }
            }
            // Original logic for normal item marts (not Scott's)
            else if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sShopData->totalCost))
            {
                BuyMenuDisplayMessage(taskId, gText_YouDontHaveMoney, BuyMenuReturnToItemList);
            }
            else
            {
                if (sMartInfo.martType == MART_TYPE_NORMAL)
                {
                    CopyItemName(itemId, gStringVar1);
                    if (GetItemImportance(itemId))
                    {
                        ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);
                        StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);
                        tItemCount = 1;
                    if (FlagGet(FLAG_FREE_SHOP))
                        sShopData->totalCost = 0;
                    else
                        sShopData->totalCost = GetMartItemPrice(tItemId) * tItemCount;
                        BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                    }
                    else if (GetItemPocket(itemId) == POCKET_TM_HM)
                    {
                        StringCopy(gStringVar2, GetMoveName(ItemIdToBattleMoveId(itemId)));
                        BuyMenuDisplayMessage(taskId, gText_Var1CertainlyHowMany2, Task_BuyHowManyDialogueInit);
                    }
                    else
                    {
                        BuyMenuDisplayMessage(taskId, gText_Var1CertainlyHowMany, Task_BuyHowManyDialogueInit);
                    }
                }
                else
                {
                    StringCopy(gStringVar1, gDecorations[itemId].name);
                    ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);

                    if (sMartInfo.martType == MART_TYPE_DECOR)
                        StringExpandPlaceholders(gStringVar4, gText_Var1IsItThatllBeVar2);
                    else // MART_TYPE_DECOR2
                        StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);

                    BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                }
            }
            break;
        }
    }
}

static void Task_BuyHowManyDialogueInit(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    u16 quantityInBag = CountTotalItemQuantityInBag(tItemId);
    u16 maxQuantity;

    DrawStdFrameWithCustomTileAndPalette(WIN_QUANTITY_IN_BAG, FALSE, 1, 13);
    ConvertIntToDecimalStringN(gStringVar1, quantityInBag, STR_CONV_MODE_RIGHT_ALIGN, MAX_ITEM_DIGITS + 1);
    StringExpandPlaceholders(gStringVar4, gText_InBagVar1);
    BuyMenuPrint(WIN_QUANTITY_IN_BAG, gStringVar4, 0, 1, 0, COLORID_NORMAL);
    tItemCount = 1;
    DrawStdFrameWithCustomTileAndPalette(WIN_QUANTITY_PRICE, FALSE, 1, 13);
    BuyMenuPrintItemQuantityAndPrice(taskId);
    ScheduleBgCopyTilemapToVram(0);

    // Avoid division by zero in-case something costs 0 pokedollars.
    if (sShopData->totalCost == 0)
        maxQuantity = MAX_BAG_ITEM_CAPACITY;
    else
        maxQuantity = GetMoney(&gSaveBlock1Ptr->money) / sShopData->totalCost;

    if (maxQuantity > MAX_BAG_ITEM_CAPACITY)
        sShopData->maxQuantity = MAX_BAG_ITEM_CAPACITY;
    else
        sShopData->maxQuantity = maxQuantity;

    gTasks[taskId].func = Task_BuyHowManyDialogueHandleInput;
}

static void Task_BuyHowManyDialogueHandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, sShopData->maxQuantity) == TRUE)
    {
        if (FlagGet(FLAG_FREE_SHOP))
            sShopData->totalCost = 0;
        else
            sShopData->totalCost = (GetItemPrice(tItemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT)) * tItemCount;
        BuyMenuPrintItemQuantityAndPrice(taskId);
    }
    else
    {
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_PRICE, FALSE);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_IN_BAG, FALSE);
            ClearWindowTilemap(WIN_QUANTITY_PRICE);
            ClearWindowTilemap(WIN_QUANTITY_IN_BAG);
            PutWindowTilemap(WIN_ITEM_LIST);
            CopyItemName(tItemId, gStringVar1);
            ConvertIntToDecimalStringN(gStringVar2, tItemCount, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
            ConvertIntToDecimalStringN(gStringVar3, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
            BuyMenuDisplayMessage(taskId, gText_Var1AndYouWantedVar2, BuyMenuConfirmPurchase);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_PRICE, FALSE);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_IN_BAG, FALSE);
            ClearWindowTilemap(WIN_QUANTITY_PRICE);
            ClearWindowTilemap(WIN_QUANTITY_IN_BAG);
            BuyMenuReturnToItemList(taskId);
        }
    }
}

static void BuyMenuConfirmPurchase(u8 taskId)
{
    CreateYesNoMenuWithCallbacks(taskId, &sShopBuyMenuYesNoWindowTemplates, 1, 0, 0, 1, 13, &sShopPurchaseYesNoFuncs);
}

static void BuyMenuTryMakePurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    PutWindowTilemap(WIN_ITEM_LIST);

    if (sMartInfo.martType == MART_TYPE_NORMAL)
    {
        if (AddBagItem(tItemId, tItemCount) == TRUE)
        {
            GetSetItemObtained(tItemId, FLAG_SET_ITEM_OBTAINED);
            // Mark TM as purchased in Scott's shop and update purchase count
            if (sIsScottTmShop)
            {
                u16 i;
                for (i = 0; i < 6; i++) // Only for the 6 TMs
                {
                    if (sScottTmItemList[i] == tItemId)
                    {
                        if (!sScottTmPurchased[i]) // Only increment if not already purchased
                        {
                            sScottTmPurchased[i] = TRUE;
                            sScottTmPurchasedCount++; // Increment count of TMs bought
                        }
                        break;
                    }
                }
            }
            RecordItemPurchase(taskId);
            BuyMenuDisplayMessage(taskId, gText_HereYouGoThankYou, BuyMenuSubtractMoney);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_NoMoreRoomForThis, BuyMenuReturnToItemList);
        }
    }
    else
    {
        if (DecorationAdd(tItemId))
        {
            if (sMartInfo.martType == MART_TYPE_DECOR)
                BuyMenuDisplayMessage(taskId, gText_ThankYouIllSendItHome, BuyMenuSubtractMoney);
            else // MART_TYPE_DECOR2
                BuyMenuDisplayMessage(taskId, gText_ThanksIllSendItHome, BuyMenuSubtractMoney);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_SpaceForVar1Full, BuyMenuReturnToItemList);
        }
    }
}

static void BuyMenuSubtractMoney(u8 taskId)
{
    IncrementGameStat(GAME_STAT_SHOPPED);
    RemoveMoney(&gSaveBlock1Ptr->money, sShopData->totalCost);
    PlaySE(SE_SHOP);
    PrintMoneyAmountInMoneyBox(WIN_MONEY, GetMoney(&gSaveBlock1Ptr->money), 0);

    if (sMartInfo.martType == MART_TYPE_NORMAL)
        gTasks[taskId].func = Task_ReturnToItemListAfterItemPurchase;
    else
        gTasks[taskId].func = Task_ReturnToItemListAfterDecorationPurchase;
}

static void Task_ReturnToItemListAfterItemPurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        u16 premierBallsToAdd = tItemCount / 10;
        if (premierBallsToAdd >= 1
         && ((I_PREMIER_BALL_BONUS <= GEN_7 && tItemId == ITEM_POKE_BALL)
          || (I_PREMIER_BALL_BONUS >= GEN_8 && (GetItemPocket(tItemId) == POCKET_POKE_BALLS))))
        {
            u32 spaceAvailable = GetFreeSpaceForItemInBag(ITEM_PREMIER_BALL);
            if (spaceAvailable < premierBallsToAdd)
                premierBallsToAdd = spaceAvailable;
        }
        else
        {
            premierBallsToAdd = 0;
        }

        PlaySE(SE_SELECT);
        AddBagItem(ITEM_PREMIER_BALL, premierBallsToAdd);
        if (premierBallsToAdd > 0)
        {
            ConvertIntToDecimalStringN(gStringVar1, premierBallsToAdd, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
            BuyMenuDisplayMessage(taskId, (premierBallsToAdd >= 2 ? gText_ThrowInPremierBalls : gText_ThrowInPremierBall), BuyMenuReturnToItemList);
        }
        else
        {
            BuyMenuReturnToItemList(taskId);
        }
    }
}

static void Task_ReturnToItemListAfterDecorationPurchase(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BuyMenuReturnToItemList(taskId);
    }
}

static void BuyMenuReturnToItemList(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    ClearDialogWindowAndFrameToTransparent(WIN_MESSAGE, FALSE);
    RedrawListMenu(tListTaskId);
    BuyMenuPrintCursor(tListTaskId, COLORID_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_DESCRIPTION);
    ScheduleBgCopyTilemapToVram(0);
    BuyMenuAddScrollIndicatorArrows();
    gTasks[taskId].func = Task_BuyMenu;
}

static void BuyMenuPrintItemQuantityAndPrice(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    FillWindowPixelBuffer(WIN_QUANTITY_PRICE, PIXEL_FILL(1));
    // Check if this is Scott's TM shop and if the item has been purchased
    if (sIsScottTmShop)
    {
        u16 i;
        bool8 itemIsPurchased = FALSE;

        // Check for TMs
        for (i = 0; i < 5; i++)
        {
            if (sScottTmItemList[i] == tItemId && sScottTmPurchased[i])
            {
                itemIsPurchased = TRUE;
                break;
            }
        }
        // Check for Invert
        if (tItemId == ITEM_SCOTT_TM_INVERT && sScottTmInvertPurchased)
            itemIsPurchased = TRUE;

        if (itemIsPurchased)
        {
            BuyMenuPrint(WIN_QUANTITY_PRICE, gText_Purchased, 0, 1, 0, COLORID_NORMAL);
            return;
        }
    }
    PrintMoneyAmount(WIN_QUANTITY_PRICE, CalculateMoneyTextHorizontalPosition(sShopData->totalCost), 1, sShopData->totalCost, TEXT_SKIP_DRAW);
    ConvertIntToDecimalStringN(gStringVar1, tItemCount, STR_CONV_MODE_LEADING_ZEROS, MAX_ITEM_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    BuyMenuPrint(WIN_QUANTITY_PRICE, gStringVar4, 0, 1, 0, COLORID_NORMAL);
}

static void ExitBuyMenu(u8 taskId)
{
    if (FlagGet(FLAG_IN_BASEMENT))
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
    else if (sIsScottTmShop)
        gFieldCallback = ScriptContext_Enable; // Skip "Anything else?" for Scott's shop
    else
        gFieldCallback = MapPostLoadHook_ReturnToShopMenu;

    sIsScottTmShop = FALSE;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_ExitBuyMenu;
}

static void Task_ExitBuyMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        RemoveMoneyLabelObject();
        if (VarGet(VAR_POWER_TM_CLERK) == 1)
        {
            u8 i;
            for (i = 0; i < 10; i++)
                if (sShopData->pokemonIconSpriteIds[i] != SPRITE_NONE)
                    DestroySprite(&gSprites[sShopData->pokemonIconSpriteIds[i]]);
            VarSet(VAR_POWER_TM_CLERK, 0);
        }
        BuyMenuFreeMemory();
        SetMainCallback2(CB2_ReturnToField);
        DestroyTask(taskId);
    }
}

static void ClearItemPurchases(void)
{
    sPurchaseHistoryId = 0;
    memset(gMartPurchaseHistory, 0, sizeof(gMartPurchaseHistory));
}

static void RecordItemPurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    u16 i;

    for (i = 0; i < ARRAY_COUNT(gMartPurchaseHistory); i++)
    {
        if (gMartPurchaseHistory[i].itemId == tItemId && gMartPurchaseHistory[i].quantity != 0)
        {
            if (gMartPurchaseHistory[i].quantity + tItemCount > 255)
                gMartPurchaseHistory[i].quantity = 255;
            else
                gMartPurchaseHistory[i].quantity += tItemCount;
            return;
        }
    }

    if (sPurchaseHistoryId < ARRAY_COUNT(gMartPurchaseHistory))
    {
        gMartPurchaseHistory[sPurchaseHistoryId].itemId = tItemId;
        gMartPurchaseHistory[sPurchaseHistoryId].quantity = tItemCount;
        sPurchaseHistoryId++;
    }
}

#undef tItemCount
#undef tItemId
#undef tListTaskId
#undef tCallbackHi
#undef tCallbackLo

void CreateScottTmShopMenu(void)
{
    u8 i;
    PrepareScottTmShopInventory();
    SetShopItemsForSale(sScottTmItemList);
    sMartInfo.priceList = sScottTmPriceList;
    ClearItemPurchases();
    SetShopMenuCallback(ScriptContext_Enable);
    LockPlayerFieldControls();
    sMartInfo.martType = MART_TYPE_NORMAL;
    sIsScottTmShop = TRUE;
    // Initialize purchase tracking for this session
    for (i = 0; i < 5; i++)
        sScottTmPurchased[i] = FALSE;
    sScottTmPurchasedCount = 0; // Initialize new counter
    sScottTmInvertPurchased = FALSE;
    VarSet(VAR_POWER_TM_CLERK, 1);
    CreateTask(Task_HandleShopMenuBuy, 8);
}

void CreatePokemartMenu(const u16 *itemsForSale)
{
    SetShopItemsForSale(itemsForSale);
    ClearItemPurchases();
    SetShopMenuCallback(ScriptContext_Enable);

    if (FlagGet(FLAG_IN_BASEMENT))
    {
        LockPlayerFieldControls();
        sMartInfo.martType = MART_TYPE_NORMAL;
        CreateTask(Task_HandleShopMenuBuy, 8);
    }
    else
    {
        CreateShopMenu(MART_TYPE_NORMAL);
    }
}

void CreateDecorationShop1Menu(const u16 *itemsForSale)
{
    SetShopItemsForSale(itemsForSale);
    SetShopMenuCallback(ScriptContext_Enable);

    if (FlagGet(FLAG_IN_BASEMENT))
    {
        LockPlayerFieldControls();
        sMartInfo.martType = MART_TYPE_DECOR;
        CreateTask(Task_HandleShopMenuBuy, 8);
    }
    else
    {
        CreateShopMenu(MART_TYPE_DECOR);
    }
}

void CreateDecorationShop2Menu(const u16 *itemsForSale)
{
    SetShopItemsForSale(itemsForSale);
    SetShopMenuCallback(ScriptContext_Enable);

    if (FlagGet(FLAG_IN_BASEMENT))
    {
        LockPlayerFieldControls();
        sMartInfo.martType = MART_TYPE_DECOR2;
        CreateTask(Task_HandleShopMenuBuy, 8);
    }
    else
    {
        CreateShopMenu(MART_TYPE_DECOR2);
    }
}

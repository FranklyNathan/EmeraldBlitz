#ifndef GUARD_SCRIPT_MENU_H
#define GUARD_SCRIPT_MENU_H

#include "list_menu.h"
#include "constants/script_menu.h"
#include "menu.h"

// The default size the stack for dynamic multichoice is initialized to
// If you try to push an element when the stack is full, it will be reallocated
// With increasing capacity of MULTICHOICE_DYNAMIC_STACK_INC

#define MULTICHOICE_DYNAMIC_STACK_SIZE 5
#define MULTICHOICE_DYNAMIC_STACK_INC 5

#define GIFT_MON_FINISH_ID 999
#define GIFT_MON_RANDOM_ID 1000
#define GIFT_MON_RAND_TEAM_ID 1001
#define GIFT_MON_TEAM_SIZE 8

extern const u8 *const gStdStrings[];

u8 GenerateRandomGiftTeam(struct ListMenuItem *items, u32 numItems, u16 *outTeam);
u16 GetRandomGiftEggSpecies(void);

// Draft team handed in by the website's embedded emulator at the fixed EWRAM
// address 0x0203F100 (see ".auto_obtain" in ld_script_modern.ld). Entries are
// national dex numbers; AUTO_OBTAIN_EGG_ID means a Mystery Egg.
#define AUTO_OBTAIN_MAGIC 0xB17A
#define AUTO_OBTAIN_MAX_MONS 12
#define AUTO_OBTAIN_EGG_ID 0xFFFF
struct AutoObtainRequest // 28 bytes
{
    vu16 magic; // AUTO_OBTAIN_MAGIC while a request is pending; cleared once consumed
    vu16 count;
    vu16 dexNums[AUTO_OBTAIN_MAX_MONS];
};
extern volatile struct AutoObtainRequest gAutoObtainRequest;
void GiveAutoObtainMons(void);

struct DynamicMultichoiceStack
{
    s32 top;
    u32 capacity;
    struct ListMenuItem *elements;
};

void MultichoiceDynamic_InitStack(u32 capacity);
void MultichoiceDynamic_ReallocStack(u32 newCapacity);
bool32 MultichoiceDynamic_StackFull(void);
bool32 MultichoiceDynamic_StackEmpty(void);
u32 MultichoiceDynamic_StackSize(void);
void MultichoiceDynamic_PushElement(struct ListMenuItem item);
struct ListMenuItem *MultichoiceDynamic_PopElement(void);
struct ListMenuItem *MultichoiceDynamic_PeekElement(void);
struct ListMenuItem *MultichoiceDynamic_PeekElementAt(u32 index);
void MultichoiceDynamic_DestroyStack(void);
bool8 ScriptMenu_MultichoiceDynamic(u8 left, u8 top, u8 argc, struct ListMenuItem *items, bool8 ignoreBPress, u8 maxBeforeScroll, u32 initialRow, u32 callbackSet);
bool8 ScriptMenu_Multichoice(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBPress);
bool8 ScriptMenu_MultichoiceWithDefault(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBPress, u8 defaultChoice);
void DrawMultichoiceMenuInternal(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBPress, u8 cursorPos, const struct MenuAction *actions, int count);
bool8 ScriptMenu_YesNo(u8 left, u8 top);
bool8 ScriptMenu_MultichoiceGrid(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBPress, u8 columnCount);
bool8 ScriptMenu_ShowPokemonPic(u16 species, u8 x, u8 y);
bool8 (*ScriptMenu_HidePokemonPic(void))(void);
int ConvertPixelWidthToTileWidth(int width);
u8 CreateWindowFromRect(u8 x, u8 y, u8 width, u8 height);
void ClearToTransparentAndRemoveWindow(u8 windowId);
int DisplayTextAndGetWidth(const u8 *str, int prevWidth);
int ScriptMenu_AdjustLeftCoordFromWidth(int left, int width);
bool16 ScriptMenu_CreatePCMultichoice(void);
void ScriptMenu_DisplayPCStartupPrompt(void);
void ScriptMenu_ClearDynMultichoice(void);
void ScriptMenu_AddDynmultichoice(const u8 *name, s32 id, s32 unused);
void SetIsGiftPokemonMenu(void);

#endif //GUARD_SCRIPT_MENU_H

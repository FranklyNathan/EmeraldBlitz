#ifndef GUARD_POKEDEX_AREA_SCREEN_H
#define GUARD_POKEDEX_AREA_SCREEN_H

#include "rtc.h"

extern u8 gAreaTimeOfDay;

enum PokedexAreaScreenState
{
    DEX_SHOW_AREA_SCREEN,
    DEX_UPDATE_AREA_SCREEN
};

void DisplayPokedexAreaScreen(u16 species, u8 *screenSwitchState, enum TimeOfDay timeOfDay, enum PokedexAreaScreenState areaState);
void ShowPokedexAreaScreen(u16 species, u8 *screenSwitchState);

void PokedexAreaScreen_UpdateAreaShadeBlend(u16 shadeBldArgLo, u16 shadeBldArgHi);
extern const u32 gAreaGlow_Gfx[];
extern const u32 gAreaGlow_Pal[8];

#endif // GUARD_POKEDEX_AREA_SCREEN_H

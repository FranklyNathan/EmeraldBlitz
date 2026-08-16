#ifndef GUARD_PRESET_SETTINGS_H
#define GUARD_PRESET_SETTINGS_H

#include "global.h"

// The frame number shown in the Options menu is 1-based ("TYPE 1" - "TYPE 40").
#define PRESET_FRAME(displayNumber) ((displayNumber) - 1)

#define PRESET_PALETTE_DEFAULT      0
#define PRESET_PALETTE_BLUE         1
#define PRESET_PALETTE_YELLOW       2
#define PRESET_PALETTE_ORANGE       3
#define PRESET_PALETTE_CYAN         4
#define PRESET_PALETTE_PINK         5
#define PRESET_PALETTE_SILVER       6
#define PRESET_PALETTE_GOLD         7
#define PRESET_PALETTE_PERIWINKLE   8
#define PRESET_PALETTE_FOREST       9
#define PRESET_PALETTE_SKY_BLUE     10

struct PlayerNamePreset
{
    const u8 name[PLAYER_NAME_LENGTH + 1]; // Matched case-insensitively against the player's name.
    u8 shuppetGuides;                      // OPTIONS_SHUPPET_GUIDES_[OFF/ON]
    u8 flygonDust;                         // 0 = off, 1 = on (stored in optionsBattleStyle)
    u8 windowFrameType;                    // 0-based; use PRESET_FRAME() with the in-menu number
    u8 playerPalette;                      // VAR_PLAYER_PALETTE_CHOICE; use PRESET_PALETTE_*
};

extern const struct PlayerNamePreset gPlayerNamePresets[];

// Applies the matching preset for the current player name, if one exists.
void ApplyPlayerNamePresetSettings(void);

#endif // GUARD_PRESET_SETTINGS_H

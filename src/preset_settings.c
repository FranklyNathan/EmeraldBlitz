#include "global.h"
#include "preset_settings.h"
#include "event_data.h"
#include "string_util.h"

// Presets are applied when a new game is created.
// To add a preset, just append a new entry below. The name is matched
// case-insensitively against the player's name.
const struct PlayerNamePreset gPlayerNamePresets[] =
{
    {
        .name = _("freez$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_ON,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(38),
        .playerPalette = PRESET_PALETTE_PINK,
    },
    {
        .name = _("Kch42$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(1),
        .playerPalette = PRESET_PALETTE_SILVER,
    },
    {
        .name = _("phony.$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(17),
        .playerPalette = PRESET_PALETTE_GOLD,
    },
    {
        .name = _("Jeans$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(30),
        .playerPalette = PRESET_PALETTE_BLUE,
    },
    {
        .name = _("Alboy$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(11),
        .playerPalette = PRESET_PALETTE_SILVER,
    },
    {
        .name = _("Kagami$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(33),
        .playerPalette = PRESET_PALETTE_CYAN,
    },
    {
        .name = _("swag$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(37),
        .playerPalette = PRESET_PALETTE_CYAN,
    },
    {
        .name = _("Johan$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(9),
        .playerPalette = PRESET_PALETTE_BLUE,
    },
    {
        .name = _("Human$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_ON,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(13),
        .playerPalette = PRESET_PALETTE_ORANGE,
    },
    {
        .name = _("Jari$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 1, // On
        .windowFrameType = PRESET_FRAME(35),
        .playerPalette = PRESET_PALETTE_SKY_BLUE,
    },
    {
        .name = _("DJ$"),
        .shuppetGuides = OPTIONS_SHUPPET_GUIDES_OFF,
        .flygonDust = 0, // Off
        .windowFrameType = PRESET_FRAME(5),
        .playerPalette = PRESET_PALETTE_YELLOW,
    },
};

static const struct PlayerNamePreset *FindPlayerNamePreset(const u8 *playerName)
{
    u8 upperPlayerName[PLAYER_NAME_LENGTH + 1];
    u8 upperPresetName[PLAYER_NAME_LENGTH + 1];
    u32 i;

    StringCopyUppercase(upperPlayerName, playerName);

    for (i = 0; i < ARRAY_COUNT(gPlayerNamePresets); i++)
    {
        StringCopyUppercase(upperPresetName, gPlayerNamePresets[i].name);
        if (StringCompare(upperPlayerName, upperPresetName) == 0)
            return &gPlayerNamePresets[i];
    }

    return NULL;
}

void ApplyPlayerNamePresetSettings(void)
{
    const struct PlayerNamePreset *preset = FindPlayerNamePreset(gSaveBlock2Ptr->playerName);

    if (preset == NULL)
        return;

    gSaveBlock2Ptr->optionsShuppetGuides = preset->shuppetGuides;
    gSaveBlock2Ptr->optionsBattleStyle = preset->flygonDust;
    gSaveBlock2Ptr->optionsWindowFrameType = preset->windowFrameType;
    VarSet(VAR_PLAYER_PALETTE_CHOICE, preset->playerPalette);
}

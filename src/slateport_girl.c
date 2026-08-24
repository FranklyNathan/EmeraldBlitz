#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "string_util.h"
#include "event_object_movement.h"

void DeleteMove(struct Pokemon *mon, u32 move);

bool8 IsEeveelution(u16 species)
{
    switch (species)
    {
    case SPECIES_VAPOREON:
    case SPECIES_JOLTEON:
    case SPECIES_FLAREON:
    case SPECIES_ESPEON:
    case SPECIES_UMBREON:
    case SPECIES_LEAFEON:
    case SPECIES_GLACEON:
    case SPECIES_SYLVEON:
        return TRUE;
    }
    return FALSE;
}

void CheckPartyForEeveelution(void)
{
    u8 i;
    u16 species;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
        if (IsEeveelution(species))
        {
            gSpecialVar_Result = TRUE;
            VarSet(VAR_0x8004, i);
            return;
        }
    }
    gSpecialVar_Result = FALSE;
}

void DevolveEeveelution(void)
{
    u8 i, j;
    u16 species = SPECIES_EEVEE;
    u16 move;
    u8 partyIndex = VarGet(VAR_0x8004);
    struct Pokemon *mon = &gPlayerParty[partyIndex];
    u16 oldSpecies = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    bool8 updateNickname = FALSE;
    u16 movesToRemove[] = {
        MOVE_PURSUIT,
        MOVE_SCREECH,
        MOVE_SWORDS_DANCE,
        MOVE_BARRIER,
        MOVE_SCARY_FACE,
        MOVE_AGILITY,
        MOVE_PSYCH_UP,
        MOVE_WATER_GUN,
        MOVE_THUNDER_SHOCK,
        MOVE_EMBER,
        MOVE_FAIRY_WIND,
        MOVE_CONFUSION,
        MOVE_RAZOR_LEAF,
        MOVE_SNARL,
        MOVE_DRAINING_KISS,
        MOVE_LEECH_SEED,
        MOVE_CALM_MIND,
        MOVE_PSYCHIC,
        MOVE_MOONBLAST,
        MOVE_FLAMETHROWER,
        MOVE_THUNDERBOLT,
        MOVE_SURF,
        MOVE_ICE_BEAM,
        MOVE_BLIZZARD,
        MOVE_DISCHARGE,
        MOVE_OVERHEAT,
        MOVE_ICY_WIND
    };

    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    if (StringCompare(nickname, gSpeciesInfo[oldSpecies].speciesName) == 0)
    {
        updateNickname = TRUE;
    }

    SetMonData(mon, MON_DATA_SPECIES, &species);
    CalculateMonStats(mon);

    if (updateNickname)
    {
        SetMonData(mon, MON_DATA_NICKNAME, gSpeciesInfo[SPECIES_EEVEE].speciesName);
    }

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = GetMonData(mon, MON_DATA_MOVE1 + i, NULL);
        if (move == MOVE_NONE) continue;

        for (j = 0; j < ARRAY_COUNT(movesToRemove); j++)
        {
            if (move == movesToRemove[j])
            {
                DeleteMove(mon, move);
                i--; // Recheck this slot as moves shifted down
                break;
            }
        }
    }
    RemoveFollowingPokemon();
}
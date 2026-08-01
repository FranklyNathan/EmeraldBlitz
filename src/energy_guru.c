#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/moves.h"
#include "constants/species.h"
#include "constants/items.h"
#include "evolution_scene.h"
#include "overworld.h"

// Checks if a specific species meets the Energy Guru's criteria
// Criteria: Evolves via Level Up > 30 AND the target species can evolve again.
static u16 GetEnergyGuruEvolutionTarget(struct Pokemon *mon, u32 partyId)
{
    int i;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (evolutions == NULL)
        return SPECIES_NONE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        if (evolutions[i].method == EVO_LEVEL 
            && evolutions[i].param > 30
            && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, partyId, NULL, CHECK_EVO))
        {
            // Check if the target species can evolve further
            const struct Evolution *targetEvolutions = GetSpeciesEvolutions(evolutions[i].targetSpecies);
            if (targetEvolutions != NULL && targetEvolutions[0].method != EVOLUTIONS_END)
            {
                return evolutions[i].targetSpecies;
            }
        }
    }

    return SPECIES_NONE;
}

void CheckPartyForEnergyGuruMon(void)
{
    int i;
    struct Pokemon *mon;

    gSpecialVar_Result = FALSE;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        mon = &gPlayerParty[i];

        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetEnergyGuruEvolutionTarget(mon, i) != SPECIES_NONE)
        {
            gSpecialVar_Result = TRUE;
            return;
        }
    }
}

void CheckSelectedMonForEnergyGuru(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];

    gSpecialVar_Result = FALSE;

    if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
        return;

    if (GetEnergyGuruEvolutionTarget(mon, gSpecialVar_0x8004) != SPECIES_NONE)
    {
        gSpecialVar_Result = TRUE;
    }
}

void TriggerEnergyGuruEvolution(void)
{
    u16 targetSpecies;
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];

    targetSpecies = GetEnergyGuruEvolutionTarget(mon, gSpecialVar_0x8004);

    if (targetSpecies != SPECIES_NONE)
    {
        gCB2_AfterEvolution = CB2_ReturnToField;
        // Trigger evolution scene
        BeginEvolutionScene(mon, targetSpecies, TRUE, gSpecialVar_0x8004);
    }
}

// Checks if a specific species meets the Effort Ribbon Woman's criteria
// Criteria:
// 1. Current form didn't evolve from any pokemon (Base stage).
// 2. Evolves via Level Up > 36.
// 3. Target species cannot evolve further (Only evolves one more time).
static u16 GetEffortRibbonEvolutionTarget(struct Pokemon *mon, u32 partyId)
{
    int i;
    const struct Evolution *evolutions;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);

    // Condition 1: Current form didn't evolve from any pokemon
    if (GetSpeciesPreEvolution(species) != SPECIES_NONE)
        return SPECIES_NONE;

    evolutions = GetSpeciesEvolutions(species);
    if (evolutions == NULL)
        return SPECIES_NONE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        // Condition 2: Evolves via Level Up > 36
        if (evolutions[i].method == EVO_LEVEL 
            && evolutions[i].param > 36 
            && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, partyId, NULL, CHECK_EVO))
        {
            // Condition 3: Target species cannot evolve further
            const struct Evolution *targetEvolutions = GetSpeciesEvolutions(evolutions[i].targetSpecies);
            if (targetEvolutions == NULL || targetEvolutions[0].method == EVOLUTIONS_END)
            {
                return evolutions[i].targetSpecies;
            }
        }
    }

    return SPECIES_NONE;
}

void CheckPartyForEffortRibbonMon(void)
{
    int i;
    struct Pokemon *mon;

    gSpecialVar_Result = FALSE;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        mon = &gPlayerParty[i];

        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetEffortRibbonEvolutionTarget(mon, i) != SPECIES_NONE)
        {
            gSpecialVar_Result = TRUE;
            return;
        }
    }
}

void CheckSelectedMonForEffortRibbon(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];

    gSpecialVar_Result = FALSE;

    if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
        return;

    if (GetEffortRibbonEvolutionTarget(mon, gSpecialVar_0x8004) != SPECIES_NONE)
    {
        gSpecialVar_Result = TRUE;
    }
}

void TriggerEffortRibbonEvolution(void)
{
    u16 targetSpecies;
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];

    targetSpecies = GetEffortRibbonEvolutionTarget(mon, gSpecialVar_0x8004);

    if (targetSpecies != SPECIES_NONE)
    {
        gCB2_AfterEvolution = CB2_ReturnToField;
        // Trigger evolution scene
        BeginEvolutionScene(mon, targetSpecies, TRUE, gSpecialVar_0x8004);
    }
}
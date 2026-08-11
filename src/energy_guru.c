#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "constants/moves.h"
#include "constants/species.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "evolution_scene.h"
#include "overworld.h"
#include "pokemon_storage_system.h"
#include "party_menu.h"

static bool8 sDidSwap;
static u8 sOriginalBoxPos;
static struct Pokemon sSwappedPartyMon;

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
    struct Pokemon tempMon;

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

    for (i = 0; i < IN_BOX_COUNT; i++)
    {
        if (GetBoxMonData(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][i], MON_DATA_SANITY_HAS_SPECIES))
        {
            BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][i], &tempMon);
            if (!GetMonData(&tempMon, MON_DATA_IS_EGG, NULL) && GetEnergyGuruEvolutionTarget(&tempMon, PARTY_SIZE) != SPECIES_NONE)
            {
                gSpecialVar_Result = TRUE;
                return;
            }
        }
    }
}

void CheckSelectedMonForEnergyGuru(void)
{
    struct Pokemon tempMon;
    struct Pokemon *mon;
    u32 partyId;

    gSpecialVar_Result = FALSE;

    if (gSpecialVar_0x8004 >= PARTY_SIZE && !IsPcSlot(gSpecialVar_0x8004))
        return;

    if (IsPcSlot(gSpecialVar_0x8004))
    {
        u8 boxPos = GetPcSlotBoxPosition(gSpecialVar_0x8004);
        if (boxPos == 0xFF)
            return;
        BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos], &tempMon);
        mon = &tempMon;
        partyId = PARTY_SIZE;
    }
    else
    {
        mon = &gPlayerParty[gSpecialVar_0x8004];
        partyId = gSpecialVar_0x8004;
    }

    if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
        return;

    if (GetEnergyGuruEvolutionTarget(mon, partyId) != SPECIES_NONE)
        gSpecialVar_Result = TRUE;
}

static void DoSwapBackToPC(void)
{
    if (sDidSwap)
    {
        u8 partySlot = gSpecialVar_0x8004;
        struct BoxPokemon evolvedBox = gPlayerParty[partySlot].box;
        gPlayerParty[partySlot] = sSwappedPartyMon;
        gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][sOriginalBoxPos] = evolvedBox;
        sDidSwap = FALSE;
    }
}

static void PostEvolutionSwapBackToPC(void)
{
    DoSwapBackToPC();
    CB2_ReturnToField();
}

static bool8 WithdrawPcMonForEvolution(void)
{
    sDidSwap = FALSE;

    if (!IsPcSlot(gSpecialVar_0x8004))
        return TRUE;

    u8 boxPos = GetPcSlotBoxPosition(gSpecialVar_0x8004);
    if (boxPos == 0xFF)
        return FALSE;

    u8 partySlot = GetFirstEmptyPartySlot();
    if (partySlot >= PARTY_SIZE)
    {
        partySlot = PARTY_SIZE - 1;
        sSwappedPartyMon = gPlayerParty[partySlot];
        BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos], &gPlayerParty[partySlot]);
        gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos] = sSwappedPartyMon.box;
    }
    else
    {
        BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos], &gPlayerParty[partySlot]);
        ZeroBoxMonData(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos]);
    }
    CalculatePlayerPartyCount();
    gSpecialVar_0x8004 = partySlot;
    sOriginalBoxPos = boxPos;
    sDidSwap = TRUE;
    return TRUE;
}

void TriggerEnergyGuruEvolution(void)
{
    u16 targetSpecies;
    struct Pokemon *mon;

    if (!WithdrawPcMonForEvolution())
        return;

    mon = &gPlayerParty[gSpecialVar_0x8004];
    targetSpecies = GetEnergyGuruEvolutionTarget(mon, gSpecialVar_0x8004);

    if (targetSpecies != SPECIES_NONE)
    {
        gCB2_AfterEvolution = sDidSwap ? PostEvolutionSwapBackToPC : CB2_ReturnToField;
        BeginEvolutionScene(mon, targetSpecies, TRUE, gSpecialVar_0x8004);
    }
    else if (sDidSwap)
    {
        DoSwapBackToPC();
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
    struct Pokemon tempMon;

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

    for (i = 0; i < IN_BOX_COUNT; i++)
    {
        if (GetBoxMonData(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][i], MON_DATA_SANITY_HAS_SPECIES))
        {
            BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][i], &tempMon);
            if (!GetMonData(&tempMon, MON_DATA_IS_EGG, NULL) && GetEffortRibbonEvolutionTarget(&tempMon, PARTY_SIZE) != SPECIES_NONE)
            {
                gSpecialVar_Result = TRUE;
                return;
            }
        }
    }
}

void CheckSelectedMonForEffortRibbon(void)
{
    struct Pokemon tempMon;
    struct Pokemon *mon;
    u32 partyId;

    gSpecialVar_Result = FALSE;

    if (gSpecialVar_0x8004 >= PARTY_SIZE && !IsPcSlot(gSpecialVar_0x8004))
        return;

    if (IsPcSlot(gSpecialVar_0x8004))
    {
        u8 boxPos = GetPcSlotBoxPosition(gSpecialVar_0x8004);
        if (boxPos == 0xFF)
            return;
        BoxMonToMon(&gPokemonStoragePtr->boxes[PARTY_PC_BOX_ID][boxPos], &tempMon);
        mon = &tempMon;
        partyId = PARTY_SIZE;
    }
    else
    {
        mon = &gPlayerParty[gSpecialVar_0x8004];
        partyId = gSpecialVar_0x8004;
    }

    if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
        return;

    if (GetEffortRibbonEvolutionTarget(mon, partyId) != SPECIES_NONE)
        gSpecialVar_Result = TRUE;
}

void TriggerEffortRibbonEvolution(void)
{
    u16 targetSpecies;
    struct Pokemon *mon;

    if (!WithdrawPcMonForEvolution())
        return;

    mon = &gPlayerParty[gSpecialVar_0x8004];
    targetSpecies = GetEffortRibbonEvolutionTarget(mon, gSpecialVar_0x8004);

    if (targetSpecies != SPECIES_NONE)
    {
        gCB2_AfterEvolution = sDidSwap ? PostEvolutionSwapBackToPC : CB2_ReturnToField;
        BeginEvolutionScene(mon, targetSpecies, TRUE, gSpecialVar_0x8004);
    }
    else if (sDidSwap)
    {
        DoSwapBackToPC();
    }
}

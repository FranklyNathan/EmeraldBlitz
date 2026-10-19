#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "script.h"
#include "constants/items.h"
#include "constants/species.h"
#include "money.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "daycare.h"
#include "string_util.h"

void CB2_ReturnToFieldContinueScriptPlayMapMusic(void);

// VAR_0x8004 = Species to remove
// Returns: 0 = Removed and was alive, 1 = Removed and was fainted, 2 = Not found
void RemoveRentalMon(void)
{
    u16 speciesToRemove = VarGet(VAR_0x8004);
    int i;
    u16 species;
    u16 hp;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
        if (species == speciesToRemove)
        {
            hp = GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL);
            
            // Shift remaining mons
            int j;
            for (j = i; j < gPlayerPartyCount - 1; j++)
            {
                gPlayerParty[j] = gPlayerParty[j + 1];
            }
            // Clear last slot
            ZeroMonData(&gPlayerParty[gPlayerPartyCount - 1]);
            gPlayerPartyCount--;
            
            if (hp == 0)
                gSpecialVar_Result = 1; // Fainted
            else
                gSpecialVar_Result = 0; // Alive
            return;
        }
    }

    // Check PC
    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        int j;
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            species = GetBoxMonData(&gPokemonStoragePtr->boxes[i][j], MON_DATA_SPECIES, NULL);
            if (species == speciesToRemove)
            {
                struct Pokemon tempMon;

                BoxMonToMon(&gPokemonStoragePtr->boxes[i][j], &tempMon);
                if (tempMon.hp == 0)
                    gSpecialVar_Result = 1; // Fainted
                else
                    gSpecialVar_Result = 0; // Alive

                ZeroBoxMonAt(i, j);
                return;
            }
        }
    }

    // Check Day Care
    {
        struct DayCare *daycare = &gSaveBlock1Ptr->daycare;
        int j;
        for (j = 0; j < DAYCARE_MON_COUNT; j++)
        {
            if (GetBoxMonData(&daycare->mons[j].mon, MON_DATA_SPECIES, NULL) == speciesToRemove)
            {
                memset(&daycare->mons[j], 0, sizeof(struct DaycareMon));
                if (j == 0 && GetBoxMonData(&daycare->mons[1].mon, MON_DATA_SPECIES, NULL) != SPECIES_NONE)
                {
                    daycare->mons[0] = daycare->mons[1];
                    memset(&daycare->mons[1], 0, sizeof(struct DaycareMon));
                }
                gSpecialVar_Result = 3; // Found in Day Care
                return;
            }
        }
    }

    gSpecialVar_Result = 2; // Not found
}

static u16 CalculateRentalMonLevel(u16 badges)
{
    u16 level = 10;
    
    if (badges >= 7)
        level = 48;
    else if (badges >= 6)
        level = 42;
    else if (badges >= 5)
        level = 35;
    else if (badges >= 4)
        level = 32;
    else if (badges >= 3)
        level = 29;
    else if (badges >= 2)
        level = 24;
    else if (badges >= 1)
        level = 19;
    
    return level;
}

void GetRentalMonLevel(void)
{
    u16 badges = VarGet(VAR_0x8004); // Pass badge count in VAR_0x8004
    gSpecialVar_Result = CalculateRentalMonLevel(badges);
}

void ShowRentalMon(void)
{
    u16 species = VarGet(VAR_RENTAL_MON_OFFER);
    u16 badges = VarGet(VAR_BADGE_COUNT);
    u16 level = CalculateRentalMonLevel(badges);
    
    CreateMon(&gEnemyParty[0], species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    CalculateMonStats(&gEnemyParty[0]);
    
    ShowPokemonSummaryScreen(SUMMARY_MODE_SELECT_MOVE, &gEnemyParty[0], 0, 0, CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void GiveRentalMon(void)
{
    struct Pokemon *mon = &gEnemyParty[0];
    u8 count = CalculatePlayerPartyCount();

    if (count < PARTY_SIZE)
    {
        gPlayerParty[count] = *mon;
        gPlayerPartyCount = count + 1;
        gSpecialVar_Result = 0; // Added to party
    }
    else
    {
        u8 result = GiveMonToPlayer(mon);
        gSpecialVar_Result = result;
    }
}

void GenerateRentalOffer(void)
{
    u16 trainerId = (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];
    u16 badges = VarGet(VAR_BADGE_COUNT);
    // Deterministic seed based on Player ID and Badge Count.
    // This ensures the same species is offered until a badge is earned.
    u32 seed = (u32)trainerId + (badges * 127);
    gSpecialVar_Result = seed % 29;
}

void TakeAllMoney(void)
{
    u32 money = GetMoney(&gSaveBlock1Ptr->money);
    RemoveMoney(&gSaveBlock1Ptr->money, money);
    gSpecialVar_Result = money;
}

void BufferRentalCost(void)
{
    u16 count = VarGet(VAR_RENTAL_RETURN_COUNT);
    //u32 cost = 5000 + (count * 1000);
    u32 cost = 8000;
    ConvertIntToDecimalStringN(gStringVar1, cost, STR_CONV_MODE_LEFT_ALIGN, 6);
}

void CheckHasRentalCost(void)
{
    u16 count = VarGet(VAR_RENTAL_RETURN_COUNT);
    //u32 cost = 5000 + (count * 1000);
    u32 cost = 8000;
    if (GetMoney(&gSaveBlock1Ptr->money) >= cost)
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

void TakeRentalCost(void)
{
    u16 count = VarGet(VAR_RENTAL_RETURN_COUNT);
    //u32 cost = 5000 + (count * 1000);
    u32 cost = 8000;
    RemoveMoney(&gSaveBlock1Ptr->money, cost);
}

void HasEnoughMonsForBattle(void)
{
    int i, j;

    // Check Party for a non-fainted, non-egg mon
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
            && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, NULL)
            && GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) != 0)
        {
            gSpecialVar_Result = TRUE;
            return;
        }
    }

    // Check PC for any non-egg mon
    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            struct BoxPokemon *boxMon = &gPokemonStoragePtr->boxes[i][j];
            u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
            if (species != SPECIES_NONE && !GetBoxMonData(boxMon, MON_DATA_IS_EGG, NULL))
            {
                struct Pokemon tempMon;
                BoxMonToMon(boxMon, &tempMon);
                if (tempMon.hp != 0)
                {
                    gSpecialVar_Result = TRUE;
                    return;
                }
            }
        }
    }

    gSpecialVar_Result = FALSE;
}
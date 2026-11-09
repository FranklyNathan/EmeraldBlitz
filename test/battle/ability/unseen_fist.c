#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveMakesContact(MOVE_SCRATCH));
    ASSUME(!MoveMakesContact(MOVE_WATER_GUN));
    ASSUME(GetMoveEffect(MOVE_PROTECT) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_KINGS_SHIELD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_SPIKY_SHIELD) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_BANEFUL_BUNKER) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_BURNING_BULWARK) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_OBSTRUCT) == EFFECT_PROTECT);
    ASSUME(GetMoveEffect(MOVE_SILK_TRAP) == EFFECT_PROTECT);
}

SINGLE_BATTLE_TEST("Unseen Fist bypasses Protect with contact moves and deals full damage", s16 damage)
{
    u32 protect;

    PARAMETRIZE { protect = FALSE; }
    PARAMETRIZE { protect = TRUE; }

    GIVEN {
        PLAYER(SPECIES_URSHIFU) { Ability(ABILITY_UNSEEN_FIST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        if (protect)
            TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_SCRATCH); }
        else
            TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        if (protect)
            ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Unseen Fist doesn't bypass Protect with non-contact moves")
{
    GIVEN {
        PLAYER(SPECIES_URSHIFU) { Ability(ABILITY_UNSEEN_FIST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, opponent);
        MESSAGE("The opposing Wobbuffet protected itself!");
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
            HP_BAR(opponent);
        }
    }
}

SINGLE_BATTLE_TEST("Unseen Fist bypasses protect effects without triggering their contact effects")
{
    enum Move protectMove = MOVE_NONE;
    u8 loweredStat = 0;

    PARAMETRIZE { protectMove = MOVE_SPIKY_SHIELD;    loweredStat = 0; }
    PARAMETRIZE { protectMove = MOVE_KINGS_SHIELD;    loweredStat = STAT_ATK; }
    PARAMETRIZE { protectMove = MOVE_BANEFUL_BUNKER;  loweredStat = 0; }
    PARAMETRIZE { protectMove = MOVE_BURNING_BULWARK; loweredStat = 0; }
    PARAMETRIZE { protectMove = MOVE_OBSTRUCT;        loweredStat = STAT_DEF; }
    PARAMETRIZE { protectMove = MOVE_SILK_TRAP;       loweredStat = STAT_SPEED; }

    GIVEN {
        PLAYER(SPECIES_URSHIFU) { Ability(ABILITY_UNSEEN_FIST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, protectMove); MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, protectMove, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        NONE_OF {
            HP_BAR(player);
            STATUS_ICON(player, STATUS1_POISON);
            STATUS_ICON(player, STATUS1_BURN);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        }
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
        EXPECT_EQ(player->status1, STATUS1_NONE);
        if (loweredStat != 0)
            EXPECT_EQ(player->statStages[loweredStat], DEFAULT_STAT_STAGE);
    }
}

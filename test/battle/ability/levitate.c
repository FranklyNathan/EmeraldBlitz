#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Levitate activates when targeted by ground type moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_LUNATONE) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_LEVITATE);
        MESSAGE("Lunatone makes Ground-type moves miss with Levitate!");
    }
}

SINGLE_BATTLE_TEST("Levitate does not activate if protected")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_LUNATONE) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PROTECT); MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_LEVITATE);
            MESSAGE("Lunatone makes Ground-type moves miss with Levitate!");
        }
    }
}

SINGLE_BATTLE_TEST("Levitate does not activate on status moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SAND_ATTACK) == TYPE_GROUND);
        ASSUME(GetMoveCategory(MOVE_SAND_ATTACK) == DAMAGE_CATEGORY_STATUS);
        PLAYER(SPECIES_LUNATONE) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SAND_ATTACK); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_LEVITATE);
            MESSAGE("Lunatone makes Ground-type moves miss with Levitate!");
        }
    }
}

SINGLE_BATTLE_TEST("Levitate does not activate if attacked by an opponent with Mold Breaker")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_LUNATONE) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_TINKATON) { Ability(ABILITY_MOLD_BREAKER); }
    } WHEN {
        TURN { MOVE(player, MOVE_PROTECT); MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_LEVITATE);
            MESSAGE("Lunatone makes Ground-type moves miss with Levitate!");
        }
    }
}

DOUBLE_BATTLE_TEST("Levitate does not cause single remaining target to take higher damage")
{
    s16 damage[3];
    GIVEN {
        PLAYER(SPECIES_REGIROCK)  { Speed(1); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(4); }
        OPPONENT(SPECIES_LUNATONE) { Speed(3); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerRight, MOVE_CELEBRATE); MOVE(playerLeft, MOVE_EARTHQUAKE); }
        TURN { MOVE(playerRight, MOVE_MEMENTO, target:opponentLeft); MOVE(playerLeft, MOVE_EARTHQUAKE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, playerLeft);
        HP_BAR(playerRight, captureDamage: &damage[0]);
        HP_BAR(opponentRight, captureDamage: &damage[1]);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEMENTO, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, playerLeft);
        HP_BAR(opponentRight, captureDamage: &damage[2]);

    } THEN {
        EXPECT_EQ(damage[0], damage[1]);
        EXPECT_EQ(damage[1], damage[2]);
    }
}

AI_SINGLE_BATTLE_TEST("Levitate is seen correctly by switch AI")
{
    enum Ability ability = ABILITY_NONE, item = ITEM_NONE;

    PARAMETRIZE { ability = ABILITY_OWN_TEMPO, item = ITEM_NONE ; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER, item = ITEM_NONE ; }
    PARAMETRIZE { ability = ABILITY_MOLD_BREAKER, item = ITEM_ABILITY_SHIELD ; }

    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_TINKATON) { Ability(ability); Speed(3); }
        OPPONENT(SPECIES_PONYTA) { Level(1); Item(ITEM_EJECT_PACK); Moves(MOVE_OVERHEAT); Speed(4); } // Forces switchout
        OPPONENT(SPECIES_VIKAVOLT) { HP(1); Speed(1); Ability(ABILITY_LEVITATE); Moves(MOVE_FLAMETHROWER); Item(item); }
        OPPONENT(SPECIES_HYPNO) { Speed(1); Moves(MOVE_IRON_HEAD); }
    } WHEN {
        if ((ability == ABILITY_MOLD_BREAKER) && (item != ITEM_ABILITY_SHIELD))
            TURN { MOVE(player, MOVE_MUD_SLAP); EXPECT_SEND_OUT(opponent, 2); }
        else
            TURN { MOVE(player, MOVE_MUD_SLAP); EXPECT_SEND_OUT(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI avoids Ground moves against Levitate after the ability is revealed")
{
    PASSES_RANDOMLY(2, 3, RNG_AI_ABILITY);
    GIVEN {
        ASSUME(GetMoveType(MOVE_EARTHQUAKE) == TYPE_GROUND);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT);
        PLAYER(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_SWAMPERT) { Moves(MOVE_EARTHQUAKE, MOVE_SURF); }
    } WHEN {
        // The AI doesn't know the ability and may guess wrong, using a Ground move that gets blocked.
        TURN { EXPECT_MOVE(opponent, MOVE_EARTHQUAKE); }
        // Once Levitate is revealed it must stop spamming Earthquake.
        TURN { EXPECT_MOVE(opponent, MOVE_SURF); }
        TURN { EXPECT_MOVE(opponent, MOVE_SURF); }
        TURN { EXPECT_MOVE(opponent, MOVE_SURF); }
    } SCENE {
        MESSAGE("Bronzong makes Ground-type moves miss with Levitate!");
    }
}

AI_SINGLE_BATTLE_TEST("AI avoids Ground moves against Levitate when the attacker faints and a new attacker comes in")
{
    PASSES_RANDOMLY(2, 3, RNG_AI_ABILITY);
    GIVEN {
        ASSUME(GetMoveType(MOVE_EARTHQUAKE) == TYPE_GROUND);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT);
        PLAYER(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); Speed(2); HP(200); Moves(MOVE_IRON_HEAD, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_FLYGON) { Moves(MOVE_EARTHQUAKE); Speed(3); HP(1); }
        OPPONENT(SPECIES_RHYPERIOR) { Moves(MOVE_EARTHQUAKE, MOVE_STONE_EDGE); Speed(1); }
    } WHEN {
        // Turn 1: Flygon uses Earthquake (misses due to Levitate), then Bronzong KOs Flygon, Rhyperior comes in
        TURN { MOVE(player, MOVE_IRON_HEAD); EXPECT_MOVE(opponent, MOVE_EARTHQUAKE); EXPECT_SEND_OUT(opponent, 1); }
        // Turn 2: Rhyperior comes in - must avoid Earthquake now that Levitate is revealed.
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_STONE_EDGE); }
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_STONE_EDGE); }
    } SCENE {
        MESSAGE("Bronzong makes Ground-type moves miss with Levitate!");
    }
}

AI_SINGLE_BATTLE_TEST("AI avoids Ground moves against Levitate when attacker has EQ and Stone Edge (no faint)")
{
    PASSES_RANDOMLY(2, 3, RNG_AI_ABILITY);
    GIVEN {
        ASSUME(GetMoveType(MOVE_EARTHQUAKE) == TYPE_GROUND);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT);
        PLAYER(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); Speed(1); HP(200); }
        OPPONENT(SPECIES_RHYPERIOR) { Moves(MOVE_EARTHQUAKE, MOVE_STONE_EDGE); Speed(3); }
    } WHEN {
        // Turn 1: AI doesn't know Levitate, may guess wrong.
        TURN { EXPECT_MOVE(opponent, MOVE_EARTHQUAKE); }
        // Turn 2+: Once Levitate is revealed, must avoid Earthquake.
        TURN { EXPECT_MOVE(opponent, MOVE_STONE_EDGE); }
        TURN { EXPECT_MOVE(opponent, MOVE_STONE_EDGE); }
    } SCENE {
        MESSAGE("Bronzong makes Ground-type moves miss with Levitate!");
    }
}


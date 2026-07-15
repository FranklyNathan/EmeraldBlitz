#include "test/battle.h"

SINGLE_BATTLE_TEST("Protean resets when Mega Evolving")
{
    GIVEN {
        PLAYER(SPECIES_GRENINJA) { Ability(ABILITY_PROTEAN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_QUICK_ATTACK); } // Greninja becomes Normal type
        TURN { MOVE(player, MOVE_MEGA_EVOLUTION); MOVE(opponent, MOVE_CELEBRATE); } // Mega Evolve
        TURN { MOVE(player, MOVE_WATER_SHURIKEN); } // Should become Water type again
    } SCENE {
        // After first move, Protean should have activated
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, player);
        ABILITY_POPUP(player, ABILITY_PROTEAN);
        MESSAGE("Greninja's Protean transformed it into the Normal type!");

        // Mega evolution happens
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_EVOLUTION, player);

        // After mega evolution, Protean should reset and activate again
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_SHURIKEN, player);
        ABILITY_POPUP(player, ABILITY_PROTEAN);
        MESSAGE("Greninja's Protean transformed it into the Water type!");
    }
}

SINGLE_BATTLE_TEST("Protean resets when de-Mega Evolving")
{
    GIVEN {
        PLAYER(SPECIES_GRENINJA) { Ability(ABILITY_PROTEAN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_QUICK_ATTACK); } // Greninja becomes Normal type
        TURN { MOVE(player, MOVE_MEGA_EVOLUTION); MOVE(opponent, MOVE_CELEBRATE); } // Mega Evolve
        TURN { MOVE(player, MOVE_WATER_SHURIKEN); } // Should become Water type again
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); } // End of battle, de-mega
        TURN { MOVE(player, MOVE_TACKLE); } // Should become Normal type again
    } SCENE {
        // After first move, Protean should have activated
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, player);
        ABILITY_POPUP(player, ABILITY_PROTEAN);
        MESSAGE("Greninja's Protean transformed it into the Normal type!");

        // Mega evolution happens
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_EVOLUTION, player);

        // After mega evolution, Protean should reset and activate again
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_SHURIKEN, player);
        ABILITY_POPUP(player, ABILITY_PROTEAN);
        MESSAGE("Greninja's Protean transformed it into the Water type!");

        // After de-mega evolution (end of battle), Protean should reset and activate again
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        ABILITY_POPUP(player, ABILITY_PROTEAN);
        MESSAGE("Greninja's Protean transformed it into the Normal type!");
    }
}

#include "global.h"
#include "test/battle.h"

AI_SINGLE_BATTLE_TEST("AI favors Speed boosts that let it outspeed the target")
{
    u16 move;

    PARAMETRIZE { move = MOVE_AGILITY; }
    PARAMETRIZE { move = MOVE_AUTOTOMIZE; }
    PARAMETRIZE { move = MOVE_DRAGON_DANCE; }
    PARAMETRIZE { move = MOVE_QUIVER_DANCE; }
    PARAMETRIZE { move = MOVE_VICTORY_DANCE; }
    PARAMETRIZE { move = MOVE_SHIFT_GEAR; }
    PARAMETRIZE { move = MOVE_SHELL_SMASH; }
    PARAMETRIZE { move = MOVE_GEOMANCY; }
    PARAMETRIZE { move = MOVE_FILLET_AWAY; }
    PARAMETRIZE { move = MOVE_CLANGOROUS_SOUL; }
    PARAMETRIZE { move = MOVE_NO_RETREAT; }
    PARAMETRIZE { move = MOVE_TIDY_UP; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET) { Speed(140); Moves(MOVE_SCRATCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(move); }
    } WHEN {
        TURN { SCORE_GT_VAL(opponent, move, AI_SCORE_DEFAULT + 4); }
    }
}

AI_SINGLE_BATTLE_TEST("AI does not favor a Speed boost if it remains slower after boosting")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET) { Speed(151); Moves(MOVE_SCRATCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_AGILITY); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_AGILITY, AI_SCORE_DEFAULT + 4); }
    }
}

AI_SINGLE_BATTLE_TEST("AI does not favor a Speed boost if the target has shown a Speed-lowering move")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET) { Speed(130); Moves(MOVE_ICY_WIND); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_AGILITY); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_ICY_WIND);
            SCORE_EQ_VAL(opponent, MOVE_AGILITY, AI_SCORE_DEFAULT);
        }
    }
}
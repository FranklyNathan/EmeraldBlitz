#include "global.h"
#include "test/battle.h"

AI_SINGLE_BATTLE_TEST("AI avoids Ground moves when fooled by Illusion disguised as a Levitate mon")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT);
        PLAYER(SPECIES_ZOROARK) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_ROTOM) { Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_DUGTRIO) { Moves(MOVE_EARTHQUAKE, MOVE_IRON_HEAD); }
    } WHEN {
        TURN {
            EXPECT_MOVE(opponent, MOVE_IRON_HEAD);
            NOT_EXPECT_MOVE(opponent, MOVE_EARTHQUAKE);
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI does not fall for Illusion if it already knows the ability")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT);
        PLAYER(SPECIES_ZOROARK) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_ROTOM) { Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_DUGTRIO) { Moves(MOVE_EARTHQUAKE, MOVE_IRON_HEAD); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_IRON_HEAD); }
    } THEN {
        // Illusion is broken once the AI sees a move that does not match the disguise.
        EXPECT(gBattleHistory->abilities[0] != ABILITY_ILLUSION);
    }
}

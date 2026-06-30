EverGrandeCity_SpensersRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_SpensersRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SpensersRoom_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_SpensersRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_SpensersRoom_OnFrame
	.byte 0

EverGrandeCity_SpensersRoom_OnTransition:
	setflag FLAG_MET_SCOTT_IN_EVERGRANDE
	setflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	end

EverGrandeCity_SpensersRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SpensersRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 1, EverGrandeCity_SpensersRoom_EventScript_CloseDoor
	end

EverGrandeCity_SpensersRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_SpensersRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_SpensersRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_SpensersRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_SpensersRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_SpensersRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 0, EverGrandeCity_SpensersRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_SpensersRoom_EventScript_WalkInCloseDoor::
	setvar VAR_FORCEANIM, 1
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 1
	releaseall
	end

EverGrandeCity_SpensersRoom_EventScript_Spenser::
	lock
	faceplayer
	specialvar VAR_RESULT, Script_CheckPartyBelowLevelCap
	goto_if_eq VAR_RESULT, TRUE, EverGrandeCity_SpensersRoom_EventScript_NotReady
	goto_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SpensersRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_SpensersRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SPENSER, EverGrandeCity_SpensersRoom_Text_Defeat
	goto EverGrandeCity_SpensersRoom_EventScript_Defeated
	end

EverGrandeCity_SpensersRoom_EventScript_NotReady::
	msgbox EverGrandeCity_SpensersRoom_Text_NotReady, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SpensersRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_SpensersRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SpensersRoom_EventScript_Defeated::
	setvar VAR_FORCEANIM, 0
	recordtrainerwin TRAINER_SPENSER
	setflag FLAG_DEFEATED_ELITE_4_SIDNEY
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_SpensersRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	//turnobject LOCALID_PLAYER, DIR_SOUTH
    //forcesave
	release
	end

EverGrandeCity_SpensersRoom_Text_NotReady:
	.string "I look forward to our fight,\n"
	.string "but your POKéMON are not yet\p"
	.string "strong enough.\p"
	.string "Level up your POKéMON and return\n"
	.string "when you're ready.$"

EverGrandeCity_SpensersRoom_Text_IntroSpeech:
	.string "My physical being is with POKéMON,\n"
	.string "my mind is with POKéMON!\p"
	.string "Challenger, let us see if your heart\n"
	.string "beats as one with your partners!$"

EverGrandeCity_SpensersRoom_Text_Defeat:
	.string "Gwahahaha! You and your POKéMON\n"
	.string "are truly one!$"

EverGrandeCity_SpensersRoom_Text_PostBattleSpeech:
	.string "A marvelous battle!\p"
	.string "The next room holds your next trial.\n"
	.string "Go forth with your head held high!$"

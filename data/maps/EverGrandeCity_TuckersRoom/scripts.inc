EverGrandeCity_TuckersRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_TuckersRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_TuckersRoom_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_TuckersRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_TuckersRoom_OnFrame
	.byte 0

EverGrandeCity_TuckersRoom_OnTransition:
	end

EverGrandeCity_TuckersRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_GLACIA, EverGrandeCity_TuckersRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 3, EverGrandeCity_TuckersRoom_EventScript_CloseDoor
	end

EverGrandeCity_TuckersRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_TuckersRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_TuckersRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_TuckersRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_TuckersRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_TuckersRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 2, EverGrandeCity_TuckersRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_TuckersRoom_EventScript_WalkInCloseDoor::
	setvar VAR_FORCEANIM, 1
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 3
	releaseall
	end

EverGrandeCity_TuckersRoom_EventScript_Tucker::
	lock
	faceplayer
	specialvar VAR_RESULT, Script_CheckPartyBelowLevelCap
	goto_if_eq VAR_RESULT, TRUE, EverGrandeCity_TuckersRoom_EventScript_NotReady
	goto_if_set FLAG_DEFEATED_ELITE_4_GLACIA, EverGrandeCity_TuckersRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_TuckersRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TUCKER, EverGrandeCity_TuckersRoom_Text_Defeat
	goto EverGrandeCity_TuckersRoom_EventScript_Defeated
	end

EverGrandeCity_TuckersRoom_EventScript_NotReady::
	msgbox EverGrandeCity_TuckersRoom_Text_NotReady, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_TuckersRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_TuckersRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_TuckersRoom_EventScript_Defeated::
	setvar VAR_FORCEANIM, 0
	recordtrainerwin TRAINER_TUCKER
	setflag FLAG_DEFEATED_ELITE_4_GLACIA
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_TuckersRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	//turnobject LOCALID_PLAYER, DIR_SOUTH
	//forcesave
	release
	end

EverGrandeCity_TuckersRoom_Text_NotReady:
	.string "I look forward to our fight,\n"
	.string "but your POKéMON are not yet\p"
	.string "strong enough.\p"
	.string "Level up your POKéMON and return\n"
	.string "when you're ready.$"

EverGrandeCity_TuckersRoom_Text_IntroSpeech:
	.string "I am TUCKER, the DOME ACE!\p"
	.string "I've heard much about your battles.\n"
	.string "Now, let's see your star power shine!$"

EverGrandeCity_TuckersRoom_Text_Defeat:
	.string "The crowd is going wild for you!\n"
	.string "You've truly earned this victory.$"

EverGrandeCity_TuckersRoom_Text_PostBattleSpeech:
	.string "Advance to the next room.\p"
	.string "And there, confirm the truly fearsome\n"
	.string "side of the POKéMON LEAGUE.$"

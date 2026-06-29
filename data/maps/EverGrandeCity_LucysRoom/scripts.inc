EverGrandeCity_LucysRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_LucysRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_LucysRoom_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_LucysRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_LucysRoom_OnFrame
	.byte 0

EverGrandeCity_LucysRoom_OnTransition:
	end

EverGrandeCity_LucysRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_LucysRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 2, EverGrandeCity_LucysRoom_EventScript_CloseDoor
	end

EverGrandeCity_LucysRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_LucysRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_LucysRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_LucysRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_LucysRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_LucysRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 1, EverGrandeCity_LucysRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_LucysRoom_EventScript_WalkInCloseDoor::
	setvar VAR_FORCEANIM, 1
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 2
	releaseall
	end

EverGrandeCity_LucysRoom_EventScript_Lucy::
	lock
	faceplayer
	specialvar VAR_RESULT, Script_CheckPartyBelowLevelCap
	goto_if_eq VAR_RESULT, TRUE, EverGrandeCity_LucysRoom_EventScript_NotReady
	goto_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_LucysRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_LucysRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LUCY, EverGrandeCity_LucysRoom_Text_Defeat
	goto EverGrandeCity_LucysRoom_EventScript_Defeated
	end

EverGrandeCity_LucysRoom_EventScript_NotReady::
	msgbox EverGrandeCity_LucysRoom_Text_NotReady, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_LucysRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_LucysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_LucysRoom_EventScript_Defeated::
	setvar VAR_FORCEANIM, 0
	recordtrainerwin TRAINER_LUCY
	setflag FLAG_DEFEATED_ELITE_4_PHOEBE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_LucysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT

	turnobject LOCALID_PLAYER, DIR_SOUTH
	forcesave
	release
	end

EverGrandeCity_LucysRoom_Text_NotReady:
	.string "I look forward to our fight,\n"
	.string "but your POKéMON are not yet\p"
	.string "strong enough.\p"
	.string "Level up your POKéMON and return\n"
	.string "when you're ready.$"

EverGrandeCity_LucysRoom_Text_IntroSpeech:
	.string "I am LUCY, the PIKE QUEEN...\p"
	.string "I don't care much for talk.\n"
	.string "Just show me what you've got.$"

EverGrandeCity_LucysRoom_Text_Defeat:
	.string "Hmph. I've lost...\n"
	.string "You're quite lucky.$"

EverGrandeCity_LucysRoom_Text_PostBattleSpeech:
	.string "The next room holds your next trial.\n"
	.string "Go forth.$"
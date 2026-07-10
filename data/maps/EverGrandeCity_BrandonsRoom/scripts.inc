EverGrandeCity_BrandonsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_BrandonsRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_BrandonsRoom_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_BrandonsRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_BrandonsRoom_OnFrame
	.byte 0

EverGrandeCity_BrandonsRoom_OnTransition:
	end

EverGrandeCity_BrandonsRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_BrandonsRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 4, EverGrandeCity_BrandonsRoom_EventScript_CloseDoor
	end

EverGrandeCity_BrandonsRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_BrandonsRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_BrandonsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_BrandonsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_BrandonsRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_BrandonsRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_BrandonsRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_BrandonsRoom_EventScript_WalkInCloseDoor::
	setvar VAR_FORCEANIM, 1
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_BrandonsRoom_EventScript_Brandon::
	lock
	faceplayer
	specialvar VAR_RESULT, Script_CheckPartyBelowLevelCap
	goto_if_eq VAR_RESULT, TRUE, EverGrandeCity_BrandonsRoom_EventScript_NotReady
	goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_BrandonsRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_BrandonsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BRANDON, EverGrandeCity_BrandonsRoom_Text_Defeat
	goto EverGrandeCity_BrandonsRoom_EventScript_Defeated
	end

EverGrandeCity_BrandonsRoom_EventScript_NotReady::
	msgbox EverGrandeCity_BrandonsRoom_Text_NotReady, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_BrandonsRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_BrandonsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_BrandonsRoom_EventScript_Defeated::
	setvar VAR_FORCEANIM, 0
	recordtrainerwin TRAINER_BRANDON
	setflag FLAG_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_BrandonsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	//turnobject LOCALID_PLAYER, DIR_SOUTH
	//forcesave
	release
	end

EverGrandeCity_BrandonsRoom_Text_NotReady:
	.string "I look forward to our fight,\n"
	.string "but your POKéMON are not yet\p"
	.string "strong enough.\p"
	.string "Level up your POKéMON and return\n"
	.string "when you're ready.$"

EverGrandeCity_BrandonsRoom_Text_IntroSpeech:
	.string "I am BRANDON, the PYRAMID KING!\p"
	.string "Your journey to reach me was long.\n"
	.string "Now, let's see if you have the bravery\l"
	.string "to overcome my challenge!$"

EverGrandeCity_BrandonsRoom_Text_Defeat:
	.string "Bravo! Your spirit is truly\n"
	.string "unbreakable!$"

EverGrandeCity_BrandonsRoom_Text_PostBattleSpeech:
	.string "The CHAMPION awaits you.\n"
	.string "Step through that door and finish it!$"


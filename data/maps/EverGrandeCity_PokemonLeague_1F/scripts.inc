EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	setflag FLAG_VISITED_VERDANTURF_TOWN 
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MART_EMPLOYEE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_LEAGUE_GUARD_1, 9, 2
	setobjectxyperm LOCALID_LEAGUE_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LEAGUE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	goto_if_eq VAR_SLATEPORT_RENTAL_STATE, 2, EverGrandeCity_PokemonLeague_1F_EventScript_ClerkTrap
	goto_if_eq VAR_SLATEPORT_RENTAL_STATE, 1, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRentalFraud
	goto EverGrandeCity_PokemonLeague_1F_EventScript_ClerkShop

EverGrandeCity_PokemonLeague_1F_EventScript_ClerkShop::
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_CheckRentalFraud::
	copyvar VAR_0x8005, VAR_BADGE_COUNT
	subvar VAR_0x8005, VAR_RENTAL_BADGE_COUNT
	goto_if_gt VAR_0x8005, 1, EverGrandeCity_PokemonLeague_1F_EventScript_ClerkTrap
	goto EverGrandeCity_PokemonLeague_1F_EventScript_ClerkShop

EverGrandeCity_PokemonLeague_1F_EventScript_ClerkTrap::
	applymovement LOCALID_LEAGUE_CLERK, EverGrandeCity_PokemonLeague_1F_Movement_ClerkTwirl
	waitmovement 0
	removeobject LOCALID_LEAGUE_CLERK
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAN_1
	addobject LOCALID_LEAGUE_CLERK
	applymovement LOCALID_LEAGUE_CLERK, Common_Movement_FacePlayer
	waitmovement 0
	callnative DoLightsOutFast
	waitstate
	setflashlevel 6
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CantHideFromMe, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_RENTAL_MON_SPECIES
	callnative RemoveRentalMon
	updatefollowingmon
	setvar VAR_SLATEPORT_RENTAL_STATE, 2
	setvar VAR_RENTAL_MON_SPECIES, 0
	callnative TakeAllMoney
	goto_if_eq VAR_RESULT, 0, EverGrandeCity_PokemonLeague_1F_EventScript_ClerkTrap_SkipMoney
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox EverGrandeCity_PokemonLeague_1F_Text_TookMoney, MSGBOX_DEFAULT
EverGrandeCity_PokemonLeague_1F_EventScript_ClerkTrap_SkipMoney::
	closemessage
	applymovement LOCALID_LEAGUE_CLERK, EverGrandeCity_PokemonLeague_1F_Movement_ClerkTwirl
	waitmovement 0
	removeobject LOCALID_LEAGUE_CLERK
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MART_EMPLOYEE
	addobject LOCALID_LEAGUE_CLERK
	applymovement LOCALID_LEAGUE_CLERK, Common_Movement_FacePlayer
	waitmovement 0
	callnative DoLightsOnFast
	waitstate
	setflashlevel 0
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, EverGrandeCity_PokemonLeague_1F_EventScript_ClerkGiveSpinda
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_ClerkGiveSpinda::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GetLost, MSGBOX_DEFAULT
	givemon SPECIES_SPINDA, 5
	release
	end

EverGrandeCity_PokemonLeague_1F_Movement_ClerkTwirl:
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	delay_4
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	step_end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ABOMASITE
	.2byte ITEM_AGGRONITE
	.2byte ITEM_AMPHAROSITE
	.2byte ITEM_BANETTITE
	.2byte ITEM_BARBARACITE
	.2byte ITEM_BAXCALIBRITE
	.2byte ITEM_BEEDRILLITE
	.2byte ITEM_BLASTOISINITE
	.2byte ITEM_BLAZIKENITE
	.2byte ITEM_CAMERUPTITE
	.2byte ITEM_CHANDELURITE
	.2byte ITEM_CHARIZARDITE_X
	.2byte ITEM_CHESNAUGHTITE
	.2byte ITEM_CHIMECHITE
	.2byte ITEM_CLEFABLITE
	.2byte ITEM_DELPHOXITE
	.2byte ITEM_DRAGALGITE
	.2byte ITEM_DRAGONINITE
	.2byte ITEM_EELEKTROSSITE
	.2byte ITEM_EXCADRITE
	.2byte ITEM_FERALIGITE
	.2byte ITEM_FROSLASSITE
	.2byte ITEM_GALLADITE
	.2byte ITEM_GARCHOMPITE
	.2byte ITEM_GARDEVOIRITE
	.2byte ITEM_GENGARITE
	.2byte ITEM_GLALITITE
	.2byte ITEM_GRENINJITE
	.2byte ITEM_HOUNDOOMINITE
	.2byte ITEM_LOPUNNITE
	.2byte ITEM_LUCARIONITE
	.2byte ITEM_MALAMARITE
	.2byte ITEM_MANECTITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_MEDICHAMITE
	.2byte ITEM_MEOWSTICITE
	.2byte ITEM_METAGROSSITE
	.2byte ITEM_PYROARITE
	.2byte ITEM_RAICHUNITE_X
	.2byte ITEM_SABLENITE
	.2byte ITEM_SALAMENCITE
	.2byte ITEM_SCEPTILITE
	.2byte ITEM_SCIZORITE
	.2byte ITEM_SCOLIPITE
	.2byte ITEM_SCRAFTINITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_STARAPTITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_STEELIXITE
	.2byte ITEM_SWAMPERTITE
	.2byte ITEM_TYRANITARITE
	.2byte ITEM_VENUSAURITE
	pokemartlistend

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_LEAGUE_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_LEAGUE_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	closemessage
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_1
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"

EverGrandeCity_PokemonLeague_1F_Text_CantHideFromMe:
	.string "You thought you were really clever,\n"
	.string "huh? Stealing my POKéMON!\p"
	.string "But you can't hide from me.\p"
	.string "That POKéMON and every penny you've\n"
	.string "ever earned are mine!$"

EverGrandeCity_PokemonLeague_1F_Text_TookMoney:
	.string "{PLAYER} handed over ¥{STR_VAR_1}.$"

EverGrandeCity_PokemonLeague_1F_Text_GetLost:
	.string "You don't even have any more POKéMON?\n"
	.string "Pathetic. Take this and get lost!$"

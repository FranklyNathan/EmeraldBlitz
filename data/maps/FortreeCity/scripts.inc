FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FortreeCity_OnFrame
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_EventScript_ScottEncounter::
	lockall
	clearflag FLAG_SCOTT_ENCOUNTER_PENDING
	setvar VAR_LAST_TALKED, LOCALID_FORTREE_SCOTT
	call Common_EventScript_ScottExclamation
	applymovement LOCALID_FORTREE_SCOTT, Common_Movement_ScottApproachAlt
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	call_if_eq VAR_BADGE_COUNT, 6, FortreeCity_EventScript_ScottText3
	call_if_eq VAR_BADGE_COUNT, 7, FortreeCity_EventScript_ScottText4
	call_if_eq VAR_BADGE_COUNT, 8, FortreeCity_EventScript_ScottText5
	setflag FLAG_HIDE_FORTREE_CITY_SCOTT
	releaseall
	end

FortreeCity_EventScript_ScottText3::
	call_if_eq VAR_SLATEPORT_RENTAL_STATE, 1, Common_EventScript_CheckRentalFraudforScott
	msgbox gText_ScottPostGym3, MSGBOX_DEFAULT
	setvar VAR_LAST_TALKED, LOCALID_FORTREE_SCOTT
	special OpenScottTmShop
	waitstate
	msgbox gText_ScottFinalSentence3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_HM_FLY
	waitfanfare
	setflag FLAG_RECEIVED_HM_FLY
	call Common_EventScript_ScottFlyAway
	return

Common_EventScript_PityFly::
	setflag FLAG_RECEIVED_HM_FLY
	msgbox gText_ScottPityHM, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_HM_FLY
	waitfanfare
	releaseall
	end

FortreeCity_EventScript_ScottText4::
	call_if_eq VAR_SLATEPORT_RENTAL_STATE, 1, Common_EventScript_CheckRentalFraudforScott
	msgbox gText_ScottPostGym4, MSGBOX_DEFAULT
	setvar VAR_LAST_TALKED, LOCALID_FORTREE_SCOTT
	special OpenScottTmShop
	waitstate
	msgbox gText_ScottFinalSentence3, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	setflag FLAG_RECEIVED_HM_FLY
	call Common_EventScript_ScottFlyAway
	return

FortreeCity_EventScript_ScottText5::
	call_if_eq VAR_SLATEPORT_RENTAL_STATE, 1, Common_EventScript_CheckRentalFraudforScott
	msgbox gText_ScottPostGym5, MSGBOX_DEFAULT
	setvar VAR_LAST_TALKED, LOCALID_FORTREE_SCOTT
	special OpenScottTmShop
	waitstate
	msgbox gText_ScottFinalSentence3, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	setflag FLAG_RECEIVED_HM_FLY
	call Common_EventScript_ScottFlyAway
	return

FortreeCity_EventScript_GymDoor::
	goto_if_eq VAR_FORTREE_LOCKED, 1, RandGym_EventScript_Locked
	setrespawn HEAL_LOCATION_FORTREE_CITY
	random 8
	copyvar VAR_0x800A, VAR_RESULT
	switch VAR_RESULT
 	case 0, FortreeCity_EventScript_RandGymRustboro   // If the result is 0, send the player to Rustboro Gym
    case 1, FortreeCity_EventScript_RandGymDewford    // If the result is 1, send the player to Dewford Gym
    case 2, FortreeCity_EventScript_RandGymMauville   // If the result is 2, send the player to Mauville Gym
    case 3, FortreeCity_EventScript_RandGymLavaridge  // If the result is 3, send the player to Lavaridge Gym
    case 4, FortreeCity_EventScript_RandGymPetalburg  // If the result is 4, send the player to Fallarbor Gym
    case 5, FortreeCity_EventScript_RandGymFortree // If the result is 5, send the player to Sootopolis Gym
    case 6, FortreeCity_EventScript_RandGymMossdeep  // If the result is 6, send the player to Petalburg Gym
    case 7, FortreeCity_EventScript_RandGymSootopolis  // If the result is 7, send the player to Slateport Gym
    release
    end

FortreeCity_EventScript_RandGymRustboro::
	call_if_set FLAG_DEFEATED_RUSTBORO_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
	random 2
	goto_if_eq VAR_RESULT, 1, FortreeCity_EventScript_RandGymViola
	setdynamicwarp MAP_RUSTBORO_CITY_GYM, 5, 19
	end

FortreeCity_EventScript_RandGymViola::
	setdynamicwarp MAP_RUSTBORO_CITY_GYM_VIOLA_EDITION, 5, 19
	end

FortreeCity_EventScript_RandGymDewford::
	call_if_set FLAG_DEFEATED_DEWFORD_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
	setdynamicwarp MAP_DEWFORD_TOWN_GYM, 5, 27
	end

FortreeCity_EventScript_RandGymMauville::
	call_if_set FLAG_DEFEATED_MAUVILLE_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_MAUVILLE_CITY_GYM, 4, 20
    end

FortreeCity_EventScript_RandGymLavaridge::
	call_if_set FLAG_DEFEATED_LAVARIDGE_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_LAVARIDGE_TOWN_GYM_1F, 13, 18
    end

FortreeCity_EventScript_RandGymPetalburg::
	call_if_set FLAG_DEFEATED_PETALBURG_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_PETALBURG_CITY_GYM, 4, 111
    end

FortreeCity_EventScript_RandGymFortree::
	call_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_FORTREE_CITY_GYM, 15, 24
    end

FortreeCity_EventScript_RandGymMossdeep::
	call_if_set FLAG_DEFEATED_MOSSDEEP_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_MOSSDEEP_CITY_GYM, 6, 35
    end

FortreeCity_EventScript_RandGymSootopolis::
	call_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, FortreeCity_EventScript_AlreadyBeaten
	setvar VAR_RETURN_MAP, 5
    setdynamicwarp MAP_SOOTOPOLIS_CITY_GYM_1F, 8, 25
    end

FortreeCity_EventScript_AlreadyBeaten::
	goto FortreeCity_EventScript_GymDoor
   	end

FortreeCity_OnFrame:
	map_script_2 VAR_FORTREE_CITY_STATE, 2, FortreeCity_EventScript_WalkDown
	.2byte 0

FortreeCity_EventScript_WalkDown::
	lockall
	goto_if_set FLAG_SCOTT_ENCOUNTER_PENDING, FortreeCity_EventScript_CheckScottEncounter
	setvar VAR_STEP_DOWN, 0
	setvar VAR_FORTREE_CITY_STATE, 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkRight
	waitmovement 0
	call_if_set FLAG_SCOTT_DISAPPOINTED, FortreeCity_EventScript_FlygonOvercame
	forcesave
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

FortreeCity_EventScript_CheckScottEncounter::
	call_if_ge VAR_BADGE_COUNT, 4, FortreeCity_EventScript_ScottEncounter
	releaseall
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "No one believes me, but I saw this\n"
	.string "gigantic POKéMON in the sky.\p"
	.string "It seemed to squirm as it flew toward\n"
	.string "ROUTE 131.\p"
	.string "By the way… Sniff…\n"
	.string "Um… You, uh…smell singed.\p"
	.string "Were you at a volcano or something?$"

FortreeCity_Text_SomethingBlockingGym:
	.string "I want to go to the POKéMON GYM,\n"
	.string "but something's blocking the way.\p"
	.string "After all the bother I went through\n"
	.string "training on ROUTE 120…$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "I've got my pride-and-joy POKéMON\n"
	.string "with me. This time, I'll beat WINONA.$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "The ground absorbs rainwater, and\n"
	.string "trees grow by drinking that water…\p"
	.string "Our FORTREE CITY exists because\n"
	.string "there's both water and soil.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "The CITY consists of homes built on\n"
	.string "trees.\p"
	.string "Perhaps because of that lifestyle,\n"
	.string "everyone is healthy and lively.\p"
	.string "Why, even myself--I feel as if I've\n"
	.string "grown thirty years younger.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Living on top of trees is okay.\p"
	.string "But sometimes BUG POKéMON come in\n"
	.string "through windows.\l"
	.string "It can be really startling.$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "There are POKéMON that evolve when\n"
	.string "you trade them! That's what I heard.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Something unseeable is in the way.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Something unseeable is in the way.\p"
	.string "Want to use the DEVON SCOPE?$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{PLAYER} used the DEVON SCOPE.\p"
	.string "An invisible POKéMON became completely\n"
	.string "visible!\p"
	.string "The startled POKéMON fled!$"

FortreeCity_Text_CitySign:
	.string "FORTREE CITY\n"
	.string "“The treetop city that frolics with\l"
	.string "nature.”$"

FortreeCity_Text_GymSign:
	.string "FORTREE CITY POKéMON GYM\n"
	.string "LEADER: WINONA\p"
	.string "“The bird user taking flight into\n"
	.string "the world.”$"

FortreeCity_EventScript_FlygonOvercame:
	msgbox FortreeCity_Text_FlygonLearnedFly, MSGBOX_DEFAULT
	closemessage
	return

FortreeCity_Text_FlygonLearnedFly:
	.string "BIRCH'S FLYGON is feeling great!\n"
	.string "It can fly to new heights!$"

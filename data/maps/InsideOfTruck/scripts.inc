@
@ NOTE: The moving boxes are objects 1, 2, and 3.
#define LOCALID_KOMMOO 4
#define LOCALID_SHUPPET_1 5
#define LOCALID_SHUPPET_2 6
#define LOCALID_SHUPPET_3 7
#define LOCALID_SHUPPET_4 8
#define LOCALID_SHUPPET_5 9
#define LOCALID_SHUPPET_6 10
#define LOCALID_JELLICENT_1 11
#define LOCALID_JELLICENT_2 12
#define LOCALID_JELLICENT_3 13
#define LOCALID_JELLICENT_4 14
#define LOCALID_JELLICENT_5 15
#define LOCALID_JELLICENT_6 16
#define LOCALID_JELLICENT_7 17
#define LOCALID_JELLICENT_8 18
#define LOCALID_JELLICENT_9 19
#define LOCALID_JELLICENT_10 20
#define LOCALID_JELLICENT_11 21
#define LOCALID_LOUDRED 22
#define LOCALID_CASTFORM 23
#define LOCALID_EXEGGUTOR 24
#define LOCALID_MIMIKYU 25
#define LOCALID_DARKRAI 26
#define LOCALID_COFAGRIGUS_1 27
#define LOCALID_COFAGRIGUS_2 28
#define LOCALID_COFAGRIGUS_3 29
#define LOCALID_COFAGRIGUS_4 30
#define LOCALID_TV 31
#define LOCALID_CUBCHOO 32
#define LOCALID_SKITTY 33
#define LOCALID_PANSEAR 34
#define LOCALID_PANPOUR 35
#define LOCALID_PANSAGE 36
#define LOCALID_KECLEON 37
#define LOCALID_VIGOROTH 38

InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, InsideOfTruck_OnFrameTable
	.byte 0

InsideOfTruck_OnFrameTable:
	map_script_2 VAR_TRUCK_SAVE_TRIGGER, 0, InsideOfTruck_EventScript_ForceSave
	.2byte 0

InsideOfTruck_EventScript_ForceSave::
	lockall
	delay 40
	setvar VAR_TRUCK_SAVE_TRIGGER, 1 @ Stops the script from looping infinitely
	forcesave
	releaseall
	end

InsideOfTruck_EventScript_WarpToNathansLair:
	lockall
	msgbox InsideOfTruck_Text_WarpToNathansLair, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, 1, InsideOfTruck_EventScript_DoWarpToNathansLair
	releaseall
	return

InsideOfTruck_EventScript_DoWarpToNathansLair:
	warp 4, 5, 4, 3
	waitstate
	releaseall
	end

InsideOfTruck_OnLoad:
	setweather WEATHER_NONE
	doweather
	setmetatile 4, 1, METATILE_InsideOfTruck_DoorClosedFloor_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_DoorClosedFloor_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_DoorClosedFloor_Bottom, FALSE
	@ Hide all scenario NPCs by default. They will only appear if their flag is cleared.
	setflag FLAG_HIDE_TRUCK_KOMMOO
	setflag FLAG_HIDE_TRUCK_SHUPPET
	setflag FLAG_HIDE_TRUCK_JELLICENT
	setflag FLAG_HIDE_TRUCK_LOUDRED
	setflag FLAG_HIDE_TRUCK_CASTFORM
	setflag FLAG_HIDE_TRUCK_EXEGGUTOR
	setflag FLAG_HIDE_TRUCK_MIMIKYU
	setflag FLAG_HIDE_TRUCK_DARKRAI
	setflag FLAG_HIDE_TRUCK_COFAGRIGUS
	setflag FLAG_HIDE_TRUCK_TV
	setflag FLAG_HIDE_TRUCK_CUBCHOO
	setflag FLAG_HIDE_TRUCK_SKITTY
	setflag FLAG_HIDE_TRUCK_PANSEAR
	setflag FLAG_HIDE_TRUCK_KECLEON
	setflag FLAG_HIDE_TRUCK_VIGOROTH
	@ Check if a scenario was already selected (saved)
	copyvar VAR_RESULT, VAR_TRUCK_SCENARIO
	compare VAR_RESULT, 255 @ 255 = not set yet
	goto_if_eq VAR_RESULT, 255, InsideOfTruck_EventScript_SelectRandomScenario
	@ Use saved scenario
	goto InsideOfTruck_EventScript_ApplyScenario

InsideOfTruck_EventScript_SelectRandomScenario:
	@ Randomly select a scenario and un-hide the corresponding NPCs
	random 13 @ Number of scenarios
	copyvar VAR_TRUCK_SCENARIO, VAR_RESULT @ Save the selection

InsideOfTruck_EventScript_ApplyScenario:
	copyvar VAR_RESULT, VAR_TRUCK_SCENARIO
	switch VAR_RESULT
	case 0, InsideOfTruck_EventScript_SetupKommoo
	case 1, InsideOfTruck_EventScript_SetupShuppets
	case 2, InsideOfTruck_EventScript_SetupJellicents
	case 3, InsideOfTruck_EventScript_SetupLoudred
	case 4, InsideOfTruck_EventScript_SetupCastform
	case 5, InsideOfTruck_EventScript_SetupExeggutor
	case 6, InsideOfTruck_EventScript_SetupMimikyu
	case 7, InsideOfTruck_EventScript_SetupDarkrai
	case 8, InsideOfTruck_EventScript_SetupCofagrigus
	@ case 9, InsideOfTruck_EventScript_SetupCubchooTV
	case 9, InsideOfTruck_EventScript_SetupSkitty
	case 10, InsideOfTruck_EventScript_SetupMonkeys
	case 11, InsideOfTruck_EventScript_SetupKecleon
	case 12, InsideOfTruck_EventScript_SetupVigoroth
	end

InsideOfTruck_EventScript_SetupKommoo::
	clearflag FLAG_HIDE_TRUCK_KOMMOO
	return

InsideOfTruck_EventScript_SetupShuppets::
	clearflag FLAG_HIDE_TRUCK_SHUPPET
	return

InsideOfTruck_EventScript_SetupJellicents::
	clearflag FLAG_HIDE_TRUCK_JELLICENT
	return

InsideOfTruck_EventScript_SetupLoudred::
	clearflag FLAG_HIDE_TRUCK_LOUDRED
	return

InsideOfTruck_EventScript_SetupCastform::
	clearflag FLAG_HIDE_TRUCK_CASTFORM
	setweather WEATHER_RAIN
	doweather
	return

InsideOfTruck_EventScript_SetupExeggutor::
	clearflag FLAG_HIDE_TRUCK_EXEGGUTOR
	return

InsideOfTruck_EventScript_SetupMimikyu::
	setflashlevel 7
	clearflag FLAG_HIDE_TRUCK_MIMIKYU
	return

InsideOfTruck_EventScript_SetupDarkrai::
	clearflag FLAG_HIDE_TRUCK_DARKRAI
	return

InsideOfTruck_EventScript_SetupCofagrigus::
	clearflag FLAG_HIDE_TRUCK_COFAGRIGUS
	return

InsideOfTruck_EventScript_SetupCubchooTV::
	clearflag FLAG_HIDE_TRUCK_TV
	clearflag FLAG_HIDE_TRUCK_CUBCHOO
	return

InsideOfTruck_EventScript_SetupSkitty::
	clearflag FLAG_HIDE_TRUCK_SKITTY
	return

InsideOfTruck_EventScript_SetupMonkeys::
	clearflag FLAG_HIDE_TRUCK_PANSEAR
	return

InsideOfTruck_EventScript_SetupKecleon::
	clearflag FLAG_HIDE_TRUCK_KECLEON
	return

InsideOfTruck_EventScript_SetupVigoroth::
	clearflag FLAG_HIDE_TRUCK_VIGOROTH
	return

InsideOfTruck_EventScript_KommooCry::
	lock
	getdirectiontoface VAR_RESULT, LOCALID_KOMMOO, LOCALID_PLAYER
	compare VAR_RESULT, DIR_SOUTH @ Player is below
	call_if_eq InsideOfTruck_EventScript_KommooFaceWest
	compare VAR_RESULT, DIR_NORTH @ Player is above
	call_if_eq InsideOfTruck_EventScript_KommooFaceEast
	compare VAR_RESULT, DIR_WEST @ Player is to the left
	call_if_eq InsideOfTruck_EventScript_KommooFaceSouth
	compare VAR_RESULT, DIR_EAST @ Player is to the right
	call_if_eq InsideOfTruck_EventScript_KommooFaceNorth
	msgbox InsideOfTruck_Text_SideEye, MSGBOX_DEFAULT
	release
	end

InsideOfTruck_EventScript_KommooFaceWest::
	applymovement LOCALID_KOMMOO, InsideOfTruck_Movement_KommooFaceWest
	waitmovement 0
	return

InsideOfTruck_EventScript_KommooFaceSouth::
	applymovement LOCALID_KOMMOO, InsideOfTruck_Movement_KommooFaceSouth
	waitmovement 0
	return

InsideOfTruck_EventScript_KommooFaceEast::
	applymovement LOCALID_KOMMOO, InsideOfTruck_Movement_KommooFaceEast
	waitmovement 0
	return

InsideOfTruck_EventScript_KommooFaceNorth::
	applymovement LOCALID_KOMMOO, InsideOfTruck_Movement_KommooFaceNorth
	waitmovement 0
	return

InsideOfTruck_Movement_KommooFaceWest:
	walk_in_place_fast_left
	face_left
	step_end

InsideOfTruck_Movement_KommooFaceEast:
	walk_in_place_fast_right
	face_right
	step_end

InsideOfTruck_Movement_KommooFaceSouth:
	walk_in_place_fast_down
	face_down
	step_end

InsideOfTruck_Movement_KommooFaceNorth:
	walk_in_place_fast_up
	face_up
	step_end

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

InsideOfTruck_EventScript_SetIntroFlags::
	end

InsideOfTruck_EventScript_SetIntroFlagsMale::
	end

InsideOfTruck_EventScript_MovingBox::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with an EMERALD BLITZ\n"
	.string "logo.\p"
	.string "…\p"
	.string "It's filled to the brim with\n"
	.string "your hopes and dreams for this run.$"

InsideOfTruck_EventScript_Cofagrigus::
	lockall
	msgbox InsideOfTruck_Text_Cofagrigus, MSGBOX_SIGN
	releaseall
	end

InsideOfTruck_EventScript_Jellicent::
	lockall
	msgbox InsideOfTruck_Text_Jellicent, MSGBOX_SIGN
	releaseall
	end

InsideOfTruck_EventScript_Castform::
	lockall
	faceplayer
	msgbox InsideOfTruck_Text_Castform, MSGBOX_NPC
	releaseall
	end

InsideOfTruck_EventScript_Exeggutor::
	lockall
	msgbox InsideOfTruck_Text_Exeggutor, MSGBOX_SIGN
	releaseall
	end

InsideOfTruck_EventScript_Mimikyu::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Mimikyu, MSGBOX_SIGN
	fadescreen FADE_TO_BLACK
	setflashlevel 8
	setflag FLAG_HIDE_TRUCK_MIMIKYU
	removeobject LOCALID_MIMIKYU
	playmoncry SPECIES_MIMIKYU, CRY_MODE_NORMAL
	waitmoncry
	waitstate

InsideOfTruck_EventScript_Darkrai::
	lockall
	faceplayer
	playmoncry SPECIES_DARKRAI, CRY_MODE_NORMAL
	waitmoncry
	setvar VAR_RESULT, 4
	special DoOrbEffect
	waitstate
	waitstate
	msgbox InsideOfTruck_Text_Darkrai, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	waitstate
	waitstate

InsideOfTruck_Text_Darkrai:
	.string "After a run like that, you're suddenly\n"
	.string "feeling… so very… so very sleepy………$"

InsideOfTruck_Text_Cofagrigus:
	.string "Well this is no good. Even with so\n"
	.string "many coffins, there still aren't enough\l"
	.string "to fit all of the POKéMON you let die.$"

InsideOfTruck_Text_Exeggutor:
	.string "EXEGGUTOR seems to think it's being\n"
	.string "very sneaky.$"

InsideOfTruck_Text_Mimikyu:
	.string "The MIMIKYU is smiling at you\n"
	.string "menacingly.\p"
	.string "It seems to have been waiting for\n"
	.string "just this moment.$"

InsideOfTruck_Text_Castform:
	.string "CASTFORM appears to have set the\n"
	.string "weather based on your mood.$"

InsideOfTruck_Text_Jellicent:
	.string "……………\p"
	.string "…Well this is a little cramped.$"

InsideOfTruck_EventScript_Loudred::
	lockall
	faceplayer
	playmoncry SPECIES_LOUDRED, CRY_MODE_NORMAL
	waitmoncry
	msgbox InsideOfTruck_Text_Loudred, MSGBOX_NPC
	releaseall
	end

InsideOfTruck_EventScript_TV::
	lockall
	msgbox InsideOfTruck_Text_TruckTVWipe, MSGBOX_SIGN
	releaseall
	end

InsideOfTruck_EventScript_Cubchoo::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_TruckCubchooRecognizes, MSGBOX_NPC
	release
	end

InsideOfTruck_EventScript_Skitty::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_SKITTY, InsideOfTruck_Movement_Heart
	waitmovement 0
	msgbox InsideOfTruck_Text_Skitty, MSGBOX_NPC
	release
	end

InsideOfTruck_Movement_Heart:
	emote_heart
	step_end

InsideOfTruck_Text_TruckTVWipe:
	.string "This just in, folks. {PLAYER} has\n"
	.string "wiped again in yet another embarrassing\l"
	.string "turn of events. This time…\p"
	.string "The anchor is speaking over a montage\n"
	.string "of each of your POKéMON being brutally\l"
	.string "knocked out one after the next.$"

InsideOfTruck_Text_TruckCubchooRecognizes:
	.string "CUBCHOO's eyes light up looking at\n"
	.string "you. It seems to recognize your\l"
	.string "discouraged expression from the TV.$"

InsideOfTruck_Text_Skitty:
	.string "SKITTY looks thrilled to finally have\n"
	.string "some friends to play with. It's looking\l"
	.string "eagerly at your POKé BALLS.\p"
	.string "…She's going to be very disappointed.$"

InsideOfTruck_Text_Loudred:
	.string "KRRRZZZZTBOOM BAMBAMBAMBAMBAM\n"
	.string "BWOOM BWOOM BWOOM VVVVVREEEEE\p"
	.string "LOUDRED is blasting noise so loud you\n"
	.string "can hardly hear yourself think.\p"
	.string "KRRRZZZZTBLAM KRRRZZZZTBLAM\p"
	.string "This is truly a fate worse than death.$"

InsideOfTruck_Text_SideEye:
	.string "………\p"
	.string "………………………\p"
	.string "…………………………………………………………………………\p"
	.string "KOMMO-O is giving you some judgmental\n"
	.string "side eye.\p"
	.string "…………\p"
	.string "…Well, this sure is awkward.$"

InsideOfTruck_EventScript_Shuppet1::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Shuppet1, MSGBOX_NPC
	release
	end

InsideOfTruck_EventScript_Shuppet2::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Shuppet2, MSGBOX_NPC
	release
	end

InsideOfTruck_EventScript_Shuppet3::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Shuppet3, MSGBOX_NPC
	release
	end

InsideOfTruck_Text_Shuppet1:
	.string "This SHUPPET seems to feel bad for you.$"

InsideOfTruck_Text_Shuppet2:
	.string "This SHUPPET seems to be amused by\n"
	.string "your failure.$"

InsideOfTruck_Text_Shuppet3:
	.string "This SHUPPET seems not to notice you.$"

InsideOfTruck_EventScript_Pansear::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Pansear, MSGBOX_NPC
	release
	end

InsideOfTruck_EventScript_Panpour::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Panpour, MSGBOX_NPC
	release
	end

InsideOfTruck_EventScript_Pansage::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Pansage, MSGBOX_NPC
	release
	end

InsideOfTruck_Text_Pansear:
	.string "PANSEAR doesn't seem to understand\n"
	.string "that this is no time for monkey business.$"

InsideOfTruck_Text_Panpour:
	.string "PANPOUR is monkeying around like\n"
	.string "there's no tomorrow.$"

InsideOfTruck_Text_Pansage:
	.string "PANSAGE seems to think this truck is\n"
	.string "more fun than a barrel full of monkeys.$"

InsideOfTruck_EventScript_Kecleon::
	lock
	playse SE_SUCCESS
	applymovement LOCALID_KECLEON, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_KECLEON, InsideOfTruck_Movement_KecleonShow
	waitmovement 0
	msgbox InsideOfTruck_Text_Kecleon, MSGBOX_DEFAULT
	release
	end

InsideOfTruck_Movement_KecleonShow:
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	step_end

InsideOfTruck_Text_Kecleon:
	.string "KECLEON is frozen in surprise.\p"
	.string "…Actually, its surprise doesn't look\n"
	.string "very genuine.\p"
	.string "It seems like it was expecting you to\n"
	.string "end up here all along.$"

InsideOfTruck_EventScript_Vigoroth::
	lock
	faceplayer
	msgbox InsideOfTruck_Text_Vigoroth, MSGBOX_NPC
	release
	end

InsideOfTruck_Text_Vigoroth:
	.string "VIGOROTH looks surprisingly content\n"
	.string "for being trapped in the back of a\l"
	.string "moving truck for all eternity.\p"
	.string "…I guess you'll have to learn from\n"
	.string "its positive attitude.$"

InsideOfTruck_Text_WarpToNathansLair:
	.string "Warp to Nathan's Lair?$"

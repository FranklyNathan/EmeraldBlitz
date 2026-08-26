.set LOCALID_NPC1, 1
.set LOCALID_NPC2, 2

LilycoveCity_LilycoveMuseum_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_LilycoveMuseum_3F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_LilycoveMuseum_3F_OnFrame
	.byte 0

@ ============================================================
@ OnFrame: Run battle sequence after warp re-enter
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_OnFrame:
	map_script_2 VAR_TEMP_0, 0, LilycoveCity_LilycoveMuseum_3F_EventScript_CheckPendingBattle
	.2byte 0

LilycoveCity_LilycoveMuseum_3F_EventScript_CheckPendingBattle:
	setvar VAR_TEMP_0, 1
	goto_if_set FLAG_MUSEUM_3F_BATTLE, LilycoveCity_LilycoveMuseum_3F_EventScript_PostWarpBattle
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_PostWarpBattle:
	clearflag FLAG_MUSEUM_3F_BATTLE
	lockall
	hidefollower 0
	turnobject LOCALID_PLAYER, DIR_WEST
	delay 20
	goto_if_eq VAR_0x8005, 0, Museum3F_ApproachTrainerAtNPC1
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach1
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach2
	waitmovement 0
	delay 20
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, LilycoveCity_LilycoveMuseum_3F_Movement_camerapanleft
	waitmovement 0
	special RemoveCameraObject
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleDispatch

Museum3F_ApproachTrainerAtNPC1:
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach1
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach2
	waitmovement 0
	delay 20
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, LilycoveCity_LilycoveMuseum_3F_Movement_camerapanleft
	waitmovement 0
	special RemoveCameraObject
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleDispatch

@ ============================================================
@ OnTransition: Randomly assign trainer and filler NPCs
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_OnTransition:
	goto_if_set FLAG_MUSEUM_3F_BATTLE, Museum3F_OnTransition_BattleSetup
	cleartrainerflag TRAINER_MUSEUM_JASON
	cleartrainerflag TRAINER_MUSEUM_KCH42
	cleartrainerflag TRAINER_MUSEUM_JEANS
	cleartrainerflag TRAINER_MUSEUM_BEASTLY
	cleartrainerflag TRAINER_MUSEUM_FREEZ
	random 5
	copyvar VAR_0x8004, VAR_RESULT
	random 2
	copyvar VAR_0x8005, VAR_RESULT
	random 10
	copyvar VAR_0x8006, VAR_RESULT
	goto Museum3F_SetupSprites

Museum3F_OnTransition_BattleSetup:
	copyvar VAR_0x8004, VAR_MUSEUM_3F_TRAINER
	copyvar VAR_0x8005, VAR_MUSEUM_3F_LOCATION
	copyvar VAR_0x8006, VAR_MUSEUM_3F_FILLER
	setvar VAR_TEMP_0, 0
	settrainerflag TRAINER_MUSEUM_JASON
	settrainerflag TRAINER_MUSEUM_KCH42
	settrainerflag TRAINER_MUSEUM_JEANS
	settrainerflag TRAINER_MUSEUM_BEASTLY
	settrainerflag TRAINER_MUSEUM_FREEZ
	goto_if_eq VAR_0x8005, 0, Museum3F_BattleSetup_TrainerAtLeft
	setobjectxyperm LOCALID_NPC2, 14, 11
	goto Museum3F_SetupSprites

Museum3F_BattleSetup_TrainerAtLeft:
	setobjectxyperm LOCALID_NPC1, 14, 11
	setobjectmovementtype LOCALID_NPC1, MOVEMENT_TYPE_FACE_RIGHT
	goto Museum3F_SetupSprites

Museum3F_SetupSprites:
	goto_if_eq VAR_0x8005, 0, Museum3F_TrainerAtLeft
	goto Museum3F_SetTrainerGfx

Museum3F_TrainerAtLeft:
	goto Museum3F_SetTrainerGfx

Museum3F_SetTrainerGfx:
	switch VAR_0x8004
	case 0, Museum3F_GfxDefault
	case 1, Museum3F_GfxSilver
	case 2, Museum3F_GfxBlue
	case 3, Museum3F_GfxDefault
	case 4, Museum3F_GfxPink
	end

Museum3F_GfxDefault:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_NORMAL
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxSilver:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_SILVER
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxBlue:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_BLUE
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxPink:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_PINK
	goto Museum3F_ApplyTrainerGfx

Museum3F_ApplyTrainerGfx:
	goto_if_eq VAR_0x8005, 0, Museum3F_ApplyTrainerGfxToID0
	copyvar VAR_OBJ_GFX_ID_1, VAR_0x8007
	goto Museum3F_SetFillerSprite

Museum3F_ApplyTrainerGfxToID0:
	copyvar VAR_OBJ_GFX_ID_0, VAR_0x8007

Museum3F_SetFillerSprite:
	switch VAR_0x8006
	case 0, Museum3F_SpriteVal0
	case 1, Museum3F_SpriteVal1
	case 2, Museum3F_SpriteVal2
	case 3, Museum3F_SpriteVal3
	case 4, Museum3F_SpriteVal4
	case 5, Museum3F_SpriteVal5
	case 6, Museum3F_SpriteVal6
	case 7, Museum3F_SpriteVal7
	case 8, Museum3F_SpriteVal8
	case 9, Museum3F_SpriteVal9
	end

Museum3F_SpriteVal0:
	setvar VAR_0x8007, OBJ_EVENT_GFX_YOUNGSTER
	goto Museum3F_CopyFiller
Museum3F_SpriteVal1:
	setvar VAR_0x8007, OBJ_EVENT_GFX_MAN_1
	goto Museum3F_CopyFiller
Museum3F_SpriteVal2:
	setvar VAR_0x8007, OBJ_EVENT_GFX_MAN_2
	goto Museum3F_CopyFiller
Museum3F_SpriteVal3:
	setvar VAR_0x8007, OBJ_EVENT_GFX_EXPERT_M
	goto Museum3F_CopyFiller
Museum3F_SpriteVal4:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BLACK_BELT
	goto Museum3F_CopyFiller
Museum3F_SpriteVal5:
	setvar VAR_0x8007, OBJ_EVENT_GFX_CAMPER
	goto Museum3F_CopyFiller
Museum3F_SpriteVal6:
	setvar VAR_0x8007, OBJ_EVENT_GFX_MAN_3
	goto Museum3F_CopyFiller
Museum3F_SpriteVal7:
	setvar VAR_0x8007, OBJ_EVENT_GFX_MAN_4
	goto Museum3F_CopyFiller
Museum3F_SpriteVal8:
	setvar VAR_0x8007, OBJ_EVENT_GFX_MAN_5
	goto Museum3F_CopyFiller
Museum3F_SpriteVal9:
	setvar VAR_0x8007, OBJ_EVENT_GFX_SCHOOL_KID_M
	goto Museum3F_CopyFiller

Museum3F_CopyFiller:
	goto_if_eq VAR_0x8005, 0, Museum3F_CopyFillerToID1
	copyvar VAR_OBJ_GFX_ID_0, VAR_0x8007
	end

Museum3F_CopyFillerToID1:
	copyvar VAR_OBJ_GFX_ID_1, VAR_0x8007
	end

@ ============================================================
@ NPC Interaction Scripts
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_NPC1::
	lock
	faceplayer
	goto_if_eq VAR_0x8005, 0, LilycoveCity_LilycoveMuseum_3F_EventScript_TrainerTalk
	call LilycoveCity_LilycoveMuseum_3F_EventScript_FillerDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_NPC2::
	lock
	faceplayer
	goto_if_eq VAR_0x8005, 1, LilycoveCity_LilycoveMuseum_3F_EventScript_TrainerTalk
	call LilycoveCity_LilycoveMuseum_3F_EventScript_FillerDialogue
	release
	end

@ ============================================================
@ Trainer Talk and Battle Sequence
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_TrainerTalk:
	switch VAR_0x8004
	case 0, Museum3F_TrainerTalkJason
	case 1, Museum3F_TrainerTalkKCH42
	case 2, Museum3F_TrainerTalkJeans
	case 3, Museum3F_TrainerTalkBeastly
	case 4, Museum3F_TrainerTalkFreez
	end

Museum3F_TrainerTalkJason:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipses, MSGBOX_DEFAULT
	goto Museum3F_TrainerTalkContinue

Museum3F_TrainerTalkKCH42:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses, MSGBOX_DEFAULT
	goto Museum3F_TrainerTalkContinue

Museum3F_TrainerTalkJeans:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses, MSGBOX_DEFAULT
	goto Museum3F_TrainerTalkContinue

Museum3F_TrainerTalkBeastly:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses, MSGBOX_DEFAULT
	goto Museum3F_TrainerTalkContinue

Museum3F_TrainerTalkFreez:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses, MSGBOX_DEFAULT
	goto Museum3F_TrainerTalkContinue

Museum3F_TrainerTalkContinue:
	closemessage
	hidefollower 0
	copyvar VAR_MUSEUM_3F_TRAINER, VAR_0x8004
	copyvar VAR_MUSEUM_3F_LOCATION, VAR_0x8005
	copyvar VAR_MUSEUM_3F_FILLER, VAR_0x8006
	setflag FLAG_MUSEUM_3F_BATTLE
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_3F, 23, 11
	waitstate
	end

@ ============================================================
@ Battle Dispatch
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_BattleDispatch:
	switch VAR_0x8004
	case 0, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJason
	case 1, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleKCH42
	case 2, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJeans
	case 3, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleBeastly
	case 4, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleFreez
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJason:
	cleartrainerflag TRAINER_MUSEUM_JASON
	trainerbattle_no_intro TRAINER_MUSEUM_JASON, LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipses
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon

LilycoveCity_LilycoveMuseum_3F_EventScript_BattleKCH42:
	cleartrainerflag TRAINER_MUSEUM_KCH42
	trainerbattle_no_intro TRAINER_MUSEUM_KCH42, LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon

LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJeans:
	cleartrainerflag TRAINER_MUSEUM_JEANS
	trainerbattle_no_intro TRAINER_MUSEUM_JEANS, LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon

LilycoveCity_LilycoveMuseum_3F_EventScript_BattleBeastly:
	cleartrainerflag TRAINER_MUSEUM_BEASTLY
	trainerbattle_no_intro TRAINER_MUSEUM_BEASTLY, LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon

LilycoveCity_LilycoveMuseum_3F_EventScript_BattleFreez:
	cleartrainerflag TRAINER_MUSEUM_FREEZ
	trainerbattle_no_intro TRAINER_MUSEUM_FREEZ, LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses
	goto LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon

@ ============================================================
@ Battle Won
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_BattleWon:
	goto_if_eq VAR_0x8005, 0, Museum3F_RemoveTrainerNPC1
	removeobject LOCALID_NPC2
	goto Museum3F_BattleCleanup

Museum3F_RemoveTrainerNPC1:
	removeobject LOCALID_NPC1

Museum3F_BattleCleanup:
	hidefollower 0
	setobjectxy LOCALID_PLAYER, 20, 11
	updatefollowingmon
	release
	end

@ ============================================================
@ Filler Dialogue
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_FillerDialogue:
	switch VAR_0x8006
	case 0, Museum3F_Filler0
	case 1, Museum3F_Filler1
	case 2, Museum3F_Filler2
	case 3, Museum3F_Filler3
	case 4, Museum3F_Filler4
	case 5, Museum3F_Filler5
	case 6, Museum3F_Filler6
	case 7, Museum3F_Filler7
	case 8, Museum3F_Filler8
	case 9, Museum3F_Filler9
	return

Museum3F_Filler0:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler0, MSGBOX_DEFAULT
	return
Museum3F_Filler1:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler1, MSGBOX_DEFAULT
	return
Museum3F_Filler2:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler2, MSGBOX_DEFAULT
	return
Museum3F_Filler3:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler3, MSGBOX_DEFAULT
	return
Museum3F_Filler4:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler4, MSGBOX_DEFAULT
	return
Museum3F_Filler5:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler5, MSGBOX_DEFAULT
	return
Museum3F_Filler6:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler6, MSGBOX_DEFAULT
	return
Museum3F_Filler7:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler7, MSGBOX_DEFAULT
	return
Museum3F_Filler8:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler8, MSGBOX_DEFAULT
	return
Museum3F_Filler9:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_Filler9, MSGBOX_DEFAULT
	return

@ ============================================================
@ Movement Data
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach1:
	walk_left
	walk_left
	step_end

LilycoveCity_LilycoveMuseum_3F_Movement_PlayerApproach2:
	walk_left
	step_end

LilycoveCity_LilycoveMuseum_3F_Movement_camerapanleft:
	walk_left
	walk_left
	walk_left
	step_end

@ ============================================================
@ Text
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipses:
	.string "JASON: ...$"

LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses:
	.string "KCH42: ...$"

LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses:
	.string "JEANS: ...$"

LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses:
	.string "BEASTLY: ...$"

LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses:
	.string "FREEZ: ...$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler0:
	.string "I'm just here for the refreshments.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler1:
	.string "I don't recognize you.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler2:
	.string "Just relaxing.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler3:
	.string "This place is really something!$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler4:
	.string "I love looking at the exhibits.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler5:
	.string "Where am I?$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler6:
	.string "I think I'm lost.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler7:
	.string "Nice museum.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler8:
	.string "I'm studying the artifacts.$"

LilycoveCity_LilycoveMuseum_3F_Text_Filler9:
	.string "This is a cool place.$"

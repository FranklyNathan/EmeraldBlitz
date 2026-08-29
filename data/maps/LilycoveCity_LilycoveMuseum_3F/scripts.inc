.set LOCALID_NPC1, 1
.set LOCALID_NPC2, 2
.set LOCALID_POKE1, 3
.set LOCALID_POKE2, 4
.set LOCALID_POKE3, 5
.set LOCALID_POKE4, 6
.set LOCALID_POKE5, 7
.set LOCALID_POKE6, 8
.set LOCALID_POKE7, 9
.set LOCALID_POKE8, 10
.set LOCALID_POKE9, 11
.set LOCALID_POKE10, 12
.set LOCALID_POKE11, 13
.set LOCALID_POKE12, 14

LilycoveCity_LilycoveMuseum_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_LilycoveMuseum_3F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_LilycoveMuseum_3F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LilycoveCity_LilycoveMuseum_3F_OnWarp
	.byte 0

LilycoveCity_LilycoveMuseum_3F_OnWarp:
	.2byte 0

LilycoveCity_LilycoveMuseum_3F_OnFrame:
	map_script_2 VAR_TEMP_E, 0, LilycoveCity_LilycoveMuseum_3F_EventScript_CheckPendingBattle
	.2byte 0

LilycoveCity_LilycoveMuseum_3F_EventScript_CheckPendingBattle:
	setvar VAR_TEMP_E, 1
	goto_if_set FLAG_MUSEUM_3F_BATTLE, LilycoveCity_LilycoveMuseum_3F_EventScript_PostWarpBattle
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_PostWarpBattle:
	lockall
	turnobject LOCALID_PLAYER, DIR_WEST
	hidefollower 0
	delay 20
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
@ OnTransition
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_OnTransition:
	goto_if_set FLAG_MUSEUM_3F_BATTLE, Museum3F_OnTransition_BattleSetup
	settrainerflag TRAINER_MUSEUM_JASON
	settrainerflag TRAINER_MUSEUM_KCH42
	settrainerflag TRAINER_MUSEUM_JEANS
	settrainerflag TRAINER_MUSEUM_BEASTLY
	settrainerflag TRAINER_MUSEUM_FREEZ
	call Museum3F_CheckAllDefeated
	compare VAR_RESULT, 1
	goto_if_eq Museum3F_CrownTransition
	goto_if_set FLAG_MUSEUM_3F_LEGEND_ACTIVE, Museum3F_LoadLockedLegend
	call Museum3F_PickLegend
	copyvar VAR_MUSEUM_3F_TRAINER, VAR_0x8004
	random 2
	copyvar VAR_MUSEUM_3F_LOCATION, VAR_RESULT
	copyvar VAR_0x8005, VAR_RESULT
	random 10
	copyvar VAR_MUSEUM_3F_FILLER, VAR_RESULT
	copyvar VAR_0x8006, VAR_RESULT
	setflag FLAG_MUSEUM_3F_LEGEND_ACTIVE
	goto Museum3F_SetupLocked

Museum3F_LoadLockedLegend:
	copyvar VAR_0x8004, VAR_MUSEUM_3F_TRAINER
	copyvar VAR_0x8005, VAR_MUSEUM_3F_LOCATION
	copyvar VAR_0x8006, VAR_MUSEUM_3F_FILLER

Museum3F_SetupLocked:
	call Museum3F_ClearActiveTrainer
	call Museum3F_SetSpawnFlags
	goto Museum3F_SetupSprites

Museum3F_OnTransition_BattleSetup:
	copyvar VAR_0x8004, VAR_MUSEUM_3F_TRAINER
	copyvar VAR_0x8005, VAR_MUSEUM_3F_LOCATION
	copyvar VAR_0x8006, VAR_MUSEUM_3F_FILLER
	setvar VAR_TEMP_E, 0
	settrainerflag TRAINER_MUSEUM_JASON
	settrainerflag TRAINER_MUSEUM_KCH42
	settrainerflag TRAINER_MUSEUM_JEANS
	settrainerflag TRAINER_MUSEUM_BEASTLY
	settrainerflag TRAINER_MUSEUM_FREEZ
	call Museum3F_SetSpawnFlags
	goto_if_eq VAR_0x8005, 0, Museum3F_BattleSetup_TrainerAtLeft
	setobjectxyperm LOCALID_NPC2, 14, 11
	goto Museum3F_SetupSprites

Museum3F_BattleSetup_TrainerAtLeft:
	setobjectxyperm LOCALID_NPC1, 14, 11
	setobjectmovementtype LOCALID_NPC1, MOVEMENT_TYPE_FACE_RIGHT
	goto Museum3F_SetupSprites

Museum3F_CheckAllDefeated:
	setvar VAR_RESULT, 1
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_JASON_DEFEATED, Museum3F_NotAllDefeated
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_KCH42_DEFEATED, Museum3F_NotAllDefeated
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_JEANS_DEFEATED, Museum3F_NotAllDefeated
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_BEASTLY_DEFEATED, Museum3F_NotAllDefeated
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_FREEZ_DEFEATED, Museum3F_NotAllDefeated
	return

Museum3F_NotAllDefeated:
	setvar VAR_RESULT, 0
	return

Museum3F_PickLegend:
	random 5
	copyvar VAR_0x8004, VAR_RESULT
	switch VAR_0x8004
	case 0, Museum3F_PickJASON
	case 1, Museum3F_PickKCH42
	case 2, Museum3F_PickJEANS
	case 3, Museum3F_PickBEASTLY
	case 4, Museum3F_PickFREEZ
	end

Museum3F_PickJASON:
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_JASON_DEFEATED, Museum3F_PickLive
	setvar VAR_0x8004, 1
	goto Museum3F_PickKCH42
Museum3F_PickKCH42:
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_KCH42_DEFEATED, Museum3F_PickLive
	setvar VAR_0x8004, 2
	goto Museum3F_PickJEANS
Museum3F_PickJEANS:
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_JEANS_DEFEATED, Museum3F_PickLive
	setvar VAR_0x8004, 3
	goto Museum3F_PickBEASTLY
Museum3F_PickBEASTLY:
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_BEASTLY_DEFEATED, Museum3F_PickLive
	setvar VAR_0x8004, 4
	goto Museum3F_PickFREEZ
Museum3F_PickFREEZ:
	goto_if_unset FLAG_MUSEUM_3F_LEGEND_FREEZ_DEFEATED, Museum3F_PickLive
	setvar VAR_0x8004, 0
	goto Museum3F_PickJASON

Museum3F_PickLive:
	return

Museum3F_ClearActiveTrainer:
	switch VAR_0x8004
	case 0, Museum3F_ClearJASON
	case 1, Museum3F_ClearKCH42
	case 2, Museum3F_ClearJEANS
	case 3, Museum3F_ClearBEASTLY
	case 4, Museum3F_ClearFREEZ
	end
Museum3F_ClearJASON:
	cleartrainerflag TRAINER_MUSEUM_JASON
	return
Museum3F_ClearKCH42:
	cleartrainerflag TRAINER_MUSEUM_KCH42
	return
Museum3F_ClearJEANS:
	cleartrainerflag TRAINER_MUSEUM_JEANS
	return
Museum3F_ClearBEASTLY:
	cleartrainerflag TRAINER_MUSEUM_BEASTLY
	return
Museum3F_ClearFREEZ:
	cleartrainerflag TRAINER_MUSEUM_FREEZ
	return

Museum3F_MarkDefeated:
	switch VAR_0x8004
	case 0, Museum3F_MarkJASON
	case 1, Museum3F_MarkKCH42
	case 2, Museum3F_MarkJEANS
	case 3, Museum3F_MarkBEASTLY
	case 4, Museum3F_MarkFREEZ
	end
Museum3F_MarkJASON:
	setflag FLAG_MUSEUM_3F_LEGEND_JASON_DEFEATED
	settrainerflag TRAINER_MUSEUM_JASON
	return
Museum3F_MarkKCH42:
	setflag FLAG_MUSEUM_3F_LEGEND_KCH42_DEFEATED
	settrainerflag TRAINER_MUSEUM_KCH42
	return
Museum3F_MarkJEANS:
	setflag FLAG_MUSEUM_3F_LEGEND_JEANS_DEFEATED
	settrainerflag TRAINER_MUSEUM_JEANS
	return
Museum3F_MarkBEASTLY:
	setflag FLAG_MUSEUM_3F_LEGEND_BEASTLY_DEFEATED
	settrainerflag TRAINER_MUSEUM_BEASTLY
	return
Museum3F_MarkFREEZ:
	setflag FLAG_MUSEUM_3F_LEGEND_FREEZ_DEFEATED
	settrainerflag TRAINER_MUSEUM_FREEZ
	return

Museum3F_CrownTransition:
	copyvar VAR_0x8005, VAR_MUSEUM_3F_LOCATION
	random 10
	copyvar VAR_0x8006, VAR_RESULT
	goto Museum3F_CrownSetup

Museum3F_CrownSetup:
	call Museum3F_SetSpawnFlags
	goto_if_set FLAG_MUSEUM_3F_CROWN_TAKEN, Museum3F_CrownTaken
	setvar VAR_0x8007, OBJ_EVENT_GFX_ITEM_BALL
	goto Museum3F_ApplyTrainerGfx

Museum3F_CrownTaken:
	setvar VAR_0x8007, OBJ_EVENT_GFX_SCHOOL_KID_M
	goto_if_eq VAR_0x8005, 0, Museum3F_CrownRemoveNPC1
	removeobject LOCALID_NPC2
	goto Museum3F_ApplyTrainerGfx
Museum3F_CrownRemoveNPC1:
	removeobject LOCALID_NPC1
	goto Museum3F_ApplyTrainerGfx

Museum3F_CrownPickup:
	goto_if_set FLAG_MUSEUM_3F_CROWN_TAKEN, Museum3F_CrownEmpty
	giveitem ITEM_RELIC_CROWN
	goto_if_eq VAR_RESULT, FALSE, Museum3F_CrownBagFull
	setflag FLAG_MUSEUM_3F_CROWN_TAKEN
	goto_if_eq VAR_0x8005, 0, Museum3F_CrownPickNPC1
	removeobject LOCALID_NPC2
	goto Museum3F_CrownDone
Museum3F_CrownPickNPC1:
	removeobject LOCALID_NPC1
Museum3F_CrownDone:
	release
	end

Museum3F_CrownBagFull:
	release
	end

Museum3F_CrownEmpty:
	msgbox MTextMuseumCrownEmpty, MSGBOX_DEFAULT
	release
	end

Museum3F_SetSpawnFlags:
	goto_if_eq VAR_0x8005, 0, Museum3F_SpawnFlagsNPC1
	setflag FLAG_MUSEUM_3F_SPAWN_NPC1
	clearflag FLAG_MUSEUM_3F_SPAWN_NPC2
	return
Museum3F_SpawnFlagsNPC1:
	clearflag FLAG_MUSEUM_3F_SPAWN_NPC1
	setflag FLAG_MUSEUM_3F_SPAWN_NPC2
	return

Museum3F_SetupSprites:
	goto_if_eq VAR_0x8005, 0, Museum3F_TrainerAtLeft
	goto Museum3F_SetTrainerGfx

Museum3F_TrainerAtLeft:
	goto Museum3F_SetTrainerGfx

Museum3F_SetTrainerGfx:
	switch VAR_0x8004
	case 0, Museum3F_GfxOrange
	case 1, Museum3F_GfxSilver
	case 2, Museum3F_GfxBlue
	case 3, Museum3F_GfxPurple
	case 4, Museum3F_GfxPink
	end

Museum3F_GfxOrange:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_ORANGE
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxSilver:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_SILVER
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxBlue:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_BLUE
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxPurple:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_PURPLE
	goto Museum3F_ApplyTrainerGfx
Museum3F_GfxPink:
	setvar VAR_0x8007, OBJ_EVENT_GFX_BRENDAN_PINK
	goto Museum3F_ApplyTrainerGfx

Museum3F_ApplyTrainerGfx:
	goto_if_eq VAR_0x8005, 0, Museum3F_ApplyTrainerGfxToID0
	copyvar VAR_OBJ_GFX_ID_1, VAR_0x8007
	goto Museum3F_SetupPokemon

Museum3F_ApplyTrainerGfxToID0:
	copyvar VAR_OBJ_GFX_ID_0, VAR_0x8007

Museum3F_SetupPokemon:
	@ Assign a random species (from the pool) + matching gfx to each of the 12 Pokemon seats.
	random 32
	copyvar VAR_TEMP_0, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_2, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_1, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_3, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_2, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_4, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_3, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_5, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_4, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_6, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_5, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_7, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_6, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_8, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_8, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_9, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_9, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_A, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_A, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_B, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_B, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_C, VAR_TEMP_7
	random 32
	copyvar VAR_TEMP_C, VAR_RESULT
	copyvar VAR_0x8008, VAR_RESULT
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_D, VAR_TEMP_7
	@ The living legend takes a seat in one room, so hide that seat's Pokemon.
	goto_if_eq VAR_0x8005, 0, Museum3F_LegendSeatRight
	setflag FLAG_MUSEUM_3F_SEAT_LEFT
	clearflag FLAG_MUSEUM_3F_SEAT_RIGHT
	end
Museum3F_LegendSeatRight:
	setflag FLAG_MUSEUM_3F_SEAT_RIGHT
	clearflag FLAG_MUSEUM_3F_SEAT_LEFT
	end

@ ============================================================
@ NPC Interaction Scripts
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_NPC1::
	lock
	faceplayer
	call Museum3F_CheckAllDefeated
	compare VAR_RESULT, 1
	goto_if_eq Museum3F_CrownPickup
	goto_if_eq VAR_0x8005, 0, LilycoveCity_LilycoveMuseum_3F_EventScript_TrainerTalk
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_NPC2::
	lock
	faceplayer
	call Museum3F_CheckAllDefeated
	compare VAR_RESULT, 1
	goto_if_eq Museum3F_CrownPickup
	goto_if_eq VAR_0x8005, 1, LilycoveCity_LilycoveMuseum_3F_EventScript_TrainerTalk
	release
	end

@ ============================================================
@ Trainer Talk and Battle
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
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_ChallengeJason, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Museum3F_DeclineJason
	goto Museum3F_TrainerTalkContinue
Museum3F_TrainerTalkKCH42:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses, MSGBOX_DEFAULT
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_ChallengeKCH42, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Museum3F_DeclineKCH42
	goto Museum3F_TrainerTalkContinue
Museum3F_TrainerTalkJeans:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses, MSGBOX_DEFAULT
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_ChallengeJeans, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Museum3F_DeclineJeans
	goto Museum3F_TrainerTalkContinue
Museum3F_TrainerTalkBeastly:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses, MSGBOX_DEFAULT
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_ChallengeBeastly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Museum3F_DeclineBeastly
	goto Museum3F_TrainerTalkContinue
Museum3F_TrainerTalkFreez:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses, MSGBOX_DEFAULT
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_ChallengeFreez, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Museum3F_DeclineFreez
	goto Museum3F_TrainerTalkContinue

Museum3F_DeclineJason:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipsesSingle, MSGBOX_DEFAULT
	call Museum3F_TurnBackFacing
	release
	end
Museum3F_DeclineKCH42:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_KCH42EllipsesSingle, MSGBOX_DEFAULT
	call Museum3F_TurnBackFacing
	release
	end
Museum3F_DeclineJeans:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipsesSingle, MSGBOX_DEFAULT
	call Museum3F_TurnBackFacing
	release
	end
Museum3F_DeclineBeastly:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipsesSingle, MSGBOX_DEFAULT
	call Museum3F_TurnBackFacing
	release
	end
Museum3F_DeclineFreez:
	msgbox LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipsesSingle, MSGBOX_DEFAULT
	call Museum3F_TurnBackFacing
	release
	end

Museum3F_TrainerTalkContinue:
	closemessage
	hidefollower 0
	copyvar VAR_MUSEUM_3F_TRAINER, VAR_0x8004
	copyvar VAR_MUSEUM_3F_LOCATION, VAR_0x8005
	copyvar VAR_MUSEUM_3F_FILLER, VAR_0x8006
	setvar VAR_TEMP_E, 0
	setflag FLAG_MUSEUM_3F_BATTLE
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_3F, 23, 11
	waitstate
	end

@ ============================================================
@ Battle Dispatch
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_BattleDispatch:
	clearflag FLAG_MUSEUM_3F_BATTLE
	switch VAR_0x8004
	case 0, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJason
	case 1, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleKCH42
	case 2, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleJeans
	case 3, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleBeastly
	case 4, LilycoveCity_LilycoveMuseum_3F_EventScript_BattleFreez
	end

Museum3F_TurnBackFacing:
	goto_if_eq VAR_0x8005, 0, Museum3F_TurnBackNPC1
	applymovement LOCALID_NPC2, Museum3F_Movement_TurnBackRight
	waitmovement 0
	return
Museum3F_TurnBackNPC1:
	applymovement LOCALID_NPC1, Museum3F_Movement_TurnBackLeft
	waitmovement 0
	return

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
	call Museum3F_MarkDefeated
	goto_if_eq VAR_0x8005, 0, Museum3F_RemoveTrainerNPC1
	removeobject LOCALID_NPC2
	goto Museum3F_AdvancePool
Museum3F_RemoveTrainerNPC1:
	removeobject LOCALID_NPC1
Museum3F_AdvancePool:
	call Museum3F_CheckAllDefeated
	compare VAR_RESULT, 1
	goto_if_eq Museum3F_EnterCrown
	call Museum3F_PickLegend
	copyvar VAR_MUSEUM_3F_TRAINER, VAR_0x8004
	random 2
	copyvar VAR_MUSEUM_3F_LOCATION, VAR_RESULT
	random 10
	copyvar VAR_MUSEUM_3F_FILLER, VAR_RESULT
	setflag FLAG_MUSEUM_3F_LEGEND_ACTIVE
	goto Museum3F_BattleCleanup
Museum3F_EnterCrown:
	clearflag FLAG_MUSEUM_3F_LEGEND_ACTIVE
	clearflag FLAG_MUSEUM_3F_CROWN_TAKEN
	random 2
	copyvar VAR_MUSEUM_3F_LOCATION, VAR_RESULT
Museum3F_BattleCleanup:
	hidefollower 0
	setobjectxy LOCALID_PLAYER, 20, 11
	updatefollowingmon
	release
	end



@ ============================================================
@ Species ... GFX  (input: VAR_0x8008, output: VAR_TEMP_7)
@ ============================================================
Museum3F_SpeciesToGfx:
	switch VAR_0x8008
	case 0, MSTG_Lopunny
	case 1, MSTG_Gardevoir
	case 2, MSTG_Chesnaught
	case 3, MSTG_Slowking
	case 4, MSTG_Ampharos
	case 5, MSTG_MimeJr
	case 6, MSTG_Drifloon
	case 7, MSTG_Oshawott
	case 8, MSTG_Greedent
	case 9, MSTG_Snubbull
	case 10, MSTG_Slurpuff
	case 11, MSTG_Hitmontop
	case 12, MSTG_Yamper
	case 13, MSTG_Appletun
	case 14, MSTG_Skiploom
	case 15, MSTG_Swoobat
	case 16, MSTG_Seel
	case 17, MSTG_Furret
	case 18, MSTG_Torchic
	case 19, MSTG_Spinda
	case 20, MSTG_Darumaka
	case 21, MSTG_Gholdengo
	case 22, MSTG_Ducklett
	case 23, MSTG_Helioptile
	case 24, MSTG_Brionne
	case 25, MSTG_Corphish
	case 26, MSTG_Teddiursa
	case 27, MSTG_Magnemite
	case 28, MSTG_SliggooHisui
	case 29, MSTG_Persian
	case 30, MSTG_Rhydon
	case 31, MSTG_Unfezant
	end

MSTG_Lopunny:
	setvar VAR_TEMP_7, 16812
	return
MSTG_Gardevoir:
	setvar VAR_TEMP_7, 16666
	return
MSTG_Chesnaught:
	setvar VAR_TEMP_7, 17036
	return
MSTG_Slowking:
	setvar VAR_TEMP_7, 16583, FALSE
	return
MSTG_Ampharos:
	setvar VAR_TEMP_7, 16565, FALSE
	return
MSTG_MimeJr:
	setvar VAR_TEMP_7, 16823
	return
MSTG_Drifloon:
	setvar VAR_TEMP_7, 16809
	return
MSTG_Oshawott:
	setvar VAR_TEMP_7, 16885
	return
MSTG_Greedent:
	setvar VAR_TEMP_7, 17204
	return
MSTG_Snubbull:
	setvar VAR_TEMP_7, 16593, FALSE
	return
MSTG_Slurpuff:
	setvar VAR_TEMP_7, 17069
	return
MSTG_Hitmontop:
	setvar VAR_TEMP_7, 16621, FALSE
	return
MSTG_Yamper:
	setvar VAR_TEMP_7, 17219
	return
MSTG_Appletun:
	setvar VAR_TEMP_7, 17226
	return
MSTG_Skiploom:
	setvar VAR_TEMP_7, 16572, FALSE
	return
MSTG_Swoobat:
	setvar VAR_TEMP_7, 16912
	return
MSTG_Seel:
	setvar VAR_TEMP_7, 16470, FALSE
	return
MSTG_Furret:
	setvar VAR_TEMP_7, 16546, FALSE
	return
MSTG_Torchic:
	setvar VAR_TEMP_7, 16639, FALSE
	return
MSTG_Spinda:
	setvar VAR_TEMP_7, 16711
	return
MSTG_Darumaka:
	setvar VAR_TEMP_7, 16938
	return
MSTG_Gholdengo:
	setvar VAR_TEMP_7, 17777
	return
MSTG_Ducklett:
	setvar VAR_TEMP_7, 16964
	return
MSTG_Helioptile:
	setvar VAR_TEMP_7, 17078
	return
MSTG_Brionne:
	setvar VAR_TEMP_7, 17113
	return
MSTG_Corphish:
	setvar VAR_TEMP_7, 16725
	return
MSTG_Teddiursa:
	setvar VAR_TEMP_7, 16600, FALSE
	return
MSTG_Magnemite:
	setvar VAR_TEMP_7, 16465, FALSE
	return
MSTG_SliggooHisui:
	setvar VAR_TEMP_7, 17389
	return
MSTG_Persian:
	setvar VAR_TEMP_7, 16437, FALSE
	return
MSTG_Rhydon:
	setvar VAR_TEMP_7, 16496, FALSE
	return
MSTG_Unfezant:
	setvar VAR_TEMP_7, 16905, FALSE
	return

@ ============================================================
@ Pokemon Interaction Scripts
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_Poke1::
	lock
	setvar VAR_0x8009, 1
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke2::
	lock
	setvar VAR_0x8009, 2
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke3::
	lock
	setvar VAR_0x8009, 3
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke4::
	lock
	setvar VAR_0x8009, 4
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke5::
	lock
	setvar VAR_0x8009, 5
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke6::
	lock
	setvar VAR_0x8009, 6
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke7::
	lock
	setvar VAR_0x8009, 7
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke8::
	lock
	setvar VAR_0x8009, 8
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke9::
	lock
	setvar VAR_0x8009, 9
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke10::
	lock
	setvar VAR_0x8009, 10
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke11::
	lock
	setvar VAR_0x8009, 11
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke12::
	lock
	setvar VAR_0x8009, 12
	call Museum3F_PokemonDialogue
	release
	end

@ ============================================================
@ Pokemon Dialogue Dispatch
@ ============================================================
@ Reads VAR_0x8009 (1-6), loads encoded species from VAR_TEMP_X
@ into VAR_0x8008 (decoded), checks table (encoded >= 29).

Museum3F_PokemonDialogue:
	switch VAR_0x8009
	case 1, MDialogueLoad1
	case 2, MDialogueLoad2
	case 3, MDialogueLoad3
	case 4, MDialogueLoad4
	case 5, MDialogueLoad5
	case 6, MDialogueLoad6
	case 7, MDialogueLoad7
	case 8, MDialogueLoad8
	case 9, MDialogueLoad9
	case 10, MDialogueLoad10
	case 11, MDialogueLoad11
	case 12, MDialogueLoad12
	end

MDialogueLoad1:
	copyvar VAR_0x8008, VAR_TEMP_0
	goto MDialogueGeneric
MDialogueLoad2:
	copyvar VAR_0x8008, VAR_TEMP_1
	goto MDialogueGeneric
MDialogueLoad3:
	copyvar VAR_0x8008, VAR_TEMP_2
	goto MDialogueGeneric
MDialogueLoad4:
	copyvar VAR_0x8008, VAR_TEMP_3
	goto MDialogueGeneric
MDialogueLoad5:
	copyvar VAR_0x8008, VAR_TEMP_4
	goto MDialogueGeneric
MDialogueLoad6:
	copyvar VAR_0x8008, VAR_TEMP_5
	goto MDialogueGeneric
MDialogueLoad7:
	copyvar VAR_0x8008, VAR_TEMP_6
	goto MDialogueGeneric
MDialogueLoad8:
	copyvar VAR_0x8008, VAR_TEMP_8
	goto MDialogueGeneric
MDialogueLoad9:
	copyvar VAR_0x8008, VAR_TEMP_9
	goto MDialogueGeneric
MDialogueLoad10:
	copyvar VAR_0x8008, VAR_TEMP_A
	goto MDialogueGeneric
MDialogueLoad11:
	copyvar VAR_0x8008, VAR_TEMP_B
	goto MDialogueGeneric
MDialogueLoad12:
	copyvar VAR_0x8008, VAR_TEMP_C
	goto MDialogueGeneric

MDialogueGeneric:
	call Museum3F_IndexToSpecies
	bufferspeciesname STR_VAR_1, VAR_0x800B
	@ Deterministic card-game phrase per species (index mod 10) so repeated talks are always the same
	switch VAR_0x8008
	case 0, MTextCardPhrase0
	case 1, MTextCardPhrase1
	case 2, MTextCardPhrase2
	case 3, MTextCardPhrase3
	case 4, MTextCardPhrase4
	case 5, MTextCardPhrase5
	case 6, MTextCardPhrase6
	case 7, MTextCardPhrase7
	case 8, MTextCardPhrase8
	case 9, MTextCardPhrase9
	case 10, MTextCardPhrase0
	case 11, MTextCardPhrase1
	case 12, MTextCardPhrase2
	case 13, MTextCardPhrase3
	case 14, MTextCardPhrase4
	case 15, MTextCardPhrase5
	case 16, MTextCardPhrase6
	case 17, MTextCardPhrase7
	case 18, MTextCardPhrase8
	case 19, MTextCardPhrase9
	case 20, MTextCardPhrase0
	case 21, MTextCardPhrase1
	case 22, MTextCardPhrase2
	case 23, MTextCardPhrase3
	case 24, MTextCardPhrase4
	case 25, MTextCardPhrase5
	case 26, MTextCardPhrase6
	case 27, MTextCardPhrase7
	case 28, MTextCardPhrase8
	case 29, MTextCardPhrase9
	case 30, MTextCardPhrase0
	case 31, MTextCardPhrase1
	end

@ ============================================================
@ Convert species index (VAR_0x8008, 0-31) into SPECIES_* (VAR_0x800B)
@ ============================================================
Museum3F_IndexToSpecies:
	switch VAR_0x8008
	case 0, MISLopunny
	case 1, MISGardevoir
	case 2, MISChesnaught
	case 3, MISSlowking
	case 4, MISAmpharos
	case 5, MISMimeJr
	case 6, MISDrifloon
	case 7, MISOShawott
	case 8, MISGreedent
	case 9, MISSnubbull
	case 10, MISSlurpuff
	case 11, MISHitmontop
	case 12, MISYamper
	case 13, MISAppletun
	case 14, MISSkiploom
	case 15, MISSwoobat
	case 16, MISSeel
	case 17, MISFurret
	case 18, MISTorchic
	case 19, MISSpinda
	case 20, MISDarumaka
	case 21, MISGholdengo
	case 22, MISDucklett
	case 23, MISHelioptile
	case 24, MISBrionne
	case 25, MISCorphish
	case 26, MISTeddiursa
	case 27, MISMagnemite
	case 28, MISSliggoo
	case 29, MISPersian
	case 30, MISRhydon
	case 31, MISUnfezant
	end

MISLopunny:
	setvar VAR_0x800B, SPECIES_LOPUNNY
	return
MISGardevoir:
	setvar VAR_0x800B, SPECIES_GARDEVOIR
	return
MISChesnaught:
	setvar VAR_0x800B, SPECIES_CHESNAUGHT
	return
MISSlowking:
	setvar VAR_0x800B, SPECIES_SLOWKING
	return
MISAmpharos:
	setvar VAR_0x800B, SPECIES_AMPHAROS
	return
MISMimeJr:
	setvar VAR_0x800B, SPECIES_MIME_JR
	return
MISDrifloon:
	setvar VAR_0x800B, SPECIES_DRIFLOON
	return
MISOShawott:
	setvar VAR_0x800B, SPECIES_OSHAWOTT
	return
MISGreedent:
	setvar VAR_0x800B, SPECIES_GREEDENT
	return
MISSnubbull:
	setvar VAR_0x800B, SPECIES_SNUBBULL
	return
MISSlurpuff:
	setvar VAR_0x800B, SPECIES_SLURPUFF
	return
MISHitmontop:
	setvar VAR_0x800B, SPECIES_HITMONTOP
	return
MISYamper:
	setvar VAR_0x800B, SPECIES_YAMPER
	return
MISAppletun:
	setvar VAR_0x800B, SPECIES_APPLETUN
	return
MISSkiploom:
	setvar VAR_0x800B, SPECIES_SKIPLOOM
	return
MISSwoobat:
	setvar VAR_0x800B, SPECIES_SWOOBAT
	return
MISSeel:
	setvar VAR_0x800B, SPECIES_SEEL
	return
MISFurret:
	setvar VAR_0x800B, SPECIES_FURRET
	return
MISTorchic:
	setvar VAR_0x800B, SPECIES_TORCHIC
	return
MISSpinda:
	setvar VAR_0x800B, SPECIES_SPINDA
	return
MISDarumaka:
	setvar VAR_0x800B, SPECIES_DARUMAKA
	return
MISGholdengo:
	setvar VAR_0x800B, SPECIES_GHOLDENGO
	return
MISDucklett:
	setvar VAR_0x800B, SPECIES_DUCKLETT
	return
MISHelioptile:
	setvar VAR_0x800B, SPECIES_HELIOPTILE
	return
MISBrionne:
	setvar VAR_0x800B, SPECIES_BRIONNE
	return
MISCorphish:
	setvar VAR_0x800B, SPECIES_CORPHISH
	return
MISTeddiursa:
	setvar VAR_0x800B, SPECIES_TEDDIURSA
	return
MISMagnemite:
	setvar VAR_0x800B, SPECIES_MAGNEMITE
	return
MISSliggoo:
	setvar VAR_0x800B, SPECIES_SLIGGOO
	return
MISPersian:
	setvar VAR_0x800B, SPECIES_PERSIAN
	return
MISRhydon:
	setvar VAR_0x800B, SPECIES_RHYDON
	return
MISUnfezant:
	setvar VAR_0x800B, SPECIES_UNFEZANT
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

Museum3F_Movement_TurnBackLeft:
	face_left
	step_end

Museum3F_Movement_TurnBackRight:
	face_right
	step_end

@ ============================================================
@ Text - Trainer
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipses:
	.string "JASON: ... ... ...$"
LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses:
	.string "KCH42: ... ... ...$"
LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses:
	.string "JEANS: ... ... ...$"
LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses:
	.string "BEASTLY: ... ... ...$"
LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses:
	.string "FREEZ: ... ... ...$"

LilycoveCity_LilycoveMuseum_3F_Text_ChallengeJason:
	.string "Challenge JASON?$"
LilycoveCity_LilycoveMuseum_3F_Text_ChallengeKCH42:
	.string "Challenge KCH42?$"
LilycoveCity_LilycoveMuseum_3F_Text_ChallengeJeans:
	.string "Challenge JEANS?$"
LilycoveCity_LilycoveMuseum_3F_Text_ChallengeBeastly:
	.string "Challenge BEASTLY?$"
LilycoveCity_LilycoveMuseum_3F_Text_ChallengeFreez:
	.string "Challenge FREEZ?$"

LilycoveCity_LilycoveMuseum_3F_Text_JasonEllipsesSingle:
	.string "JASON: ...$"
LilycoveCity_LilycoveMuseum_3F_Text_KCH42EllipsesSingle:
	.string "KCH42: ...$"
LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipsesSingle:
	.string "JEANS: ...$"
LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipsesSingle:
	.string "BEASTLY: ...$"
LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipsesSingle:
	.string "FREEZ: ...$"


@ ============================================================
@ Text - Pokemon Card Game
@ ============================================================
MTextCardPhrase0:
	msgbox MTextCardPhrase0Str, MSGBOX_DEFAULT
	return
MTextCardPhrase0Str:
	.string "{STR_VAR_1} is extremely focused on\n"
	.string "their hand of cards.$"
MTextCardPhrase1:
	msgbox MTextCardPhrase1Str, MSGBOX_DEFAULT
	return
MTextCardPhrase1Str:
	.string "{STR_VAR_1} is fidgeting nervously.$"
MTextCardPhrase2:
	msgbox MTextCardPhrase2Str, MSGBOX_DEFAULT
	return
MTextCardPhrase2Str:
	.string "{STR_VAR_1} is holding their cards\n"
	.string "upside down...$"
MTextCardPhrase3:
	msgbox MTextCardPhrase3Str, MSGBOX_DEFAULT
	return
MTextCardPhrase3Str:
	.string "{STR_VAR_1} is too focused on the game\n"
	.string "to pay you any mind.$"
MTextCardPhrase4:
	msgbox MTextCardPhrase4Str, MSGBOX_DEFAULT
	return
MTextCardPhrase4Str:
	.string "You peer over {STR_VAR_1}'s shoulder...\n"
	.string "Their hand doesn't seem very good.$"
MTextCardPhrase5:
	msgbox MTextCardPhrase5Str, MSGBOX_DEFAULT
	return
MTextCardPhrase5Str:
	.string "{STR_VAR_1} is dealing cards like\n"
	.string "a pro!$"
MTextCardPhrase6:
	msgbox MTextCardPhrase6Str, MSGBOX_DEFAULT
	return
MTextCardPhrase6Str:
	.string "{STR_VAR_1} looks like they're doing\n"
	.string "well in the game so far$"
MTextCardPhrase7:
	msgbox MTextCardPhrase7Str, MSGBOX_DEFAULT
	return
MTextCardPhrase7Str:
	.string "{STR_VAR_1} is thinking about their\n"
	.string "next move carefully.$"
MTextCardPhrase8:
	msgbox MTextCardPhrase8Str, MSGBOX_DEFAULT
	return
MTextCardPhrase8Str:
	.string "{STR_VAR_1} has won big so far!$"
MTextCardPhrase9:
	msgbox MTextCardPhrase9Str, MSGBOX_DEFAULT
	return
MTextCardPhrase9Str:
	.string "{STR_VAR_1} is studying their cards\n"
	.string "closely.$"

MTextMuseumCrownEmpty:
	.string "There's nothing here anymore.$"

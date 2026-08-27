.set LOCALID_NPC1, 1
.set LOCALID_NPC2, 2
.set LOCALID_POKE1, 3
.set LOCALID_POKE2, 4
.set LOCALID_POKE3, 5
.set LOCALID_POKE4, 6
.set LOCALID_POKE5, 7
.set LOCALID_POKE6, 8

LilycoveCity_LilycoveMuseum_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_LilycoveMuseum_3F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_LilycoveMuseum_3F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LilycoveCity_LilycoveMuseum_3F_OnWarp
	.byte 0

@ ============================================================
@ OnFrame
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
@ OnWarp
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_OnWarp:
	goto_if_set FLAG_MUSEUM_3F_BATTLE, Museum3F_OnWarp_FaceWest
	end

Museum3F_OnWarp_FaceWest:
	turnobject LOCALID_PLAYER, DIR_WEST
	end

@ ============================================================
@ OnTransition
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
	call Museum3F_SetupPokemon
	end

Museum3F_CopyFillerToID1:
	copyvar VAR_OBJ_GFX_ID_1, VAR_0x8007
	call Museum3F_SetupPokemon
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
@ Pokémon Setup
@ ============================================================
@ VAR_0x8005 = 0: trainer right → Pokémon left room
@ VAR_0x8005 = 1: trainer left → Pokémon right room
@ Left room:  (0,11)-(5,16), off-limits (2,14)/(3,14), table (2,13)/(3,13)
@ Right room: (29,11)-(34,16), off-limits (31,14)/(32,14), table (31,13)/(32,13)
@
@ VAR_TEMP_0-5: per-Pokémon storage, encoded as:
@   value 0-28   = species index, not on table
@   value 29-57  = species index - 29, ON table (species = value - 29)
@
@ VAR_0x8007: Pokémon count (5 or 6)
@ VAR_0x8008: scratch (species decode / GFX input)
@ VAR_0x8009: Pokémon interaction index (1-6) during dialogue

Museum3F_SetupPokemon:
	@ Remove the filler NPC from the Pokémon room
	goto_if_eq VAR_0x8005, 0, MPokemonRemoveNPC2
	removeobject LOCALID_NPC1
	goto MPokemonRandomCount
MPokemonRemoveNPC2:
	removeobject LOCALID_NPC2
MPokemonRandomCount:
	random 2
	addvar VAR_RESULT, 5
	copyvar VAR_0x8007, VAR_RESULT

	@ Select non-adjacent position template (10 pre-verified layouts)
	random 10
	switch VAR_RESULT
	case 0, MTemplate0
	case 1, MTemplate1
	case 2, MTemplate2
	case 3, MTemplate3
	case 4, MTemplate4
	case 5, MTemplate5
	case 6, MTemplate6
	case 7, MTemplate7
	case 8, MTemplate8
	case 9, MTemplate9
	end

MTemplate0:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 3
	setvar VAR_TEMP_2, 7
	setvar VAR_TEMP_3, 19
	setvar VAR_TEMP_4, 24
	setvar VAR_TEMP_5, 31
	goto MPhase2
MTemplate1:
	setvar VAR_TEMP_0, 1
	setvar VAR_TEMP_1, 4
	setvar VAR_TEMP_2, 9
	setvar VAR_TEMP_3, 20
	setvar VAR_TEMP_4, 25
	setvar VAR_TEMP_5, 30
	goto MPhase2
MTemplate2:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 2
	setvar VAR_TEMP_2, 4
	setvar VAR_TEMP_3, 20
	setvar VAR_TEMP_4, 25
	setvar VAR_TEMP_5, 30
	goto MPhase2
MTemplate3:
	setvar VAR_TEMP_0, 1
	setvar VAR_TEMP_1, 3
	setvar VAR_TEMP_2, 10
	setvar VAR_TEMP_3, 18
	setvar VAR_TEMP_4, 24
	setvar VAR_TEMP_5, 33
	goto MPhase2
MTemplate4:
	setvar VAR_TEMP_0, 1
	setvar VAR_TEMP_1, 5
	setvar VAR_TEMP_2, 6
	setvar VAR_TEMP_3, 20
	setvar VAR_TEMP_4, 24
	setvar VAR_TEMP_5, 29
	goto MPhase2
MTemplate5:
	setvar VAR_TEMP_0, 2
	setvar VAR_TEMP_1, 4
	setvar VAR_TEMP_2, 11
	setvar VAR_TEMP_3, 18
	setvar VAR_TEMP_4, 23
	setvar VAR_TEMP_5, 31
	goto MPhase2
MTemplate6:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 3
	setvar VAR_TEMP_2, 8
	setvar VAR_TEMP_3, 21
	setvar VAR_TEMP_4, 26
	setvar VAR_TEMP_5, 31
	goto MPhase2
MTemplate7:
	setvar VAR_TEMP_0, 1
	setvar VAR_TEMP_1, 5
	setvar VAR_TEMP_2, 8
	setvar VAR_TEMP_3, 18
	setvar VAR_TEMP_4, 25
	setvar VAR_TEMP_5, 29
	goto MPhase2
MTemplate8:
	setvar VAR_TEMP_0, 0
	setvar VAR_TEMP_1, 4
	setvar VAR_TEMP_2, 8
	setvar VAR_TEMP_3, 19
	setvar VAR_TEMP_4, 24
	setvar VAR_TEMP_5, 31
	goto MPhase2
MTemplate9:
	setvar VAR_TEMP_0, 3
	setvar VAR_TEMP_1, 5
	setvar VAR_TEMP_2, 6
	setvar VAR_TEMP_3, 19
	setvar VAR_TEMP_4, 24
	setvar VAR_TEMP_5, 33
	goto MPhase2

MPhase2:
	@ Per Pokémon — set position, pick species, encode table, set GFX, set movement
	@ Pokémon 1
	call Museum3F_SetPos1
	random 29
	@ Check if on table (position index 14 or 15)
	compare VAR_TEMP_0, 14
	goto_if_eq MPPoke1OnTable
	compare VAR_TEMP_0, 15
	goto_if_eq MPPoke1OnTable
	@ Not on table — store species as-is
	copyvar VAR_TEMP_0, VAR_RESULT
	goto MPPoke1Gfx
MPPoke1OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_0, VAR_RESULT
MPPoke1Gfx:
	call Museum3F_DecodeSpecies1
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_2, VAR_TEMP_7
	call Museum3F_SetMove1

	@ Pokémon 2
	call Museum3F_SetPos2
	random 29
	compare VAR_TEMP_1, 14
	goto_if_eq MPPoke2OnTable
	compare VAR_TEMP_1, 15
	goto_if_eq MPPoke2OnTable
	copyvar VAR_TEMP_1, VAR_RESULT
	goto MPPoke2Gfx
MPPoke2OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_1, VAR_RESULT
MPPoke2Gfx:
	call Museum3F_DecodeSpecies2
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_3, VAR_TEMP_7
	call Museum3F_SetMove2

	@ Pokémon 3
	call Museum3F_SetPos3
	random 29
	compare VAR_TEMP_2, 14
	goto_if_eq MPPoke3OnTable
	compare VAR_TEMP_2, 15
	goto_if_eq MPPoke3OnTable
	copyvar VAR_TEMP_2, VAR_RESULT
	goto MPPoke3Gfx
MPPoke3OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_2, VAR_RESULT
MPPoke3Gfx:
	call Museum3F_DecodeSpecies3
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_4, VAR_TEMP_7
	call Museum3F_SetMove3

	@ Pokémon 4
	call Museum3F_SetPos4
	random 29
	compare VAR_TEMP_3, 14
	goto_if_eq MPPoke4OnTable
	compare VAR_TEMP_3, 15
	goto_if_eq MPPoke4OnTable
	copyvar VAR_TEMP_3, VAR_RESULT
	goto MPPoke4Gfx
MPPoke4OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_3, VAR_RESULT
MPPoke4Gfx:
	call Museum3F_DecodeSpecies4
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_5, VAR_TEMP_7
	call Museum3F_SetMove4

	@ Pokémon 5
	call Museum3F_SetPos5
	random 29
	compare VAR_TEMP_4, 14
	goto_if_eq MPPoke5OnTable
	compare VAR_TEMP_4, 15
	goto_if_eq MPPoke5OnTable
	copyvar VAR_TEMP_4, VAR_RESULT
	goto MPPoke5Gfx
MPPoke5OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_4, VAR_RESULT
MPPoke5Gfx:
	call Museum3F_DecodeSpecies5
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_6, VAR_TEMP_7
	call Museum3F_SetMove5

	@ Pokémon 6
	call Museum3F_SetPos6
	random 29
	compare VAR_TEMP_5, 14
	goto_if_eq MPPoke6OnTable
	compare VAR_TEMP_5, 15
	goto_if_eq MPPoke6OnTable
	copyvar VAR_TEMP_5, VAR_RESULT
	goto MPPoke6Gfx
MPPoke6OnTable:
	addvar VAR_RESULT, 29
	copyvar VAR_TEMP_5, VAR_RESULT
MPPoke6Gfx:
	call Museum3F_DecodeSpecies6
	call Museum3F_SpeciesToGfx
	setorcopyvar VAR_OBJ_GFX_ID_7, VAR_TEMP_7
	call Museum3F_SetMove6

	@ Hide unused slot if only 5
	compare VAR_0x8007, 5
	goto_if_ne MPokemonAllSix
	removeobject LOCALID_POKE6
MPokemonAllSix:
	setvar VAR_TEMP_0, 0
	return

@ ============================================================
@ Decode Species from VAR_TEMP_X → VAR_0x8008
@ ============================================================
Museum3F_DecodeSpecies1:
	setorcopyvar VAR_0x8008, VAR_TEMP_0
	compare VAR_0x8008, 29
	goto_if_lt MDS1done
	subvar VAR_0x8008, 29
MDS1done:
	return

Museum3F_DecodeSpecies2:
	setorcopyvar VAR_0x8008, VAR_TEMP_1
	compare VAR_0x8008, 29
	goto_if_lt MDS2done
	subvar VAR_0x8008, 29
MDS2done:
	return

Museum3F_DecodeSpecies3:
	setorcopyvar VAR_0x8008, VAR_TEMP_2
	compare VAR_0x8008, 29
	goto_if_lt MDS3done
	subvar VAR_0x8008, 29
MDS3done:
	return

Museum3F_DecodeSpecies4:
	setorcopyvar VAR_0x8008, VAR_TEMP_3
	compare VAR_0x8008, 29
	goto_if_lt MDS4done
	subvar VAR_0x8008, 29
MDS4done:
	return

Museum3F_DecodeSpecies5:
	setorcopyvar VAR_0x8008, VAR_TEMP_4
	compare VAR_0x8008, 29
	goto_if_lt MDS5done
	subvar VAR_0x8008, 29
MDS5done:
	return

Museum3F_DecodeSpecies6:
	setorcopyvar VAR_0x8008, VAR_TEMP_5
	compare VAR_0x8008, 29
	goto_if_lt MDS6done
	subvar VAR_0x8008, 29
MDS6done:
	return

@ ============================================================
@ Species → GFX  (input: VAR_0x8008, output: VAR_TEMP_7)
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
	case 21, MSTG_Maractus
	case 22, MSTG_Ducklett
	case 23, MSTG_Helioptile
	case 24, MSTG_Brionne
	case 25, MSTG_Corphish
	case 26, MSTG_Teddiursa
	case 27, MSTG_Magnemite
	case 28, MSTG_SliggooHisui
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
	setvar VAR_TEMP_7, 16583
	return
MSTG_Ampharos:
	setvar VAR_TEMP_7, 16565
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
	setvar VAR_TEMP_7, 16593
	return
MSTG_Slurpuff:
	setvar VAR_TEMP_7, 17069
	return
MSTG_Hitmontop:
	setvar VAR_TEMP_7, 16621
	return
MSTG_Yamper:
	setvar VAR_TEMP_7, 17219
	return
MSTG_Appletun:
	setvar VAR_TEMP_7, 17226
	return
MSTG_Skiploom:
	setvar VAR_TEMP_7, 16572
	return
MSTG_Swoobat:
	setvar VAR_TEMP_7, 16912
	return
MSTG_Seel:
	setvar VAR_TEMP_7, 16470
	return
MSTG_Furret:
	setvar VAR_TEMP_7, 16546
	return
MSTG_Torchic:
	setvar VAR_TEMP_7, 16639
	return
MSTG_Spinda:
	setvar VAR_TEMP_7, 16711
	return
MSTG_Darumaka:
	setvar VAR_TEMP_7, 16938
	return
MSTG_Maractus:
	setvar VAR_TEMP_7, 16940
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
	setvar VAR_TEMP_7, 16600
	return
MSTG_Magnemite:
	setvar VAR_TEMP_7, 16465
	return
MSTG_SliggooHisui:
	setvar VAR_TEMP_7, 17389
	return

@ ============================================================
@ Pokémon Interaction Scripts
@ ============================================================
LilycoveCity_LilycoveMuseum_3F_EventScript_Poke1::
	lock
	faceplayer
	setvar VAR_0x8009, 1
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke2::
	lock
	faceplayer
	setvar VAR_0x8009, 2
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke3::
	lock
	faceplayer
	setvar VAR_0x8009, 3
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke4::
	lock
	faceplayer
	setvar VAR_0x8009, 4
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke5::
	lock
	faceplayer
	setvar VAR_0x8009, 5
	call Museum3F_PokemonDialogue
	release
	end

LilycoveCity_LilycoveMuseum_3F_EventScript_Poke6::
	lock
	faceplayer
	setvar VAR_0x8009, 6
	call Museum3F_PokemonDialogue
	release
	end

@ ============================================================
@ Pokémon Dialogue Dispatch
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
	end

MDialogueLoad1:
	call Museum3F_DecodeSpecies1
	goto MDialogueCheckTable
MDialogueLoad2:
	call Museum3F_DecodeSpecies2
	goto MDialogueCheckTable
MDialogueLoad3:
	call Museum3F_DecodeSpecies3
	goto MDialogueCheckTable
MDialogueLoad4:
	call Museum3F_DecodeSpecies4
	goto MDialogueCheckTable
MDialogueLoad5:
	call Museum3F_DecodeSpecies5
	goto MDialogueCheckTable
MDialogueLoad6:
	call Museum3F_DecodeSpecies6
	goto MDialogueCheckTable

MDialogueCheckTable:
	@ Table flag is encoded: if original VAR_TEMP_X >= 29, on table
	@ We need the original encoded value. Re-load it.
	switch VAR_0x8009
	case 1, MChkTbl1
	case 2, MChkTbl2
	case 3, MChkTbl3
	case 4, MChkTbl4
	case 5, MChkTbl5
	case 6, MChkTbl6
	end

MChkTbl1:
	compare VAR_TEMP_0, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric
MChkTbl2:
	compare VAR_TEMP_1, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric
MChkTbl3:
	compare VAR_TEMP_2, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric
MChkTbl4:
	compare VAR_TEMP_3, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric
MChkTbl5:
	compare VAR_TEMP_4, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric
MChkTbl6:
	compare VAR_TEMP_5, 29
	goto_if_ge MDialogueOnTable
	goto MDialogueGeneric

MDialogueGeneric:
	switch VAR_0x8008
	case 0, MTextGenericLopunny
	case 1, MTextGenericGardevoir
	case 2, MTextGenericChesnaught
	case 3, MTextGenericSlowking
	case 4, MTextGenericAmpharos
	case 5, MTextGenericMimeJr
	case 6, MTextGenericDrifloon
	case 7, MTextGenericOshawott
	case 8, MTextGenericGreedent
	case 9, MTextGenericSnubbull
	case 10, MTextGenericSlurpuff
	case 11, MTextGenericHitmontop
	case 12, MTextGenericYamper
	case 13, MTextGenericAppletun
	case 14, MTextGenericSkiploom
	case 15, MTextGenericSwoobat
	case 16, MTextGenericSeel
	case 17, MTextGenericFurret
	case 18, MTextGenericTorchic
	case 19, MTextGenericSpinda
	case 20, MTextGenericDarumaka
	case 21, MTextGenericMaractus
	case 22, MTextGenericDucklett
	case 23, MTextGenericHelioptile
	case 24, MTextGenericBrionne
	case 25, MTextGenericCorphish
	case 26, MTextGenericTeddiursa
	case 27, MTextGenericMagnemite
	case 28, MTextGenericSliggoo
	end

MDialogueOnTable:
	switch VAR_0x8008
	case 0, MTextTableLopunny
	case 1, MTextTableGardevoir
	case 2, MTextTableChesnaught
	case 3, MTextTableSlowking
	case 4, MTextTableAmpharos
	case 5, MTextTableMimeJr
	case 6, MTextTableDrifloon
	case 7, MTextTableOshawott
	case 8, MTextTableGreedent
	case 9, MTextTableSnubbull
	case 10, MTextTableSlurpuff
	case 11, MTextTableHitmontop
	case 12, MTextTableYamper
	case 13, MTextTableAppletun
	case 14, MTextTableSkiploom
	case 15, MTextTableSwoobat
	case 16, MTextTableSeel
	case 17, MTextTableFurret
	case 18, MTextTableTorchic
	case 19, MTextTableSpinda
	case 20, MTextTableDarumaka
	case 21, MTextTableMaractus
	case 22, MTextTableDucklett
	case 23, MTextTableHelioptile
	case 24, MTextTableBrionne
	case 25, MTextTableCorphish
	case 26, MTextTableTeddiursa
	case 27, MTextTableMagnemite
	case 28, MTextTableSliggoo
	end

@ ============================================================
@ Position Index → Coordinates (left room base)
@ Input: VAR_TEMP_7 = index 0-33
@ Output: VAR_TEMP_6 = x, VAR_TEMP_7 = y
@ ============================================================
Museum3F_IndexToCoords:
	copyvar VAR_TEMP_6, VAR_TEMP_7
	compare VAR_TEMP_6, 6
	goto_if_lt MICRow11
	compare VAR_TEMP_6, 12
	goto_if_lt MICRow12
	compare VAR_TEMP_6, 18
	goto_if_lt MICRow13
	compare VAR_TEMP_6, 22
	goto_if_lt MICRow14
	compare VAR_TEMP_6, 28
	goto_if_lt MICRow15
	goto MICRow16
MICRow11:
	setvar VAR_TEMP_7, 11
	return
MICRow12:
	setvar VAR_TEMP_7, 12
	addvar VAR_TEMP_6, -6
	return
MICRow13:
	setvar VAR_TEMP_7, 13
	addvar VAR_TEMP_6, -12
	return
MICRow14:
	setvar VAR_TEMP_7, 14
	addvar VAR_TEMP_6, -18
	compare VAR_TEMP_6, 2
	goto_if_lt MICRow14Done
	addvar VAR_TEMP_6, 2
MICRow14Done:
	return
MICRow15:
	setvar VAR_TEMP_7, 15
	addvar VAR_TEMP_6, -22
	return
MICRow16:
	setvar VAR_TEMP_7, 16
	addvar VAR_TEMP_6, -28
	return

@ ============================================================
@ Set Pokémon Position
@ ============================================================
Museum3F_SetPos1:
	copyvar VAR_TEMP_7, VAR_TEMP_0
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP1Left
	addvar VAR_TEMP_6, 29
MSP1Left:
	setobjectxyperm LOCALID_POKE1, VAR_TEMP_6, VAR_TEMP_7
	return

Museum3F_SetPos2:
	copyvar VAR_TEMP_7, VAR_TEMP_1
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP2Left
	addvar VAR_TEMP_6, 29
MSP2Left:
	setobjectxyperm LOCALID_POKE2, VAR_TEMP_6, VAR_TEMP_7
	return

Museum3F_SetPos3:
	copyvar VAR_TEMP_7, VAR_TEMP_2
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP3Left
	addvar VAR_TEMP_6, 29
MSP3Left:
	setobjectxyperm LOCALID_POKE3, VAR_TEMP_6, VAR_TEMP_7
	return

Museum3F_SetPos4:
	copyvar VAR_TEMP_7, VAR_TEMP_3
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP4Left
	addvar VAR_TEMP_6, 29
MSP4Left:
	setobjectxyperm LOCALID_POKE4, VAR_TEMP_6, VAR_TEMP_7
	return

Museum3F_SetPos5:
	copyvar VAR_TEMP_7, VAR_TEMP_4
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP5Left
	addvar VAR_TEMP_6, 29
MSP5Left:
	setobjectxyperm LOCALID_POKE5, VAR_TEMP_6, VAR_TEMP_7
	return

Museum3F_SetPos6:
	copyvar VAR_TEMP_7, VAR_TEMP_5
	call Museum3F_IndexToCoords
	compare VAR_0x8005, 1
	goto_if_ne MSP6Left
	addvar VAR_TEMP_6, 29
MSP6Left:
	setobjectxyperm LOCALID_POKE6, VAR_TEMP_6, VAR_TEMP_7
	return

@ ============================================================
@ Set Movement Type
@ VAR_0x8008 = decoded species, VAR_TEMP_X = encoded value
@ ============================================================
@ Appletun (13) → FACE_LEFT always
@ On table (encoded >= 29, not Appletun) → random rotate CW/CCW
@ Mime Jr. (5) → ROTATE_CLOCKWISE always
@ Default → FACE_DOWN

Museum3F_SetMove1:
	compare VAR_0x8008, 13
	goto_if_eq MSM1Appletun
	compare VAR_TEMP_0, 29
	goto_if_ge MSM1Table
	compare VAR_0x8008, 5
	goto_if_eq MSM1MimeJr
	setobjectmovementtype LOCALID_POKE1, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM1Appletun:
	setobjectmovementtype LOCALID_POKE1, MOVEMENT_TYPE_FACE_LEFT
	return
MSM1Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM1TableCW
	setobjectmovementtype LOCALID_POKE1, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM1TableCW:
	setobjectmovementtype LOCALID_POKE1, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM1MimeJr:
	setobjectmovementtype LOCALID_POKE1, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

Museum3F_SetMove2:
	compare VAR_0x8008, 13
	goto_if_eq MSM2Appletun
	compare VAR_TEMP_1, 29
	goto_if_ge MSM2Table
	compare VAR_0x8008, 5
	goto_if_eq MSM2MimeJr
	setobjectmovementtype LOCALID_POKE2, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM2Appletun:
	setobjectmovementtype LOCALID_POKE2, MOVEMENT_TYPE_FACE_LEFT
	return
MSM2Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM2TableCW
	setobjectmovementtype LOCALID_POKE2, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM2TableCW:
	setobjectmovementtype LOCALID_POKE2, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM2MimeJr:
	setobjectmovementtype LOCALID_POKE2, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

Museum3F_SetMove3:
	compare VAR_0x8008, 13
	goto_if_eq MSM3Appletun
	compare VAR_TEMP_2, 29
	goto_if_ge MSM3Table
	compare VAR_0x8008, 5
	goto_if_eq MSM3MimeJr
	setobjectmovementtype LOCALID_POKE3, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM3Appletun:
	setobjectmovementtype LOCALID_POKE3, MOVEMENT_TYPE_FACE_LEFT
	return
MSM3Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM3TableCW
	setobjectmovementtype LOCALID_POKE3, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM3TableCW:
	setobjectmovementtype LOCALID_POKE3, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM3MimeJr:
	setobjectmovementtype LOCALID_POKE3, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

Museum3F_SetMove4:
	compare VAR_0x8008, 13
	goto_if_eq MSM4Appletun
	compare VAR_TEMP_3, 29
	goto_if_ge MSM4Table
	compare VAR_0x8008, 5
	goto_if_eq MSM4MimeJr
	setobjectmovementtype LOCALID_POKE4, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM4Appletun:
	setobjectmovementtype LOCALID_POKE4, MOVEMENT_TYPE_FACE_LEFT
	return
MSM4Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM4TableCW
	setobjectmovementtype LOCALID_POKE4, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM4TableCW:
	setobjectmovementtype LOCALID_POKE4, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM4MimeJr:
	setobjectmovementtype LOCALID_POKE4, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

Museum3F_SetMove5:
	compare VAR_0x8008, 13
	goto_if_eq MSM5Appletun
	compare VAR_TEMP_4, 29
	goto_if_ge MSM5Table
	compare VAR_0x8008, 5
	goto_if_eq MSM5MimeJr
	setobjectmovementtype LOCALID_POKE5, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM5Appletun:
	setobjectmovementtype LOCALID_POKE5, MOVEMENT_TYPE_FACE_LEFT
	return
MSM5Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM5TableCW
	setobjectmovementtype LOCALID_POKE5, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM5TableCW:
	setobjectmovementtype LOCALID_POKE5, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM5MimeJr:
	setobjectmovementtype LOCALID_POKE5, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return

Museum3F_SetMove6:
	compare VAR_0x8008, 13
	goto_if_eq MSM6Appletun
	compare VAR_TEMP_5, 29
	goto_if_ge MSM6Table
	compare VAR_0x8008, 5
	goto_if_eq MSM6MimeJr
	setobjectmovementtype LOCALID_POKE6, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN
	return
MSM6Appletun:
	setobjectmovementtype LOCALID_POKE6, MOVEMENT_TYPE_FACE_LEFT
	return
MSM6Table:
	random 2
	compare VAR_RESULT, 0
	goto_if_eq MSM6TableCW
	setobjectmovementtype LOCALID_POKE6, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE
	return
MSM6TableCW:
	setobjectmovementtype LOCALID_POKE6, MOVEMENT_TYPE_ROTATE_CLOCKWISE
	return
MSM6MimeJr:
	setobjectmovementtype LOCALID_POKE6, MOVEMENT_TYPE_ROTATE_CLOCKWISE
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
	.string "JASON: … … …$"
LilycoveCity_LilycoveMuseum_3F_Text_KCH42Ellipses:
	.string "KCH42: … … …$"
LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipses:
	.string "JEANS: … … …$"
LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipses:
	.string "BEASTLY: … … …$"
LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipses:
	.string "FREEZ: … … …$"

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
	.string "JASON: …$"
LilycoveCity_LilycoveMuseum_3F_Text_KCH42EllipsesSingle:
	.string "KCH42: …$"
LilycoveCity_LilycoveMuseum_3F_Text_JeansEllipsesSingle:
	.string "JEANS: …$"
LilycoveCity_LilycoveMuseum_3F_Text_BeastlyEllipsesSingle:
	.string "BEASTLY: …$"
LilycoveCity_LilycoveMuseum_3F_Text_FreezEllipsesSingle:
	.string "FREEZ: …$"

@ ============================================================
@ Text - Filler
@ ============================================================
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

@ ============================================================
@ Text - Pokémon Generic
@ ============================================================
	MTextGenericLopunny:
	msgbox MTextGenericLopunnyStr, MSGBOX_DEFAULT
	return
MTextGenericLopunnyStr:
	.string "Lopunny is partying it up!$"
	MTextGenericGardevoir:
	msgbox MTextGenericGardevoirStr, MSGBOX_DEFAULT
	return
MTextGenericGardevoirStr:
	.string "Gardevoir looks thrilled to be here!$"
	MTextGenericChesnaught:
	msgbox MTextGenericChesnaughtStr, MSGBOX_DEFAULT
	return
MTextGenericChesnaughtStr:
	.string "Chesnaught is partying it up!$"
	MTextGenericSlowking:
	msgbox MTextGenericSlowkingStr, MSGBOX_DEFAULT
	return
MTextGenericSlowkingStr:
	.string "Slowking looks thrilled to be here!$"
	MTextGenericAmpharos:
	msgbox MTextGenericAmpharosStr, MSGBOX_DEFAULT
	return
MTextGenericAmpharosStr:
	.string "Ampharos is partying it up!$"
	MTextGenericMimeJr:
	msgbox MTextGenericMimeJrStr, MSGBOX_DEFAULT
	return
MTextGenericMimeJrStr:
	.string "Mime Jr. looks thrilled to be here!$"
	MTextGenericDrifloon:
	msgbox MTextGenericDrifloonStr, MSGBOX_DEFAULT
	return
MTextGenericDrifloonStr:
	.string "Drifloon is partying it up!$"
	MTextGenericOshawott:
	msgbox MTextGenericOshawottStr, MSGBOX_DEFAULT
	return
MTextGenericOshawottStr:
	.string "Oshawott looks thrilled to be here!$"
	MTextGenericGreedent:
	msgbox MTextGenericGreedentStr, MSGBOX_DEFAULT
	return
MTextGenericGreedentStr:
	.string "Greedent is partying it up!$"
	MTextGenericSnubbull:
	msgbox MTextGenericSnubbullStr, MSGBOX_DEFAULT
	return
MTextGenericSnubbullStr:
	.string "Snubbull looks thrilled to be here!$"
	MTextGenericSlurpuff:
	msgbox MTextGenericSlurpuffStr, MSGBOX_DEFAULT
	return
MTextGenericSlurpuffStr:
	.string "Slurpuff is partying it up!$"
	MTextGenericHitmontop:
	msgbox MTextGenericHitmontopStr, MSGBOX_DEFAULT
	return
MTextGenericHitmontopStr:
	.string "Hitmontop looks thrilled to be here!$"
	MTextGenericYamper:
	msgbox MTextGenericYamperStr, MSGBOX_DEFAULT
	return
MTextGenericYamperStr:
	.string "Yamper is partying it up!$"
	MTextGenericAppletun:
	msgbox MTextGenericAppletunStr, MSGBOX_DEFAULT
	return
MTextGenericAppletunStr:
	.string "Appletun looks thrilled to be here!$"
	MTextGenericSkiploom:
	msgbox MTextGenericSkiploomStr, MSGBOX_DEFAULT
	return
MTextGenericSkiploomStr:
	.string "Skiploom is partying it up!$"
	MTextGenericSwoobat:
	msgbox MTextGenericSwoobatStr, MSGBOX_DEFAULT
	return
MTextGenericSwoobatStr:
	.string "Swoobat looks thrilled to be here!$"
	MTextGenericSeel:
	msgbox MTextGenericSeelStr, MSGBOX_DEFAULT
	return
MTextGenericSeelStr:
	.string "Seel is partying it up!$"
	MTextGenericFurret:
	msgbox MTextGenericFurretStr, MSGBOX_DEFAULT
	return
MTextGenericFurretStr:
	.string "Furret looks thrilled to be here!$"
	MTextGenericTorchic:
	msgbox MTextGenericTorchicStr, MSGBOX_DEFAULT
	return
MTextGenericTorchicStr:
	.string "Torchic is partying it up!$"
	MTextGenericSpinda:
	msgbox MTextGenericSpindaStr, MSGBOX_DEFAULT
	return
MTextGenericSpindaStr:
	.string "Spinda looks thrilled to be here!$"
	MTextGenericDarumaka:
	msgbox MTextGenericDarumakaStr, MSGBOX_DEFAULT
	return
MTextGenericDarumakaStr:
	.string "Darumaka is partying it up!$"
	MTextGenericMaractus:
	msgbox MTextGenericMaractusStr, MSGBOX_DEFAULT
	return
MTextGenericMaractusStr:
	.string "Maractus looks thrilled to be here!$"
	MTextGenericDucklett:
	msgbox MTextGenericDucklettStr, MSGBOX_DEFAULT
	return
MTextGenericDucklettStr:
	.string "Ducklett is partying it up!$"
	MTextGenericHelioptile:
	msgbox MTextGenericHelioptileStr, MSGBOX_DEFAULT
	return
MTextGenericHelioptileStr:
	.string "Helioptile looks thrilled to be here!$"
	MTextGenericBrionne:
	msgbox MTextGenericBrionneStr, MSGBOX_DEFAULT
	return
MTextGenericBrionneStr:
	.string "Brionne is partying it up!$"
	MTextGenericCorphish:
	msgbox MTextGenericCorphishStr, MSGBOX_DEFAULT
	return
MTextGenericCorphishStr:
	.string "Corphish looks thrilled to be here!$"
	MTextGenericTeddiursa:
	msgbox MTextGenericTeddiursaStr, MSGBOX_DEFAULT
	return
MTextGenericTeddiursaStr:
	.string "Teddiursa is partying it up!$"
	MTextGenericMagnemite:
	msgbox MTextGenericMagnemiteStr, MSGBOX_DEFAULT
	return
MTextGenericMagnemiteStr:
	.string "Magnemite looks thrilled to be here!$"
	MTextGenericSliggoo:
	msgbox MTextGenericSliggooStr, MSGBOX_DEFAULT
	return
MTextGenericSliggooStr:
	.string "Sliggoo is partying it up!$"

@ ============================================================
@ Text - Pokémon On Table
@ ============================================================
	MTextTableLopunny:
	msgbox MTextTableLopunnyStr, MSGBOX_DEFAULT
	return
MTextTableLopunnyStr:
	.string "Lopunny is dancing on the table!$"
	MTextTableGardevoir:
	msgbox MTextTableGardevoirStr, MSGBOX_DEFAULT
	return
MTextTableGardevoirStr:
	.string "Gardevoir is dancing on the table!$"
	MTextTableChesnaught:
	msgbox MTextTableChesnaughtStr, MSGBOX_DEFAULT
	return
MTextTableChesnaughtStr:
	.string "Chesnaught is dancing on the table!$"
	MTextTableSlowking:
	msgbox MTextTableSlowkingStr, MSGBOX_DEFAULT
	return
MTextTableSlowkingStr:
	.string "Slowking is dancing on the table!$"
	MTextTableAmpharos:
	msgbox MTextTableAmpharosStr, MSGBOX_DEFAULT
	return
MTextTableAmpharosStr:
	.string "Ampharos is dancing on the table!$"
	MTextTableMimeJr:
	msgbox MTextTableMimeJrStr, MSGBOX_DEFAULT
	return
MTextTableMimeJrStr:
	.string "Mime Jr. is dancing on the table!$"
	MTextTableDrifloon:
	msgbox MTextTableDrifloonStr, MSGBOX_DEFAULT
	return
MTextTableDrifloonStr:
	.string "Drifloon is dancing on the table!$"
	MTextTableOshawott:
	msgbox MTextTableOshawottStr, MSGBOX_DEFAULT
	return
MTextTableOshawottStr:
	.string "Oshawott is dancing on the table!$"
	MTextTableGreedent:
	msgbox MTextTableGreedentStr, MSGBOX_DEFAULT
	return
MTextTableGreedentStr:
	.string "Greedent is dancing on the table!$"
	MTextTableSnubbull:
	msgbox MTextTableSnubbullStr, MSGBOX_DEFAULT
	return
MTextTableSnubbullStr:
	.string "Snubbull is dancing on the table!$"
	MTextTableSlurpuff:
	msgbox MTextTableSlurpuffStr, MSGBOX_DEFAULT
	return
MTextTableSlurpuffStr:
	.string "Slurpuff is dancing on the table!$"
	MTextTableHitmontop:
	msgbox MTextTableHitmontopStr, MSGBOX_DEFAULT
	return
MTextTableHitmontopStr:
	.string "Hitmontop is dancing on the table!$"
	MTextTableYamper:
	msgbox MTextTableYamperStr, MSGBOX_DEFAULT
	return
MTextTableYamperStr:
	.string "Yamper is dancing on the table!$"
	MTextTableAppletun:
	msgbox MTextTableAppletunStr, MSGBOX_DEFAULT
	return
MTextTableAppletunStr:
	.string "Appletun is looking like an excellent feast!$"
	MTextTableSkiploom:
	msgbox MTextTableSkiploomStr, MSGBOX_DEFAULT
	return
MTextTableSkiploomStr:
	.string "Skiploom is dancing on the table!$"
	MTextTableSwoobat:
	msgbox MTextTableSwoobatStr, MSGBOX_DEFAULT
	return
MTextTableSwoobatStr:
	.string "Swoobat is dancing on the table!$"
	MTextTableSeel:
	msgbox MTextTableSeelStr, MSGBOX_DEFAULT
	return
MTextTableSeelStr:
	.string "Seel is dancing on the table!$"
	MTextTableFurret:
	msgbox MTextTableFurretStr, MSGBOX_DEFAULT
	return
MTextTableFurretStr:
	.string "Furret is dancing on the table!$"
	MTextTableTorchic:
	msgbox MTextTableTorchicStr, MSGBOX_DEFAULT
	return
MTextTableTorchicStr:
	.string "Torchic is dancing on the table!$"
	MTextTableSpinda:
	msgbox MTextTableSpindaStr, MSGBOX_DEFAULT
	return
MTextTableSpindaStr:
	.string "Spinda is dancing on the table!$"
	MTextTableDarumaka:
	msgbox MTextTableDarumakaStr, MSGBOX_DEFAULT
	return
MTextTableDarumakaStr:
	.string "Darumaka is dancing on the table!$"
	MTextTableMaractus:
	msgbox MTextTableMaractusStr, MSGBOX_DEFAULT
	return
MTextTableMaractusStr:
	.string "Maractus is dancing on the table!$"
	MTextTableDucklett:
	msgbox MTextTableDucklettStr, MSGBOX_DEFAULT
	return
MTextTableDucklettStr:
	.string "Ducklett is dancing on the table!$"
	MTextTableHelioptile:
	msgbox MTextTableHelioptileStr, MSGBOX_DEFAULT
	return
MTextTableHelioptileStr:
	.string "Helioptile is dancing on the table!$"
	MTextTableBrionne:
	msgbox MTextTableBrionneStr, MSGBOX_DEFAULT
	return
MTextTableBrionneStr:
	.string "Brionne is dancing on the table!$"
	MTextTableCorphish:
	msgbox MTextTableCorphishStr, MSGBOX_DEFAULT
	return
MTextTableCorphishStr:
	.string "Corphish is dancing on the table!$"
	MTextTableTeddiursa:
	msgbox MTextTableTeddiursaStr, MSGBOX_DEFAULT
	return
MTextTableTeddiursaStr:
	.string "Teddiursa is dancing on the table!$"
	MTextTableMagnemite:
	msgbox MTextTableMagnemiteStr, MSGBOX_DEFAULT
	return
MTextTableMagnemiteStr:
	.string "Magnemite is dancing on the table!$"
	MTextTableSliggoo:
	msgbox MTextTableSliggooStr, MSGBOX_DEFAULT
	return
MTextTableSliggooStr:
	.string "Sliggoo is dancing on the table!$"

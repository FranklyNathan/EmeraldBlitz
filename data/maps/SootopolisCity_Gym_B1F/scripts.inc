SootopolisCity_Gym_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_B1F_EventScript_HideGabbyTy
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_B1F_MapScripts_OnFrame
	.byte 0

SootopolisCity_Gym_B1F_MapScripts_OnFrame:
	map_script_2 VAR_SOOTOPOLIS_GYM_B1F_SCENE, 1, SootopolisCity_Gym_B1F_EventScript_InterviewScene
	.2byte 0

SootopolisCity_Gym_B1F_EventScript_HideGabbyTy:
	setflag FLAG_HIDE_SOOTOPOLIS_GYM_B1F_GABBY_TY
	end

SootopolisCity_Gym_B1F_EventScript_InterviewScene::
	setvar VAR_SOOTOPOLIS_GYM_B1F_SCENE, 0
	lockall
	clearflag FLAG_HIDE_SOOTOPOLIS_GYM_B1F_GABBY_TY
	addobject LOCALID_SOOTOPOLIS_GYM_B1F_GABBY
	addobject LOCALID_SOOTOPOLIS_GYM_B1F_TY
	special SootopolisGymB1F_SetupGabbyTy
	special SootopolisGymB1F_StartAshPuffGabbyTy
	delay 14
	goto_if_set FLAG_SOOTOPOLIS_GYM_INTERVIEWED, SootopolisCity_Gym_B1F_EventScript_RepeatInterviewScene
	special SootopolisGymB1F_ShowGabbyTy
	playse SE_M_DIG
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_PopOut
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_PopOut
	waitmovement 0
	playbgm MUS_ENCOUNTER_INTERVIEWER, FALSE
	goto_if_eq VAR_RESULT, 0, SootopolisCity_Gym_B1F_EventScript_InterviewBelow
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceDown
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceDown
	goto SootopolisCity_Gym_B1F_EventScript_InterviewExclaimDown

SootopolisCity_Gym_B1F_EventScript_InterviewBelow::
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceUp
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceUp
	goto SootopolisCity_Gym_B1F_EventScript_InterviewExclaimUp

SootopolisCity_Gym_B1F_EventScript_InterviewExclaimDown::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_MID
	special SetOptionsTextSpeed
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_GabbyWowTy, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TySureDidGabby, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyItGetsWorse, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_TyHopeNobodyNoticed, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyGoodThingWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyGetComment, MSGBOX_DEFAULT
	setvar VAR_0x8005, 1
	goto SootopolisCity_Gym_B1F_EventScript_InterviewLoop

SootopolisCity_Gym_B1F_EventScript_InterviewExclaimUp::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_MID
	special SetOptionsTextSpeed
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_GabbyWowTy, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TySureDidGabby, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyItGetsWorse, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_TyHopeNobodyNoticed, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyGoodThingWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyGetComment, MSGBOX_DEFAULT
	setvar VAR_0x8005, 0

SootopolisCity_Gym_B1F_EventScript_InterviewLoop::
	msgbox SootopolisCity_Gym_B1F_Text_GabbyCareToComment, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_SOOTOPOLIS_FALL
	call Common_ShowEasyChatScreen
	lockall
	goto_if_eq VAR_RESULT, 0, SootopolisCity_Gym_B1F_EventScript_InterviewLoop
	goto_if_eq VAR_0x8005, 0, SootopolisCity_Gym_B1F_EventScript_InterviewLoop_GabbyJumpUp
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	goto SootopolisCity_Gym_B1F_EventScript_InterviewLoop_AfterGabbyJump
SootopolisCity_Gym_B1F_EventScript_InterviewLoop_GabbyJumpUp:
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
SootopolisCity_Gym_B1F_EventScript_InterviewLoop_AfterGabbyJump:
	msgbox SootopolisCity_Gym_B1F_Text_GabbySummarizes, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_TyWellSaid, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyDontGiveUp, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_FAST
	special SetOptionsTextSpeed
	setflag FLAG_SOOTOPOLIS_GYM_INTERVIEWED
	fadescreen FADE_TO_BLACK
	delay 30
	removeobject LOCALID_SOOTOPOLIS_GYM_B1F_GABBY
	removeobject LOCALID_SOOTOPOLIS_GYM_B1F_TY
	setflag FLAG_HIDE_SOOTOPOLIS_GYM_B1F_GABBY_TY
	delay 10
	fadescreen FADE_FROM_BLACK
	playbgm MUS_GYM, FALSE
	releaseall
	end

SootopolisCity_Gym_B1F_EventScript_RepeatInterviewScene::
	special SootopolisGymB1F_ShowGabby
	playse SE_M_DIG
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_PopOut
	waitmovement 0
	playbgm MUS_ENCOUNTER_INTERVIEWER, FALSE
	goto_if_eq VAR_RESULT, 0, SootopolisCity_Gym_B1F_EventScript_RepeatBelow
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceDown
	goto SootopolisCity_Gym_B1F_EventScript_RepeatExclaimDown

SootopolisCity_Gym_B1F_EventScript_RepeatBelow::
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceUp
	goto SootopolisCity_Gym_B1F_EventScript_RepeatExclaimUp

SootopolisCity_Gym_B1F_EventScript_RepeatExclaimDown::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_MID
	special SetOptionsTextSpeed
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_GabbyGetUpHere, MSGBOX_DEFAULT
	special SootopolisGymB1F_ShowGabbyTy
	playse SE_M_DIG
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_PopOut
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceDown
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyBackToBack, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceLeft
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceRight
	waitmovement 0
	delay 20
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceDown
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceDown
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_ItsPlayerAgain, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyFallenAgain, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyHardlyBelieve, MSGBOX_DEFAULT
	setvar VAR_0x8005, 1
	goto SootopolisCity_Gym_B1F_EventScript_RepeatInterviewLoop

SootopolisCity_Gym_B1F_EventScript_RepeatExclaimUp::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_MID
	special SetOptionsTextSpeed
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_GabbyGetUpHere, MSGBOX_DEFAULT
	special SootopolisGymB1F_ShowGabbyTy
	playse SE_M_DIG
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_PopOut
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceUp
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyBackToBack, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceLeft
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceRight
	waitmovement 0
	delay 20
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, Common_Movement_FaceUp
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, Common_Movement_FaceUp
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_ItsPlayerAgain, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyFallenAgain, MSGBOX_DEFAULT
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_TY, SootopolisCity_Gym_B1F_Movement_TyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	msgbox SootopolisCity_Gym_B1F_Text_TyHardlyBelieve, MSGBOX_DEFAULT
	setvar VAR_0x8005, 0

SootopolisCity_Gym_B1F_EventScript_RepeatInterviewLoop::
	msgbox SootopolisCity_Gym_B1F_Text_GabbyCareToComment, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_SOOTOPOLIS_FALL_2
	call Common_ShowEasyChatScreen
	lockall
	goto_if_eq VAR_RESULT, 0, SootopolisCity_Gym_B1F_EventScript_RepeatInterviewLoop
	goto_if_eq VAR_0x8005, 0, SootopolisCity_Gym_B1F_EventScript_RepeatLoop_GabbyJumpUp
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpDown
	playse SE_LEDGE
	waitse
	waitmovement 0
	goto SootopolisCity_Gym_B1F_EventScript_RepeatLoop_AfterGabbyJump
SootopolisCity_Gym_B1F_EventScript_RepeatLoop_GabbyJumpUp:
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement LOCALID_SOOTOPOLIS_GYM_B1F_GABBY, SootopolisCity_Gym_B1F_Movement_GabbyJumpUp
	playse SE_LEDGE
	waitse
	waitmovement 0
SootopolisCity_Gym_B1F_EventScript_RepeatLoop_AfterGabbyJump:
	msgbox SootopolisCity_Gym_B1F_Text_GabbyUnspeakably, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_WaywithWords, MSGBOX_DEFAULT
	msgbox SootopolisCity_Gym_B1F_Text_GabbyDontGiveUpAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, OPTIONS_TEXT_SPEED_FAST
	special SetOptionsTextSpeed
	fadescreen FADE_TO_BLACK
	delay 30
	removeobject LOCALID_SOOTOPOLIS_GYM_B1F_GABBY
	removeobject LOCALID_SOOTOPOLIS_GYM_B1F_TY
	setflag FLAG_HIDE_SOOTOPOLIS_GYM_B1F_GABBY_TY
	delay 10
	fadescreen FADE_FROM_BLACK
	playbgm MUS_GYM, FALSE
	releaseall
	end

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "I'll show you the sublime techniques\n"
	.string "I learned from our LEADER JUAN!$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "Please forgive me, JUAN…$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "Watch what happens if you crack all\n"
	.string "the floor tiles.$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "You came all the way here, but you won't\n"
	.string "get to see JUAN.\p"
	.string "Not if you lose to me, you won't!$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "You're strong!\n"
	.string "I was fooled by your cute looks!$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "You might be good enough to avoid\n"
	.string "being wiped out in one hit by JUAN.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "The sight of JUAN conducting\n"
	.string "a battle…\p"
	.string "The very beauty of it compelled me to\n"
	.string "become a TRAINER.$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "You battled with more beauty than\n"
	.string "I could muster…$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "The grace you bring to battle is\n"
	.string "fabulous.\p"
	.string "Oh… I'm so fortunate to have found\n"
	.string "POKéMON.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "I should teach you how harsh battles\n"
	.string "can be.$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "Oh.\n"
	.string "You're strong.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "I'll tell you something good.\p"
	.string "If you want to reach JUAN, you\n"
	.string "need to walk on each floor tile once.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "The POKéMON GYM of the highest level\n"
	.string "in the HOENN region…\p"
	.string "That's the SOOTOPOLIS GYM.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "What a high level you are!$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "Rather than being satisfied by being\n"
	.string "in a strong GYM, I imagine training in\l"
	.string "other places will make you stronger.\l"
	.string "But above all, it looks more fun.$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "I train my POKéMON together with\n"
	.string "JUAN.\p"
	.string "Don't think I'm a pushover.$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "I was beaten…$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "I think you have potential.\n"
	.string "Why don't you stay and train with us?$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "A graceful glide across the ice while\n"
	.string "crossing no lines…\p"
	.string "A TRAINER putting on that performance\n"
	.string "would be elegantly beautiful!$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "Well, excuse me?!$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "This is really obvious, but how strong\n"
	.string "you are as a TRAINER has nothing to do\l"
	.string "with how young or old you are.$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "When I'm with my POKéMON, the time\n"
	.string "flies by before you can say, “Oops!”$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "Oops!$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "I wish I could forget about lost causes\n"
	.string "before I can manage an “Oops!”$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "I can battle with really rare POKéMON\n"
	.string "if you'd like.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "Oh, there now! Did you have a good look\n"
	.string "at my POKéMON?$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "I came to this GYM because JUAN\n"
	.string "praised me for my darling POKéMON.\p"
	.string "Oh, if only I'd met JUAN years ago\n"
	.string "when I was younger…$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "Giggle…\n"
	.string "Your grim look is so charming.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "Oh, dear.\n"
	.string "I went much too easy on you.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "You couldn't lay a finger on JUAN,\n"
	.string "I'm sure. Giggle…$"


SootopolisCity_Gym_B1F_Text_GabbyWowTy:
	.string "GABBY: Wow TY, did you see that!?$"

SootopolisCity_Gym_B1F_Text_TySureDidGabby:
	.string "TY: Sure did, GABBY! Looks like {PLAYER}\n"
	.string "just royally botched the gym puzzle!$"

SootopolisCity_Gym_B1F_Text_GabbyItGetsWorse:
	.string "GABBY: That's right TY, but it gets even\n"
	.string "worse! This is a race where every\l"
	.string "second counts.\p"
	.string "They can't afford to waste any time.\n"
	.string "And now, they'll have to do that\l"
	.string "whole puzzle again!$"

SootopolisCity_Gym_B1F_Text_TyHopeNobodyNoticed:
	.string "TY: Oh man, their poor reputation! I bet\n"
	.string "they sure do wish nobody noticed!$"

SootopolisCity_Gym_B1F_Text_GabbyGoodThingWaiting:
	.string "GABBY: Good thing we're here\n"
	.string "around the clock waiting!\p"
	.string "This mistake will be primetime news!$"

SootopolisCity_Gym_B1F_Text_TyGetComment:
	.string "TY: Great point, GABBY!\n"
	.string "Let's get an interview!$"

SootopolisCity_Gym_B1F_Text_GabbyCareToComment:
	.string "GABBY: {PLAYER}! Care to comment on how\n"
	.string "embarrassing this is for you?$"

SootopolisCity_Gym_B1F_Text_GabbySummarizes:
	.string "GABBY: Extremely embarrassed!\p"
	.string "I'd say that just about sums it up!$"

SootopolisCity_Gym_B1F_Text_TyWellSaid:
	.string "TY: So well said!$"

SootopolisCity_Gym_B1F_Text_GabbyDontGiveUp:
	.string "GABBY: Well, we've got our story!\n"
	.string "{PLAYER}, don't give up!\p"
	.string "Give it another shot! After all,\n"
	.string "it can't go any worse than it just did!$"

SootopolisCity_Gym_B1F_Text_GabbyDontGiveUpAgain:
	.string "GABBY: Well, we've got our story!\n"
	.string "{PLAYER}, don't give up!\p"
	.string "Give it another shot! After all,\n"
	.string "you clearly need the practice!$"

SootopolisCity_Gym_B1F_Text_GabbyGetUpHere:
	.string "GABBY: TY, get up here!\n"
	.string "Another trainer fell!$"

SootopolisCity_Gym_B1F_Text_TyBackToBack:
	.string "TY: Wow, back to back!\n"
	.string "Who is it this time?$"

SootopolisCity_Gym_B1F_Text_ItsPlayerAgain:
	.string "GABBY and TY: It's {PLAYER} AGAIN!$"

SootopolisCity_Gym_B1F_Text_GabbyFallenAgain:
	.string "GABBY: {PLAYER}, you've fallen AGAIN!\p"
	.string "This is going to be front page news!\n"
	.string "This is going to be the story of\l"
	.string "the century!$"

SootopolisCity_Gym_B1F_Text_TyHardlyBelieve:
	.string "TY: I can hardly believe what I'm\n"
	.string "seeing! Gabby, let's get an interview!\l"
	.string "I'm rolling!$"

SootopolisCity_Gym_B1F_Text_GabbyUnspeakably:
	.string "GABBY: Unspeakably embarrassed!\p"
	.string "I'd say that just about sums it up!$"

SootopolisCity_Gym_B1F_Text_WaywithWords:
	.string "TY: They have such a way with words!$"

SootopolisCity_Gym_B1F_Movement_PopOut:
	jump_in_place_right
	step_end

SootopolisCity_Gym_B1F_Movement_GabbyJumpUp:
	jump_in_place_up
	step_end

SootopolisCity_Gym_B1F_Movement_TyJumpUp:
	jump_in_place_up
	step_end

SootopolisCity_Gym_B1F_Movement_GabbyJumpDown:
	jump_in_place_down
	step_end

SootopolisCity_Gym_B1F_Movement_TyJumpDown:
	jump_in_place_down
	step_end

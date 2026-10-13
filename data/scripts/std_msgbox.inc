Std_MsgboxNPC:
	lock
	faceplayer
	message NULL
	waitmessage
	waitbuttonpress
	release
	return

Std_MsgboxSign:
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	lockall
	message NULL
	waitmessage
	waitbuttonpress
	releaseall
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	return

Std_MsgboxDefault:
	message NULL
	waitmessage
	waitbuttonpress
	return

Std_MsgboxYesNo:
	message NULL
	waitmessage
	yesnobox 20, 8
	return

Std_MsgboxGetPoints:
	message NULL
	playfanfare MUS_OBTAIN_B_POINTS
	waitfanfare
	waitmessage
	return

@ Never used, pokenavcall is always used directly instead
Std_MsgboxPokenav:
	pokenavcall NULL
	waitmessage
	return

EventScript_UnusedReturn:
	return

Common_EventScript_SaveGame::
	special SaveGame
	waitstate
	return

Common_EventScript_ScottExclamation::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	return

Common_EventScript_ScottFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	return

@ Opens Scott's TM shop after a gym. When the player backs out, ask whether
@ they are really finished; if not, re-open the shop in the exact state it was
@ left in instead of re-rolling the inventory.
Common_EventScript_ScottTmShop::
	special OpenScottTmShop
	waitstate
Common_EventScript_ScottTmShop_Ask:
	msgbox gText_ScottFinishedBuyingTMs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_EventScript_ScottTmShop_Reopen
	return

Common_EventScript_ScottTmShop_Reopen:
	special ReopenScottTmShop
	waitstate
	goto Common_EventScript_ScottTmShop_Ask

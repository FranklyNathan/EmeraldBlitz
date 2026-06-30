OldaleTown_House2_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, OldaleTown_House2_OnLoad
	.byte 0

OldaleTown_House2_OnLoad:
	call_if_set FLAG_OLDALE_HOUSE_SECRET_STAIRS, OldaleTown_House2_EventScript_SetStairs
	end

OldaleTown_House2_EventScript_SetStairs::
	setmetatile 10, 3, 0x219, FALSE
	return

OldaleTown_House2_EventScript_FallIntoBasement::
	goto_if_set FLAG_OLDALE_HOUSE_SECRET_STAIRS, OldaleTown_House2_EventScript_DoFall
	return

OldaleTown_House2_EventScript_DoFall::
	lockall
	playse SE_FALL
	setholewarp MAP_OLDALE_TOWN_HOUSE2_BASEMENT, 13, 11
	warphole MAP_UNDEFINED
	waitstate
	end

OldaleTown_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_OLDALE_HOUSE_SECRET_STAIRS, OldaleTown_House2_EventScript_WomanStairsRevealed
	msgbox OldaleTown_House2_Text_DraftIntro, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_QUIZ_ANSWER
	call Common_ShowEasyChatScreen
	goto_if_eq VAR_RESULT, 0, OldaleTown_House2_EventScript_DraftWrong
	specialvar VAR_0x8005, Special_GetQuizAnswer
	goto_if_eq VAR_0x8005, EC_WORD_PREPOSTEROUS, OldaleTown_House2_EventScript_DraftCorrect
	msgbox OldaleTown_House2_Text_DraftWrong, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_EventScript_DraftWrong::
	msgbox OldaleTown_House2_Text_DraftWrong, MSGBOX_DEFAULT
	closemessage
	release
	end

OldaleTown_House2_EventScript_DraftCorrect::
	msgbox OldaleTown_House2_Text_DraftCorrect, MSGBOX_DEFAULT
	closemessage
	setmetatile 10, 3, 0x219, FALSE
	special DrawWholeMapView
	setflag FLAG_OLDALE_HOUSE_SECRET_STAIRS
	playse SE_PIN
	msgbox OldaleTown_House2_Text_RevealedStairs, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_EventScript_WomanStairsRevealed::
	msgbox OldaleTown_House2_Text_StairsRevealed, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_DraftIntro:
	.string "Hm? No, nothing suspicious going on\n"
	.string "here. I'm just having a fun draft with\l"
	.string "my friend. Say, what's the most\l"
	.string "important aspect of the draft?$"

OldaleTown_House2_Text_DraftCorrect:
	.string "Oh, I'm so sorry! I hadn't realized\n"
	.string "that you were one of us…$"

OldaleTown_House2_Text_DraftWrong:
	.string "Oh, that's so true! I'll keep that\n"
	.string "in mind…$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Ha, I've saved up so much money, I'll\n"
	.string "be able to win at least a dozen\l"
	.string "POKéMON in this draft!$"

OldaleTown_House2_Text_RevealedStairs:
	.string "Go right ahead!$"

OldaleTown_House2_Text_StairsRevealed:
	.string "Ah, I always spend too much of my\n"
	.string "money in the first half of the draft…$"

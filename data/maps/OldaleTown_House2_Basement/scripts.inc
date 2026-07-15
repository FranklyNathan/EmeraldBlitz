.set SCROLL_MULTI_HIDDEN_POWER_TYPES, 13

OldaleTown_House2_Basement_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_House2_Basement_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OldaleTown_House2_Basement_OnFrame
	.byte 0

OldaleTown_House2_Basement_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN_HOUSE2_BASEMENT
	call_if_set FLAG_IN_BASEMENT, OldaleTown_House2_Basement_EventScript_InstantLights
	special HealPlayerParty
	setvar VAR_FORCEANIM, 1
	end

OldaleTown_House2_Basement_EventScript_InstantLights::
	setvar VAR_TEMP_0, 1
	setflashlevel 0
	return

OldaleTown_House2_Basement_OnFrame:
	map_script_2 VAR_TEMP_0, 0, OldaleTown_House2_Basement_EventScript_LightUpRoom
	.2byte 0

OldaleTown_House2_Basement_EventScript_LightUpRoom::
	lockall
	setvar VAR_TEMP_0, 1
	setflag FLAG_IN_BASEMENT
	animateflash 0
	setflashlevel 0
	callnative Script_ShowMapNamePopup
	releaseall
	end

OldaleTown_House2_EventScript_LevelCapNPC::
    clearflag FLAG_SYS_OPPONENT_LEVEL_1
	lock
	faceplayer
	message OldaleTown_House2_Text_LevelCapIntro
	waitmessage
	dynmultipush OldaleTown_House2_Text_LevelCaps0, 0
	dynmultipush OldaleTown_House2_Text_LevelCaps1, 1
	dynmultipush OldaleTown_House2_Text_LevelCaps2, 2
	dynmultipush OldaleTown_House2_Text_LevelCaps3, 3
	dynmultipush OldaleTown_House2_Text_LevelCaps4, 4
	dynmultipush OldaleTown_House2_Text_LevelCaps5, 5
	dynmultipush OldaleTown_House2_Text_LevelCaps6, 6
	dynmultipush OldaleTown_House2_Text_LevelCaps7, 7
	dynmultipush OldaleTown_House2_Text_LevelCaps8, 8
	dynmultipush gText_Exit, 9
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, OldaleTown_House2_EventScript_Set0Badges
	case 1, OldaleTown_House2_EventScript_Set1Badge
	case 2, OldaleTown_House2_EventScript_Set2Badges
	case 3, OldaleTown_House2_EventScript_Set3Badges
	case 4, OldaleTown_House2_EventScript_Set4Badges
	case 5, OldaleTown_House2_EventScript_Set5Badges
	case 6, OldaleTown_House2_EventScript_Set6Badges
	case 7, OldaleTown_House2_EventScript_Set7Badges
	case 8, OldaleTown_House2_EventScript_Set8Badges
	goto OldaleTown_House2_EventScript_LevelCapCancel
	end

OldaleTown_House2_EventScript_Set0Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setvar VAR_BADGE_COUNT, 0
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set1Badge::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setvar VAR_BADGE_COUNT, 1
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set2Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setvar VAR_BADGE_COUNT, 2
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set3Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setvar VAR_BADGE_COUNT, 3
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set4Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setvar VAR_BADGE_COUNT, 4
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set5Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setvar VAR_BADGE_COUNT, 5
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set6Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setvar VAR_BADGE_COUNT, 6
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set7Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setvar VAR_BADGE_COUNT, 7
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_Set8Badges::
	call OldaleTown_House2_EventScript_ClearAllBadges
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setvar VAR_BADGE_COUNT, 8
	goto OldaleTown_House2_EventScript_LevelCapEnd

OldaleTown_House2_EventScript_ClearAllBadges::
	clearflag FLAG_BADGE01_GET
	clearflag FLAG_BADGE02_GET
	clearflag FLAG_BADGE03_GET
	clearflag FLAG_BADGE04_GET
	clearflag FLAG_BADGE05_GET
	clearflag FLAG_BADGE06_GET
	clearflag FLAG_BADGE07_GET
	clearflag FLAG_BADGE08_GET
	return

OldaleTown_House2_EventScript_LevelCapEnd::
	msgbox OldaleTown_House2_Text_LevelCapUpdated, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_EventScript_LevelCapCancel::
	msgbox OldaleTown_House2_Text_LevelCapCancel, MSGBOX_DEFAULT
	release
	end


OldaleTown_House2_Text_LevelCapIntro:
	.string "I can help you adjust your level cap.\n"
	.string "How many badges should you have?$"

OldaleTown_House2_Text_LevelCapUpdated:
	.string "Done! Your level cap has been updated.$"

OldaleTown_House2_Text_LevelCapCancel:
	.string "Come back if you change your mind.$"

OldaleTown_House2_Text_LevelCaps0:
	.string "0 Badges (Lv 15)$"
OldaleTown_House2_Text_LevelCaps1:
	.string "1 Badge (Lv 19)$"
OldaleTown_House2_Text_LevelCaps2:
	.string "2 Badges (Lv 24)$"
OldaleTown_House2_Text_LevelCaps3:
	.string "3 Badges (Lv 29)$"
OldaleTown_House2_Text_LevelCaps4:
	.string "4 Badges (Lv 32)$"
OldaleTown_House2_Text_LevelCaps5:
	.string "5 Badges (Lv 35)$"
OldaleTown_House2_Text_LevelCaps6:
	.string "6 Badges (Lv 42)$"
OldaleTown_House2_Text_LevelCaps7:
	.string "7 Badges (Lv 48)$"
OldaleTown_House2_Text_LevelCaps8:
	.string "8 Badges (Lv 58)$"

OldaleTown_House2_Basement_EventScript_GiftPokemonBox::
	lockall
	faceplayer
	setflag FLAG_IN_BASEMENT
	call EventScript_ChooseGiftPokemon_Basement
	releaseall
	end

OldaleTown_House2_Basement_EventScript_GiftPokemonBox2::
	lockall
	faceplayer
	setflag FLAG_IN_BASEMENT
	call EventScript_ChooseGiftPokemon2_Basement
	releaseall
	end

OldaleTown_House2_Basement_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	checkflag FLAG_SYS_BATTLE_DEBUG
	goto_if_set FLAG_SYS_BATTLE_DEBUG, OldaleTown_House2_Basement_EventScript_MiltankDisable
	msgbox OldaleTown_House2_Basement_Text_MiltankIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OldaleTown_House2_Basement_EventScript_EnableDebug
	release
	end

OldaleTown_House2_Basement_EventScript_EnableDebug::
	setflag FLAG_SYS_BATTLE_DEBUG
	msgbox OldaleTown_House2_Basement_Text_MiltankYes, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_EventScript_MiltankDisable::
	msgbox OldaleTown_House2_Basement_Text_MiltankDisable, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OldaleTown_House2_Basement_EventScript_DisableDebug
	release
	end

OldaleTown_House2_Basement_EventScript_DisableDebug::
	clearflag FLAG_SYS_BATTLE_DEBUG
	msgbox OldaleTown_House2_Basement_Text_MiltankNo, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_Text_MiltankIntro:
	.string "Moooo! (Would you like to enable\n"
	.string "debug mode?)$"

OldaleTown_House2_Basement_Text_MiltankYes:
	.string "Moo! (Battle Debug active.\n"
	.string "Press SELECT during move selection.)$"

OldaleTown_House2_Basement_Text_MiltankDisable:
	.string "Moo? (Would you like to disable\n"
	.string "debug mode?)$"

OldaleTown_House2_Basement_Text_MiltankNo:
	.string "Moo… (Debug mode disabled.)$"

OldaleTown_House2_Basement_EventScript_Shopkeeper::
	lock
	faceplayer
	setflag FLAG_FREE_SHOP
	setflag FLAG_IN_BASEMENT
	message OldaleTown_House2_Basement_Text_HowMayIHelpYou
	waitmessage
OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu::
	dynmultipush OldaleTown_House2_Basement_Text_CategoryTMs, 0
	dynmultipush OldaleTown_House2_Basement_Text_CategoryMegaStones, 1
	dynmultipush OldaleTown_House2_Basement_Text_CategoryEvoItems, 2
	dynmultipush OldaleTown_House2_Basement_Text_CategoryHeldItems, 3
	dynmultipush OldaleTown_House2_Basement_Text_CategoryStatChangers, 4
	dynmultipush gText_Exit, 5
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, OldaleTown_House2_Basement_EventScript_ShopTMs
	case 1, OldaleTown_House2_Basement_EventScript_ShopMegaStones
	case 2, OldaleTown_House2_Basement_EventScript_ShopEvoItems
	case 3, OldaleTown_House2_Basement_EventScript_ShopHeldItems
	case 4, OldaleTown_House2_Basement_EventScript_ShopStatChangers
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Exit
	end

OldaleTown_House2_Basement_EventScript_TM_Clerk::
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper

OldaleTown_House2_Basement_EventScript_ShopTMs::
	setvar VAR_POWER_TM_CLERK, 1
	pokemart OldaleTown_House2_Basement_Mart_TMs
	setvar VAR_POWER_TM_CLERK, 0
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu

OldaleTown_House2_Basement_EventScript_ShopMegaStones::
	pokemart OldaleTown_House2_Basement_Mart_MegaStones
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu

OldaleTown_House2_Basement_EventScript_ShopEvoItems::
	pokemart OldaleTown_House2_Basement_Mart_EvoItems
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu

OldaleTown_House2_Basement_EventScript_ShopHeldItems::
	pokemart OldaleTown_House2_Basement_Mart_HeldItems
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu

OldaleTown_House2_Basement_EventScript_ShopStatChangers::
	pokemart OldaleTown_House2_Basement_Mart_AbilitiesMints
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper_Menu

OldaleTown_House2_Basement_EventScript_Shopkeeper_Exit::
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_House2_Basement_Mart_TMs:
	.hword ITEM_TM_AERIAL_ACE
	.hword ITEM_TM_AIR_SLASH
	.hword ITEM_TM_BLIZZARD
	.hword ITEM_TM_BRICK_BREAK
	.hword ITEM_TM_BULK_UP
	.hword ITEM_TM_BUG_BUZZ
	.hword ITEM_TM_BULLET_SEED
	.hword ITEM_TM_CALM_MIND
	.hword ITEM_TM_CRUNCH
	.hword ITEM_TM_DARK_PULSE
	.hword ITEM_TM_DAZZLING_GLEAM
	.hword ITEM_TM_DIG
	.hword ITEM_TM_DRAGON_CLAW
	.hword ITEM_TM_DRAGON_PULSE
	.hword ITEM_TM_DUAL_WINGBEAT
	.hword ITEM_TM_EARTHQUAKE
	.hword ITEM_TM_FACADE
	.hword ITEM_TM_FIRE_BLAST
	.hword ITEM_TM_FIRE_PUNCH
	.hword ITEM_TM_FLAMETHROWER
	.hword ITEM_TM_FLASH_CANNON
	.hword ITEM_TM_FLIP_TURN
	.hword ITEM_TM_FOCUS_BLAST
	.hword ITEM_TM_GIGA_DRAIN
	.hword ITEM_TM_HAIL
	.hword ITEM_TM_HONE_CLAWS
	.hword ITEM_TM_HYPER_BEAM
	.hword ITEM_TM_HYPER_VOICE
	.hword ITEM_TM_ICE_BEAM
	.hword ITEM_TM_ICE_PUNCH
	.hword ITEM_TM_ICY_WIND
	.hword ITEM_TM_IRON_TAIL
	.hword ITEM_TM_LIGHT_SCREEN
	.hword ITEM_TM_MUD_SHOT
	.hword ITEM_TM_OVERHEAT
	.hword ITEM_TM_PLAY_ROUGH
	.hword ITEM_TM_POISON_JAB
	.hword ITEM_TM_POUNCE
	.hword ITEM_TM_POWER_GEM
	.hword ITEM_TM_PROTECT
	.hword ITEM_TM_PSYCHIC
	.hword ITEM_TM_RAIN_DANCE
	.hword ITEM_TM_REFLECT
	.hword ITEM_TM_REST
	.hword ITEM_TM_RETURN
	.hword ITEM_TM_ROCK_SLIDE
	.hword ITEM_TM_ROCK_TOMB
	.hword ITEM_TM_SANDSTORM
	.hword ITEM_TM_SCALD
	.hword ITEM_TM_SCORCHING_SANDS
	.hword ITEM_TM_SEED_BOMB
	.hword ITEM_TM_SHADOW_BALL
	.hword ITEM_TM_SHADOW_CLAW
	.hword ITEM_TM_SHOCK_WAVE
	.hword ITEM_TM_SLUDGE_BOMB
	.hword ITEM_TM_SOLAR_BEAM
	.hword ITEM_TM_STEEL_WING
	.hword ITEM_TM_SUNNY_DAY
	.hword ITEM_TM_TAUNT
	.hword ITEM_TM_THIEF
	.hword ITEM_TM_THUNDER
	.hword ITEM_TM_THUNDERBOLT
	.hword ITEM_TM_THUNDER_PUNCH
	.hword ITEM_TM_TRICK_ROOM
	.hword ITEM_TM_WATER_PULSE
	.hword ITEM_TM_X_SCISSOR
	.hword ITEM_TM_ZEN_HEADBUTT
	.hword ITEM_HM_CUT
	.hword ITEM_HM_DIVE
	.hword ITEM_HM_FLY
	.hword ITEM_HM_ROCK_SMASH
	.hword ITEM_HM_STRENGTH
	.hword ITEM_HM_SURF
	.hword ITEM_HM_WATERFALL
	.hword ITEM_NONE

OldaleTown_House2_Basement_EventScript_MegaStone_Clerk::
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper

	.align 2
OldaleTown_House2_Basement_Mart_MegaStones:
	.hword ITEM_ABOMASITE
	.hword ITEM_ABSOLITE
	.hword ITEM_AGGRONITE
	.hword ITEM_AMPHAROSITE
	.hword ITEM_BANETTITE
	.hword ITEM_BARBARACITE
	.hword ITEM_BAXCALIBRITE
	.hword ITEM_BEEDRILLITE
	.hword ITEM_BLASTOISINITE
	.hword ITEM_BLAZIKENITE
	.hword ITEM_CAMERUPTITE
	.hword ITEM_CHANDELURITE
	.hword ITEM_CHARIZARDITE_X
	.hword ITEM_CHESNAUGHTITE
	.hword ITEM_CHIMECHITE
	.hword ITEM_CLEFABLITE
	.hword ITEM_DELPHOXITE
	.hword ITEM_DRAGALGITE
	.hword ITEM_DRAGONINITE
	.hword ITEM_DRAMPANITE
	.hword ITEM_EELEKTROSSITE
	.hword ITEM_EXCADRITE
	.hword ITEM_FALINKSITE
	.hword ITEM_FERALIGITE
	.hword ITEM_FROSLASSITE
	.hword ITEM_GALLADITE
	.hword ITEM_GARCHOMPITE
	.hword ITEM_GARDEVOIRITE
	.hword ITEM_GENGARITE
	.hword ITEM_GLALITITE
	.hword ITEM_GRENINJITE
	.hword ITEM_HAWLUCHANITE
	.hword ITEM_HERACRONITE
	.hword ITEM_HOUNDOOMINITE
	.hword ITEM_KANGASKHANITE
	.hword ITEM_LOPUNNITE
	.hword ITEM_LUCARIONITE
	.hword ITEM_MALAMARITE
	.hword ITEM_MANECTITE
	.hword ITEM_MAWILITE
	.hword ITEM_MEDICHAMITE
	.hword ITEM_MEOWSTICITE
	.hword ITEM_METAGROSSITE
	.hword ITEM_PINSIRITE
	.hword ITEM_PYROARITE
	.hword ITEM_RAICHUNITE_X
	.hword ITEM_SABLENITE
	.hword ITEM_SALAMENCITE
	.hword ITEM_SCEPTILITE
	.hword ITEM_SCIZORITE
	.hword ITEM_SCOLIPITE
	.hword ITEM_SCRAFTINITE
	.hword ITEM_SHARPEDONITE
	.hword ITEM_SKARMORITE
	.hword ITEM_STARAPTITE
	.hword ITEM_STARMINITE
	.hword ITEM_STEELIXITE
	.hword ITEM_SWAMPERTITE
	.hword ITEM_TYRANITARITE
	.hword ITEM_VENUSAURITE
	.hword ITEM_NONE

OldaleTown_House2_Basement_EventScript_Evo_Clerk::
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper

	.align 2
OldaleTown_House2_Basement_Mart_EvoItems:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_DUSK_STONE
	.hword ITEM_DRAGON_SCALE
	.hword ITEM_KINGS_ROCK
	.hword ITEM_METAL_COAT
	.hword ITEM_LINKING_CORD
	.hword ITEM_ROTOM_CATALOG
	.hword ITEM_BURMY_BINDER
	.hword ITEM_TART_APPLE
	.hword ITEM_SWEET_APPLE
	.hword ITEM_SYRUPY_APPLE
	.hword ITEM_NONE

OldaleTown_House2_Basement_EventScript_AbilityMint_Clerk::
	goto OldaleTown_House2_Basement_EventScript_Shopkeeper

	.align 2
OldaleTown_House2_Basement_Mart_AbilitiesMints:
	.hword ITEM_ABILITY_CAPSULE
	.hword ITEM_ABILITY_PATCH
	.hword ITEM_GOLD_BOTTLE_CAP
	.hword ITEM_SILVER_BOTTLE_CAP
	.hword ITEM_FOOLS_BOTTLE_CAP
	.hword ITEM_LONELY_MINT
	.hword ITEM_ADAMANT_MINT
	.hword ITEM_NAUGHTY_MINT
	.hword ITEM_BRAVE_MINT
	.hword ITEM_BOLD_MINT
	.hword ITEM_IMPISH_MINT
	.hword ITEM_LAX_MINT
	.hword ITEM_RELAXED_MINT
	.hword ITEM_MODEST_MINT
	.hword ITEM_MILD_MINT
	.hword ITEM_RASH_MINT
	.hword ITEM_QUIET_MINT
	.hword ITEM_CALM_MINT
	.hword ITEM_GENTLE_MINT
	.hword ITEM_CAREFUL_MINT
	.hword ITEM_SASSY_MINT
	.hword ITEM_TIMID_MINT
	.hword ITEM_HASTY_MINT
	.hword ITEM_JOLLY_MINT
	.hword ITEM_NAIVE_MINT
	.hword ITEM_SERIOUS_MINT
	.hword ITEM_NONE

	.align 2
OldaleTown_House2_Basement_Mart_HeldItems:
	.hword ITEM_SITRUS_BERRY
	.hword ITEM_LUM_BERRY
	.hword ITEM_LEPPA_BERRY
	.hword ITEM_ORAN_BERRY
	.hword ITEM_CHERI_BERRY
	.hword ITEM_CHESTO_BERRY
	.hword ITEM_PECHA_BERRY
	.hword ITEM_RAWST_BERRY
	.hword ITEM_ASPEAR_BERRY
	.hword ITEM_PERSIM_BERRY
	.hword ITEM_BLACK_GLASSES
	.hword ITEM_CHARCOAL
	.hword ITEM_MIRACLE_SEED
	.hword ITEM_MYSTIC_WATER
	.hword ITEM_NEVER_MELT_ICE
	.hword ITEM_SILK_SCARF
	.hword ITEM_SOFT_SAND
	.hword ITEM_WHITE_HERB
	.hword ITEM_LEEK
	.hword ITEM_THICK_CLUB
	.hword ITEM_NONE

OldaleTown_House2_Basement_Text_HowMayIHelpYou:
	.string "Welcome to Nathan's Lair!\n"
	.string "How may I help you today?$"

OldaleTown_House2_Basement_Text_CategoryTMs:
	.string "TMs$"
OldaleTown_House2_Basement_Text_CategoryMegaStones:
	.string "Mega Stones$"
OldaleTown_House2_Basement_Text_CategoryEvoItems:
	.string "Evo Items$"
OldaleTown_House2_Basement_Text_CategoryHeldItems:
	.string "Held Items$"
OldaleTown_House2_Basement_Text_CategoryStatChangers:
	.string "Stat Changers$"


OldaleTown_House2_Basement_EventScript_MoveRelearner::
	lock
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 4, OldaleTown_House2_Basement_EventScript_MoveRelearnerNotEnoughBadges
	msgbox OldaleTown_House2_Basement_Text_MoveRelearnerIntro, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_ChooseMon
	end

OldaleTown_House2_Basement_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, OldaleTown_House2_Basement_EventScript_End
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_House2_Basement_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, OldaleTown_House2_Basement_EventScript_NoMoveToTeachMon
	goto OldaleTown_House2_Basement_EventScript_ChooseMove
	end

OldaleTown_House2_Basement_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, OldaleTown_House2_Basement_EventScript_ChooseMon
	release
	end

OldaleTown_House2_Basement_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_ChooseMon
	end

OldaleTown_House2_Basement_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_ChooseMon
	end

OldaleTown_House2_Basement_EventScript_End::
	release
	end

OldaleTown_House2_Basement_EventScript_MoveRelearnerNotEnoughBadges::
	msgbox OldaleTown_House2_Basement_Text_MoveRelearnerNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_Text_MoveRelearnerIntro:
	.string "I'm the MOVE TUTOR.\p"
	.string "I know all the moves that POKéMON\n"
	.string "learn--every one of them--and I can\l"
	.string "teach POKéMON those moves.\p"
	.string "I can teach a move to a POKéMON\n"
	.string "of yours if you'd like.$"

OldaleTown_House2_Basement_EventScript_MoveTutorNPC::
	lock
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 4, OldaleTown_House2_Basement_EventScript_MoveTutorNotEnoughBadges
	msgbox OldaleTown_House2_Basement_Text_MoveTutorIntro, MSGBOX_DEFAULT

OldaleTown_House2_Basement_EventScript_MoveTutorMenu::
	message OldaleTown_House2_Basement_Text_WhichMoveToTeach
	waitmessage
	dynmultipush OldaleTown_House2_Basement_Text_DoubleEdge, 0
	dynmultipush OldaleTown_House2_Basement_Text_DynamicPunch, 1
	dynmultipush OldaleTown_House2_Basement_Text_Explosion, 2
	dynmultipush OldaleTown_House2_Basement_Text_FuryCutter, 3
	dynmultipush OldaleTown_House2_Basement_Text_Metronome, 4
	dynmultipush OldaleTown_House2_Basement_Text_Mimic, 5
	dynmultipush OldaleTown_House2_Basement_Text_Rollout, 6
	dynmultipush OldaleTown_House2_Basement_Text_SleepTalk, 7
	dynmultipush OldaleTown_House2_Basement_Text_Substitute, 8
	dynmultipush OldaleTown_House2_Basement_Text_Swagger, 9
	dynmultipush gText_Exit, 10
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, OldaleTown_House2_Basement_EventScript_DoubleEdge
	case 1, OldaleTown_House2_Basement_EventScript_DynamicPunch
	case 2, OldaleTown_House2_Basement_EventScript_Explosion
	case 3, OldaleTown_House2_Basement_EventScript_FuryCutter
	case 4, OldaleTown_House2_Basement_EventScript_Metronome
	case 5, OldaleTown_House2_Basement_EventScript_Mimic
	case 6, OldaleTown_House2_Basement_EventScript_Rollout
	case 7, OldaleTown_House2_Basement_EventScript_SleepTalk
	case 8, OldaleTown_House2_Basement_EventScript_Substitute
	case 9, OldaleTown_House2_Basement_EventScript_Swagger
	goto OldaleTown_House2_Basement_EventScript_TutorCancel
	end

OldaleTown_House2_Basement_EventScript_DoubleEdge::
	setvar VAR_0x8005, MOVE_DOUBLE_EDGE
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_DynamicPunch::
	setvar VAR_0x8005, MOVE_DYNAMIC_PUNCH
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Explosion::
	setvar VAR_0x8005, MOVE_EXPLOSION
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_FuryCutter::
	setvar VAR_0x8005, MOVE_FURY_CUTTER
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Metronome::
	setvar VAR_0x8005, MOVE_METRONOME
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Mimic::
	setvar VAR_0x8005, MOVE_MIMIC
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Rollout::
	setvar VAR_0x8005, MOVE_ROLLOUT
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_SleepTalk::
	setvar VAR_0x8005, MOVE_SLEEP_TALK
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Substitute::
	setvar VAR_0x8005, MOVE_SUBSTITUTE
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_Swagger::
	setvar VAR_0x8005, MOVE_SWAGGER
	goto OldaleTown_House2_Basement_EventScript_DoTutor

OldaleTown_House2_Basement_EventScript_DoTutor::
	special ChooseMonForMoveTutor
	waitstate
	goto OldaleTown_House2_Basement_EventScript_MoveTutorMenu

OldaleTown_House2_Basement_EventScript_TutorCancel::
	msgbox OldaleTown_House2_Basement_Text_TutorCancel, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_EventScript_MoveTutorNotEnoughBadges::
	msgbox OldaleTown_House2_Basement_Text_MoveTutorNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_Text_TutorCancel:
	.string "I'll be here if you want to learn\n"
	.string "something new!$"

OldaleTown_House2_Basement_Text_MoveTutorIntro:
	.string "I can teach your precious POKéMON\n"
	.string "something new!$"

OldaleTown_House2_Basement_Text_MoveTutorNotEnoughBadges:
	.string "I'm sorry, but I only teach these\n"
	.string "moves to experienced TRAINERS.\p"
	.string "Come back once you have at least\n"
	.string "four GYM BADGES.$"

OldaleTown_House2_Basement_Text_DoubleEdge:
	.string "DOUBLE-EDGE$"

OldaleTown_House2_Basement_Text_DynamicPunch:
	.string "DYNAMICPUNCH$"

OldaleTown_House2_Basement_Text_Explosion:
	.string "EXPLOSION$"

OldaleTown_House2_Basement_Text_FuryCutter:
	.string "FURY CUTTER$"

OldaleTown_House2_Basement_Text_Metronome:
	.string "METRONOME$"

OldaleTown_House2_Basement_Text_Mimic:
	.string "MIMIC$"

OldaleTown_House2_Basement_Text_Rollout:
	.string "ROLLOUT$"

OldaleTown_House2_Basement_Text_SleepTalk:
	.string "SLEEP TALK$"

OldaleTown_House2_Basement_Text_Substitute:
	.string "SUBSTITUTE$"

OldaleTown_House2_Basement_Text_Swagger:
	.string "SWAGGER$"

OldaleTown_House2_Basement_Text_TeachDoubleEdge:
	.string "Would you like to teach DOUBLE-EDGE?$"

OldaleTown_House2_Basement_Text_TeachDynamicPunch:
	.string "Would you like to teach DYNAMICPUNCH?$"

OldaleTown_House2_Basement_Text_TeachExplosion:
	.string "Would you like to teach EXPLOSION?$"

OldaleTown_House2_Basement_Text_TeachFuryCutter:
	.string "Would you like to teach FURY CUTTER?$"

OldaleTown_House2_Basement_Text_TeachMetronome:
	.string "Would you like to teach METRONOME?$"

OldaleTown_House2_Basement_Text_TeachMimic:
	.string "Would you like to teach MIMIC?$"

OldaleTown_House2_Basement_Text_TeachRollout:
	.string "Would you like to teach ROLLOUT?$"

OldaleTown_House2_Basement_Text_TeachSleepTalk:
	.string "Would you like to teach SLEEP TALK?$"

OldaleTown_House2_Basement_Text_TeachSubstitute:
	.string "Would you like to teach SUBSTITUTE?$"

OldaleTown_House2_Basement_Text_TeachSwagger:
	.string "Would you like to teach SWAGGER?$"

OldaleTown_House2_Basement_Text_NoOtherMoves:
	.string "I don't have any more moves to offer.\n"
	.string "Would you like to see the list again?$"

OldaleTown_House2_Basement_Text_WhichMoveToTeach:
	.string "Which move should I teach?$"

OldaleTown_House2_Basement_EventScript_BossNPC::
	lock
	faceplayer
	callnative Script_IsPartyOverLevelCap
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_House2_Basement_EventScript_BossOverleveled
	message OldaleTown_House2_Basement_Text_WhichBossToFight
	waitmessage
	goto_if_set FLAG_BADGE08_GET, OldaleTown_House2_Basement_EventScript_BossMenu_8Badges
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_BossMenu_7Badges
	goto OldaleTown_House2_Basement_EventScript_BossMenu_Normal

OldaleTown_House2_Basement_EventScript_BossOverleveled::
	msgbox OldaleTown_House2_Basement_Text_BossOverleveled, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_EventScript_BossMenu_Normal::
	dynmultipush OldaleTown_House2_Basement_Text_Viola, 0
	dynmultipush OldaleTown_House2_Basement_Text_Roxanne, 1
	dynmultipush OldaleTown_House2_Basement_Text_Brawly, 2
	dynmultipush OldaleTown_House2_Basement_Text_Wattson, 3
	dynmultipush OldaleTown_House2_Basement_Text_Flannery, 4
	dynmultipush OldaleTown_House2_Basement_Text_Norman, 5
	dynmultipush OldaleTown_House2_Basement_Text_Winona, 6
	dynmultipush OldaleTown_House2_Basement_Text_TateLiza, 7
	dynmultipush OldaleTown_House2_Basement_Text_JuanWallace, 8
	dynmultipush gText_Exit, 9
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, OldaleTown_House2_Basement_EventScript_FightViola
	case 1, OldaleTown_House2_Basement_EventScript_FightRoxanne
	case 2, OldaleTown_House2_Basement_EventScript_FightBrawly
	case 3, OldaleTown_House2_Basement_EventScript_FightWattson
	case 4, OldaleTown_House2_Basement_EventScript_FightFlannery
	case 5, OldaleTown_House2_Basement_EventScript_FightNorman
	case 6, OldaleTown_House2_Basement_EventScript_FightWinona
	case 7, OldaleTown_House2_Basement_EventScript_FightTateLiza
	case 8, OldaleTown_House2_Basement_EventScript_FightJuanWallace
	goto OldaleTown_House2_Basement_EventScript_TutorCancel
	end

OldaleTown_House2_Basement_EventScript_BossMenu_7Badges::
	dynmultipush OldaleTown_House2_Basement_Text_Viola, 0
	dynmultipush OldaleTown_House2_Basement_Text_Roxanne, 1
	dynmultipush OldaleTown_House2_Basement_Text_Brawly, 2
	dynmultipush OldaleTown_House2_Basement_Text_Wattson, 3
	dynmultipush OldaleTown_House2_Basement_Text_Flannery, 4
	dynmultipush OldaleTown_House2_Basement_Text_Norman, 5
	dynmultipush OldaleTown_House2_Basement_Text_Winona, 6
	dynmultipush OldaleTown_House2_Basement_Text_TateLiza, 7
	dynmultipush OldaleTown_House2_Basement_Text_JuanWallace, 8
	dynmultipush OldaleTown_House2_Basement_Text_Maxie, 10
	dynmultipush OldaleTown_House2_Basement_Text_Archie, 11
	dynmultipush gText_Exit, 9
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, OldaleTown_House2_Basement_EventScript_FightViola
	case 1, OldaleTown_House2_Basement_EventScript_FightRoxanne
	case 2, OldaleTown_House2_Basement_EventScript_FightBrawly
	case 3, OldaleTown_House2_Basement_EventScript_FightWattson
	case 4, OldaleTown_House2_Basement_EventScript_FightFlannery
	case 5, OldaleTown_House2_Basement_EventScript_FightNorman
	case 6, OldaleTown_House2_Basement_EventScript_FightWinona
	case 7, OldaleTown_House2_Basement_EventScript_FightTateLiza
	case 8, OldaleTown_House2_Basement_EventScript_FightJuanWallace
	case 10, OldaleTown_House2_Basement_EventScript_FightMaxie
	case 11, OldaleTown_House2_Basement_EventScript_FightArchie
	goto OldaleTown_House2_Basement_EventScript_TutorCancel
	end

OldaleTown_House2_Basement_EventScript_BossMenu_8Badges::
	dynmultipush OldaleTown_House2_Basement_Text_Sidney, 12
	dynmultipush OldaleTown_House2_Basement_Text_Spenser, 13
	dynmultipush OldaleTown_House2_Basement_Text_Phoebe, 14
	dynmultipush OldaleTown_House2_Basement_Text_Lucy, 15
	dynmultipush OldaleTown_House2_Basement_Text_Glacia, 16
	dynmultipush OldaleTown_House2_Basement_Text_Tucker, 17
	dynmultipush OldaleTown_House2_Basement_Text_Drake, 18
	dynmultipush OldaleTown_House2_Basement_Text_Brandon, 19
	dynmultipush OldaleTown_House2_Basement_Text_Wally, 20
	dynmultipush OldaleTown_House2_Basement_Text_Steven, 21
	dynmultipush gText_Exit, 9
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 12, OldaleTown_House2_Basement_EventScript_FightSidney
	case 13, OldaleTown_House2_Basement_EventScript_FightSpenser
	case 14, OldaleTown_House2_Basement_EventScript_FightPhoebe
	case 15, OldaleTown_House2_Basement_EventScript_FightLucy
	case 16, OldaleTown_House2_Basement_EventScript_FightGlacia
	case 17, OldaleTown_House2_Basement_EventScript_FightTucker
	case 18, OldaleTown_House2_Basement_EventScript_FightDrake
	case 19, OldaleTown_House2_Basement_EventScript_FightBrandon
	case 20, OldaleTown_House2_Basement_EventScript_FightWally
	case 21, OldaleTown_House2_Basement_EventScript_FightSteven
	goto OldaleTown_House2_Basement_EventScript_TutorCancel
	end

OldaleTown_House2_Basement_EventScript_FightFlannery::
	setvar VAR_0x8005, OBJ_EVENT_GFX_FLANNERY
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Flannery8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Flannery7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Flannery6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Flannery5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Flannery4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Flannery3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Flannery2
	goto OldaleTown_House2_Basement_EventScript_Flannery1
	end

OldaleTown_House2_Basement_EventScript_Flannery1:
	trainerbattle_no_intro TRAINER_FLANNERY_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery2:
	trainerbattle_no_intro TRAINER_FLANNERY_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery3:
	trainerbattle_no_intro TRAINER_FLANNERY_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery4:
	trainerbattle_no_intro TRAINER_FLANNERY_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery5:
	trainerbattle_no_intro TRAINER_FLANNERY_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery6:
	trainerbattle_no_intro TRAINER_FLANNERY_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery7:
	trainerbattle_no_intro TRAINER_FLANNERY_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Flannery8:
	trainerbattle_no_intro TRAINER_FLANNERY_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightViola::
	setvar VAR_0x8005, OBJ_EVENT_GFX_VIOLA
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Viola8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Viola7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Viola6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Viola5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Viola4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Viola3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Viola2
	goto OldaleTown_House2_Basement_EventScript_Viola1
	end

OldaleTown_House2_Basement_EventScript_Viola1:
	trainerbattle_no_intro TRAINER_VIOLA_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola2:
	trainerbattle_no_intro TRAINER_VIOLA_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola3:
	trainerbattle_no_intro TRAINER_VIOLA_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola4:
	trainerbattle_no_intro TRAINER_VIOLA_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola5:
	trainerbattle_no_intro TRAINER_VIOLA_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola6:
	trainerbattle_no_intro TRAINER_VIOLA_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola7:
	trainerbattle_no_intro TRAINER_VIOLA_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Viola8:
	trainerbattle_no_intro TRAINER_VIOLA_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightRoxanne::
	setvar VAR_0x8005, OBJ_EVENT_GFX_ROXANNE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Roxanne8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Roxanne7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Roxanne6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Roxanne5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Roxanne4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Roxanne3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Roxanne2
	goto OldaleTown_House2_Basement_EventScript_Roxanne1
	end

OldaleTown_House2_Basement_EventScript_Roxanne1:
	trainerbattle_no_intro TRAINER_ROXANNE_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne2:
	trainerbattle_no_intro TRAINER_ROXANNE_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne3:
	trainerbattle_no_intro TRAINER_ROXANNE_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne4:
	trainerbattle_no_intro TRAINER_ROXANNE_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne5:
	trainerbattle_no_intro TRAINER_ROXANNE_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne6:
	trainerbattle_no_intro TRAINER_ROXANNE_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne7:
	trainerbattle_no_intro TRAINER_ROXANNE_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Roxanne8:
	trainerbattle_no_intro TRAINER_ROXANNE_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightBrawly::
	setvar VAR_0x8005, OBJ_EVENT_GFX_BRAWLY
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Brawly8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Brawly7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Brawly6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Brawly5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Brawly4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Brawly3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Brawly2
	goto OldaleTown_House2_Basement_EventScript_Brawly1
	end

OldaleTown_House2_Basement_EventScript_Brawly1:
	trainerbattle_no_intro TRAINER_BRAWLY_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly2:
	trainerbattle_no_intro TRAINER_BRAWLY_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly3:
	trainerbattle_no_intro TRAINER_BRAWLY_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly4:
	trainerbattle_no_intro TRAINER_BRAWLY_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly5:
	trainerbattle_no_intro TRAINER_BRAWLY_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly6:
	trainerbattle_no_intro TRAINER_BRAWLY_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly7:
	trainerbattle_no_intro TRAINER_BRAWLY_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Brawly8:
	trainerbattle_no_intro TRAINER_BRAWLY_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightWattson::
	setvar VAR_0x8005, OBJ_EVENT_GFX_WATTSON
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Wattson8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Wattson7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Wattson6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Wattson5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Wattson4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Wattson3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Wattson2
	goto OldaleTown_House2_Basement_EventScript_Wattson1
	end

OldaleTown_House2_Basement_EventScript_Wattson1:
	trainerbattle_no_intro TRAINER_WATTSON_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson2:
	trainerbattle_no_intro TRAINER_WATTSON_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson3:
	trainerbattle_no_intro TRAINER_WATTSON_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson4:
	trainerbattle_no_intro TRAINER_WATTSON_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson5:
	trainerbattle_no_intro TRAINER_WATTSON_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson6:
	trainerbattle_no_intro TRAINER_WATTSON_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson7:
	trainerbattle_no_intro TRAINER_WATTSON_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Wattson8:
	trainerbattle_no_intro TRAINER_WATTSON_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightNorman::
	setvar VAR_0x8005, OBJ_EVENT_GFX_NORMAN
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Norman8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Norman7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Norman6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Norman5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Norman4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Norman3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Norman2
	goto OldaleTown_House2_Basement_EventScript_Norman1
	end

OldaleTown_House2_Basement_EventScript_Norman1:
	trainerbattle_no_intro TRAINER_NORMAN_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman2:
	trainerbattle_no_intro TRAINER_NORMAN_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman3:
	trainerbattle_no_intro TRAINER_NORMAN_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman4:
	trainerbattle_no_intro TRAINER_NORMAN_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman5:
	trainerbattle_no_intro TRAINER_NORMAN_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman6:
	trainerbattle_no_intro TRAINER_NORMAN_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman7:
	trainerbattle_no_intro TRAINER_NORMAN_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Norman8:
	trainerbattle_no_intro TRAINER_NORMAN_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightWinona::
	setvar VAR_0x8005, OBJ_EVENT_GFX_WINONA
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Winona8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Winona7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Winona6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Winona5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Winona4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Winona3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Winona2
	goto OldaleTown_House2_Basement_EventScript_Winona1
	end

OldaleTown_House2_Basement_EventScript_Winona1:
	trainerbattle_no_intro TRAINER_WINONA_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona2:
	trainerbattle_no_intro TRAINER_WINONA_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona3:
	trainerbattle_no_intro TRAINER_WINONA_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona4:
	trainerbattle_no_intro TRAINER_WINONA_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona5:
	trainerbattle_no_intro TRAINER_WINONA_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona6:
	trainerbattle_no_intro TRAINER_WINONA_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona7:
	trainerbattle_no_intro TRAINER_WINONA_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Winona8:
	trainerbattle_no_intro TRAINER_WINONA_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightTateLiza::
	setvar VAR_0x8005, OBJ_EVENT_GFX_TATE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_TateLiza8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_TateLiza7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_TateLiza6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_TateLiza5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_TateLiza4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_TateLiza3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_TateLiza2
	goto OldaleTown_House2_Basement_EventScript_TateLiza1
	end

OldaleTown_House2_Basement_EventScript_TateLiza1:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza2:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza3:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza4:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza5:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza6:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza7:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_TateLiza8:
	trainerbattle_no_intro TRAINER_TATE_AND_LIZA_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightJuanWallace::
	setvar VAR_0x8005, OBJ_EVENT_GFX_JUAN
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	goto_if_set FLAG_BADGE07_GET, OldaleTown_House2_Basement_EventScript_Juan8
	goto_if_set FLAG_BADGE06_GET, OldaleTown_House2_Basement_EventScript_Juan7
	goto_if_set FLAG_BADGE05_GET, OldaleTown_House2_Basement_EventScript_Juan6
	goto_if_set FLAG_BADGE04_GET, OldaleTown_House2_Basement_EventScript_Juan5
	goto_if_set FLAG_BADGE03_GET, OldaleTown_House2_Basement_EventScript_Juan4
	goto_if_set FLAG_BADGE02_GET, OldaleTown_House2_Basement_EventScript_Juan3
	goto_if_set FLAG_BADGE01_GET, OldaleTown_House2_Basement_EventScript_Juan2
	goto OldaleTown_House2_Basement_EventScript_Juan1
	end

OldaleTown_House2_Basement_EventScript_Juan1:
	trainerbattle_no_intro TRAINER_JUAN_1, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan2:
	trainerbattle_no_intro TRAINER_JUAN_2, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan3:
	trainerbattle_no_intro TRAINER_JUAN_3, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan4:
	trainerbattle_no_intro TRAINER_JUAN_4, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan5:
	trainerbattle_no_intro TRAINER_JUAN_5, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan6:
	trainerbattle_no_intro TRAINER_JUAN_6, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan7:
	trainerbattle_no_intro TRAINER_JUAN_7, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_Juan8:
	trainerbattle_no_intro TRAINER_JUAN_8, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_EventScript_FightMaxie::
	setvar VAR_0x8005, OBJ_EVENT_GFX_MAXIE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightArchie::
	setvar VAR_0x8005, OBJ_EVENT_GFX_ARCHIE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_ARCHIE, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightSidney::
	setvar VAR_0x8005, OBJ_EVENT_GFX_SIDNEY
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_SIDNEY, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightSpenser::
	setvar VAR_0x8005, OBJ_EVENT_GFX_SPENSER
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_SPENSER, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightPhoebe::
	setvar VAR_0x8005, OBJ_EVENT_GFX_PHOEBE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_PHOEBE, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightLucy::
	setvar VAR_0x8005, OBJ_EVENT_GFX_LUCY
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_LUCY, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightGlacia::
	setvar VAR_0x8005, OBJ_EVENT_GFX_GLACIA
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_GLACIA, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightTucker::
	setvar VAR_0x8005, OBJ_EVENT_GFX_TUCKER
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_TUCKER, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightDrake::
	setvar VAR_0x8005, OBJ_EVENT_GFX_DRAKE
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_DRAKE, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightBrandon::
	setvar VAR_0x8005, OBJ_EVENT_GFX_BRANDON
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_BRANDON, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightWally::
	setvar VAR_0x8005, OBJ_EVENT_GFX_WALLY
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_WALLY, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset
OldaleTown_House2_Basement_EventScript_FightSteven::
	setvar VAR_0x8005, OBJ_EVENT_GFX_STEVEN
	call OldaleTown_House2_Basement_EventScript_BossTwirlAndChange
	trainerbattle_no_intro TRAINER_STEVEN, OldaleTown_House2_Basement_Text_BossDefeated
	goto OldaleTown_House2_Basement_EventScript_BossReset

OldaleTown_House2_Basement_Text_WhichBossToFight:
	.string "Which Boss would you like to fight?$"
OldaleTown_House2_Basement_Text_BossDefeated:
	.string "What a spectacular performance!$"
OldaleTown_House2_Basement_Text_Viola:
	.string "VIOLA$"
OldaleTown_House2_Basement_Text_Roxanne:
	.string "ROXANNE$"
OldaleTown_House2_Basement_Text_Brawly:
	.string "BRAWLY$"
OldaleTown_House2_Basement_Text_Wattson:
	.string "WATTSON$"
OldaleTown_House2_Basement_Text_Flannery:
	.string "FLANNERY$"
OldaleTown_House2_Basement_Text_Norman:
	.string "NORMAN$"
OldaleTown_House2_Basement_Text_Winona:
	.string "WINONA$"
OldaleTown_House2_Basement_Text_TateLiza:
	.string "TATE&LIZA$"
OldaleTown_House2_Basement_Text_JuanWallace:
	.string "JUAN&WALCE$"
OldaleTown_House2_Basement_Text_Maxie:
	.string "MAXIE$"
OldaleTown_House2_Basement_Text_Archie:
	.string "ARCHIE$"
OldaleTown_House2_Basement_Text_Sidney:
	.string "SIDNEY$"
OldaleTown_House2_Basement_Text_Spenser:
	.string "SPENSER$"
OldaleTown_House2_Basement_Text_Phoebe:
	.string "PHOEBE$"
OldaleTown_House2_Basement_Text_Lucy:
	.string "LUCY$"
OldaleTown_House2_Basement_Text_Glacia:
	.string "GLACIA$"
OldaleTown_House2_Basement_Text_Tucker:
	.string "TUCKER$"
OldaleTown_House2_Basement_Text_Drake:
	.string "DRAKE$"
OldaleTown_House2_Basement_Text_Brandon:
	.string "BRANDON$"
OldaleTown_House2_Basement_Text_Wally:
	.string "WALLY$"
OldaleTown_House2_Basement_Text_Steven:
	.string "STEVEN$"

OldaleTown_House2_Basement_EventScript_Cook::
	goto SlateportCity_EventScript_Cook

OldaleTown_House2_Basement_EventScript_HiddenPowerNPC::
	lock
	faceplayer
	msgbox OldaleTown_House2_Basement_Text_HiddenPowerNPC_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_HiddenPowerNPC_Decline
	msgbox SlateportCity_Text_HiddenPowerNPC_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, 255, SlateportCity_EventScript_HiddenPowerNPC_Decline
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_HiddenPowerNPC_Egg
	callnative CheckHiddenPower
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_HiddenPowerNPC_NoHiddenPower
	msgbox SlateportCity_Text_HiddenPowerNPC_ChooseType, MSGBOX_DEFAULT
	copyvar VAR_0x8006, VAR_0x8004
	setvar VAR_0x8004, SCROLL_MULTI_HIDDEN_POWER_TYPES
	special ShowScrollableMultichoice
	waitstate
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, SlateportCity_EventScript_HiddenPowerNPC_Decline
	copyvar VAR_0x8005, VAR_RESULT
	callnative MapHiddenPowerMenuSelectionToType
	copyvar VAR_0x8004, VAR_0x8006
	callnative SetHiddenPowerType
	msgbox SlateportCity_Text_HiddenPowerNPC_Success, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_Text_HiddenPowerNPC_Intro:
	.string "I can change the type of your\n"
	.string "POKéMON's HIDDEN POWER.\p"
	.string "Would you like to do that?$"

OldaleTown_House2_Basement_EventScript_EnergyGuru::
	goto SlateportCity_EventScript_EnergyGuru
	goto_if_lt VAR_BADGE_COUNT, 2, OldaleTown_House2_Basement_EventScript_EnergyGuruNotEnoughBadges

OldaleTown_House2_Basement_EventScript_EnergyOracle::
	goto SlateportCity_EventScript_EnergyOracle

OldaleTown_House2_Basement_EventScript_EnergyGuruNotEnoughBadges::
	msgbox OldaleTown_House2_Basement_Text_EnergyGuruNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_Text_HiddenPowerNPC_Decline:
	.string "Come back if you change your mind.$"

OldaleTown_House2_Basement_Text_MoveRelearnerNotEnoughBadges:
	.string "I'm sorry, but I only teach these\n"
	.string "moves to experienced TRAINERS.\p"
	.string "Come back once you have at least\n"
	.string "four GYM BADGES.$"

OldaleTown_House2_Basement_Text_EnergyGuruNotEnoughBadges:
	.string "I'm sorry, but I only help experienced\n"
	.string "TRAINERS with their POKéMON.\p"
	.string "Come back once you have at least\n"
	.string "two GYM BADGES.$"

OldaleTown_House2_Basement_EventScript_EggMoveTutor::
	lock
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 2,  OldaleTown_House2_Basement_EventScript_EggMoveTutor_NotEnoughBadges
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_House2_Basement_EventScript_EggMoveTutor_IsEgg
	copyvar VAR_TEMP_1, VAR_0x8004 @ Store party slot
	specialvar VAR_0x8004, ScriptGetPartyMonSpecies @ Overwrites VAR_0x8004 with species
	special GetFirstEggMoveForSpecies
	goto_if_eq VAR_RESULT, MOVE_NONE, OldaleTown_House2_Basement_EventScript_EggMoveTutor_NoEggMove
	copyvar VAR_0x8004, VAR_TEMP_1 @ Restore party slot
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	setmoverelearnerstate MOVE_RELEARNER_EGG_MOVES
	special TeachMoveRelearnerMove
	waitstate
	goto OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline
	end

OldaleTown_House2_Basement_EventScript_EggMoveTutor_NotEnoughBadges::
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_NotEnoughBadges, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline::
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_Decline, MSGBOX_DEFAULT
	release
	end

OldaleTown_House2_Basement_EventScript_EggMoveTutor_IsEgg::
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_IsEgg, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline

OldaleTown_House2_Basement_EventScript_EggMoveTutor_NoEggMove::
	msgbox OldaleTown_House2_Basement_Text_EggMoveTutor_NoEggMove, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_EggMoveTutor_Decline

OldaleTown_House2_Basement_Text_EggMoveTutor_Intro:
	.string "I am an expert on POKéMON genetics.\n"
	.string "I can teach a POKéMON a move it\l"
	.string "normally only knows from birth.\p"
	.string "Would you like me to try?$"

OldaleTown_House2_Basement_Text_EggMoveTutor_NotEnoughBadges:
	.string "I'm sorry, but I only help experienced\n"
	.string "TRAINERS with their POKéMON.\p"
	.string "Come back once you have at least\n"
	.string "two GYM BADGES.$"

OldaleTown_House2_Basement_Text_EggMoveTutor_ChooseMon:
	.string "Which POKéMON should I tutor?$"

OldaleTown_House2_Basement_Text_EggMoveTutor_NoEggMove:
	.string "I'm sorry, but this species doesn't\n"
	.string "seem to have any EGG MOVES.$"

OldaleTown_House2_Basement_Text_EggMoveTutor_IsEgg:
	.string "I cannot teach an EGG.$"

OldaleTown_House2_Basement_Text_EggMoveTutor_Decline:
	.string "Farewell.$"

OldaleTown_House2_Basement_EventScript_BossTwirlAndChange::
	copyvar VAR_0x8004, VAR_LAST_TALKED
	applymovement VAR_0x8004, OldaleTown_House2_Basement_Movement_Twirl
	waitmovement 0
	callnative SetObjectGfx
	return

OldaleTown_House2_Basement_EventScript_BossReset::
	copyvar VAR_0x8004, VAR_LAST_TALKED
	applymovement VAR_0x8004, OldaleTown_House2_Basement_Movement_Twirl
	waitmovement 0
	setvar VAR_0x8005, OBJ_EVENT_GFX_OLD_MAN
	callnative SetObjectGfx
	special HealPlayerParty
	release
	end

OldaleTown_House2_Basement_Movement_Twirl:
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end

OldaleTown_House2_Basement_EventScript_Houndstone::
	lock
	faceplayer
	msgbox OldaleTown_House2_Basement_Text_HoundstoneIntro, MSGBOX_DEFAULT
	callnative Script_BuildFaintCounterMenu
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, OldaleTown_House2_Basement_EventScript_Houndstone_Exit
	copyvar VAR_0x8004, VAR_RESULT
	callnative Script_SetPlayerFaintCounter
	goto_if_eq VAR_0x8004, 0, OldaleTown_House2_Basement_EventScript_Houndstone_Disappointed
	msgbox OldaleTown_House2_Basement_Text_HoundstoneEnd, MSGBOX_DEFAULT
	goto OldaleTown_House2_Basement_EventScript_Houndstone_Exit

OldaleTown_House2_Basement_EventScript_Houndstone_Disappointed::
	msgbox OldaleTown_House2_Basement_Text_HoundstoneDisappointed, MSGBOX_DEFAULT
OldaleTown_House2_Basement_EventScript_Houndstone_Exit::
	release
	end

OldaleTown_House2_Basement_Text_HoundstoneIntro:
	.string "HOUNDSTONE looks at you intensely,\n"
	.string "as if eager to learn how many POKéMON\l"
	.string "you've allowed to faint.$"

OldaleTown_House2_Basement_Text_HoundstoneEnd:
	.string "HOUNDSTONE let out a low howl of\n"
	.string "satisfaction.$"

OldaleTown_House2_Basement_Text_HoundstoneDisappointed:
	.string "HOUNDSTONE let out a low howl of\n"
	.string "disappointment…$"

OldaleTown_House2_Basement_Text_BossOverleveled:
	.string "I'm sorry, but you have a POKéMON\n"
	.string "that's too high a level to fight me.$"

OldaleTown_House2_Basement_EventScript_WallEtching::
	msgbox OldaleTown_House2_Basement_Text_WallEtching, MSGBOX_SIGN
	end

OldaleTown_House2_Basement_Text_WallEtching:
	.string "Two words are etched into the wall:\n"
	.string "BLITZ JAIL$"

OldaleTown_House2_Basement_EventScript_Slowbro::
    lock
    faceplayer
    goto_if_set FLAG_DISABLE_CRITICAL_HITS, OldaleTown_House2_Basement_EventScript_Slowbro_Enabled
    msgbox OldaleTown_House2_Basement_Text_Slowbro_Disable, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, OldaleTown_House2_Basement_EventScript_Slowbro_DoDisable
    release
    end

OldaleTown_House2_Basement_EventScript_Slowbro_DoDisable::
    setflag FLAG_DISABLE_CRITICAL_HITS
    msgbox OldaleTown_House2_Basement_Text_Slowbro_Disabled, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_EventScript_Slowbro_Enabled::
    msgbox OldaleTown_House2_Basement_Text_Slowbro_Enable, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, OldaleTown_House2_Basement_EventScript_Slowbro_DoEnable
    release
    end

OldaleTown_House2_Basement_EventScript_Slowbro_DoEnable::
    clearflag FLAG_DISABLE_CRITICAL_HITS
    msgbox OldaleTown_House2_Basement_Text_Slowbro_EnabledMsg, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_Text_Slowbro_Disable:
    .string "SLOWBRO's carefree demeanor fills you\n"
    .string "with confidence. Disable Critical Hits?$"

OldaleTown_House2_Basement_Text_Slowbro_Disabled:
    .string "Critical hits have been disabled.$"

OldaleTown_House2_Basement_Text_Slowbro_Enable:
    .string "Critical hits are currently disabled.\n"
    .string "Would you like to enable them?$"

OldaleTown_House2_Basement_Text_Slowbro_EnabledMsg:
    .string "Critical hits have been enabled.$"

OldaleTown_House2_Basement_EventScript_Hypno::
    lock
    faceplayer
    msgbox OldaleTown_House2_Basement_Text_HypnoIntro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, OldaleTown_House2_Basement_EventScript_Hypno_Decline
	closemessage
    fadescreen FADE_TO_BLACK
    special AdvanceTimeToNextPeriod
    fadescreen FADE_FROM_BLACK
    gettimeofday
    copyvar VAR_RESULT, VAR_0x8000
    switch VAR_RESULT
    case 0, OldaleTown_House2_Basement_EventScript_Hypno_Morning
    case 1, OldaleTown_House2_Basement_EventScript_Hypno_Day
    case 2, OldaleTown_House2_Basement_EventScript_Hypno_Night
    case 3, OldaleTown_House2_Basement_EventScript_Hypno_Night
	release
    end

OldaleTown_House2_Basement_EventScript_Hypno_Morning::
    msgbox OldaleTown_House2_Basement_Text_HypnoMorning, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_EventScript_Hypno_Day::
    msgbox OldaleTown_House2_Basement_Text_HypnoDay, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_EventScript_Hypno_Night::
    msgbox OldaleTown_House2_Basement_Text_HypnoNight, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_EventScript_Hypno_Decline::
    msgbox OldaleTown_House2_Basement_Text_HypnoDecline, MSGBOX_DEFAULT
    release
    end

OldaleTown_House2_Basement_Text_HypnoIntro:
    .string "HYPNO's pendulum swings rhythmically.\p"
    .string "Would you like me to advance time\n"
    .string "to the next period?$"

OldaleTown_House2_Basement_Text_HypnoMorning:
    .string "It is now morning.$"

OldaleTown_House2_Basement_Text_HypnoDay:
    .string "It is now day.$"

OldaleTown_House2_Basement_Text_HypnoNight:
    .string "It is now night.$"

OldaleTown_House2_Basement_Text_HypnoDecline:
    .string "HYPNO continues swinging its pendulum…$"

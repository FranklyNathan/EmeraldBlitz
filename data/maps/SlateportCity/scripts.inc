.set LOCALID_SHADY_MAN, 38

SlateportCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

.set SCROLL_MULTI_HIDDEN_POWER_TYPES, 13

SlateportCity_OnTransition:
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_MovePeopleForSternInterview
	call_if_eq VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport::
	setflag FLAG_VISITED_SLATEPORT_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	return

SlateportCity_EventScript_MovePeopleForSternInterview::
	setobjectxyperm LOCALID_SLATEPORT_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_SLATEPORT_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_SLATEPORT_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_SLATEPORT_COOK, 27, 16
	setobjectxyperm LOCALID_SLATEPORT_GIRL, 28, 16
	setobjectxyperm LOCALID_SLATEPORT_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_SLATEPORT_MAN_1, 31, 14
	setobjectmovementtype LOCALID_SLATEPORT_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_SLATEPORT_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 30, SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft::
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame:
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.2byte 0

SlateportCity_EventScript_ScottScene::
	lockall
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ScottApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru::
	lock
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 2, SlateportCity_EventScript_EnergyGuruNotEnoughBadges
	callnative CheckPartyForEnergyGuruMon
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_EnergyGuru_NoMon
	msgbox SlateportCity_Text_EnergyGuru_HaveMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_EnergyGuru_Decline
	msgbox SlateportCity_Text_EnergyGuru_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, SlateportCity_EventScript_EnergyGuru_Decline
	callnative CheckSelectedMonForEnergyGuru
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_EnergyGuru_InvalidMon
	callnative TriggerEnergyGuruEvolution
	waitstate
	goto SlateportCity_EventScript_EnergyGuru_Decline
	end

SlateportCity_EventScript_EnergyGuruNotEnoughBadges::
	msgbox SlateportCity_Text_EnergyGuruNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_EnergyGuru_NoMon::
	msgbox SlateportCity_Text_EnergyGuru_Explain, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_EnergyGuru_Decline
	end

SlateportCity_EventScript_EnergyGuru_InvalidMon::
	msgbox SlateportCity_Text_EnergyGuru_InvalidMon, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_EnergyGuru_Decline
	end

SlateportCity_EventScript_EnergyGuru_Decline::
	msgbox SlateportCity_Text_EnergyGuru_Hooplah, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_EffortRibbonWoman::
	lock
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 4, SlateportCity_EventScript_EffortRibbonWomanNotEnoughBadges
	callnative CheckPartyForEffortRibbonMon
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_EffortRibbonWoman_NoMon
	msgbox SlateportCity_Text_EffortRibbonWoman_HaveMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_EffortRibbonWoman_Decline
	msgbox SlateportCity_Text_EffortRibbonWoman_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, SlateportCity_EventScript_EffortRibbonWoman_Decline
	callnative CheckSelectedMonForEffortRibbon
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_EffortRibbonWoman_InvalidMon
	callnative TriggerEffortRibbonEvolution
	waitstate
	goto SlateportCity_EventScript_EffortRibbonWoman_Decline
	end

SlateportCity_EventScript_EffortRibbonWoman_NoMon::
	msgbox SlateportCity_Text_EffortRibbonWoman_Explain, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_EffortRibbonWoman_Decline
	end

SlateportCity_EventScript_EffortRibbonWoman_InvalidMon::
	msgbox SlateportCity_Text_EffortRibbonWoman_InvalidMon, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_EffortRibbonWoman_Decline
	end

SlateportCity_EventScript_EffortRibbonWoman_Decline::
	msgbox SlateportCity_Text_EffortRibbonWoman_Decline, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_EffortRibbonWomanNotEnoughBadges::
	msgbox SlateportCity_Text_EffortRibbonWomanNotEnoughBadges, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed::
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon::
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook:: @ The new Status Chef
	lock
	faceplayer
	msgbox SlateportCity_Text_CookIntro, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_CookChooseStatus
	end

SlateportCity_EventScript_CookChooseStatus::
	message SlateportCity_Text_CookWhichStatus
	waitmessage
	multichoice 20, 0, MULTI_STATUS_EFFECTS, FALSE
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_CookSetStatusPoison
	case 1, SlateportCity_EventScript_CookSetStatusBurn
	case 2, SlateportCity_EventScript_CookSetStatusParalyze
	case 3, SlateportCity_EventScript_CookSetStatusFreeze
	case 4, SlateportCity_EventScript_CookSetStatusSleep
	case 5, SlateportCity_EventScript_CookCancel
	case MULTI_B_PRESSED, SlateportCity_EventScript_CookCancel
	end

SlateportCity_EventScript_CookSetStatusPoison::
	setvar VAR_0x8005, STATUS1_POISON
	goto SlateportCity_EventScript_CookChoosePokemon

SlateportCity_EventScript_CookSetStatusBurn::
	setvar VAR_0x8005, STATUS1_BURN
	goto SlateportCity_EventScript_CookChoosePokemon

SlateportCity_EventScript_CookSetStatusParalyze::
	setvar VAR_0x8005, STATUS1_PARALYSIS
	goto SlateportCity_EventScript_CookChoosePokemon

SlateportCity_EventScript_CookSetStatusFreeze::
	setvar VAR_0x8005, STATUS1_FREEZE
	goto SlateportCity_EventScript_CookChoosePokemon

SlateportCity_EventScript_CookSetStatusSleep::
	setvar VAR_0x8005, STATUS1_SLEEP
	goto SlateportCity_EventScript_CookChoosePokemon

SlateportCity_EventScript_CookChoosePokemon::
	msgbox SlateportCity_Text_CookWhichPokemon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	// Exit if player cancels party menu
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge SlateportCity_EventScript_CookCancel
	// Apply the status
	setstatus1 VAR_0x8005, VAR_0x8004
	msgbox SlateportCity_Text_CookDone, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookCancel::
	msgbox SlateportCity_Text_CookComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview::
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end
SlateportCity_EventScript_OldWoman::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview::
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl::
	lock
	faceplayer
	compare VAR_BADGE_COUNT, 4
	goto_if_eq SlateportCity_EventScript_Girl_CheckEevee
SlateportCity_EventScript_Girl_Default::
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl_CheckEevee::
	callnative CheckPartyForEeveelution
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_EventScript_Girl_OfferDevolve
	goto SlateportCity_EventScript_Girl_Default

SlateportCity_EventScript_Girl_OfferDevolve::
	msgbox SlateportCity_Text_Girl_DevolveOffer, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_EventScript_Girl_Decline
	callnative DevolveEeveelution
	addmoney 1000
	playse SE_SHOP
	msgbox SlateportCity_Text_Girl_DevolveComplete, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl_Decline::
	msgbox SlateportCity_Text_Girl_Decline, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview::
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase::
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview::
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan::
	goto_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview::
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview::
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone::
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign::
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion::
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete::
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign::
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign::
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign::
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign::
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete::
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign::
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

@ Unclear if the text here was meant to be different, but its not
SlateportCity_EventScript_ManiacSternInterview::
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2::
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1::
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2::
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_ge VAR_BADGE_COUNT, 4, SlateportCity_EventScript_PokefanF_Eeveelutions
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_PokefanF_Eeveelutions::
	randomelement SPECIES_VAPOREON, SPECIES_JOLTEON, SPECIES_FLAREON, SPECIES_ESPEON, SPECIES_UMBREON, SPECIES_LEAFEON, SPECIES_GLACEON, SPECIES_SYLVEON
	copyvar VAR_TEMP_1, VAR_RESULT
	copyvar VAR_0x8000, VAR_TEMP_1
	call SlateportCity_EventScript_BufferMon1
SlateportCity_EventScript_PokefanF_Eeveelutions_Roll2:
	randomelement SPECIES_VAPOREON, SPECIES_JOLTEON, SPECIES_FLAREON, SPECIES_ESPEON, SPECIES_UMBREON, SPECIES_LEAFEON, SPECIES_GLACEON, SPECIES_SYLVEON
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, VAR_TEMP_1, SlateportCity_EventScript_PokefanF_Eeveelutions_Roll2
	copyvar VAR_0x8000, VAR_TEMP_2
	call SlateportCity_EventScript_BufferMon2
SlateportCity_EventScript_PokefanF_Eeveelutions_Roll3:
	randomelement SPECIES_VAPOREON, SPECIES_JOLTEON, SPECIES_FLAREON, SPECIES_ESPEON, SPECIES_UMBREON, SPECIES_LEAFEON, SPECIES_GLACEON, SPECIES_SYLVEON
	copyvar VAR_TEMP_3, VAR_RESULT
	goto_if_eq VAR_TEMP_3, VAR_TEMP_1, SlateportCity_EventScript_PokefanF_Eeveelutions_Roll3
	goto_if_eq VAR_TEMP_3, VAR_TEMP_2, SlateportCity_EventScript_PokefanF_Eeveelutions_Roll3
	copyvar VAR_0x8000, VAR_TEMP_3
	call SlateportCity_EventScript_BufferMon3
	msgbox SlateportCity_Text_FavoriteEeveelutions, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	release
	end

SlateportCity_EventScript_BufferMon1::
	switch VAR_0x8000
	case SPECIES_VAPOREON, SlateportCity_EventScript_Mon1Vaporeon
	case SPECIES_JOLTEON,  SlateportCity_EventScript_Mon1Jolteon
	case SPECIES_FLAREON,  SlateportCity_EventScript_Mon1Flareon
	case SPECIES_ESPEON,   SlateportCity_EventScript_Mon1Espeon
	case SPECIES_UMBREON,  SlateportCity_EventScript_Mon1Umbreon
	case SPECIES_LEAFEON,  SlateportCity_EventScript_Mon1Leafeon
	case SPECIES_GLACEON,  SlateportCity_EventScript_Mon1Glaceon
	case SPECIES_SYLVEON,  SlateportCity_EventScript_Mon1Sylveon
	return

SlateportCity_EventScript_Mon1Vaporeon::
	bufferstring 0, SlateportCity_Text_Vaporeon
	return
SlateportCity_EventScript_Mon1Jolteon::
	bufferstring 0, SlateportCity_Text_Jolteon
	return
SlateportCity_EventScript_Mon1Flareon::
	bufferstring 0, SlateportCity_Text_Flareon
	return
SlateportCity_EventScript_Mon1Espeon::
	bufferstring 0, SlateportCity_Text_Espeon
	return
SlateportCity_EventScript_Mon1Umbreon::
	bufferstring 0, SlateportCity_Text_Umbreon
	return
SlateportCity_EventScript_Mon1Leafeon::
	bufferstring 0, SlateportCity_Text_Leafeon
	return
SlateportCity_EventScript_Mon1Glaceon::
	bufferstring 0, SlateportCity_Text_Glaceon
	return
SlateportCity_EventScript_Mon1Sylveon::
	bufferstring 0, SlateportCity_Text_Sylveon
	return

SlateportCity_EventScript_BufferMon2::
	switch VAR_0x8000
	case SPECIES_VAPOREON, SlateportCity_EventScript_Mon2Vaporeon
	case SPECIES_JOLTEON,  SlateportCity_EventScript_Mon2Jolteon
	case SPECIES_FLAREON,  SlateportCity_EventScript_Mon2Flareon
	case SPECIES_ESPEON,   SlateportCity_EventScript_Mon2Espeon
	case SPECIES_UMBREON,  SlateportCity_EventScript_Mon2Umbreon
	case SPECIES_LEAFEON,  SlateportCity_EventScript_Mon2Leafeon
	case SPECIES_GLACEON,  SlateportCity_EventScript_Mon2Glaceon
	case SPECIES_SYLVEON,  SlateportCity_EventScript_Mon2Sylveon
	return

SlateportCity_EventScript_Mon2Vaporeon::
	bufferstring 1, SlateportCity_Text_Vaporeon
	return
SlateportCity_EventScript_Mon2Jolteon::
	bufferstring 1, SlateportCity_Text_Jolteon
	return
SlateportCity_EventScript_Mon2Flareon::
	bufferstring 1, SlateportCity_Text_Flareon
	return
SlateportCity_EventScript_Mon2Espeon::
	bufferstring 1, SlateportCity_Text_Espeon
	return
SlateportCity_EventScript_Mon2Umbreon::
	bufferstring 1, SlateportCity_Text_Umbreon
	return
SlateportCity_EventScript_Mon2Leafeon::
	bufferstring 1, SlateportCity_Text_Leafeon
	return
SlateportCity_EventScript_Mon2Glaceon::
	bufferstring 1, SlateportCity_Text_Glaceon
	return
SlateportCity_EventScript_Mon2Sylveon::
	bufferstring 1, SlateportCity_Text_Sylveon
	return

SlateportCity_EventScript_BufferMon3::
	switch VAR_0x8000
	case SPECIES_VAPOREON, SlateportCity_EventScript_Mon3Vaporeon
	case SPECIES_JOLTEON,  SlateportCity_EventScript_Mon3Jolteon
	case SPECIES_FLAREON,  SlateportCity_EventScript_Mon3Flareon
	case SPECIES_ESPEON,   SlateportCity_EventScript_Mon3Espeon
	case SPECIES_UMBREON,  SlateportCity_EventScript_Mon3Umbreon
	case SPECIES_LEAFEON,  SlateportCity_EventScript_Mon3Leafeon
	case SPECIES_GLACEON,  SlateportCity_EventScript_Mon3Glaceon
	case SPECIES_SYLVEON,  SlateportCity_EventScript_Mon3Sylveon
	return

SlateportCity_EventScript_Mon3Vaporeon::
	bufferstring 2, SlateportCity_Text_Vaporeon
	return
SlateportCity_EventScript_Mon3Jolteon::
	bufferstring 2, SlateportCity_Text_Jolteon
	return
SlateportCity_EventScript_Mon3Flareon::
	bufferstring 2, SlateportCity_Text_Flareon
	return
SlateportCity_EventScript_Mon3Espeon::
	bufferstring 2, SlateportCity_Text_Espeon
	return
SlateportCity_EventScript_Mon3Umbreon::
	bufferstring 2, SlateportCity_Text_Umbreon
	return
SlateportCity_EventScript_Mon3Leafeon::
	bufferstring 2, SlateportCity_Text_Leafeon
	return
SlateportCity_EventScript_Mon3Glaceon::
	bufferstring 2, SlateportCity_Text_Glaceon
	return
SlateportCity_EventScript_Mon3Sylveon::
	bufferstring 2, SlateportCity_Text_Sylveon
	return

SlateportCity_EventScript_Man2::
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5::
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7::
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt:
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10::
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11::
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_eq VAR_BADGE_COUNT, 2, SlateportCity_PokemartDecor_Badge2
	goto_if_eq VAR_BADGE_COUNT, 3, SlateportCity_PokemartDecor_Badge3
	goto_if_eq VAR_BADGE_COUNT, 4, SlateportCity_PokemartDecor_Badge4
	goto_if_eq VAR_BADGE_COUNT, 5, SlateportCity_PokemartDecor_Badge4
	goto_if_ge VAR_BADGE_COUNT, 6, SlateportCity_PokemartDecor_Badge6
	pokemart SlateportCity_PokemartDecor_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Basic:
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_PokemartDecor_Badge2::
	pokemart SlateportCity_Pokemart_Badge2Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
	
	.align 2
SlateportCity_Pokemart_Badge2Items:
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_PokemartDecor_Badge3::
	pokemart SlateportCity_Pokemart_Badge3Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_Badge3Items:
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_PokemartDecor_Badge4::
	pokemart SlateportCity_Pokemart_Badge4Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_Badge4Items:
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
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_METAL_COAT
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_PokemartDecor_Badge5::
	pokemart SlateportCity_Pokemart_Badge5Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_Badge5Items:
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
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_METAL_COAT
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_PokemartDecor_Badge6::
	pokemart SlateportCity_Pokemart_Badge6Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_Badge6Items:
	.2byte ITEM_LINKING_CORD
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
	.2byte ITEM_DRAGON_SCALE
	.2byte ITEM_KINGS_ROCK
	.2byte ITEM_METAL_COAT
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_ABILITY_PATCH
	.2byte ITEM_SERIOUS_MINT
	pokemartlistend

SlateportCity_EventScript_ComeBackWithSecretPower::
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor:
	.2byte DECOR_RED_BRICK
	.2byte DECOR_BLUE_BRICK
	.2byte DECOR_YELLOW_BRICK
	.2byte DECOR_RED_BALLOON
	.2byte DECOR_BLUE_BALLOON
	.2byte DECOR_YELLOW_BALLOON
	.2byte DECOR_C_LOW_NOTE_MAT
	.2byte DECOR_D_NOTE_MAT
	.2byte DECOR_E_NOTE_MAT
	.2byte DECOR_F_NOTE_MAT
	.2byte DECOR_G_NOTE_MAT
	.2byte DECOR_A_NOTE_MAT
	.2byte DECOR_B_NOTE_MAT
	.2byte DECOR_C_HIGH_NOTE_MAT
	pokemartlistend

SlateportCity_EventScript_PowerTMClerk::
	lock
	setvar VAR_POWER_TM_CLERK, 1
	faceplayer
	goto_if_lt VAR_BADGE_COUNT, 2, SlateportCity_Pokemart_PowerTMs_NotYet
	message gText_HowMayIServeYou
	waitmessage
	goto_if_ge VAR_BADGE_COUNT, 6, SlateportCity_Pokemart_PowerTMs_Badge6TMs
	goto_if_ge VAR_BADGE_COUNT, 4, SlateportCity_Pokemart_PowerTMs_Badge4TMs
	goto_if_le VAR_BADGE_COUNT, 4, SlateportCity_Pokemart_PowerTMs_Badge2TMs
	@ goto_if_eq VAR_BADGE_COUNT, 4, SlateportCity_Pokemart_PowerTMs_Badge4TMs
	pokemart SlateportCity_Pokemart_PowerTMs_Badge4TMs
	setvar VAR_POWER_TM_CLERK, 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_Pokemart_PowerTMs_NotYet::
	msgbox SlateportCity_Text_NotSellingYet, MSGBOX_DEFAULT
	closemessage
	release
	end

SlateportCity_Pokemart_PowerTMs_Badge2TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge2TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge2TMsItems:
	.2byte ITEM_TM_BULLET_SEED
	.2byte ITEM_TM_MUD_SHOT
	.2byte ITEM_TM_ICY_WIND
	.2byte ITEM_TM_POUNCE
	.2byte ITEM_TM_STEEL_WING
	.2byte ITEM_TM_TAUNT
	.2byte ITEM_TM_THIEF
	pokemartlistend

SlateportCity_Pokemart_PowerTMs_Badge3TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge3TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge3TMsItems:
	.2byte ITEM_TM_BULLET_SEED
	pokemartlistend

SlateportCity_Pokemart_PowerTMs_Badge4TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge4TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge4TMsItems:
	.2byte ITEM_TM_BULLET_SEED
	.2byte ITEM_TM_MUD_SHOT
	.2byte ITEM_TM_ICY_WIND
	.2byte ITEM_TM_POUNCE
	.2byte ITEM_TM_STEEL_WING
	.2byte ITEM_TM_TAUNT
	.2byte ITEM_TM_THIEF
	.2byte ITEM_TM_HAIL
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_RAIN_DANCE
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_REST
	.2byte ITEM_TM_SANDSTORM
	.2byte ITEM_TM_SUNNY_DAY
    .2byte ITEM_TM_TRICK_ROOM
	.2byte ITEM_TM_PROTECT
	pokemartlistend

SlateportCity_Pokemart_PowerTMs_Badge5TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge5TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge5TMsItems:
	.2byte ITEM_TM_THIEF
	pokemartlistend

SlateportCity_Pokemart_PowerTMs_Badge6TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge6TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge6TMsItems:
	.2byte ITEM_TM_BULLET_SEED
	.2byte ITEM_TM_MUD_SHOT
	.2byte ITEM_TM_ICY_WIND
	.2byte ITEM_TM_POUNCE
	.2byte ITEM_TM_STEEL_WING
	.2byte ITEM_TM_TAUNT
	.2byte ITEM_TM_THIEF
	.2byte ITEM_TM_HAIL
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_RAIN_DANCE
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_REST
	.2byte ITEM_TM_PROTECT
	.2byte ITEM_TM_SANDSTORM
	.2byte ITEM_TM_SUNNY_DAY
    .2byte ITEM_TM_TRICK_ROOM
	.2byte ITEM_TM_SOLAR_BEAM
	.2byte ITEM_TM_BLIZZARD
	.2byte ITEM_TM_FIRE_BLAST
	.2byte ITEM_TM_THUNDER
	.2byte ITEM_TM_HONE_CLAWS
	pokemartlistend

SlateportCity_Pokemart_PowerTMs_Badge7TMs::
	pokemart SlateportCity_Pokemart_PowerTMs_Badge7TMsItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	setvar VAR_POWER_TM_CLERK, 0
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs_Badge7TMsItems:
	.2byte ITEM_TM_HONE_CLAWS
	pokemartlistend

SlateportCity_EventScript_MegaSalesman::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	compare VAR_BADGE_COUNT, 6
	goto_if_lt SlateportCity_EventScript_SellStageOneStones
	compare VAR_BADGE_COUNT, 6
	goto_if_eq SlateportCity_EventScript_SellStageTwoStonesPlusRentals
	compare VAR_BADGE_COUNT, 8
	goto_if_lt SlateportCity_EventScript_SellStageTwoStones
	pokemart SlateportCity_Pokemart_StageThreeMegas
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_SellStageOneStones::
	pokemart SlateportCity_Pokemart_StageOneMegas
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_SellStageTwoStonesPlusRentals::
	pokemart SlateportCity_Pokemart_StageTwoMegasPlusRentals
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_SellStageTwoStones::
	pokemart SlateportCity_Pokemart_StageTwoMegas
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_StageOneMegas:
	.2byte ITEM_MAWILITE
	.2byte ITEM_SABLENITE
	pokemartlistend

	.align 2
SlateportCity_Pokemart_StageTwoMegas:
	.2byte ITEM_ABOMASITE
	.2byte ITEM_BANETTITE
	.2byte ITEM_BARBARACITE
	.2byte ITEM_CAMERUPTITE
	.2byte ITEM_CHIMECHITE
	.2byte ITEM_DRAGALGITE
	.2byte ITEM_EXCADRITE
	.2byte ITEM_FROSLASSITE
	.2byte ITEM_GLALITITE
	.2byte ITEM_HOUNDOOMINITE
	.2byte ITEM_LOPUNNITE
	.2byte ITEM_LUCARIONITE
	.2byte ITEM_MALAMARITE
	.2byte ITEM_MANECTITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_MEDICHAMITE
	.2byte ITEM_MEOWSTICITE
	.2byte ITEM_PYROARITE
	.2byte ITEM_SABLENITE
	.2byte ITEM_SCIZORITE
	.2byte ITEM_SCRAFTINITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_STEELIXITE
	pokemartlistend

	.align 2
SlateportCity_Pokemart_StageTwoMegasPlusRentals:
	.2byte ITEM_ABOMASITE
	.2byte ITEM_ABSOLITE
	.2byte ITEM_BANETTITE
	.2byte ITEM_BARBARACITE
	.2byte ITEM_CAMERUPTITE
	.2byte ITEM_CHIMECHITE
	.2byte ITEM_DRAGALGITE
	.2byte ITEM_DRAMPANITE
	.2byte ITEM_EXCADRITE
	.2byte ITEM_FALINKSITE
	.2byte ITEM_FROSLASSITE
	.2byte ITEM_GLALITITE
	.2byte ITEM_HAWLUCHANITE
	.2byte ITEM_HERACRONITE
	.2byte ITEM_HOUNDOOMINITE
	.2byte ITEM_KANGASKHANITE
	.2byte ITEM_LOPUNNITE
	.2byte ITEM_LUCARIONITE
	.2byte ITEM_MALAMARITE
	.2byte ITEM_MANECTITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_MEDICHAMITE
	.2byte ITEM_MEOWSTICITE
	.2byte ITEM_PINSIRITE
	.2byte ITEM_PYROARITE
	.2byte ITEM_SABLENITE
	.2byte ITEM_SCIZORITE
	.2byte ITEM_SCRAFTINITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_SKARMORITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_STEELIXITE
	pokemartlistend

	.align 2
SlateportCity_Pokemart_StageThreeMegas:
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
	.2byte ITEM_SCRAFTINITE
	.2byte ITEM_SCOLIPITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_STARAPTITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_STEELIXITE
	.2byte ITEM_SWAMPERTITE
	.2byte ITEM_TYRANITARITE
	.2byte ITEM_VENUSAURITE
	pokemartlistend

SlateportCity_EventScript_ShadyRentalMan::
	lock
	faceplayer
	goto_if_eq VAR_SLATEPORT_RENTAL_STATE, 2, SlateportCity_EventScript_ShadyManDebt
	goto_if_eq VAR_SLATEPORT_RENTAL_STATE, 1, SlateportCity_EventScript_ShadyManActive
	goto_if_ge VAR_BADGE_COUNT, 7, SlateportCity_EventScript_ShadyManRefuse
	
	callnative BufferRentalCost
	msgbox SlateportCity_Text_ShadyManIntro, MSGBOX_DEFAULT
	
	@ Generate offer if not already set
	goto_if_ne VAR_RENTAL_MON_OFFER, 0, SlateportCity_EventScript_ShadyManShowOffer
	callnative GenerateRentalOffer
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_SetOfferSkarmory
	case 1, SlateportCity_EventScript_SetOfferFalinks
	case 2, SlateportCity_EventScript_SetOfferHawlucha
	case 3, SlateportCity_EventScript_SetOfferDrampa
	case 4, SlateportCity_EventScript_SetOfferHeracross
	case 5, SlateportCity_EventScript_SetOfferPinsir
	case 6, SlateportCity_EventScript_SetOfferKangaskhan
	case 7, SlateportCity_EventScript_SetOfferAbsol
	case 8, SlateportCity_EventScript_SetOfferZangoose
	case 9, SlateportCity_EventScript_SetOfferSeviper
	case 10, SlateportCity_EventScript_SetOfferTorkoal
	case 11, SlateportCity_EventScript_SetOfferTropius
	case 12, SlateportCity_EventScript_SetOfferTurtonator
	case 13, SlateportCity_EventScript_SetOfferLapras
	case 14, SlateportCity_EventScript_SetOfferMiltank
	case 15, SlateportCity_EventScript_SetOfferMimikyu
	case 16, SlateportCity_EventScript_SetOfferTogedemaru
	case 17, SlateportCity_EventScript_SetOfferBombirdier
	case 18, SlateportCity_EventScript_SetOfferDhelmise
	case 19, SlateportCity_EventScript_SetOfferRelicanth
	case 20, SlateportCity_EventScript_SetOfferBouffalant
	case 21, SlateportCity_EventScript_SetOfferCarnivine
	case 22, SlateportCity_EventScript_SetOfferHeatmor
	case 23, SlateportCity_EventScript_SetOfferDurant
	case 24, SlateportCity_EventScript_SetOfferComfey
	case 25, SlateportCity_EventScript_SetOfferCryogonal
	case 26, SlateportCity_EventScript_SetOfferStonjourner
	case 27, SlateportCity_EventScript_SetOfferAlomomola
	end

SlateportCity_EventScript_SetOfferSkarmory::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_SKARMORY
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferFalinks::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_FALINKS
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferHawlucha::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_HAWLUCHA
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferDrampa::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_DRAMPA
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferHeracross::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_HERACROSS
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferPinsir::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_PINSIR
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferKangaskhan::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_KANGASKHAN
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferAbsol::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_ABSOL
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferZangoose::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_ZANGOOSE
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferSeviper::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_SEVIPER
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferTorkoal::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_TORKOAL
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferRelicanth::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_RELICANTH
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferTropius::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_TROPIUS
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferTurtonator::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_TURTONATOR
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferLapras::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_LAPRAS
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferMiltank::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_MILTANK
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferMimikyu::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_MIMIKYU
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferTogedemaru::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_TOGEDEMARU
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferBombirdier::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_BOMBIRDIER
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferDhelmise::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_DHELMISE
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferBouffalant::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_BOUFFALANT
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferCarnivine::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_CARNIVINE
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferHeatmor::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_HEATMOR
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferDurant::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_DURANT
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferComfey::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_COMFEY
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferCryogonal::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_CRYOGONAL
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferStonjourner::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_STONJOURNER
	goto SlateportCity_EventScript_ShadyManShowOffer
SlateportCity_EventScript_SetOfferAlomomola::
	setvar VAR_RENTAL_MON_OFFER, SPECIES_ALOMOMOLA
	goto SlateportCity_EventScript_ShadyManShowOffer

SlateportCity_EventScript_ShadyManShowOffer::
	bufferspeciesname STR_VAR_1, VAR_RENTAL_MON_OFFER
	msgbox SlateportCity_Text_ShadyManCheckOut, MSGBOX_DEFAULT
	callnative ShowRentalMon
	waitstate
	callnative BufferRentalCost
	msgbox SlateportCity_Text_ShadyManOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ShadyManDecline
	
	callnative CheckHasRentalCost
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ShadyManNoMoney
	
	callnative TakeRentalCost
	updatemoneybox
	
SlateportCity_EventScript_GiveRentalMon::
	callnative GiveRentalMon
	goto_if_eq VAR_RESULT, 0, SlateportCity_EventScript_RentalGiven
	goto_if_eq VAR_RESULT, 1, SlateportCity_EventScript_RentalSentToPC
	goto_if_eq VAR_RESULT, 2, SlateportCity_EventScript_ShadyManPartyFull
	
SlateportCity_EventScript_RentalGiven::
	setvar VAR_SLATEPORT_RENTAL_STATE, 1
	copyvar VAR_RENTAL_MON_SPECIES, VAR_RENTAL_MON_OFFER
	copyvar VAR_RENTAL_BADGE_COUNT, VAR_BADGE_COUNT
	setvar VAR_RENTAL_MON_OFFER, 0
	msgbox SlateportCity_Text_ShadyManWarning, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RentalSentToPC::
	setvar VAR_SLATEPORT_RENTAL_STATE, 1
	copyvar VAR_RENTAL_MON_SPECIES, VAR_RENTAL_MON_OFFER
	copyvar VAR_RENTAL_BADGE_COUNT, VAR_BADGE_COUNT
	setvar VAR_RENTAL_MON_OFFER, 0
	msgbox SlateportCity_Text_ShadyManWarning, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_SetHeracronite::
	setvar VAR_0x8006, ITEM_HERACRONITE
	return
SlateportCity_EventScript_SetPinsirite::
	setvar VAR_0x8006, ITEM_PINSIRITE
	return
SlateportCity_EventScript_SetKangaskhanite::
	setvar VAR_0x8006, ITEM_KANGASKHANITE
	return
SlateportCity_EventScript_SetAbsolite::
	setvar VAR_0x8006, ITEM_ABSOLITE
	return
SlateportCity_EventScript_SetDrampite::
	setvar VAR_0x8006, ITEM_DRAMPANITE
	return
SlateportCity_EventScript_SetSkarmorite::
	setvar VAR_0x8006, ITEM_SKARMORITE
	return
SlateportCity_EventScript_SetFalinksite::
	setvar VAR_0x8006, ITEM_FALINKSITE
	return
SlateportCity_EventScript_SetHawluchite::
	setvar VAR_0x8006, ITEM_HAWLUCHANITE
	return

SlateportCity_EventScript_ShadyManDecline::
	msgbox SlateportCity_Text_ShadyManDecline, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ShadyManNoMoney::
	msgbox SlateportCity_Text_ShadyManNoMoney, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ShadyManPartyFull::
	release
	end

SlateportCity_EventScript_ShadyManActive::
	copyvar VAR_0x8005, VAR_BADGE_COUNT
	subvar VAR_0x8005, VAR_RENTAL_BADGE_COUNT
	goto_if_gt VAR_0x8005, 1, SlateportCity_EventScript_ShadyManFraudManual
	goto_if_gt VAR_0x8005, 0, SlateportCity_EventScript_ShadyManReturnMon
	msgbox SlateportCity_Text_ShadyManActive, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ShadyManReturnMon::
	copyvar VAR_0x8004, VAR_RENTAL_MON_SPECIES
	callnative RemoveRentalMon
	updatefollowingmon
	goto_if_eq VAR_RESULT, 1, SlateportCity_EventScript_ShadyManReturnFainted
	goto_if_eq VAR_RESULT, 2, SlateportCity_EventScript_ShadyManLostMon
	goto_if_eq VAR_RESULT, 3, SlateportCity_EventScript_ShadyManFoundInDayCare
	msgbox SlateportCity_Text_RentalReturnedAlive, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, VAR_RENTAL_MON_SPECIES
	msgbox SlateportCity_Text_PlayerReturnedMon, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	addvar VAR_RENTAL_RETURN_COUNT, 1
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ShadyManGiveDucklett
	release
	end

SlateportCity_EventScript_ShadyManFraudManual::
	copyvar VAR_0x8004, VAR_RENTAL_MON_SPECIES
	callnative RemoveRentalMon
	updatefollowingmon
	msgbox SlateportCity_Text_RentalFraud, MSGBOX_DEFAULT
	callnative TakeAllMoney
	goto_if_eq VAR_RESULT, 0, SlateportCity_EventScript_ShadyManFraudManual_SkipMoney
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
SlateportCity_EventScript_ShadyManFraudManual_SkipMoney::
	setvar VAR_SLATEPORT_RENTAL_STATE, 2
	setvar VAR_RENTAL_MON_SPECIES, 0
	release
	end

SlateportCity_EventScript_ShadyManReturnFainted::
	msgbox SlateportCity_Text_RentalFaintedGreeting, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, VAR_RENTAL_MON_SPECIES
	msgbox SlateportCity_Text_PlayerReturnedMon, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_RentalFaintedReaction, MSGBOX_DEFAULT
	callnative CheckHasRentalCost
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_ShadyManPayFine
	callnative TakeAllMoney
	goto_if_eq VAR_RESULT, 0, SlateportCity_EventScript_ShadyManReturnFaintedEnd
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ShadyManReturnFaintedEnd

SlateportCity_EventScript_ShadyManPayFine::
	callnative TakeRentalCost
	updatemoneybox
	callnative BufferRentalCost
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ShadyManReturnFaintedEnd

SlateportCity_EventScript_ShadyManReturnFaintedEnd::
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	addvar VAR_RENTAL_RETURN_COUNT, 1
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ShadyManGiveDucklett
	release
	end

SlateportCity_EventScript_ShadyManFoundInDayCare::
	msgbox SlateportCity_Text_ShadyManDayCare, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	release
	end

SlateportCity_EventScript_ShadyManLostMon::
	msgbox SlateportCity_Text_ShadyManLostMon, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ShadyManRefuse::
	msgbox SlateportCity_Text_ShadyManRefuse, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ShadyManDebt::
	msgbox SlateportCity_Text_ShadyManDebt, MSGBOX_DEFAULT
	callnative TakeAllMoney
	release
	end

SlateportCity_EventScript_LightsOut::
	setvar VAR_TEMP_1, 1
	callnative DoLightsOutFast
	waitstate
	setflashlevel 6
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_RevealShadyMan
	waitmovement 0
	setobjectmovementtype LOCALID_SHADY_MAN, MOVEMENT_TYPE_FACE_DOWN
	return
	end

SlateportCity_EventScript_LightsOn::
	removeobject LOCALID_SHADY_MAN
	setobjectxy LOCALID_SHADY_MAN, 2, 33
	setobjectmovementtype LOCALID_SHADY_MAN, MOVEMENT_TYPE_TREE_DISGUISE
	addobject LOCALID_SHADY_MAN
	setvar VAR_TEMP_1, 0
	callnative DoLightsOnFast
	waitstate
	setflashlevel 0
	return
	end

SlateportCity_Movement_RevealShadyMan:
	reveal_trainer
	face_down
	step_end

SlateportCity_EventScript_RentalIntercept::
	lockall
	copyvar VAR_0x8005, VAR_BADGE_COUNT
	subvar VAR_0x8005, VAR_RENTAL_BADGE_COUNT
	goto_if_eq VAR_0x8005, 0, SlateportCity_EventScript_RentalIntercept_End

	call SlateportCity_EventScript_LightsOut
	setvar VAR_TEMP_1, 0 @ 0 for normal intercept

	addobject LOCALID_SHADY_MAN
	showobjectat LOCALID_SHADY_MAN, MAP_SLATEPORT_CITY
	applymovement LOCALID_SHADY_MAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SHADY_MAN, Common_Movement_Delay48
	waitmovement 0
	
	@ Move Shady Man to player
	getplayerxy VAR_0x8004, VAR_0x8005
	getobjectxy LOCALID_SHADY_MAN, 0, VAR_0x8006, VAR_0x8007
	getdirectiontoface VAR_0x8008, LOCALID_SHADY_MAN, OBJ_EVENT_ID_PLAYER
	
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalIntercept_TeleportPos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalIntercept_TeleportPos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalIntercept_TeleportPos3
	@ Fallback if coordinates don't match (shouldn't happen)
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManRunToPlayer 
SlateportCity_EventScript_RentalIntercept_Continue::
	waitmovement 0
	
	copyvar VAR_0x8004, VAR_RENTAL_MON_SPECIES
	callnative RemoveRentalMon
	updatefollowingmon
	@ VAR_RESULT: 0=Alive, 1=Fainted, 2=Not Found, 3=DayCare
	
	@ Check for Badge Fraud
	copyvar VAR_0x8005, VAR_BADGE_COUNT
	subvar VAR_0x8005, VAR_RENTAL_BADGE_COUNT
	goto_if_gt VAR_0x8005, 1, SlateportCity_EventScript_RentalFraud
	
	goto_if_eq VAR_RESULT, 1, SlateportCity_EventScript_RentalFainted
	goto_if_eq VAR_RESULT, 3, SlateportCity_EventScript_RentalDayCare
	
	msgbox SlateportCity_Text_RentalReturnedAlive, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, VAR_RENTAL_MON_SPECIES
	msgbox SlateportCity_Text_PlayerReturnedMon, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_RentalIntercept_GiveLedyba
	
	@ Return Shady Man (Teleport back for simplicity or walk back)
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalReturn_Pos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalReturn_Pos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalReturn_Pos3
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManReturn
SlateportCity_EventScript_RentalReturn_Continue::
	waitmovement 0
	releaseall
	end

SlateportCity_EventScript_RentalIntercept_GiveLedyba::
	msgbox SlateportCity_Text_GetLost, MSGBOX_DEFAULT
	givemon SPECIES_LEDYBA, 5
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManSpin
	waitmovement 0
	removeobject LOCALID_SHADY_MAN
	call SlateportCity_EventScript_LightsOn
	releaseall
	end

SlateportCity_EventScript_RentalIntercept_End::
	releaseall
	end

SlateportCity_EventScript_RentalIntercept_TeleportPos1::
	copyvar VAR_0x8006, VAR_0x8004
	subvar VAR_0x8006, 1 @ X - 1
	copyvar VAR_0x8007, VAR_0x8005
	goto SlateportCity_EventScript_RentalIntercept_Teleport

SlateportCity_EventScript_RentalIntercept_TeleportPos2::
	copyvar VAR_0x8006, VAR_0x8004
	subvar VAR_0x8006, 1
	copyvar VAR_0x8007, VAR_0x8005
	goto SlateportCity_EventScript_RentalIntercept_Teleport

SlateportCity_EventScript_RentalIntercept_TeleportPos3::
	copyvar VAR_0x8006, VAR_0x8004
	subvar VAR_0x8006, 1
	copyvar VAR_0x8007, VAR_0x8005
	goto SlateportCity_EventScript_RentalIntercept_Teleport

SlateportCity_EventScript_RentalIntercept_Teleport::
	setobjectxy LOCALID_SHADY_MAN, VAR_0x8006, VAR_0x8007
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManSpin
	waitmovement 0
	applymovement LOCALID_SHADY_MAN, Common_Movement_FacePlayer
	showobjectat LOCALID_SHADY_MAN, MAP_SLATEPORT_CITY
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_WEST
	goto_if_eq VAR_TEMP_1, 0, SlateportCity_EventScript_RentalIntercept_Continue
	goto SlateportCity_EventScript_RentalDebtIntercept_Continue

SlateportCity_EventScript_RentalReturn_Pos1::
	goto SlateportCity_EventScript_RentalReturn_Spin

SlateportCity_EventScript_RentalReturn_Pos2::
	goto SlateportCity_EventScript_RentalReturn_Spin

SlateportCity_EventScript_RentalReturn_Pos3::
	goto SlateportCity_EventScript_RentalReturn_Spin

SlateportCity_EventScript_RentalReturn_Spin::
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManSpin
	waitmovement 0
	removeobject LOCALID_SHADY_MAN
	call SlateportCity_EventScript_LightsOn
	goto SlateportCity_EventScript_RentalReturn_Continue

SlateportCity_EventScript_RentalFainted::
	msgbox SlateportCity_Text_RentalFaintedGreeting, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, VAR_RENTAL_MON_SPECIES
	msgbox SlateportCity_Text_PlayerReturnedMon, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_RentalFaintedReaction, MSGBOX_DEFAULT
	callnative CheckHasRentalCost
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_PayFine
	callnative TakeAllMoney
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_RentalFaintedEnd
SlateportCity_EventScript_PayFine::
	callnative TakeRentalCost
	updatemoneybox
	callnative BufferRentalCost
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
SlateportCity_EventScript_RentalFaintedEnd::
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	addvar VAR_RENTAL_RETURN_COUNT, 1
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, EventScript_WhiteOut
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalReturn_Pos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalReturn_Pos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalReturn_Pos3
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManReturn
	waitmovement 0
	releaseall
	end

SlateportCity_EventScript_RentalFraud::
	msgbox SlateportCity_Text_RentalFraud, MSGBOX_DEFAULT
	callnative TakeAllMoney
	goto_if_eq VAR_RESULT, 0, SlateportCity_EventScript_RentalFraud_SkipMoney
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
SlateportCity_EventScript_RentalFraud_SkipMoney::
	setvar VAR_SLATEPORT_RENTAL_STATE, 2
	setvar VAR_RENTAL_MON_SPECIES, 0
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ShadyManGiveDucklett
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalReturn_Pos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalReturn_Pos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalReturn_Pos3
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManReturn
	waitmovement 0
	releaseall
	end

SlateportCity_EventScript_RentalDayCare::
	msgbox SlateportCity_Text_ShadyManDayCare, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_RENTAL_STATE, 0
	setvar VAR_RENTAL_MON_SPECIES, 0
	special HasEnoughMonsForBattle
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ShadyManGiveDucklett
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalReturn_Pos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalReturn_Pos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalReturn_Pos3
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManReturn
	waitmovement 0
	releaseall
	end

SlateportCity_EventScript_RentalDebtIntercept::
	lockall
	checkmoney 1
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_RentalIntercept_End

	call SlateportCity_EventScript_LightsOut

	setvar VAR_TEMP_1, 1 @ 1 for debt intercept
	addobject LOCALID_SHADY_MAN
	showobjectat LOCALID_SHADY_MAN, MAP_SLATEPORT_CITY
	applymovement LOCALID_SHADY_MAN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SHADY_MAN, Common_Movement_Delay48
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, SlateportCity_EventScript_RentalIntercept_TeleportPos1
	goto_if_eq VAR_0x8005, 52, SlateportCity_EventScript_RentalIntercept_TeleportPos2
	goto_if_eq VAR_0x8005, 53, SlateportCity_EventScript_RentalIntercept_TeleportPos3
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManRunToPlayer
	goto SlateportCity_EventScript_RentalDebtIntercept_Continue

SlateportCity_EventScript_RentalDebtIntercept_Continue::
	waitmovement 0
	msgbox SlateportCity_Text_ShadyManDebtIntercept, MSGBOX_DEFAULT
	callnative TakeAllMoney
	goto_if_eq VAR_RESULT, 0, SlateportCity_EventScript_RentalDebtIntercept_SkipMoney
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox SlateportCity_Text_PlayerHandedOverMoney, MSGBOX_DEFAULT
SlateportCity_EventScript_RentalDebtIntercept_SkipMoney::
	applymovement LOCALID_SHADY_MAN, SlateportCity_Movement_ShadyManSpin
	waitmovement 0
	removeobject LOCALID_SHADY_MAN
	call SlateportCity_EventScript_LightsOn
	releaseall
	end

@ Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine
SlateportCity_EventScript_CaptStern::
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GABBY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 10
	applymovement LOCALID_SLATEPORT_TY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_SLATEPORT_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_SLATEPORT_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_GABBY
	removeobject LOCALID_SLATEPORT_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_COOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_FAT_MAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_SLATEPORT_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_SLATEPORT_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_SLATEPORT_CAPT_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setvar VAR_SLATEPORT_CITY_STATE, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern:
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ManConcern:
	emote_question_mark
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_GabbyExit:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_TyExit:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_Unused:
	walk_down
	walk_in_place_faster_up
	step_end

SlateportCity_Movement_SternEnterHarbor:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor:
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_EventScript_Ty::
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby::
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3::
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	//goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	//msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	//giveitem ITEM_POWDER_JAR
	//setflag FLAG_RECEIVED_POWDER_JAR
	//msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder::
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem::
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_QUICK_POWDER
	setvar VAR_0x8008, ITEM_QUICK_POWDER
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect::
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem::
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder::
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit:
	delay_16
	walk_in_place_faster_right
	step_end

SlateportCity_Movement_ScottExitBattleTent:
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign::
	lockall
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end

SlateportCity_Movement_ShadyManRunToPlayer:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

SlateportCity_Movement_ShadyManSpin:
	face_down
	delay_1
	face_left
	delay_1
	face_up
	delay_1
	face_right
	delay_1
	face_down
	step_end

SlateportCity_Movement_ShadyManReturn:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_down
	step_end

SlateportCity_Text_CookIntro:
	.string "My cooking is so potent, it can change\n"
	.string "a POKéMON's very condition!$"

SlateportCity_Text_CookWhichStatus:
	.string "What effect would you like?$"

SlateportCity_Text_CookWhichPokemon:
	.string "And for which POKéMON?$"

SlateportCity_Text_CookDone:
	.string "Voila! All done!$"

SlateportCity_Text_CookComeAgain:
	.string "Oh? Changed your mind?\n"
	.string "Come again!$"

SlateportCity_Text_EnergyGuru_Explain:
	.string "I'm the ENERGY GURU! I can help POKéMON\n"
	.string "that evolve at high levels reach their\l"
	.string "potential early!$"

SlateportCity_Text_EnergyGuru_HaveMon:
	.string "Oh! Would you like me to help your\n"
	.string "POKéMON evolve?$"

SlateportCity_Text_EnergyGuru_ChooseMon:
	.string "Which POKéMON needs my help?$"

SlateportCity_Text_EnergyGuru_InvalidMon:
	.string "Hrm… No, that POKéMON doesn't meet\n"
	.string "my criteria.$"

SlateportCity_Text_EnergyGuru_Hooplah:
	.string "Come back if you have a base form\n"
	.string "POKéMON that evolves to a middle\l"
	.string "stage after level 30!$"

SlateportCity_Text_EffortRibbonWoman_Explain:
	.string "I'm the ENERGY ORACLE! I can help POKéMON\n"
	.string "that evolve late reach their final form\l"
	.string "early if they haven't evolved before!$"

SlateportCity_Text_EffortRibbonWoman_HaveMon:
	.string "Oh! Would you like me to help your\n"
	.string "POKéMON evolve?$"

SlateportCity_Text_EffortRibbonWoman_ChooseMon:
	.string "Which POKéMON needs my help?$"

SlateportCity_Text_EffortRibbonWoman_InvalidMon:
	.string "Hrm… No, that POKéMON doesn't meet\n"
	.string "my criteria.$"

SlateportCity_Text_EffortRibbonWoman_Decline:
	.string "Come back if you have a base form\n"
	.string "POKéMON that evolves to a final\l"
	.string "stage after level 36!$"

SlateportCity_Text_OhYourPokemon:
	.string "Oh?\n"
	.string "Your {STR_VAR_1}…$"

SlateportCity_Text_PleaseGiveItThisEffortRibbon:
	.string "Went for it stupendously!\p"
	.string "As its reward, please give it this\n"
	.string "EFFORT RIBBON.$"

SlateportCity_Text_ReceivedEffortRibbon:
	.string "{PLAYER} received the EFFORT RIBBON.$"

SlateportCity_Text_PutEffortRibbonOnMon:
	.string "{PLAYER} put the EFFORT RIBBON\n"
	.string "on {STR_VAR_1}.$"

SlateportCity_Text_GoForItLittleHarder:
	.string "You have to go for it a little harder.\p"
	.string "If you do, I'll give your POKéMON\n"
	.string "something nice.$"

SlateportCity_Text_EffortRibbonLooksGoodOnIt:
	.string "Oh! Your {STR_VAR_1}, that EFFORT\n"
	.string "RIBBON looks good on it!$"

SlateportCity_Text_WonderIfLighthouseStartlesPokemon:
	.string "The light of the lighthouse reaches\n"
	.string "dozens of miles away.\p"
	.string "I wonder if it doesn't startle POKéMON\n"
	.string "in the sea.$"

SlateportCity_Text_SeaweedFullOfLife:
	.string "Ooh, look at this!\p"
	.string "The seaweed you can get around these\n"
	.string "parts is fresh and full of life.\p"
	.string "Why, it looks like it can even rear up\n"
	.string "and attack!$"

SlateportCity_Text_HowTownIsBornAndGrows:
	.string "Where the water is clean, the fruits\n"
	.string "of bountiful harvest gather.\p"
	.string "And where people gather, a market\n"
	.string "soon starts.\p"
	.string "That is how a town is born and grows.$"

SlateportCity_Text_SlateportWonderfulPlace:
	.string "Shopping where you can breathe the\n"
	.string "scent of the ocean…\p"
	.string "SLATEPORT is such a wonderful place!$"

SlateportCity_Text_BuyBricksSoDecorWontGetDirty:
	.string "If you put DOLLS or CUSHIONS on\n"
	.string "the floor, they'll get dirty.\p"
	.string "I'm going to buy some BRICKS so my\n"
	.string "DOLLS and CUSHIONS won't get dirty\l"
	.string "when I leave them out.$"

SlateportCity_Text_GoingToCompeteInBattleTent:
	.string "Wroooar! I'm going to compete in\n"
	.string "the BATTLE TENT, too!\p"
	.string "But before that, I need to catch\n"
	.string "some POKéMON!$"

SlateportCity_Text_BushedHikingFromMauville:
	.string "Whew… I'm just bushed…\p"
	.string "I hiked over from MAUVILLE CITY.\n"
	.string "But, boy, this city's huge.\p"
	.string "If I'd known this, I would've ridden\n"
	.string "my BIKE here.$"

SlateportCity_Text_EveryoneCallsHimCaptStern:
	.string "STERN, the fellow who built the\n"
	.string "MUSEUM, also happens to be the leader\l"
	.string "of an undersea exploration team.\p"
	.string "So, everyone calls him CAPT. STERN.$"

SlateportCity_Text_WhatsLongLineOverThere:
	.string "What is that over there?\n"
	.string "That long line…$"

SlateportCity_Text_VisitedMuseumOften:
	.string "When I was a child, I visited\n"
	.string "the MUSEUM often.\p"
	.string "I used to dream about the mysteries of\n"
	.string "the sea after seeing the exhibits.$"

SlateportCity_Text_QuitPushing:
	.string "Hey, there! Quit pushing!\n"
	.string "This is the line, can't you see?$"

SlateportCity_Text_AquaHasPolicy:
	.string "TEAM AQUA has a policy of\n"
	.string "assembling and dispersing at\l"
	.string "the operation site.$"

SlateportCity_Text_BossIsBrilliant:
	.string "Our BOSS is brilliant.\p"
	.string "What would he want to do with\n"
	.string "a MUSEUM now?$"

SlateportCity_Text_WhatsNewSchemeIWonder:
	.string "What's the new scheme, I wonder?\p"
	.string "Our BOSS is scary when he's mad, so\n"
	.string "I'd better not screw things up…$"

SlateportCity_Text_ShouldTakeItAll:
	.string "If there's something we need in\n"
	.string "the MUSEUM, we should take it all!$"

SlateportCity_Text_DontButtIn:
	.string "Hey, you there!\n"
	.string "Don't butt in!$"

SlateportCity_Text_RemindsMeOfLongLineForGames:
	.string "A long line, huh?\p"
	.string "It reminds me of the times I lined up to\n"
	.string "buy smash-hit games…$"

SlateportCity_Text_WhyAreWeLiningUp:
	.string "Why are we even lining up and paying?\n"
	.string "We should just march in!$"

SlateportCity_Text_WhatDoYouWant:
	.string "What?\n"
	.string "What do you want?$"

SlateportCity_Text_IllReadSignForYou:
	.string "You want to read this sign?\n"
	.string "I'll read it for you!$"

SlateportCity_Text_SaysSomethingLikeSeaIsEndless:
	.string "Let's see…\p"
	.string "Um… I think it says something like\n"
	.string "“the life in the sea is endless.”\p"
	.string "Yup, I'm pretty sure that's what\n"
	.string "it says.$"

SlateportCity_Text_ShouldveBroughtMyGameBoy:
	.string "Grumble…\p"
	.string "I should've brought my Game Boy\n"
	.string "Advance so I wouldn't get bored in line…\p"
	.string "Grumble…$"

SlateportCity_Text_HotSpringsAfterOperation:
	.string "When this operation's over, I'll take\n"
	.string "you to a hot spring spa!\p"
	.string "That's what our leader said.\n"
	.string "I can't wait!$"

SlateportCity_Text_SeaIsSoWet:
	.string "The sea is just so vast…\p"
	.string "Could the sea have been made by\n"
	.string "the tears shed by POKéMON?$"

SlateportCity_Text_SinkOldBoats:
	.string "Do you know what they do with old\n"
	.string "ships that become too creaky to sail?\p"
	.string "They sink them in the sea so they\n"
	.string "become habitats for POKéMON.$"

SlateportCity_Text_BuyTooMuch:
	.string "Whenever I visit here, I get carried\n"
	.string "away and buy too much.$"

SlateportCity_Text_FavoriteEeveelutions:
	.string "Ah, who are my favorite Eeveelutions\n"
	.string "today?\p"
	.string "I think I prefer {STR_VAR_1}, {STR_VAR_2},\n"
	.string "and {STR_VAR_3}.$"

SlateportCity_Text_Vaporeon:
	.string "{COLOR BLUE}Vaporeon{COLOR DARK_GRAY}$"
SlateportCity_Text_Jolteon:
	.string "{COLOR LIGHT_RED}Jolteon{COLOR DARK_GRAY}$"
SlateportCity_Text_Flareon:
	.string "{COLOR RED}Flareon{COLOR DARK_GRAY}$"
SlateportCity_Text_Espeon:
	.string "{COLOR RED}Espeon{COLOR DARK_GRAY}$"
SlateportCity_Text_Umbreon:
	.string "{COLOR DARK_GRAY}Umbreon{COLOR DARK_GRAY}$"
SlateportCity_Text_Leafeon:
	.string "{COLOR GREEN}Leafeon{COLOR DARK_GRAY}$"
SlateportCity_Text_Glaceon:
	.string "{COLOR DYNAMIC_COLOR6}Glaceon{COLOR DARK_GRAY}$"
SlateportCity_Text_Sylveon:
	.string "{COLOR RED}Sylveon{COLOR DARK_GRAY}$"

SlateportCity_Text_GetNameRaterToHelpYou:
	.string "If you want to change your POKéMON's\n"
	.string "nickname, you'll have to get the NAME\l"
	.string "RATER to help you.$"

SlateportCity_Text_CantChangeTradeMonName:
	.string "Any POKéMON you get in a trade,\n"
	.string "you can't change its nickname.\p"
	.string "The original TRAINER's love for that\n"
	.string "POKéMON is in the nickname.$"

SlateportCity_Text_BattleTentBuiltRecently:
	.string "Recently, a BATTLE TENT was built\n"
	.string "in SLATEPORT.\p"
	.string "GYMS are fun, but the BATTLE TENT's\n"
	.string "awesome in its own way.\p"
	.string "You should go find tough POKéMON\n"
	.string "for the BATTLE TENT!$"

SlateportCity_Text_CaptSternBeingInterviewed:
	.string "I was hoping that it was a famous star\n"
	.string "so I could get an autograph.\p"
	.string "But who's that being interviewed?\n"
	.string "Isn't that CAPT. STERN?$"

SlateportCity_Text_InterviewerSoCool:
	.string "That lady interviewer is so cool\n"
	.string "and pretty.\p"
	.string "When I grow up, I'm going to be\n"
	.string "an international journalist!$"

SlateportCity_Text_SternSaysDiscoveredSomething:
	.string "CAPT. STERN says they discovered\n"
	.string "something at the bottom of the sea.\p"
	.string "I wonder what it is?\n"
	.string "What could it be?$"

SlateportCity_Text_CaptainComeBackWithBigFish:
	.string "What's going on here?\p"
	.string "Did the good CAPTAIN come back with\n"
	.string "a big fish from the ocean floor?$"

SlateportCity_Text_AmIOnTV:
	.string "Hey! Are you watching?\n"
	.string "Am I on TV?$"

SlateportCity_Text_CaptainsACelebrity:
	.string "A TV interview! Here!\n"
	.string "The CAPTAIN's a celebrity!$"

SlateportCity_Text_BigSmileForCamera:
	.string "TY: Okay, CAPT. STERN, a big smile\n"
	.string "for the camera!$"

SlateportCity_Text_MostInvaluableExperience:
	.string "GABBY: I see, I see. You've had a most\n"
	.string "invaluable experience…$"

SlateportCity_Text_SternMoveAheadWithExploration:
	.string "CAPT. STERN: Yes, indeed. We intend to\n"
	.string "move ahead with our exploration.$"

SlateportCity_Text_GabbyWonderfulThanksForInterview:
	.string "GABBY: That's wonderful, CAPT. STERN!\n"
	.string "Thank you for taking the time from\l"
	.string "your busy schedule to talk to us.\p"
	.string "We hope we can interview you again\n"
	.string "with news of more discoveries!$"

SlateportCity_Text_SternWhewFirstInterview:
	.string "CAPT. STERN: Whew…\p"
	.string "That was my first time to be filmed for\n"
	.string "TV. That was nerve-wracking.$"

SlateportCity_Text_OhPlayerWeMadeDiscovery:
	.string "Oh! {PLAYER}{KUN}!\n"
	.string "You're looking great!\p"
	.string "We made a huge discovery on our last\n"
	.string "seafloor exploration.\p"
	.string "We found an underwater cavern on\n"
	.string "ROUTE 128.\p"
	.string "We think it's the habitat of a POKéMON\n"
	.string "that's said to have been long extinct.$"

SlateportCity_Text_AquaWillAssumeControlOfSubmarine:
	.string "Fufufu…\n"
	.string "CAPT. STERN, I presume.\p"
	.string "We of TEAM AQUA will assume\n"
	.string "control of your submarine!\p"
	.string "Your objections are meaningless!\n"
	.string "We expect your total cooperation!\p"
	.string "Fufufu…\n"
	.string "Just watch and learn what TEAM\l"
	.string "AQUA has planned!$"

SlateportCity_Text_SternWhatWasAllThat:
	.string "CAPT. STERN: What was that all about?\p"
	.string "It sounded like someone using\n"
	.string "a megaphone…\p"
	.string "Where did it come from?$"

SlateportCity_Text_FromHarborTryingToTakeSub:
	.string "It's from the HARBOR!\p"
	.string "The submarine!\n"
	.string "They're trying to take it!$"

SlateportCity_Text_PleaseComeWithMe:
	.string "{PLAYER}{KUN}!\n"
	.string "Please, come with me!$"

SlateportCity_Text_BattleTentSign:
	.string "BATTLE TENT SLATEPORT SITE\n"
	.string "“Find it! The ultimate POKéMON!”$"

SlateportCity_Text_SternsShipyardWantedSign:
	.string "STERN'S SHIPYARD\p"
	.string "“Wanted: A sailor capable of sailing\n"
	.string "in all currents.”$"

SlateportCity_Text_SternsShipyardNearsCompletion:
	.string "STERN'S SHIPYARD\p"
	.string "“The ferry S.S. TIDAL nears\n"
	.string "completion for serving the ports of\l"
	.string "SLATEPORT and LILYCOVE.”$"

SlateportCity_Text_SternsShipyardFerryComplete:
	.string "STERN'S SHIPYARD\p"
	.string "“Boarding of the SLATEPORT-LILYCOVE\n"
	.string "ferry S.S. TIDAL is handled at the\l"
	.string "HARBOR.”$"

SlateportCity_Text_PokemonFanClubSign:
	.string "POKéMON FAN CLUB\n"
	.string "“Calling all fans of POKéMON!”$"

SlateportCity_Text_OceanicMuseumSign:
	.string "“The endless sea sustains\n"
	.string "all life.”\p"
	.string "OCEANIC MUSEUM$"

SlateportCity_Text_CitySign:
	.string "SLATEPORT CITY\p"
	.string "“The port where people and POKéMON\n"
	.string "cross paths.”$"

SlateportCity_Text_MarketSign:
	.string "SLATEPORT MARKET\n"
	.string "“Unique items found nowhere else!”$"

SlateportCity_Text_HarborFerryUnderConstruction:
	.string "SLATEPORT HARBOR\p"
	.string "“The ferry S.S. TIDAL is under\n"
	.string "construction in the SHIPYARD.\p"
	.string "“Service is scheduled to begin\n"
	.string "shortly.”$"

SlateportCity_Text_HarborSign:
	.string "SLATEPORT HARBOR\p"
	.string "“Enjoy a delightful cruise on\n"
	.string "the ferry S.S. TIDAL.”$"

SlateportCity_Text_NameRatersHouseSign:
	.string "NAME RATER'S HOUSE\n"
	.string "“POKéMON nicknames rated.”$"

SlateportCity_Text_ExplainBerries:
	.string "If a wild POKéMON gets hurt, it heals\n"
	.string "itself by chewing on BERRIES.\p"
	.string "Did you know that?\p"
	.string "Somebody saw that and got the idea\n"
	.string "of making medicine from BERRIES.\p"
	.string "Did you know that?\p"
	.string "To turn BERRIES into medicine,\n"
	.string "they must be crushed into powder.\p"
	.string "Did you know that?\p"
	.string "You seem to have an interest\n"
	.string "in BERRIES!\p"
	.string "I've got something good for someone\n"
	.string "like you.$"

SlateportCity_Text_ExplainBerryPowder:
	.string "I recently had machines installed at\n"
	.string "POKéMON CENTERS for crushing BERRIES.\p"
	.string "The BERRY CRUSH machines are at\n"
	.string "the DIRECT CORNER upstairs.\p"
	.string "Did you know?\p"
	.string "Could you make BERRY POWDER for\n"
	.string "me using those machines?\p"
	.string "I can make you all sorts of medicine\n"
	.string "if you bring me lots of BERRY POWDER.$"

SlateportCity_Text_BroughtMeSomeBerryPowder:
	.string "Have you brought me some\n"
	.string "BERRY POWDER?$"

SlateportCity_Text_ExchangeWhatWithIt:
	.string "What would you like to exchange\n"
	.string "it with?$"

SlateportCity_Text_ExchangeBerryPowderForItem:
	.string "Okay, you want to exchange your\n"
	.string "BERRY POWDER for one {STR_VAR_1}?$"

SlateportCity_Text_DontHaveEnoughBerryPowder:
	.string "Oh, dear. You don't have enough\n"
	.string "BERRY POWDER.$"

SlateportCity_Text_FineBerryPowderTradeSomethingElse:
	.string "This is fine BERRY POWDER.\n"
	.string "It will make excellent medicine.\p"
	.string "Would you like to trade more of your\n"
	.string "BERRY POWDER for something else?$"

SlateportCity_Text_WhenYouGetMoreBringItToMe:
	.string "Okay! When you get some more\n"
	.string "BERRY POWDER, bring it to me, please!$"

SlateportCity_Text_ComeBackToTradeBerryPowder:
	.string "Come back if you'd like to trade your\n"
	.string "BERRY POWDER for some medicine.\p"
	.string "I'm always running a bazaar here.\p"
	.string "Did you know?$"

SlateportCity_Text_YouDroveTeamAquaAway:
	.string "SCOTT: Huh?\n"
	.string "I'm sure I met you somewhere before.\p"
	.string "Have I introduced myself to you?\n"
	.string "If not, my name's SCOTT.\p"
	.string "I just saw TEAM AQUA run away from\n"
	.string "here like they were stung.\p"
	.string "Let me guess--you drove them away?$"

SlateportCity_Text_MaybeThisTrainer:
	.string "SCOTT: Hmm…\n"
	.string "Maybe, just maybe, this TRAINER…$"

SlateportCity_Text_LetsRegisterEachOther:
	.string "SCOTT: All right! I think you're going\n"
	.string "to become a good friend.\p"
	.string "So, let's register each other in our\n"
	.string "POKéNAVS.\p"
	.string "… … … … … …$"

SlateportCity_Text_RegisteredScott:
	.string "Registered this SCOTT person\n"
	.string "in the POKéNAV.$"

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou:
	.string "SCOTT: What I'd like to do is tag along\n"
	.string "with you, but I do want to keep an eye\l"
	.string "on the talents of other people, too.\p"
	.string "So, I'll be off to roam other towns\n"
	.string "a bit more.\p"
	.string "Be seeing you, {PLAYER}{KUN}!$"

SlateportCity_Text_TakingBattleTentChallenge:
	.string "SCOTT: Oh, hey!\n"
	.string "If it isn't {PLAYER}{KUN}!\p"
	.string "{PLAYER}{KUN}, let me guess--you're going\n"
	.string "to take the BATTLE TENT challenge?\p"
	.string "Yeah! That's a good idea!\n"
	.string "That's a really great idea!\p"
	.string "After all, a tough TRAINER is\n"
	.string "the perfect fit for the BATTLE TENT!\p"
	.string "Give it your best effort!$"

SlateportCity_Text_MegaSalesmanIntro:
	.string "Psst… Kid. Looking for a good deal?$"

SlateportCity_Text_NotSellingYet:
	.string "Hello! I sell TMs to players completing\n"
	.string "the gym challenge.\p"
	.string "Come back once you have two badges!$"

SlateportCity_EventScript_HiddenPowerNPC::
	lock
	faceplayer
	msgbox SlateportCity_Text_HiddenPowerNPC_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_HiddenPowerNPC_Decline
	checkmoney 1000
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_HiddenPowerNPC_NotEnoughMoney
	msgbox SlateportCity_Text_HiddenPowerNPC_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, 255, SlateportCity_EventScript_HiddenPowerNPC_Decline
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_HiddenPowerNPC_Egg
	callnative CheckHiddenPower
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_HiddenPowerNPC_NoHiddenPower

	msgbox SlateportCity_Text_HiddenPowerNPC_ChooseType, MSGBOX_DEFAULT
	copyvar VAR_0x8006, VAR_0x8004 @ Save slot
	setvar VAR_0x8004, SCROLL_MULTI_HIDDEN_POWER_TYPES
	special ShowScrollableMultichoice
	waitstate
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, SlateportCity_EventScript_HiddenPowerNPC_Decline

	copyvar VAR_0x8005, VAR_RESULT
	callnative MapHiddenPowerMenuSelectionToType

	removemoney 1000
	updatemoneybox
	playse SE_SHOP

	copyvar VAR_0x8004, VAR_0x8006 @ Restore slot
	callnative SetHiddenPowerType

	msgbox SlateportCity_Text_HiddenPowerNPC_Success, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_HiddenPowerNPC_Decline::
	msgbox SlateportCity_Text_HiddenPowerNPC_Decline, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_HiddenPowerNPC_NotEnoughMoney::
	msgbox SlateportCity_Text_HiddenPowerNPC_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_HiddenPowerNPC_Egg::
	msgbox SlateportCity_Text_HiddenPowerNPC_Egg, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_HiddenPowerNPC_NoHiddenPower::
	msgbox SlateportCity_Text_HiddenPowerNPC_NoHiddenPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_Text_HiddenPowerNPC_Intro:
	.string "I can change the type of your\n"
	.string "POKéMON's HIDDEN POWER for ¥1000.\p"
	.string "Would you like to do that?$"

SlateportCity_Text_HiddenPowerNPC_Decline:
	.string "Come back if you change your mind.$"

SlateportCity_Text_HiddenPowerNPC_NotEnoughMoney:
	.string "You don't have enough money.$"

SlateportCity_Text_HiddenPowerNPC_ChooseMon:
	.string "Which POKéMON's HIDDEN POWER type\n"
	.string "should I change?$"

SlateportCity_Text_HiddenPowerNPC_Egg:
	.string "I can't change an EGG's HIDDEN POWER.$"

SlateportCity_Text_HiddenPowerNPC_NoHiddenPower:
	.string "That POKéMON doesn't know\n"
	.string "HIDDEN POWER.$"

SlateportCity_Text_HiddenPowerNPC_ChooseType:
	.string "Which type should it be?$"

SlateportCity_Text_HiddenPowerNPC_Success:
	.string "The type of HIDDEN POWER has been\n"
	.string "changed!$"

SlateportCity_Text_ShadyManIntro:
	.string "Psst. Hey kid.\n"
	.string "You look like you need some muscle.\p"
	.string "I run a rental service. For ¥{STR_VAR_1},\n"
	.string "you can borrow one of my POKéMON.$"

SlateportCity_Text_ShadyManCheckOut:
	.string "I've got a {STR_VAR_1} available.\p"
	.string "It's one of a kind. A POKéMON this\n"
	.string "good? You'll never find another.\p"
	.string "Take a look for yourself.$"

SlateportCity_Text_ShadyManOffer:
	.string "Want to rent it for ¥{STR_VAR_1}?$"

SlateportCity_Text_ShadyManDecline:
	.string "Suit yourself. I'll be waiting here\n"
	.string "when come crawling back.$"

SlateportCity_Text_ShadyManNoMoney:
	.string "You don't have the cash.\n"
	.string "I don't run a charity, kid.$"

SlateportCity_Text_ShadyManWarning:
	.string "Here you go. Now listen closely.\n"
	.string "If you don't bring it back alive,\l"
	.string "you'll regret it.$"

SlateportCity_Text_ShadyManActive:
	.string "Take good care of that POKéMON.\n"
	.string "Bring it back here when you're done.$"

SlateportCity_Text_ShadyManRefuse:
	.string "You've got a strange look in your eye…\n"
	.string "Like you're planning to skip town.\l"
	.string "No, I'm not renting to you.$"

SlateportCity_Text_RentalReturnedAlive:
	.string "Pleasure doing business with you.\n"
	.string "Hope it helped you out.$"

SlateportCity_Text_RentalFaintedGreeting:
	.string "Hello! I suppose you're here to return\n"
	.string "my precious POKéMON! Well thank you!$"

SlateportCity_Text_RentalFaintedReaction:
	.string "My POKéMON… What have you done!?\n"
	.string "It's fainted! This is going to cost you!\p"
	.string "Just for that, I'm charging you double!$"

SlateportCity_Text_PlayerHandedOverMoney:
	.string "{PLAYER} handed over ¥{STR_VAR_1}.$"

SlateportCity_Text_PlayerReturnedMon:
	.string "{PLAYER} returned {STR_VAR_1}.$"

SlateportCity_Text_RentalFraud:
	.string "Hold it right there!\p"
	.string "You've been busy, haven't you?\n"
	.string "Collecting badges with MY POKéMON?\p"
	.string "That wasn't the deal!\n"
	.string "I'm taking it back, and I'm taking\l"
	.string "everything you've got!\p"
	.string "Oh, you'll pay for this.\p"
	.string "You heard me! Every cent you earn\n"
	.string "moving forward has my name on it!$"

SlateportCity_Text_ShadyManLostMon:
	.string "Huh? You don't have it?\n"
	.string "Did you lose it?! Get out of here!$"

SlateportCity_Text_ShadyManDebt:
	.string "You've got some nerve showing your\n"
	.string "face here.\p"
	.string "You'll be in debt to me for the\n"
	.string "rest of your life.\p"
	.string "You heard me! Every cent you earn\n"
	.string "moving forward has my name on it!$"

SlateportCity_Text_ShadyManDebtIntercept:
	.string "Where do you think you're going?\n"
	.string "Hand over the cash!$"

SlateportCity_Text_ShadyManDayCare:
	.string "What? It's in the Day Care!?\n"
	.string "I'm going up there right now--\p"
	.string "What are you doing putting my\n"
	.string "POKéMON in the Day Care!?$"

SlateportCity_Text_Girl_DevolveOffer:
	.string "Ah, is that an evolved Eevee?\n"
	.string "If you made a mistake in your race\p"
	.string "and evolved it into an Eeveelution that\n"
	.string "had already been claimed, I can \p"
	.string "devolve it back to an Eevee for you.\n"
	.string "I'll even pay you back the ¥1000!\p"
	.string "Do you need me to devolve it?$"

SlateportCity_Text_Girl_Decline:
	.string "Oh, okay. Thanks for being honest!$"

SlateportCity_Text_Girl_DevolveComplete:
	.string "There you go! It's back to being a\n"
	.string "cute little Eevee!\p"
	.string "Here's your ¥1000.$"

SlateportCity_EventScript_ShadyManGiveDucklett::
	msgbox SlateportCity_Text_GetLost, MSGBOX_DEFAULT
	givemon SPECIES_LEDYBA, 5
	release
	end

SlateportCity_Text_GetLost:
	.string "What's this? You have no POKéMON left?\n"
	.string "How pathetic. Take this and get lost!$"

SlateportCity_Text_EffortRibbonWomanNotEnoughBadges:
	.string "I'm sorry, but I only help experienced\n"
	.string "TRAINERS with their POKéMON.\p"
	.string "Come back once you have at least\n"
	.string "four GYM BADGES.$"

SlateportCity_Text_EnergyGuruNotEnoughBadges:
	.string "I'm sorry, but I only help experienced\n"
	.string "TRAINERS with their POKéMON.\p"
	.string "Come back once you have at least\n"
	.string "two GYM BADGES.$"

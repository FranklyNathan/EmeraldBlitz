LilycoveCity_LilycoveMuseum_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_LilycoveMuseum_1F_OnTransition
	.byte 0

LilycoveCity_LilycoveMuseum_1F_OnTransition:
	setweather WEATHER_SUNNY
	callnative Script_SetTextSpeedMid
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Trapped::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_Trapped, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkUp
	waitmovement 0
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture::
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Castform::
    lock
    faceplayer
    playmoncry SPECIES_CASTFORM, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Castform, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Skitty::
    lock
    faceplayer
    playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Skitty, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Cherrim::
    lock
    faceplayer
    playmoncry SPECIES_BELLOSSOM, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Cherrim, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Smeargle::
    lock
    playmoncry SPECIES_SMEARGLE, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Smeargle, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Aegislash::
    lock
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Aegislash, MSGBOX_DEFAULT
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Wobbuffet::
    lock
    faceplayer
    playmoncry SPECIES_WOBBUFFET, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Wobbuffet, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Kricketune::
    lock
    faceplayer
    playmoncry SPECIES_KRICKETUNE, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Kricketune, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Psyduck::
    lock
    playmoncry SPECIES_PSYDUCK, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Psyduck, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Zigzagoon::
    lock
    faceplayer
    playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Zigzagoon, MSGBOX_DEFAULT
    waitmoncry
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_Pangoro::
    lock
    faceplayer
    goto_if_set FLAG_TEMP_5, LilycoveCity_LilycoveMuseum_1F_EventScript_PangoroSatisfied
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_PangoroSatisfied, MSGBOX_DEFAULT
    closemessage
    getplayerxy VAR_TEMP_0, VAR_TEMP_1
    compare VAR_TEMP_0, 16
    goto_if_gt LilycoveCity_LilycoveMuseum_1F_EventScript_PangoroStepLeft
    applymovement VAR_LAST_TALKED, LilycoveCity_LilycoveMuseum_1F_Movement_PangoroStepRight
    waitmovement 0
    setflag FLAG_TEMP_5
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_PangoroStepLeft::
    applymovement VAR_LAST_TALKED, LilycoveCity_LilycoveMuseum_1F_Movement_PangoroStepLeft
    waitmovement 0
    setflag FLAG_TEMP_5
    release
    end

LilycoveCity_LilycoveMuseum_1F_EventScript_PangoroSatisfied::
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_PangoroNap, MSGBOX_DEFAULT
    release
    end

LilycoveCity_LilycoveMuseum_1F_Movement_PangoroStepRight:
    walk_right
    face_down
    step_end

LilycoveCity_LilycoveMuseum_1F_Movement_PangoroStepLeft:
    walk_left
    face_down
    step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_Victini::
    lock
    faceplayer
    playmoncry SPECIES_VICTINI, CRY_MODE_NORMAL
    msgbox LilycoveCity_LilycoveMuseum_1F_Text_Victini, MSGBOX_DEFAULT
    waitmoncry
    closemessage
    fadescreen FADE_TO_BLACK
    callnative Script_DoHallOfFameScreenDontSaveData
    end

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting:
	.string "It's a painting of an ancient prophecy\n"
	.string "that predicted your victory today.\p"
	.string "…Maybe you can steal it to hang in\n"
	.string "your room.$"

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery:
	.string "It's a painting of NATHAN's most\n"
	.string "valiant battle against STEVEN.\p"
	.string "…Wow, this guy looks so cool.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman:
	.string "This painting looks to be of FLANNERY\n"
	.string "beside her TORKOAL.\p"
	.string "It's a good thing you had a switch in.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon:
	.string "It's an abstract painting of your\n"
	.string "strongest POKéMON!\p"
	.string "But it's so abstract, it's impossible\n"
	.string "to tell which…$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon:
	.string "It's a painting of the BELLOSSOM dancing\n"
	.string "in celebration of your victory.\p"
	.string "…Wet paint is running down the frame\n"
	.string "and dripping onto the floor.$"

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries:
	.string "It's a painting of the ORAN BERRIES the\n"
	.string "PRETTY PETAL FLOWER SHOP keeps\l"
	.string "stocked for your runs.\p"
	.string "They really think of everything!$"

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica:
	.string "It's a high-quality replica of STEVEN's\n"
	.string "SKARMORY.\p"
	.string "There are some spikes scattered on the\n"
	.string "ground beneath it…$"

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone:
	.string "It's an ancient carving of POKé BALL\n"
	.string "carved from stone.\p"
	.string "To think, there was once a day when\n"
	.string "racers had to use these to catch\l"
	.string "POKéMON.$"

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText:
	.string "It's a huge stone tablet etched with\n"
	.string "archaic markings.\p"
	.string "It appears to be an ancient version of\n"
	.string "auction.emeraldblitz.workers.dev$"

LilycoveCity_LilycoveMuseum_1F_Text_Castform:
    .string "CASTFORM appears to be thrilled\n"
    .string "with your success!$"

LilycoveCity_LilycoveMuseum_1F_Text_Skitty:
    .string "SKITTY is so happy to see you've\n"
    .string "brought POKéMON for it to befriend!$"

LilycoveCity_LilycoveMuseum_1F_Text_Cherrim:
    .string "The BELLOSSOM appear to be celebrating\n"
    .string "your nuzlocke victory!$"

LilycoveCity_LilycoveMuseum_1F_Text_Smeargle:
    .string "SMEARGLE appears to be admiring\n"
    .string "its work.$"

LilycoveCity_LilycoveMuseum_1F_Text_Aegislash:
    .string "AEGISLASH appears to be pretending\n"
    .string "to be part of the exhibit.$"

LilycoveCity_LilycoveMuseum_1F_Text_Wobbuffet:
    .string "WOBBUFFET gave you a salute to show\n"
    .string "you its respect.\p"
    .string "…Or maybe it just really likes\n"
    .string "striking that pose.$"

LilycoveCity_LilycoveMuseum_1F_Text_Kricketune:
    .string "KRICKETUNE is playing a lively melody\n"
    .string "for the POKéMON to dance to.$"

LilycoveCity_LilycoveMuseum_1F_Text_Psyduck:
    .string "PSYDUCK appears very overwhelmed\n"
    .string "with this whole victory situation.$"

LilycoveCity_LilycoveMuseum_1F_Text_Zigzagoon:
    .string "…It's the ZIGZAGOON that was chasing\n"
    .string "PROFESSOR BIRCH!\p"
    .string "The look in its eyes suggests it\n"
    .string "always knew you were destined for\l"
    .string "greatness.$"

LilycoveCity_LilycoveMuseum_1F_Text_PangoroSatisfied:
    .string "PANGORO sizes you up. He seems\n"
    .string "satisfied.$"

LilycoveCity_LilycoveMuseum_1F_Text_PangoroNap:
    .string "PANGORO looks ready for a nap.$"

LilycoveCity_LilycoveMuseum_1F_Text_Victini:
    .string "Victini is basking in your victory!$"

LilycoveCity_LilycoveMuseum_1F_Text_Trapped:
	.string "Ah, to return to HOENN!\n"
	.string "It would be sweet.\p"
	.string "But this HOENN, {PLAYER},\n"
	.string "you have already conquered.\p"
	.string "Bask in your glory.\p"
	.string "And if, some bright day, you do decide\n"
	.string "to visit it again, let it be with a\p"
	.string "new team.\p"
	.string "Your current team, in the meantime,\n"
	.string "belongs here.$"

#include "constants/moves.h"

static const u16 sNoneEggMoveLearnset[] = {
    MOVE_UNAVAILABLE,
};

#if P_FAMILY_BULBASAUR
static const u16 sBulbasaurEggMoveLearnset[] = {
    MOVE_GIGA_DRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BULBASAUR

#if P_FAMILY_CHARMANDER
static const u16 sCharmanderEggMoveLearnset[] = {
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHARMANDER

#if P_FAMILY_SQUIRTLE
static const u16 sSquirtleEggMoveLearnset[] = {
    MOVE_AURA_SPHERE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SQUIRTLE

#if P_FAMILY_PIDGEY
static const u16 sPidgeyEggMoveLearnset[] = {
    MOVE_PURSUIT,
    MOVE_FEINT_ATTACK,
    MOVE_FORESIGHT,
    MOVE_STEEL_WING,
    MOVE_AIR_CUTTER,
    MOVE_AIR_SLASH,
    MOVE_BRAVE_BIRD,
    MOVE_UPROAR,
    MOVE_DEFOG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PIDGEY

#if P_FAMILY_RATTATA
static const u16 sRattataEggMoveLearnset[] = {
    MOVE_SCREECH,
    MOVE_FLAME_WHEEL,
    MOVE_FURY_SWIPES,
    MOVE_BITE,
    MOVE_COUNTER,
    MOVE_REVERSAL,
    MOVE_UPROAR,
    MOVE_LAST_RESORT,
    MOVE_ME_FIRST,
    MOVE_REVENGE,
    MOVE_FINAL_GAMBIT,
    MOVE_UNAVAILABLE,
};

#if P_ALOLAN_FORMS
static const u16 sRattataAlolaEggMoveLearnset[] = {
    MOVE_COUNTER,
    MOVE_FINAL_GAMBIT,
    MOVE_FURY_SWIPES,
    MOVE_ME_FIRST,
    MOVE_REVENGE,
    MOVE_REVERSAL,
    MOVE_SNATCH,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SWITCHEROO,
    MOVE_UPROAR,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_RATTATA

#if P_FAMILY_SPEAROW
static const u16 sSpearowEggMoveLearnset[] = {
    MOVE_FEINT_ATTACK,
    MOVE_SCARY_FACE,
    MOVE_QUICK_ATTACK,
    MOVE_TRI_ATTACK,
    MOVE_ASTONISH,
    MOVE_SKY_ATTACK,
    MOVE_WHIRLWIND,
    MOVE_UPROAR,
    MOVE_FEATHER_DANCE,
    MOVE_STEEL_WING,
    MOVE_RAZOR_WIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPEAROW

#if P_FAMILY_EKANS
static const u16 sEkansEggMoveLearnset[] = {
    MOVE_POISON_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_EKANS

#if P_FAMILY_PIKACHU
#if P_GEN_2_CROSS_EVOS
static const u16 sPichuEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_PIKACHU

#if P_FAMILY_SANDSHREW
static const u16 sSandshrewEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sSandshrewAlolaEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_SANDSHREW

#if P_FAMILY_NIDORAN
static const u16 sNidoranFEggMoveLearnset[] = {
    MOVE_POISON_TAIL,
    MOVE_UNAVAILABLE,
};

static const u16 sNidoranMEggMoveLearnset[] = {
    MOVE_POISON_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NIDORAN

#if P_FAMILY_CLEFAIRY
#if P_GEN_2_CROSS_EVOS
static const u16 sCleffaEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_CLEFAIRY

#if P_FAMILY_VULPIX
static const u16 sVulpixEggMoveLearnset[] = {
    MOVE_FEINT_ATTACK,
    MOVE_HYPNOSIS,
    MOVE_FLAIL,
    MOVE_SPITE,
    MOVE_DISABLE,
    MOVE_HOWL,
    MOVE_HEAT_WAVE,
    MOVE_FLARE_BLITZ,
    MOVE_EXTRASENSORY,
    MOVE_POWER_SWAP,
    MOVE_SECRET_POWER,
    MOVE_HEX,
    MOVE_TAIL_SLAP,
    MOVE_CAPTIVATE,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sVulpixAlolaEggMoveLearnset[] = {
    MOVE_FREEZE_DRY,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_VULPIX

#if P_FAMILY_JIGGLYPUFF
#if P_GEN_2_CROSS_EVOS
static const u16 sIgglybuffEggMoveLearnset[] = {
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_JIGGLYPUFF

#if P_FAMILY_ZUBAT
static const u16 sZubatEggMoveLearnset[] = {
    MOVE_FEINT_ATTACK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ZUBAT

#if P_FAMILY_ODDISH
static const u16 sOddishEggMoveLearnset[] = {
    MOVE_STRENGTH_SAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ODDISH

#if P_FAMILY_PARAS
static const u16 sParasEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PARAS

#if P_FAMILY_VENONAT
static const u16 sVenonatEggMoveLearnset[] = {
    MOVE_BATON_PASS,
    MOVE_SCREECH,
    MOVE_GIGA_DRAIN,
    MOVE_SIGNAL_BEAM,
    MOVE_AGILITY,
    MOVE_MORNING_SUN,
    MOVE_TOXIC_SPIKES,
    MOVE_BUG_BITE,
    MOVE_SECRET_POWER,
    MOVE_SKILL_SWAP,
    MOVE_RAGE_POWDER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VENONAT

#if P_FAMILY_DIGLETT
static const u16 sDiglettEggMoveLearnset[] = {
    MOVE_REVERSAL,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sDiglettAlolaEggMoveLearnset[] = {
    MOVE_ANCIENT_POWER,
    MOVE_BEAT_UP,
    MOVE_ENDURE,
    MOVE_FEINT_ATTACK,
    MOVE_FINAL_GAMBIT,
    MOVE_HEADBUTT,
    MOVE_MEMENTO,
    MOVE_METAL_SOUND,
    MOVE_PURSUIT,
    MOVE_REVERSAL,
    MOVE_THRASH,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_DIGLETT

#if P_FAMILY_MEOWTH
static const u16 sMeowthEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sMeowthAlolaEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#if P_GALARIAN_FORMS
static const u16 sMeowthGalarEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_MEOWTH

#if P_FAMILY_PSYDUCK
static const u16 sPsyduckEggMoveLearnset[] = {
    MOVE_MUD_BOMB,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PSYDUCK

#if P_FAMILY_MANKEY
static const u16 sMankeyEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MANKEY

#if P_FAMILY_GROWLITHE
static const u16 sGrowlitheEggMoveLearnset[] = {
    MOVE_MORNING_SUN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GROWLITHE

#if P_FAMILY_POLIWAG
static const u16 sPoliwagEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_POLIWAG

#if P_FAMILY_ABRA
static const u16 sAbraEggMoveLearnset[] = {
    MOVE_PSYCHO_SHIFT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ABRA

#if P_FAMILY_MACHOP
static const u16 sMachopEggMoveLearnset[] = {
    MOVE_ICE_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MACHOP

#if P_FAMILY_BELLSPROUT
static const u16 sBellsproutEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_SYNTHESIS,
    MOVE_LEECH_LIFE,
    MOVE_INGRAIN,
    MOVE_MAGICAL_LEAF,
    MOVE_WORRY_SEED,
    MOVE_TICKLE,
    MOVE_WEATHER_BALL,
    MOVE_BULLET_SEED,
    MOVE_NATURAL_GIFT,
    MOVE_GIGA_DRAIN,
    MOVE_CLEAR_SMOG,
    MOVE_POWER_WHIP,
    MOVE_ACID_SPRAY,
    MOVE_BELCH,
    MOVE_STRENGTH_SAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BELLSPROUT

#if P_FAMILY_TENTACOOL
static const u16 sTentacoolEggMoveLearnset[] = {
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TENTACOOL

#if P_FAMILY_GEODUDE
static const u16 sGeodudeEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sGeodudeAlolaEggMoveLearnset[] = {
    MOVE_AUTOTOMIZE,
    MOVE_BLOCK,
    MOVE_COUNTER,
    MOVE_CURSE,
    MOVE_ENDURE,
    MOVE_FLAIL,
    MOVE_MAGNET_RISE,
    MOVE_ROCK_CLIMB,
    MOVE_SCREECH,
    MOVE_WIDE_GUARD,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_GEODUDE

#if P_FAMILY_PONYTA
static const u16 sPonytaEggMoveLearnset[] = {
    MOVE_HIGH_HORSEPOWER,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sPonytaGalarEggMoveLearnset[] = {
    MOVE_THRASH,
    MOVE_DOUBLE_KICK,
    MOVE_HYPNOSIS,
    MOVE_DOUBLE_EDGE,
    MOVE_HORN_DRILL,
    MOVE_MORNING_SUN,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_PONYTA

#if P_FAMILY_SLOWPOKE
static const u16 sSlowpokeEggMoveLearnset[] = {
    MOVE_BELLY_DRUM,
    MOVE_FUTURE_SIGHT,
    MOVE_STOMP,
    MOVE_MUD_SPORT,
    MOVE_SLEEP_TALK,
    MOVE_SNORE,
    MOVE_ME_FIRST,
    MOVE_BLOCK,
    MOVE_ZEN_HEADBUTT,
    MOVE_WONDER_ROOM,
    MOVE_BELCH,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sSlowpokeGalarEggMoveLearnset[] = {
    MOVE_BELCH,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_SLOWPOKE

#if P_FAMILY_FARFETCHD
static const u16 sFarfetchdEggMoveLearnset[] = {
    MOVE_STEEL_WING,
    MOVE_FORESIGHT,
    MOVE_MIRROR_MOVE,
    MOVE_GUST,
    MOVE_QUICK_ATTACK,
    MOVE_FLAIL,
    MOVE_FEATHER_DANCE,
    MOVE_CURSE,
    MOVE_COVET,
    MOVE_MUD_SLAP,
    MOVE_NIGHT_SLASH,
    MOVE_LEAF_BLADE,
    MOVE_REVENGE,
    MOVE_ROOST,
    MOVE_TRUMP_CARD,
    MOVE_SIMPLE_BEAM,
    MOVE_FIRST_IMPRESSION,
    MOVE_FINAL_GAMBIT,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sFarfetchdGalarEggMoveLearnset[] = {
    MOVE_SKY_ATTACK,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_FARFETCHD

#if P_FAMILY_DODUO
static const u16 sDoduoEggMoveLearnset[] = {
    MOVE_QUICK_ATTACK,
    MOVE_SUPERSONIC,
    MOVE_HAZE,
    MOVE_FEINT_ATTACK,
    MOVE_FLAIL,
    MOVE_ENDEAVOR,
    MOVE_MIRROR_MOVE,
    MOVE_BRAVE_BIRD,
    MOVE_NATURAL_GIFT,
    MOVE_ASSURANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DODUO

#if P_FAMILY_SEEL
static const u16 sSeelEggMoveLearnset[] = {
    MOVE_LICK,
    MOVE_PERISH_SONG,
    MOVE_DISABLE,
    MOVE_HORN_DRILL,
    MOVE_SLAM,
    MOVE_ENCORE,
    MOVE_FAKE_OUT,
    MOVE_ICICLE_SPEAR,
    MOVE_SIGNAL_BEAM,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SPIT_UP,
    MOVE_WATER_PULSE,
    MOVE_IRON_TAIL,
    MOVE_SLEEP_TALK,
    MOVE_BELCH,
    MOVE_ENTRAINMENT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SEEL

#if P_FAMILY_GRIMER
static const u16 sGrimerEggMoveLearnset[] = {
    MOVE_HAZE,
    MOVE_MEAN_LOOK,
    MOVE_LICK,
    MOVE_IMPRISON,
    MOVE_CURSE,
    MOVE_SHADOW_PUNCH,
    MOVE_SHADOW_SNEAK,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SPIT_UP,
    MOVE_SCARY_FACE,
    MOVE_ACID_SPRAY,
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#if P_ALOLAN_FORMS
static const u16 sGrimerAlolaEggMoveLearnset[] = {
    MOVE_ASSURANCE,
    MOVE_CLEAR_SMOG,
    MOVE_CURSE,
    MOVE_IMPRISON,
    MOVE_MEAN_LOOK,
    MOVE_POWER_UP_PUNCH,
    MOVE_PURSUIT,
    MOVE_SCARY_FACE,
    MOVE_SHADOW_SNEAK,
    MOVE_SPITE,
    MOVE_SPIT_UP,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_UNAVAILABLE,
};
#endif //P_ALOLAN_FORMS
#endif //P_FAMILY_GRIMER

#if P_FAMILY_SHELLDER
static const u16 sShellderEggMoveLearnset[] = {
    MOVE_RAPID_SPIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHELLDER

#if P_FAMILY_GASTLY
static const u16 sGastlyEggMoveLearnset[] = {
    MOVE_SCARY_FACE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GASTLY

#if P_FAMILY_ONIX
static const u16 sOnixEggMoveLearnset[] = {
    MOVE_HEAVY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ONIX

#if P_FAMILY_DROWZEE
static const u16 sDrowzeeEggMoveLearnset[] = {
    MOVE_BARRIER,
    MOVE_ASSIST,
    MOVE_ROLE_PLAY,
    MOVE_FIRE_PUNCH,
    MOVE_THUNDER_PUNCH,
    MOVE_ICE_PUNCH,
    MOVE_NASTY_PLOT,
    MOVE_FLATTER,
    MOVE_PSYCHO_CUT,
    MOVE_GUARD_SWAP,
    MOVE_SECRET_POWER,
    MOVE_SKILL_SWAP,
    MOVE_POWER_SPLIT,
    MOVE_PSYCHIC_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DROWZEE

#if P_FAMILY_KRABBY
static const u16 sKrabbyEggMoveLearnset[] = {
    MOVE_HAZE,
    MOVE_AMNESIA,
    MOVE_FLAIL,
    MOVE_SLAM,
    MOVE_KNOCK_OFF,
    MOVE_TICKLE,
    MOVE_ANCIENT_POWER,
    MOVE_AGILITY,
    MOVE_ENDURE,
    MOVE_CHIP_AWAY,
    MOVE_BIDE,
    MOVE_ALLY_SWITCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KRABBY

#if P_FAMILY_EXEGGCUTE
static const u16 sExeggcuteEggMoveLearnset[] = {
    MOVE_MOONLIGHT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_EXEGGCUTE

#if P_FAMILY_CUBONE
static const u16 sCuboneEggMoveLearnset[] = {
    MOVE_IRON_HEAD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CUBONE

#if P_FAMILY_HITMONS
#if P_GEN_2_CROSS_EVOS
static const u16 sTyrogueEggMoveLearnset[] = {
    MOVE_BULLET_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_HITMONS

#if P_FAMILY_LICKITUNG
static const u16 sLickitungEggMoveLearnset[] = {
    MOVE_BELLY_DRUM,
    MOVE_MAGNITUDE,
    MOVE_BODY_SLAM,
    MOVE_CURSE,
    MOVE_SMELLING_SALTS,
    MOVE_SLEEP_TALK,
    MOVE_SNORE,
    MOVE_AMNESIA,
    MOVE_HAMMER_ARM,
    MOVE_MUDDY_WATER,
    MOVE_ZEN_HEADBUTT,
    MOVE_BELCH,
    MOVE_THRASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LICKITUNG

#if P_FAMILY_KOFFING
static const u16 sKoffingEggMoveLearnset[] = {
    MOVE_SCREECH,
    MOVE_PSYWAVE,
    MOVE_PSYBEAM,
    MOVE_DESTINY_BOND,
    MOVE_PAIN_SPLIT,
    MOVE_GRUDGE,
    MOVE_SPITE,
    MOVE_CURSE,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SPIT_UP,
    MOVE_TOXIC_SPIKES,
    MOVE_VENOM_DRENCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KOFFING

#if P_FAMILY_RHYHORN
static const u16 sRhyhornEggMoveLearnset[] = {
    MOVE_CRUNCH,
    MOVE_REVERSAL,
    MOVE_COUNTER,
    MOVE_MAGNITUDE,
    MOVE_CURSE,
    MOVE_CRUSH_CLAW,
    MOVE_DRAGON_RUSH,
    MOVE_ICE_FANG,
    MOVE_FIRE_FANG,
    MOVE_THUNDER_FANG,
    MOVE_SKULL_BASH,
    MOVE_IRON_TAIL,
    MOVE_ROCK_CLIMB,
    MOVE_ROTOTILLER,
    MOVE_METAL_BURST,
    MOVE_GUARD_SPLIT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RHYHORN

#if P_FAMILY_CHANSEY
#if P_GEN_4_CROSS_EVOS
static const u16 sHappinyEggMoveLearnset[] = {
    MOVE_SEISMIC_TOSS,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sChanseyEggMoveLearnset[] = {
    MOVE_SEISMIC_TOSS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHANSEY

#if P_FAMILY_TANGELA
static const u16 sTangelaEggMoveLearnset[] = {
    MOVE_FLAIL,
    MOVE_CONFUSION,
    MOVE_MEGA_DRAIN,
    MOVE_AMNESIA,
    MOVE_LEECH_SEED,
    MOVE_NATURE_POWER,
    MOVE_ENDEAVOR,
    MOVE_LEAF_STORM,
    MOVE_POWER_SWAP,
    MOVE_GIGA_DRAIN,
    MOVE_RAGE_POWDER,
    MOVE_NATURAL_GIFT,
    MOVE_WAKE_UP_SLAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TANGELA

#if P_FAMILY_KANGASKHAN
static const u16 sKangaskhanEggMoveLearnset[] = {
    MOVE_HAMMER_ARM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KANGASKHAN

#if P_FAMILY_HORSEA
static const u16 sHorseaEggMoveLearnset[] = {
    MOVE_DRAGON_BREATH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HORSEA

#if P_FAMILY_GOLDEEN
static const u16 sGoldeenEggMoveLearnset[] = {
    MOVE_PSYBEAM,
    MOVE_HAZE,
    MOVE_HYDRO_PUMP,
    MOVE_SLEEP_TALK,
    MOVE_MUD_SPORT,
    MOVE_MUD_SLAP,
    MOVE_AQUA_TAIL,
    MOVE_BODY_SLAM,
    MOVE_MUD_SHOT,
    MOVE_SKULL_BASH,
    MOVE_SIGNAL_BEAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GOLDEEN

#if P_FAMILY_MR_MIME
#if P_GEN_4_CROSS_EVOS
static const u16 sMimeJrEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sMrMimeEggMoveLearnset[] = {
    MOVE_FUTURE_SIGHT,
    MOVE_HYPNOSIS,
    MOVE_MIMIC,
    MOVE_FAKE_OUT,
    MOVE_TRICK,
    MOVE_CONFUSE_RAY,
    MOVE_WAKE_UP_SLAP,
    MOVE_TEETER_DANCE,
    MOVE_NASTY_PLOT,
    MOVE_POWER_SPLIT,
    MOVE_MAGIC_ROOM,
    MOVE_ICY_WIND,
    MOVE_PSYCHIC_TERRAIN,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sMrMimeGalarEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_CONFUSE_RAY,
    MOVE_POWER_SPLIT,
    MOVE_TICKLE,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_MR_MIME

#if P_FAMILY_SCYTHER
static const u16 sScytherEggMoveLearnset[] = {
    MOVE_BUG_BUZZ,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SCYTHER

#if P_FAMILY_JYNX
#if P_GEN_2_CROSS_EVOS
static const u16 sSmoochumEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_JYNX

#if P_FAMILY_ELECTABUZZ
#if P_GEN_2_CROSS_EVOS
static const u16 sElekidEggMoveLearnset[] = {
    MOVE_ICE_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_ELECTABUZZ

#if P_FAMILY_MAGMAR
#if P_GEN_2_CROSS_EVOS
static const u16 sMagbyEggMoveLearnset[] = {
    MOVE_MACH_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_2_CROSS_EVOS
#endif //P_FAMILY_MAGMAR

#if P_FAMILY_PINSIR
static const u16 sPinsirEggMoveLearnset[] = {
    MOVE_CLOSE_COMBAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PINSIR

#if P_FAMILY_TAUROS
#if P_PALDEAN_FORMS
static const u16 sTaurosPaldeaCombatEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_ENDEAVOR,
    MOVE_UNAVAILABLE,
};

static const u16 sTaurosPaldeaBlazeEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_ENDEAVOR,
    MOVE_UNAVAILABLE,
};

static const u16 sTaurosPaldeaAquaEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_ENDEAVOR,
    MOVE_UNAVAILABLE,
};
#endif //P_PALDEAN_FORMS
#endif //P_FAMILY_TAUROS

#if P_FAMILY_LAPRAS
static const u16 sLaprasEggMoveLearnset[] = {
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LAPRAS

#if P_FAMILY_EEVEE
static const u16 sEeveeEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_EEVEE

#if P_FAMILY_OMANYTE
static const u16 sOmanyteEggMoveLearnset[] = {
    MOVE_BUBBLE_BEAM,
    MOVE_AURORA_BEAM,
    MOVE_SLAM,
    MOVE_SUPERSONIC,
    MOVE_HAZE,
    MOVE_SPIKES,
    MOVE_KNOCK_OFF,
    MOVE_WRING_OUT,
    MOVE_TOXIC_SPIKES,
    MOVE_MUDDY_WATER,
    MOVE_BIDE,
    MOVE_WATER_PULSE,
    MOVE_WHIRLPOOL,
    MOVE_REFLECT_TYPE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_OMANYTE

#if P_FAMILY_KABUTO
static const u16 sKabutoEggMoveLearnset[] = {
    MOVE_BUBBLE_BEAM,
    MOVE_AURORA_BEAM,
    MOVE_RAPID_SPIN,
    MOVE_FLAIL,
    MOVE_KNOCK_OFF,
    MOVE_CONFUSE_RAY,
    MOVE_MUD_SHOT,
    MOVE_ICY_WIND,
    MOVE_SCREECH,
    MOVE_GIGA_DRAIN,
    MOVE_FORESIGHT,
    MOVE_TAKE_DOWN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KABUTO

#if P_FAMILY_AERODACTYL
static const u16 sAerodactylEggMoveLearnset[] = {
    MOVE_WHIRLWIND,
    MOVE_PURSUIT,
    MOVE_FORESIGHT,
    MOVE_STEEL_WING,
    MOVE_DRAGON_BREATH,
    MOVE_CURSE,
    MOVE_ASSURANCE,
    MOVE_ROOST,
    MOVE_TAILWIND,
    MOVE_WIDE_GUARD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_AERODACTYL

#if P_FAMILY_SNORLAX
#if P_GEN_4_CROSS_EVOS
static const u16 sMunchlaxEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sSnorlaxEggMoveLearnset[] = {
    MOVE_LICK,
    MOVE_CHARM,
    MOVE_DOUBLE_EDGE,
    MOVE_CURSE,
    MOVE_FISSURE,
    MOVE_WHIRLWIND,
    MOVE_PURSUIT,
    MOVE_COUNTER,
    MOVE_NATURAL_GIFT,
    MOVE_AFTER_YOU,
    MOVE_BELCH,
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNORLAX

#if P_FAMILY_DRATINI
static const u16 sDratiniEggMoveLearnset[] = {
    MOVE_EXTREME_SPEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRATINI

#if P_FAMILY_CHIKORITA
static const u16 sChikoritaEggMoveLearnset[] = {
    MOVE_VINE_WHIP,
    MOVE_LEECH_SEED,
    MOVE_COUNTER,
    MOVE_ANCIENT_POWER,
    MOVE_FLAIL,
    MOVE_NATURE_POWER,
    MOVE_INGRAIN,
    MOVE_GRASS_WHISTLE,
    MOVE_LEAF_STORM,
    MOVE_AROMATHERAPY,
    MOVE_WRING_OUT,
    MOVE_BODY_SLAM,
    MOVE_REFRESH,
    MOVE_HEAL_PULSE,
    MOVE_GRASSY_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHIKORITA

#if P_FAMILY_CYNDAQUIL
static const u16 sCyndaquilEggMoveLearnset[] = {
    MOVE_EXTRASENSORY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CYNDAQUIL

#if P_FAMILY_TOTODILE
static const u16 sTotodileEggMoveLearnset[] = {
    MOVE_WATER_PULSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TOTODILE

#if P_FAMILY_SENTRET
static const u16 sSentretEggMoveLearnset[] = {
    MOVE_DOUBLE_EDGE,
    MOVE_PURSUIT,
    MOVE_SLASH,
    MOVE_FOCUS_ENERGY,
    MOVE_REVERSAL,
    MOVE_TRICK,
    MOVE_ASSIST,
    MOVE_LAST_RESORT,
    MOVE_CHARM,
    MOVE_COVET,
    MOVE_NATURAL_GIFT,
    MOVE_IRON_TAIL,
    MOVE_CAPTIVATE,
    MOVE_BABY_DOLL_EYES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SENTRET

#if P_FAMILY_HOOTHOOT
static const u16 sHoothootEggMoveLearnset[] = {
    MOVE_MIRROR_MOVE,
    MOVE_SUPERSONIC,
    MOVE_FEINT_ATTACK,
    MOVE_WING_ATTACK,
    MOVE_WHIRLWIND,
    MOVE_SKY_ATTACK,
    MOVE_FEATHER_DANCE,
    MOVE_AGILITY,
    MOVE_NIGHT_SHADE,
    MOVE_DEFOG,
    MOVE_MEAN_LOOK,
    MOVE_HURRICANE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HOOTHOOT

#if P_FAMILY_LEDYBA
static const u16 sLedybaEggMoveLearnset[] = {
    MOVE_PSYBEAM,
    MOVE_BIDE,
    MOVE_SILVER_WIND,
    MOVE_BUG_BUZZ,
    MOVE_SCREECH,
    MOVE_ENCORE,
    MOVE_KNOCK_OFF,
    MOVE_BUG_BITE,
    MOVE_FOCUS_PUNCH,
    MOVE_DRAIN_PUNCH,
    MOVE_DIZZY_PUNCH,
    MOVE_TAILWIND,
    MOVE_ENDURE,
    MOVE_COUNTER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LEDYBA

#if P_FAMILY_SPINARAK
static const u16 sSpinarakEggMoveLearnset[] = {
    MOVE_LUNGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPINARAK

#if P_FAMILY_CHINCHOU
static const u16 sChinchouEggMoveLearnset[] = {
    MOVE_PSYBEAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHINCHOU

#if P_FAMILY_TOGEPI
static const u16 sTogepiEggMoveLearnset[] = {
    MOVE_FUTURE_SIGHT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TOGEPI

#if P_FAMILY_NATU
static const u16 sNatuEggMoveLearnset[] = {
    MOVE_HAZE,
    MOVE_DRILL_PECK,
    MOVE_QUICK_ATTACK,
    MOVE_FEINT_ATTACK,
    MOVE_STEEL_WING,
    MOVE_FEATHER_DANCE,
    MOVE_REFRESH,
    MOVE_ZEN_HEADBUTT,
    MOVE_SUCKER_PUNCH,
    MOVE_SYNCHRONOISE,
    MOVE_ROOST,
    MOVE_SKILL_SWAP,
    MOVE_SIMPLE_BEAM,
    MOVE_ALLY_SWITCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NATU

#if P_FAMILY_MAREEP
static const u16 sMareepEggMoveLearnset[] = {
    MOVE_MILK_DRINK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MAREEP

#if P_FAMILY_MARILL
#if P_GEN_3_CROSS_EVOS
static const u16 sAzurillEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_3_CROSS_EVOS
static const u16 sMarillEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MARILL

#if P_FAMILY_SUDOWOODO
#if P_GEN_4_CROSS_EVOS
static const u16 sBonslyEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sSudowoodoEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SUDOWOODO

#if P_FAMILY_HOPPIP
static const u16 sHoppipEggMoveLearnset[] = {
    MOVE_CONFUSION,
    MOVE_ENCORE,
    MOVE_DOUBLE_EDGE,
    MOVE_AMNESIA,
    MOVE_HELPING_HAND,
    MOVE_AROMATHERAPY,
    MOVE_WORRY_SEED,
    MOVE_COTTON_GUARD,
    MOVE_SEED_BOMB,
    MOVE_ENDURE,
    MOVE_GRASSY_TERRAIN,
    MOVE_STRENGTH_SAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HOPPIP

#if P_FAMILY_AIPOM
static const u16 sAipomEggMoveLearnset[] = {
    MOVE_COUNTER,
    MOVE_SCREECH,
    MOVE_PURSUIT,
    MOVE_AGILITY,
    MOVE_SPITE,
    MOVE_SLAM,
    MOVE_DOUBLE_SLAP,
    MOVE_BEAT_UP,
    MOVE_FAKE_OUT,
    MOVE_COVET,
    MOVE_BOUNCE,
    MOVE_REVENGE,
    MOVE_SWITCHEROO,
    MOVE_QUICK_GUARD,
    MOVE_TAIL_SLAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_AIPOM

#if P_FAMILY_SUNKERN
static const u16 sSunkernEggMoveLearnset[] = {
    MOVE_GRASS_WHISTLE,
    MOVE_ENCORE,
    MOVE_LEECH_SEED,
    MOVE_NATURE_POWER,
    MOVE_CURSE,
    MOVE_HELPING_HAND,
    MOVE_INGRAIN,
    MOVE_SWEET_SCENT,
    MOVE_ENDURE,
    MOVE_BIDE,
    MOVE_NATURAL_GIFT,
    MOVE_MORNING_SUN,
    MOVE_GRASSY_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SUNKERN

#if P_FAMILY_YANMA
static const u16 sYanmaEggMoveLearnset[] = {
    MOVE_SIGNAL_BEAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_YANMA

#if P_FAMILY_WOOPER
static const u16 sWooperEggMoveLearnset[] = {
    MOVE_BODY_SLAM,
    MOVE_ANCIENT_POWER,
    MOVE_CURSE,
    MOVE_MUD_SPORT,
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SPIT_UP,
    MOVE_COUNTER,
    MOVE_ENCORE,
    MOVE_DOUBLE_KICK,
    MOVE_RECOVER,
    MOVE_AFTER_YOU,
    MOVE_SLEEP_TALK,
    MOVE_ACID_SPRAY,
    MOVE_GUARD_SWAP,
    MOVE_EERIE_IMPULSE,
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#if P_PALDEAN_FORMS
static const u16 sWooperPaldeaEggMoveLearnset[] = {
    MOVE_ACID_SPRAY,
    MOVE_UNAVAILABLE,
};
#endif //P_PALDEAN_FORMS
#endif //P_FAMILY_WOOPER

#if P_FAMILY_MURKROW
static const u16 sMurkrowEggMoveLearnset[] = {
    MOVE_DRILL_PECK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MURKROW

#if P_FAMILY_MISDREAVUS
static const u16 sMisdreavusEggMoveLearnset[] = {
    MOVE_OMINOUS_WIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MISDREAVUS

#if P_FAMILY_GIRAFARIG
static const u16 sGirafarigEggMoveLearnset[] = {
    MOVE_TAKE_DOWN,
    MOVE_AMNESIA,
    MOVE_FORESIGHT,
    MOVE_FUTURE_SIGHT,
    MOVE_BEAT_UP,
    MOVE_WISH,
    MOVE_MAGIC_COAT,
    MOVE_DOUBLE_KICK,
    MOVE_MIRROR_COAT,
    MOVE_RAZOR_WIND,
    MOVE_SKILL_SWAP,
    MOVE_SECRET_POWER,
    MOVE_MEAN_LOOK,
    MOVE_PSYCHIC_FANGS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GIRAFARIG

#if P_FAMILY_PINECO
static const u16 sPinecoEggMoveLearnset[] = {
    MOVE_SAND_TOMB,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PINECO

#if P_FAMILY_DUNSPARCE
static const u16 sDunsparceEggMoveLearnset[] = {
    MOVE_BIDE,
    MOVE_ANCIENT_POWER,
    MOVE_BITE,
    MOVE_HEADBUTT,
    MOVE_ASTONISH,
    MOVE_CURSE,
    MOVE_TRUMP_CARD,
    MOVE_MAGIC_COAT,
    MOVE_SNORE,
    MOVE_AGILITY,
    MOVE_SECRET_POWER,
    MOVE_SLEEP_TALK,
    MOVE_HEX,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DUNSPARCE

#if P_FAMILY_GLIGAR
static const u16 sGligarEggMoveLearnset[] = {
    MOVE_METAL_CLAW,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GLIGAR

#if P_FAMILY_SNUBBULL
static const u16 sSnubbullEggMoveLearnset[] = {
    MOVE_FAKE_TEARS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNUBBULL

#if P_FAMILY_QWILFISH
static const u16 sQwilfishEggMoveLearnset[] = {
    MOVE_FLAIL,
    MOVE_HAZE,
    MOVE_BUBBLE_BEAM,
    MOVE_SUPERSONIC,
    MOVE_ASTONISH,
    MOVE_SIGNAL_BEAM,
    MOVE_AQUA_JET,
    MOVE_WATER_PULSE,
    MOVE_BRINE,
    MOVE_ACID_SPRAY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_QWILFISH

#if P_FAMILY_SHUCKLE
static const u16 sShuckleEggMoveLearnset[] = {
    MOVE_SWEET_SCENT,
    MOVE_KNOCK_OFF,
    MOVE_HELPING_HAND,
    MOVE_ACUPRESSURE,
    MOVE_SAND_TOMB,
    MOVE_MUD_SLAP,
    MOVE_ACID,
    MOVE_ROCK_BLAST,
    MOVE_FINAL_GAMBIT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHUCKLE

#if P_FAMILY_HERACROSS
static const u16 sHeracrossEggMoveLearnset[] = {
    MOVE_ROCK_BLAST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HERACROSS

#if P_FAMILY_SNEASEL
static const u16 sSneaselEggMoveLearnset[] = {
    MOVE_ICE_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNEASEL

#if P_FAMILY_TEDDIURSA
static const u16 sTeddiursaEggMoveLearnset[] = {
    MOVE_CRUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TEDDIURSA

#if P_FAMILY_SLUGMA
static const u16 sSlugmaEggMoveLearnset[] = {
    MOVE_ACID_ARMOR,
    MOVE_HEAT_WAVE,
    MOVE_CURSE,
    MOVE_SMOKESCREEN,
    MOVE_MEMENTO,
    MOVE_STOCKPILE,
    MOVE_SPIT_UP,
    MOVE_SWALLOW,
    MOVE_ROLLOUT,
    MOVE_INFERNO,
    MOVE_EARTH_POWER,
    MOVE_GUARD_SWAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SLUGMA

#if P_FAMILY_SWINUB
static const u16 sSwinubEggMoveLearnset[] = {
    MOVE_AVALANCHE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SWINUB

#if P_FAMILY_CORSOLA
static const u16 sCorsolaEggMoveLearnset[] = {
    MOVE_LIQUIDATION,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sCorsolaGalarEggMoveLearnset[] = {
    MOVE_DESTINY_BOND,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_CORSOLA

#if P_FAMILY_REMORAID
static const u16 sRemoraidEggMoveLearnset[] = {
    MOVE_ACID_SPRAY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_REMORAID

#if P_FAMILY_DELIBIRD
static const u16 sDelibirdEggMoveLearnset[] = {
    MOVE_FREEZE_DRY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DELIBIRD

#if P_FAMILY_MANTINE
#if P_GEN_4_CROSS_EVOS
static const u16 sMantykeEggMoveLearnset[] = {
    MOVE_TAILWIND,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sMantineEggMoveLearnset[] = {
    MOVE_TAILWIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MANTINE

#if P_FAMILY_SKARMORY
static const u16 sSkarmoryEggMoveLearnset[] = {
    MOVE_DRILL_PECK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKARMORY

#if P_FAMILY_HOUNDOUR
static const u16 sHoundourEggMoveLearnset[] = {
    MOVE_SUCKER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HOUNDOUR

#if P_FAMILY_PHANPY
static const u16 sPhanpyEggMoveLearnset[] = {
    MOVE_ICE_SHARD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PHANPY

#if P_FAMILY_STANTLER
static const u16 sStantlerEggMoveLearnset[] = {
    MOVE_DOUBLE_KICK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_STANTLER

#if P_FAMILY_MILTANK
static const u16 sMiltankEggMoveLearnset[] = {
    MOVE_HEART_STAMP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MILTANK

#if P_FAMILY_LARVITAR
static const u16 sLarvitarEggMoveLearnset[] = {
    MOVE_OUTRAGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LARVITAR

#if P_FAMILY_TREECKO
static const u16 sTreeckoEggMoveLearnset[] = {
    MOVE_GRASS_WHISTLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TREECKO

#if P_FAMILY_TORCHIC
static const u16 sTorchicEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TORCHIC

#if P_FAMILY_MUDKIP
static const u16 sMudkipEggMoveLearnset[] = {
    MOVE_AVALANCHE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MUDKIP

#if P_FAMILY_POOCHYENA
static const u16 sPoochyenaEggMoveLearnset[] = {
    MOVE_POISON_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_POOCHYENA

#if P_FAMILY_ZIGZAGOON
static const u16 sZigzagoonEggMoveLearnset[] = {
    MOVE_EXTREME_SPEED,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sZigzagoonGalarEggMoveLearnset[] = {
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_ZIGZAGOON

#if P_FAMILY_LOTAD
static const u16 sLotadEggMoveLearnset[] = {
    MOVE_TEETER_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LOTAD

#if P_FAMILY_SEEDOT
static const u16 sSeedotEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_AMNESIA,
    MOVE_QUICK_ATTACK,
    MOVE_RAZOR_WIND,
    MOVE_TAKE_DOWN,
    MOVE_WORRY_SEED,
    MOVE_NASTY_PLOT,
    MOVE_POWER_SWAP,
    MOVE_DEFOG,
    MOVE_FOUL_PLAY,
    MOVE_BEAT_UP,
    MOVE_BULLET_SEED,
    MOVE_GRASSY_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SEEDOT

#if P_FAMILY_TAILLOW
static const u16 sTaillowEggMoveLearnset[] = {
    MOVE_PURSUIT,
    MOVE_SUPERSONIC,
    MOVE_REFRESH,
    MOVE_MIRROR_MOVE,
    MOVE_RAGE,
    MOVE_SKY_ATTACK,
    MOVE_WHIRLWIND,
    MOVE_BRAVE_BIRD,
    MOVE_ROOST,
    MOVE_STEEL_WING,
    MOVE_DEFOG,
    MOVE_BOOMBURST,
    MOVE_HURRICANE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TAILLOW

#if P_FAMILY_WINGULL
static const u16 sWingullEggMoveLearnset[] = {
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WINGULL

#if P_FAMILY_RALTS
static const u16 sRaltsEggMoveLearnset[] = {
    MOVE_SHADOW_SNEAK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RALTS

#if P_FAMILY_SURSKIT
static const u16 sSurskitEggMoveLearnset[] = {
    MOVE_LUNGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SURSKIT

#if P_FAMILY_SHROOMISH
static const u16 sShroomishEggMoveLearnset[] = {
    MOVE_WAKE_UP_SLAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHROOMISH

#if P_FAMILY_SLAKOTH
static const u16 sSlakothEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SLAKOTH

#if P_FAMILY_NINCADA
static const u16 sNincadaEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NINCADA

#if P_FAMILY_WHISMUR
static const u16 sWhismurEggMoveLearnset[] = {
    MOVE_TAKE_DOWN,
    MOVE_SNORE,
    MOVE_EXTRASENSORY,
    MOVE_SMELLING_SALTS,
    MOVE_SMOKESCREEN,
    MOVE_ENDEAVOR,
    MOVE_HAMMER_ARM,
    MOVE_FAKE_TEARS,
    MOVE_CIRCLE_THROW,
    MOVE_DISARMING_VOICE,
    MOVE_WHIRLWIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WHISMUR

#if P_FAMILY_MAKUHITA
static const u16 sMakuhitaEggMoveLearnset[] = {
    MOVE_DETECT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MAKUHITA

#if P_FAMILY_NOSEPASS
static const u16 sNosepassEggMoveLearnset[] = {
    MOVE_STEALTH_ROCK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NOSEPASS

#if P_FAMILY_SKITTY
static const u16 sSkittyEggMoveLearnset[] = {
    MOVE_HELPING_HAND,
    MOVE_UPROAR,
    MOVE_FAKE_TEARS,
    MOVE_WISH,
    MOVE_BATON_PASS,
    MOVE_TICKLE,
    MOVE_LAST_RESORT,
    MOVE_FAKE_OUT,
    MOVE_ZEN_HEADBUTT,
    MOVE_SUCKER_PUNCH,
    MOVE_MUD_BOMB,
    MOVE_SIMPLE_BEAM,
    MOVE_CAPTIVATE,
    MOVE_COSMIC_POWER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKITTY

#if P_FAMILY_SABLEYE
static const u16 sSableyeEggMoveLearnset[] = {
    MOVE_MOONLIGHT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SABLEYE

#if P_FAMILY_MAWILE
static const u16 sMawileEggMoveLearnset[] = {
    MOVE_THUNDER_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MAWILE

#if P_FAMILY_ARON
static const u16 sAronEggMoveLearnset[] = {
    MOVE_DRAGON_RUSH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ARON

#if P_FAMILY_MEDITITE
static const u16 sMedititeEggMoveLearnset[] = {
    MOVE_BULLET_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MEDITITE

#if P_FAMILY_ELECTRIKE
static const u16 sElectrikeEggMoveLearnset[] = {
    MOVE_FLAME_BURST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ELECTRIKE

#if P_FAMILY_PLUSLE
static const u16 sPlusleEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PLUSLE

#if P_FAMILY_MINUN
static const u16 sMinunEggMoveLearnset[] = {
    MOVE_TEARFUL_LOOK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MINUN

#if P_FAMILY_VOLBEAT_ILLUMISE
static const u16 sVolbeatEggMoveLearnset[] = {
    MOVE_BATON_PASS,
    MOVE_SILVER_WIND,
    MOVE_TRICK,
    MOVE_ENCORE,
    MOVE_BUG_BUZZ,
    MOVE_DIZZY_PUNCH,
    MOVE_SEISMIC_TOSS,
    MOVE_LUNGE,
    MOVE_UNAVAILABLE,
};

static const u16 sIllumiseEggMoveLearnset[] = {
    MOVE_BATON_PASS,
    MOVE_SILVER_WIND,
    MOVE_GROWTH,
    MOVE_ENCORE,
    MOVE_BUG_BUZZ,
    MOVE_CAPTIVATE,
    MOVE_FAKE_TEARS,
    MOVE_CONFUSE_RAY,
    MOVE_AROMATHERAPY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VOLBEAT_ILLUMISE

#if P_FAMILY_ROSELIA
#if P_GEN_4_CROSS_EVOS
static const u16 sBudewEggMoveLearnset[] = {
    MOVE_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sRoseliaEggMoveLearnset[] = {
    MOVE_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROSELIA

#if P_FAMILY_GULPIN
static const u16 sGulpinEggMoveLearnset[] = {
    MOVE_ACID_ARMOR,
    MOVE_SMOG,
    MOVE_PAIN_SPLIT,
    MOVE_CURSE,
    MOVE_DESTINY_BOND,
    MOVE_MUD_SLAP,
    MOVE_GUNK_SHOT,
    MOVE_VENOM_DRENCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GULPIN

#if P_FAMILY_CARVANHA
static const u16 sCarvanhaEggMoveLearnset[] = {
    MOVE_PSYCHIC_FANGS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CARVANHA

#if P_FAMILY_WAILMER
static const u16 sWailmerEggMoveLearnset[] = {
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WAILMER

#if P_FAMILY_NUMEL
static const u16 sNumelEggMoveLearnset[] = {
    MOVE_HEAVY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NUMEL

#if P_FAMILY_TORKOAL
static const u16 sTorkoalEggMoveLearnset[] = {
    MOVE_ERUPTION,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TORKOAL

#if P_FAMILY_SPOINK
static const u16 sSpoinkEggMoveLearnset[] = {
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPOINK

#if P_FAMILY_SPINDA
static const u16 sSpindaEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_ASSIST,
    MOVE_DISABLE,
    MOVE_BATON_PASS,
    MOVE_WISH,
    MOVE_TRICK,
    MOVE_SMELLING_SALTS,
    MOVE_FAKE_OUT,
    MOVE_ROLE_PLAY,
    MOVE_PSYCHO_CUT,
    MOVE_FAKE_TEARS,
    MOVE_RAPID_SPIN,
    MOVE_ICY_WIND,
    MOVE_WATER_PULSE,
    MOVE_PSYCHO_SHIFT,
    MOVE_GUARD_SPLIT,
    MOVE_SPOTLIGHT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPINDA

#if P_FAMILY_TRAPINCH
static const u16 sTrapinchEggMoveLearnset[] = {
    MOVE_BUG_BITE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TRAPINCH

#if P_FAMILY_CACNEA
static const u16 sCacneaEggMoveLearnset[] = {
    MOVE_COUNTER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CACNEA

#if P_FAMILY_SWABLU
static const u16 sSwabluEggMoveLearnset[] = {
    MOVE_HYPER_VOICE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SWABLU

#if P_FAMILY_ZANGOOSE
static const u16 sZangooseEggMoveLearnset[] = {
    MOVE_METAL_CLAW,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ZANGOOSE

#if P_FAMILY_SEVIPER
static const u16 sSeviperEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SEVIPER

#if P_FAMILY_BARBOACH
static const u16 sBarboachEggMoveLearnset[] = {
    MOVE_THRASH,
    MOVE_WHIRLPOOL,
    MOVE_SPARK,
    MOVE_HYDRO_PUMP,
    MOVE_FLAIL,
    MOVE_TAKE_DOWN,
    MOVE_DRAGON_DANCE,
    MOVE_EARTH_POWER,
    MOVE_MUD_SHOT,
    MOVE_MUDDY_WATER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BARBOACH

#if P_FAMILY_CORPHISH
static const u16 sCorphishEggMoveLearnset[] = {
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CORPHISH

#if P_FAMILY_LILEEP
static const u16 sLileepEggMoveLearnset[] = {
    MOVE_BARRIER,
    MOVE_RECOVER,
    MOVE_MIRROR_COAT,
    MOVE_WRING_OUT,
    MOVE_TICKLE,
    MOVE_CURSE,
    MOVE_MEGA_DRAIN,
    MOVE_ENDURE,
    MOVE_STEALTH_ROCK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LILEEP

#if P_FAMILY_ANORITH
static const u16 sAnorithEggMoveLearnset[] = {
    MOVE_AQUA_JET,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ANORITH

#if P_FAMILY_FEEBAS
static const u16 sFeebasEggMoveLearnset[] = {
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FEEBAS

#if P_FAMILY_CASTFORM
static const u16 sCastformEggMoveLearnset[] = {
    MOVE_OMINOUS_WIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CASTFORM

#if P_FAMILY_KECLEON
static const u16 sKecleonEggMoveLearnset[] = {
    MOVE_DISABLE,
    MOVE_MAGIC_COAT,
    MOVE_TRICK,
    MOVE_FAKE_OUT,
    MOVE_NASTY_PLOT,
    MOVE_DIZZY_PUNCH,
    MOVE_RECOVER,
    MOVE_SKILL_SWAP,
    MOVE_SNATCH,
    MOVE_FOUL_PLAY,
    MOVE_CAMOUFLAGE,
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KECLEON

#if P_FAMILY_SHUPPET
static const u16 sShuppetEggMoveLearnset[] = {
    MOVE_GUNK_SHOT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHUPPET

#if P_FAMILY_DUSKULL
static const u16 sDuskullEggMoveLearnset[] = {
    MOVE_PAIN_SPLIT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DUSKULL

#if P_FAMILY_TROPIUS
static const u16 sTropiusEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TROPIUS

#if P_FAMILY_CHIMECHO
#if P_GEN_4_CROSS_EVOS
static const u16 sChinglingEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_GEN_4_CROSS_EVOS
static const u16 sChimechoEggMoveLearnset[] = {
    MOVE_WISH,
};
#endif //P_FAMILY_CHIMECHO

#if P_FAMILY_ABSOL
static const u16 sAbsolEggMoveLearnset[] = {
    MOVE_PUNISHMENT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ABSOL

#if P_FAMILY_SNORUNT
static const u16 sSnoruntEggMoveLearnset[] = {
    MOVE_FAKE_TEARS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNORUNT

#if P_FAMILY_SPHEAL
static const u16 sSphealEggMoveLearnset[] = {
    MOVE_STOCKPILE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPHEAL

#if P_FAMILY_CLAMPERL
static const u16 sClamperlEggMoveLearnset[] = {
    MOVE_MUDDY_WATER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CLAMPERL

#if P_FAMILY_RELICANTH
static const u16 sRelicanthEggMoveLearnset[] = {
    MOVE_MUD_SHOT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RELICANTH

#if P_FAMILY_LUVDISC
static const u16 sLuvdiscEggMoveLearnset[] = {
    MOVE_SPLASH,
    MOVE_SUPERSONIC,
    MOVE_WATER_SPORT,
    MOVE_MUD_SPORT,
    MOVE_CAPTIVATE,
    MOVE_AQUA_RING,
    MOVE_AQUA_JET,
    MOVE_HEAL_PULSE,
    MOVE_BRINE,
    MOVE_ENTRAINMENT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LUVDISC

#if P_FAMILY_BAGON
static const u16 sBagonEggMoveLearnset[] = {
    MOVE_HYDRO_PUMP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BAGON

#if P_FAMILY_TURTWIG
static const u16 sTurtwigEggMoveLearnset[] = {
    MOVE_GROWTH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TURTWIG

#if P_FAMILY_CHIMCHAR
static const u16 sChimcharEggMoveLearnset[] = {
    MOVE_THUNDER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHIMCHAR

#if P_FAMILY_PIPLUP
static const u16 sPiplupEggMoveLearnset[] = {
    MOVE_ICY_WIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PIPLUP

#if P_FAMILY_STARLY
static const u16 sStarlyEggMoveLearnset[] = {
    MOVE_DETECT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_STARLY

#if P_FAMILY_BIDOOF
static const u16 sBidoofEggMoveLearnset[] = {
    MOVE_AQUA_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BIDOOF

#if P_FAMILY_SHINX
static const u16 sShinxEggMoveLearnset[] = {
    MOVE_ICE_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHINX

#if P_FAMILY_CRANIDOS
static const u16 sCranidosEggMoveLearnset[] = {
    MOVE_CRUNCH,
    MOVE_THRASH,
    MOVE_DOUBLE_EDGE,
    MOVE_LEER,
    MOVE_SLAM,
    MOVE_STOMP,
    MOVE_WHIRLWIND,
    MOVE_HAMMER_ARM,
    MOVE_CURSE,
    MOVE_IRON_TAIL,
    MOVE_IRON_HEAD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CRANIDOS

#if P_FAMILY_SHIELDON
static const u16 sShieldonEggMoveLearnset[] = {
    MOVE_HEADBUTT,
    MOVE_SCARY_FACE,
    MOVE_FOCUS_ENERGY,
    MOVE_DOUBLE_EDGE,
    MOVE_ROCK_BLAST,
    MOVE_BODY_SLAM,
    MOVE_SCREECH,
    MOVE_CURSE,
    MOVE_FISSURE,
    MOVE_COUNTER,
    MOVE_STEALTH_ROCK,
    MOVE_WIDE_GUARD,
    MOVE_GUARD_SPLIT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHIELDON

#if P_FAMILY_PACHIRISU
static const u16 sPachirisuEggMoveLearnset[] = {
    MOVE_COVET,
    MOVE_BITE,
    MOVE_FAKE_TEARS,
    MOVE_DEFENSE_CURL,
    MOVE_ROLLOUT,
    MOVE_FLATTER,
    MOVE_FLAIL,
    MOVE_IRON_TAIL,
    MOVE_TAIL_WHIP,
    MOVE_FOLLOW_ME,
    MOVE_CHARGE,
    MOVE_BESTOW,
    MOVE_ION_DELUGE,
    MOVE_BABY_DOLL_EYES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PACHIRISU

#if P_FAMILY_BUIZEL
static const u16 sBuizelEggMoveLearnset[] = {
    MOVE_AQUA_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BUIZEL

#if P_FAMILY_CHERUBI
static const u16 sCherubiEggMoveLearnset[] = {
    MOVE_WEATHER_BALL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHERUBI

#if P_FAMILY_SHELLOS
static const u16 sShellosEggMoveLearnset[] = {
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHELLOS

#if P_FAMILY_DRIFLOON
static const u16 sDrifloonEggMoveLearnset[] = {
    MOVE_WEATHER_BALL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRIFLOON

#if P_FAMILY_BUNEARY
static const u16 sBunearyEggMoveLearnset[] = {
    MOVE_SKY_UPPERCUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BUNEARY

#if P_FAMILY_GLAMEOW
static const u16 sGlameowEggMoveLearnset[] = {
    MOVE_BITE,
    MOVE_TAIL_WHIP,
    MOVE_QUICK_ATTACK,
    MOVE_SAND_ATTACK,
    MOVE_FAKE_TEARS,
    MOVE_ASSURANCE,
    MOVE_FLAIL,
    MOVE_SNATCH,
    MOVE_WAKE_UP_SLAP,
    MOVE_LAST_RESORT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GLAMEOW

#if P_FAMILY_STUNKY
static const u16 sStunkyEggMoveLearnset[] = {
    MOVE_PURSUIT,
    MOVE_LEER,
    MOVE_SMOG,
    MOVE_DOUBLE_EDGE,
    MOVE_CRUNCH,
    MOVE_SCARY_FACE,
    MOVE_ASTONISH,
    MOVE_PUNISHMENT,
    MOVE_HAZE,
    MOVE_IRON_TAIL,
    MOVE_FOUL_PLAY,
    MOVE_FLAME_BURST,
    MOVE_PLAY_ROUGH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_STUNKY

#if P_FAMILY_CHATOT
static const u16 sChatotEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_NIGHT_SHADE,
    MOVE_AGILITY,
    MOVE_NASTY_PLOT,
    MOVE_SUPERSONIC,
    MOVE_STEEL_WING,
    MOVE_SLEEP_TALK,
    MOVE_DEFOG,
    MOVE_AIR_CUTTER,
    MOVE_BOOMBURST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHATOT

#if P_FAMILY_SPIRITOMB
static const u16 sSpiritombEggMoveLearnset[] = {
    MOVE_DESTINY_BOND,
    MOVE_PAIN_SPLIT,
    MOVE_SMOKESCREEN,
    MOVE_IMPRISON,
    MOVE_GRUDGE,
    MOVE_SHADOW_SNEAK,
    MOVE_CAPTIVATE,
    MOVE_NIGHTMARE,
    MOVE_FOUL_PLAY,
    MOVE_DISABLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPIRITOMB

#if P_FAMILY_GIBLE
static const u16 sGibleEggMoveLearnset[] = {
    MOVE_IRON_HEAD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GIBLE

#if P_FAMILY_RIOLU
static const u16 sRioluEggMoveLearnset[] = {
    MOVE_SKY_UPPERCUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RIOLU

#if P_FAMILY_HIPPOPOTAS
static const u16 sHippopotasEggMoveLearnset[] = {
    MOVE_SLACK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HIPPOPOTAS

#if P_FAMILY_SKORUPI
static const u16 sSkorupiEggMoveLearnset[] = {
    MOVE_SCREECH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKORUPI

#if P_FAMILY_CROAGUNK
static const u16 sCroagunkEggMoveLearnset[] = {
    MOVE_DRAIN_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CROAGUNK

#if P_FAMILY_CARNIVINE
static const u16 sCarnivineEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CARNIVINE

#if P_FAMILY_FINNEON
static const u16 sFinneonEggMoveLearnset[] = {
    MOVE_SWEET_KISS,
    MOVE_CHARM,
    MOVE_FLAIL,
    MOVE_AQUA_TAIL,
    MOVE_SPLASH,
    MOVE_PSYBEAM,
    MOVE_TICKLE,
    MOVE_AGILITY,
    MOVE_BRINE,
    MOVE_AURORA_BEAM,
    MOVE_SIGNAL_BEAM,
    MOVE_CONFUSE_RAY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FINNEON

#if P_FAMILY_SNOVER
static const u16 sSnoverEggMoveLearnset[] = {
    MOVE_AVALANCHE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNOVER

#if P_FAMILY_SNIVY
static const u16 sSnivyEggMoveLearnset[] = {
    MOVE_GLARE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNIVY

#if P_FAMILY_TEPIG
static const u16 sTepigEggMoveLearnset[] = {
    MOVE_COVET,
    MOVE_BODY_SLAM,
    MOVE_THRASH,
    MOVE_MAGNITUDE,
    MOVE_SUPERPOWER,
    MOVE_CURSE,
    MOVE_ENDEAVOR,
    MOVE_YAWN,
    MOVE_SLEEP_TALK,
    MOVE_HEAVY_SLAM,
    MOVE_SUCKER_PUNCH,
    MOVE_BURN_UP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TEPIG

#if P_FAMILY_OSHAWOTT
static const u16 sOshawottEggMoveLearnset[] = {
    MOVE_SACRED_SWORD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_OSHAWOTT

#if P_FAMILY_PATRAT
static const u16 sPatratEggMoveLearnset[] = {
    MOVE_FORESIGHT,
    MOVE_IRON_TAIL,
    MOVE_SCREECH,
    MOVE_ASSURANCE,
    MOVE_PURSUIT,
    MOVE_REVENGE,
    MOVE_FLAIL,
    MOVE_TEARFUL_LOOK,
    MOVE_BULLET_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PATRAT

#if P_FAMILY_LILLIPUP
static const u16 sLillipupEggMoveLearnset[] = {
    MOVE_PSYCHIC_FANGS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LILLIPUP

#if P_FAMILY_PURRLOIN
static const u16 sPurrloinEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PURRLOIN

#if P_FAMILY_PANSAGE
static const u16 sPansageEggMoveLearnset[] = {
    MOVE_COVET,
    MOVE_LOW_KICK,
    MOVE_TICKLE,
    MOVE_NASTY_PLOT,
    MOVE_ROLE_PLAY,
    MOVE_ASTONISH,
    MOVE_GRASS_WHISTLE,
    MOVE_MAGICAL_LEAF,
    MOVE_BULLET_SEED,
    MOVE_LEAF_STORM,
    MOVE_DISARMING_VOICE,
    MOVE_SPIKY_SHIELD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PANSAGE

#if P_FAMILY_PANSEAR
static const u16 sPansearEggMoveLearnset[] = {
    MOVE_HEAT_WAVE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PANSEAR

#if P_FAMILY_PANPOUR
static const u16 sPanpourEggMoveLearnset[] = {
    MOVE_COVET,
    MOVE_LOW_KICK,
    MOVE_TICKLE,
    MOVE_NASTY_PLOT,
    MOVE_ROLE_PLAY,
    MOVE_ASTONISH,
    MOVE_AQUA_RING,
    MOVE_AQUA_TAIL,
    MOVE_MUD_SPORT,
    MOVE_HYDRO_PUMP,
    MOVE_DISARMING_VOICE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PANPOUR

#if P_FAMILY_MUNNA
static const u16 sMunnaEggMoveLearnset[] = {
    MOVE_SLEEP_TALK,
    MOVE_SECRET_POWER,
    MOVE_BARRIER,
    MOVE_MAGIC_COAT,
    MOVE_HELPING_HAND,
    MOVE_BATON_PASS,
    MOVE_SWIFT,
    MOVE_CURSE,
    MOVE_SONIC_BOOM,
    MOVE_HEALING_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MUNNA

#if P_FAMILY_PIDOVE
static const u16 sPidoveEggMoveLearnset[] = {
    MOVE_STEEL_WING,
    MOVE_HYPNOSIS,
    MOVE_UPROAR,
    MOVE_BESTOW,
    MOVE_WISH,
    MOVE_MORNING_SUN,
    MOVE_LUCKY_CHANT,
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PIDOVE

#if P_FAMILY_BLITZLE
static const u16 sBlitzleEggMoveLearnset[] = {
    MOVE_HIGH_HORSEPOWER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BLITZLE

#if P_FAMILY_ROGGENROLA
static const u16 sRoggenrolaEggMoveLearnset[] = {
    MOVE_HEAVY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROGGENROLA

#if P_FAMILY_WOOBAT
static const u16 sWoobatEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WOOBAT

#if P_FAMILY_DRILBUR
static const u16 sDrilburEggMoveLearnset[] = {
    MOVE_IRON_DEFENSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRILBUR

#if P_FAMILY_AUDINO
static const u16 sAudinoEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_HEAL_BELL,
    MOVE_LUCKY_CHANT,
    MOVE_ENCORE,
    MOVE_BESTOW,
    MOVE_SWEET_KISS,
    MOVE_YAWN,
    MOVE_SLEEP_TALK,
    MOVE_HEALING_WISH,
    MOVE_AMNESIA,
    MOVE_DRAINING_KISS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_AUDINO

#if P_FAMILY_TIMBURR
static const u16 sTimburrEggMoveLearnset[] = {
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TIMBURR

#if P_FAMILY_TYMPOLE
static const u16 sTympoleEggMoveLearnset[] = {
    MOVE_EARTH_POWER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TYMPOLE

#if P_FAMILY_SEWADDLE
static const u16 sSewaddleEggMoveLearnset[] = {
    MOVE_SCREECH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SEWADDLE

#if P_FAMILY_VENIPEDE
static const u16 sVenipedeEggMoveLearnset[] = {
    MOVE_TOXIC_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VENIPEDE

#if P_FAMILY_COTTONEE
static const u16 sCottoneeEggMoveLearnset[] = {
    MOVE_ENCORE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_COTTONEE

#if P_FAMILY_PETILIL
static const u16 sPetililEggMoveLearnset[] = {
    MOVE_GRASS_WHISTLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PETILIL

#if P_FAMILY_BASCULIN
static const u16 sBasculinEggMoveLearnset[] = {
    MOVE_SWIFT,
    MOVE_BUBBLE_BEAM,
    MOVE_MUD_SHOT,
    MOVE_MUDDY_WATER,
    MOVE_AGILITY,
    MOVE_WHIRLPOOL,
    MOVE_RAGE,
    MOVE_BRINE,
    MOVE_REVENGE,
    MOVE_HEAD_SMASH,
    MOVE_UNAVAILABLE,
};
#if P_HISUIAN_FORMS
static const u16 sBasculinWhiteStripedEggMoveLearnset[] = {
    MOVE_ENDEAVOR,
    MOVE_LAST_RESPECTS,
    MOVE_UNAVAILABLE,
};
#endif //P_HISUIAN_FORMS
#endif //P_FAMILY_BASCULIN

#if P_FAMILY_SANDILE
static const u16 sSandileEggMoveLearnset[] = {
    MOVE_FIRE_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SANDILE

#if P_FAMILY_DARUMAKA
static const u16 sDarumakaEggMoveLearnset[] = {
    MOVE_SLEEP_TALK,
    MOVE_FOCUS_PUNCH,
    MOVE_FOCUS_ENERGY,
    MOVE_ENDURE,
    MOVE_HAMMER_ARM,
    MOVE_TAKE_DOWN,
    MOVE_FLAME_WHEEL,
    MOVE_ENCORE,
    MOVE_YAWN,
    MOVE_SNATCH,
    MOVE_EXTRASENSORY,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sDarumakaGalarEggMoveLearnset[] = {
    MOVE_FOCUS_PUNCH,
    MOVE_HAMMER_ARM,
    MOVE_TAKE_DOWN,
    MOVE_FLAME_WHEEL,
    MOVE_YAWN,
    MOVE_FREEZE_DRY,
    MOVE_INCINERATE,
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_DARUMAKA

#if P_FAMILY_MARACTUS
static const u16 sMaractusEggMoveLearnset[] = {
    MOVE_BULLET_SEED,
    MOVE_BOUNCE,
    MOVE_WORRY_SEED,
    MOVE_LEECH_SEED,
    MOVE_SEED_BOMB,
    MOVE_WOOD_HAMMER,
    MOVE_SPIKES,
    MOVE_GRASS_WHISTLE,
    MOVE_GRASSY_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MARACTUS

#if P_FAMILY_DWEBBLE
static const u16 sDwebbleEggMoveLearnset[] = {
    MOVE_ENDURE,
    MOVE_IRON_DEFENSE,
    MOVE_NIGHT_SLASH,
    MOVE_SAND_TOMB,
    MOVE_COUNTER,
    MOVE_CURSE,
    MOVE_SPIKES,
    MOVE_BLOCK,
    MOVE_WIDE_GUARD,
    MOVE_ROTOTILLER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DWEBBLE

#if P_FAMILY_SCRAGGY
static const u16 sScraggyEggMoveLearnset[] = {
    MOVE_DRAGON_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SCRAGGY

#if P_FAMILY_SIGILYPH
static const u16 sSigilyphEggMoveLearnset[] = {
    MOVE_ANCIENT_POWER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SIGILYPH

#if P_FAMILY_YAMASK
static const u16 sYamaskEggMoveLearnset[] = {
    MOVE_MEMENTO,
    MOVE_FAKE_TEARS,
    MOVE_NASTY_PLOT,
    MOVE_ENDURE,
    MOVE_HEAL_BLOCK,
    MOVE_IMPRISON,
    MOVE_NIGHTMARE,
    MOVE_DISABLE,
    MOVE_ALLY_SWITCH,
    MOVE_TOXIC_SPIKES,
    MOVE_CRAFTY_SHIELD,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sYamaskGalarEggMoveLearnset[] = {
    MOVE_MEMENTO,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_YAMASK

#if P_FAMILY_TIRTOUGA
static const u16 sTirtougaEggMoveLearnset[] = {
    MOVE_LIQUIDATION,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TIRTOUGA

#if P_FAMILY_ARCHEN
static const u16 sArchenEggMoveLearnset[] = {
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ARCHEN

#if P_FAMILY_TRUBBISH
static const u16 sTrubbishEggMoveLearnset[] = {
    MOVE_SELF_DESTRUCT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TRUBBISH

#if P_FAMILY_ZORUA
static const u16 sZoruaEggMoveLearnset[] = {
    MOVE_DARK_PULSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ZORUA

#if P_FAMILY_MINCCINO
static const u16 sMinccinoEggMoveLearnset[] = {
    MOVE_AQUA_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MINCCINO

#if P_FAMILY_GOTHITA
static const u16 sGothitaEggMoveLearnset[] = {
    MOVE_DARK_PULSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GOTHITA

#if P_FAMILY_SOLOSIS
static const u16 sSolosisEggMoveLearnset[] = {
    MOVE_ACID_ARMOR,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SOLOSIS

#if P_FAMILY_DUCKLETT
static const u16 sDucklettEggMoveLearnset[] = {
    MOVE_MIRROR_MOVE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DUCKLETT

#if P_FAMILY_VANILLITE
static const u16 sVanilliteEggMoveLearnset[] = {
    MOVE_WATER_PULSE,
    MOVE_NATURAL_GIFT,
    MOVE_IMPRISON,
    MOVE_AUTOTOMIZE,
    MOVE_IRON_DEFENSE,
    MOVE_MAGNET_RISE,
    MOVE_ICE_SHARD,
    MOVE_POWDER_SNOW,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VANILLITE

#if P_FAMILY_DEERLING
static const u16 sDeerlingEggMoveLearnset[] = {
    MOVE_HEADBUTT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DEERLING

#if P_FAMILY_EMOLGA
static const u16 sEmolgaEggMoveLearnset[] = {
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_EMOLGA

#if P_FAMILY_KARRABLAST
static const u16 sKarrablastEggMoveLearnset[] = {
    MOVE_MEGAHORN,
    MOVE_PURSUIT,
    MOVE_COUNTER,
    MOVE_HORN_ATTACK,
    MOVE_FEINT_ATTACK,
    MOVE_BUG_BITE,
    MOVE_SCREECH,
    MOVE_KNOCK_OFF,
    MOVE_DRILL_RUN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KARRABLAST

#if P_FAMILY_FOONGUS
static const u16 sFoongusEggMoveLearnset[] = {
    MOVE_GASTRO_ACID,
    MOVE_GROWTH,
    MOVE_POISON_POWDER,
    MOVE_STUN_SPORE,
    MOVE_ROLLOUT,
    MOVE_DEFENSE_CURL,
    MOVE_ENDURE,
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FOONGUS

#if P_FAMILY_FRILLISH
static const u16 sFrillishEggMoveLearnset[] = {
    MOVE_PAIN_SPLIT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FRILLISH

#if P_FAMILY_ALOMOMOLA
static const u16 sAlomomolaEggMoveLearnset[] = {
    MOVE_REFRESH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ALOMOMOLA

#if P_FAMILY_JOLTIK
static const u16 sJoltikEggMoveLearnset[] = {
    MOVE_CROSS_POISON,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_JOLTIK

#if P_FAMILY_FERROSEED
static const u16 sFerroseedEggMoveLearnset[] = {
    MOVE_BULLET_SEED,
    MOVE_LEECH_SEED,
    MOVE_SPIKES,
    MOVE_WORRY_SEED,
    MOVE_SEED_BOMB,
    MOVE_GRAVITY,
    MOVE_ROCK_CLIMB,
    MOVE_STEALTH_ROCK,
    MOVE_ACID_SPRAY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FERROSEED

#if P_FAMILY_ELGYEM
static const u16 sElgyemEggMoveLearnset[] = {
    MOVE_SKILL_SWAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ELGYEM

#if P_FAMILY_LITWICK
static const u16 sLitwickEggMoveLearnset[] = {
    MOVE_CAPTIVATE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LITWICK

#if P_FAMILY_AXEW
static const u16 sAxewEggMoveLearnset[] = {
    MOVE_COUNTER,
    MOVE_FOCUS_ENERGY,
    MOVE_REVERSAL,
    MOVE_ENDURE,
    MOVE_RAZOR_WIND,
    MOVE_NIGHT_SLASH,
    MOVE_ENDEAVOR,
    MOVE_IRON_TAIL,
    MOVE_DRAGON_PULSE,
    MOVE_HARDEN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_AXEW

#if P_FAMILY_CUBCHOO
static const u16 sCubchooEggMoveLearnset[] = {
    MOVE_YAWN,
    MOVE_AVALANCHE,
    MOVE_ENCORE,
    MOVE_ICE_PUNCH,
    MOVE_NIGHT_SLASH,
    MOVE_ASSURANCE,
    MOVE_SLEEP_TALK,
    MOVE_FOCUS_PUNCH,
    MOVE_PLAY_ROUGH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CUBCHOO

#if P_FAMILY_SHELMET
static const u16 sShelmetEggMoveLearnset[] = {
    MOVE_ENDURE,
    MOVE_BATON_PASS,
    MOVE_DOUBLE_EDGE,
    MOVE_ENCORE,
    MOVE_GUARD_SPLIT,
    MOVE_MIND_READER,
    MOVE_MUD_SLAP,
    MOVE_SPIKES,
    MOVE_FEINT,
    MOVE_PURSUIT,
    MOVE_TOXIC_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHELMET

#if P_FAMILY_STUNFISK
static const u16 sStunfiskEggMoveLearnset[] = {
    MOVE_SHOCK_WAVE,
    MOVE_EARTH_POWER,
    MOVE_YAWN,
    MOVE_SLEEP_TALK,
    MOVE_ASTONISH,
    MOVE_CURSE,
    MOVE_SPITE,
    MOVE_SPARK,
    MOVE_PAIN_SPLIT,
    MOVE_EERIE_IMPULSE,
    MOVE_REFLECT_TYPE,
    MOVE_ME_FIRST,
    MOVE_UNAVAILABLE,
};
#if P_GALARIAN_FORMS
static const u16 sStunfiskGalarEggMoveLearnset[] = {
    MOVE_BIND,
    MOVE_YAWN,
    MOVE_ASTONISH,
    MOVE_CURSE,
    MOVE_SPITE,
    MOVE_COUNTER,
    MOVE_PAIN_SPLIT,
    MOVE_REFLECT_TYPE,
    MOVE_UNAVAILABLE,
};
#endif //P_GALARIAN_FORMS
#endif //P_FAMILY_STUNFISK

#if P_FAMILY_MIENFOO
static const u16 sMienfooEggMoveLearnset[] = {
    MOVE_ENDURE,
    MOVE_VITAL_THROW,
    MOVE_BATON_PASS,
    MOVE_SMELLING_SALTS,
    MOVE_LOW_KICK,
    MOVE_FEINT,
    MOVE_ME_FIRST,
    MOVE_KNOCK_OFF,
    MOVE_ALLY_SWITCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MIENFOO

#if P_FAMILY_DRUDDIGON
static const u16 sDruddigonEggMoveLearnset[] = {
    MOVE_FIRE_FANG,
    MOVE_THUNDER_FANG,
    MOVE_CRUSH_CLAW,
    MOVE_FEINT_ATTACK,
    MOVE_PURSUIT,
    MOVE_IRON_TAIL,
    MOVE_POISON_TAIL,
    MOVE_SNATCH,
    MOVE_METAL_CLAW,
    MOVE_GLARE,
    MOVE_SUCKER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRUDDIGON

#if P_FAMILY_PAWNIARD
static const u16 sPawniardEggMoveLearnset[] = {
    MOVE_REVENGE,
    MOVE_SUCKER_PUNCH,
    MOVE_PURSUIT,
    MOVE_HEADBUTT,
    MOVE_STEALTH_ROCK,
    MOVE_PSYCHO_CUT,
    MOVE_MEAN_LOOK,
    MOVE_QUICK_GUARD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PAWNIARD

#if P_FAMILY_BOUFFALANT
static const u16 sBouffalantEggMoveLearnset[] = {
    MOVE_IRON_HEAD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BOUFFALANT

#if P_FAMILY_RUFFLET
static const u16 sRuffletEggMoveLearnset[] = {
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RUFFLET

#if P_FAMILY_VULLABY
static const u16 sVullabyEggMoveLearnset[] = {
    MOVE_STEEL_WING,
    MOVE_MEAN_LOOK,
    MOVE_ROOST,
    MOVE_SCARY_FACE,
    MOVE_KNOCK_OFF,
    MOVE_FAKE_TEARS,
    MOVE_FOUL_PLAY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VULLABY

#if P_FAMILY_HEATMOR
static const u16 sHeatmorEggMoveLearnset[] = {
    MOVE_HEAT_WAVE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HEATMOR

#if P_FAMILY_DURANT
static const u16 sDurantEggMoveLearnset[] = {
    MOVE_SCREECH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DURANT

#if P_FAMILY_DEINO
static const u16 sDeinoEggMoveLearnset[] = {
    MOVE_FIRE_FANG,
    MOVE_THUNDER_FANG,
    MOVE_ICE_FANG,
    MOVE_DOUBLE_HIT,
    MOVE_ASTONISH,
    MOVE_EARTH_POWER,
    MOVE_SCREECH,
    MOVE_HEAD_SMASH,
    MOVE_ASSURANCE,
    MOVE_DARK_PULSE,
    MOVE_BELCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DEINO

#if P_FAMILY_LARVESTA
static const u16 sLarvestaEggMoveLearnset[] = {
    MOVE_MORNING_SUN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LARVESTA

#if P_FAMILY_CHESPIN
static const u16 sChespinEggMoveLearnset[] = {
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHESPIN

#if P_FAMILY_FENNEKIN
static const u16 sFennekinEggMoveLearnset[] = {
    MOVE_HYPNOSIS,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FENNEKIN

#if P_FAMILY_FROAKIE
static const u16 sFroakieEggMoveLearnset[] = {
    MOVE_TOXIC_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FROAKIE

#if P_FAMILY_BUNNELBY
static const u16 sBunnelbyEggMoveLearnset[] = {
    MOVE_SPIKES,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BUNNELBY

#if P_FAMILY_FLETCHLING
static const u16 sFletchlingEggMoveLearnset[] = {
    MOVE_BLAZE_KICK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FLETCHLING

#if P_FAMILY_SCATTERBUG
static const u16 sScatterbugEggMoveLearnset[] = {
    MOVE_RAGE_POWDER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SCATTERBUG

#if P_FAMILY_LITLEO
static const u16 sLitleoEggMoveLearnset[] = {
    MOVE_FLARE_BLITZ,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LITLEO

#if P_FAMILY_FLABEBE
static const u16 sFlabebeEggMoveLearnset[] = {
    MOVE_CAPTIVATE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FLABEBE

#if P_FAMILY_SKIDDO
static const u16 sSkiddoEggMoveLearnset[] = {
    MOVE_MILK_DRINK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKIDDO

#if P_FAMILY_PANCHAM
static const u16 sPanchamEggMoveLearnset[] = {
    MOVE_STORM_THROW,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PANCHAM

#if P_FAMILY_FURFROU
static const u16 sFurfrouEggMoveLearnset[] = {
    MOVE_ROLE_PLAY,
    MOVE_WORK_UP,
    MOVE_MIMIC,
    MOVE_CAPTIVATE,
    MOVE_REFRESH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FURFROU

#if P_FAMILY_ESPURR
static const u16 sEspurrEggMoveLearnset[] = {
    MOVE_ASSIST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ESPURR

#if P_FAMILY_HONEDGE
static const u16 sHonedgeEggMoveLearnset[] = {
    MOVE_WIDE_GUARD,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HONEDGE

#if P_FAMILY_SPRITZEE
static const u16 sSpritzeeEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPRITZEE

#if P_FAMILY_SWIRLIX
static const u16 sSwirlixEggMoveLearnset[] = {
    MOVE_STICKY_WEB,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SWIRLIX

#if P_FAMILY_INKAY
static const u16 sInkayEggMoveLearnset[] = {
    MOVE_CAMOUFLAGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_INKAY

#if P_FAMILY_BINACLE
static const u16 sBinacleEggMoveLearnset[] = {
    MOVE_TICKLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BINACLE

#if P_FAMILY_SKRELP
static const u16 sSkrelpEggMoveLearnset[] = {
    MOVE_ACID_ARMOR,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKRELP

#if P_FAMILY_CLAUNCHER
static const u16 sClauncherEggMoveLearnset[] = {
    MOVE_AQUA_JET,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CLAUNCHER

#if P_FAMILY_HELIOPTILE
static const u16 sHelioptileEggMoveLearnset[] = {
    MOVE_CAMOUFLAGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HELIOPTILE

#if P_FAMILY_TYRUNT
static const u16 sTyruntEggMoveLearnset[] = {
    MOVE_FIRE_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TYRUNT

#if P_FAMILY_AMAURA
static const u16 sAmauraEggMoveLearnset[] = {
    MOVE_DISCHARGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_AMAURA

#if P_FAMILY_HAWLUCHA
static const u16 sHawluchaEggMoveLearnset[] = {
    MOVE_AGILITY,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HAWLUCHA

#if P_FAMILY_DEDENNE
static const u16 sDedenneEggMoveLearnset[] = {
    MOVE_EERIE_IMPULSE,
    MOVE_COVET,
    MOVE_HELPING_HAND,
    MOVE_NATURAL_GIFT,
    MOVE_TEARFUL_LOOK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DEDENNE

#if P_FAMILY_GOOMY
static const u16 sGoomyEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GOOMY

#if P_FAMILY_KLEFKI
static const u16 sKlefkiEggMoveLearnset[] = {
    MOVE_SWITCHEROO,
    MOVE_THIEF,
    MOVE_LOCK_ON,
    MOVE_IRON_DEFENSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KLEFKI

#if P_FAMILY_PHANTUMP
static const u16 sPhantumpEggMoveLearnset[] = {
    MOVE_GRUDGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PHANTUMP

#if P_FAMILY_PUMPKABOO
static const u16 sPumpkabooEggMoveLearnset[] = {
    MOVE_DISABLE,
    MOVE_BESTOW,
    MOVE_DESTINY_BOND,
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PUMPKABOO

#if P_FAMILY_BERGMITE
static const u16 sBergmiteEggMoveLearnset[] = {
    MOVE_RECOVER,
    MOVE_MIST,
    MOVE_BARRIER,
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BERGMITE

#if P_FAMILY_NOIBAT
static const u16 sNoibatEggMoveLearnset[] = {
    MOVE_OUTRAGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NOIBAT

#if P_FAMILY_ROWLET
static const u16 sRowletEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROWLET

#if P_FAMILY_LITTEN
static const u16 sLittenEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LITTEN

#if P_FAMILY_POPPLIO
static const u16 sPopplioEggMoveLearnset[] = {
    MOVE_PERISH_SONG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_POPPLIO

#if P_FAMILY_PIKIPEK
static const u16 sPikipekEggMoveLearnset[] = {
    MOVE_TAILWIND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PIKIPEK

#if P_FAMILY_YUNGOOS
static const u16 sYungoosEggMoveLearnset[] = {
    MOVE_REVENGE,
    MOVE_LAST_RESORT,
    MOVE_FIRE_FANG,
    MOVE_ICE_FANG,
    MOVE_THUNDER_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_YUNGOOS

#if P_FAMILY_GRUBBIN
static const u16 sGrubbinEggMoveLearnset[] = {
    MOVE_ELECTROWEB,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GRUBBIN

#if P_FAMILY_CRABRAWLER
static const u16 sCrabrawlerEggMoveLearnset[] = {
    MOVE_WIDE_GUARD,
    MOVE_SUPERPOWER,
    MOVE_ENDEAVOR,
    MOVE_AMNESIA,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CRABRAWLER

#if P_FAMILY_ORICORIO
static const u16 sOricorioEggMoveLearnset[] = {
    MOVE_PLUCK,
    MOVE_TAILWIND,
    MOVE_SAFEGUARD,
    MOVE_CAPTIVATE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ORICORIO

#if P_FAMILY_CUTIEFLY
static const u16 sCutieflyEggMoveLearnset[] = {
    MOVE_POWDER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CUTIEFLY

#if P_FAMILY_ROCKRUFF
static const u16 sRockruffEggMoveLearnset[] = {
    MOVE_FIRE_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROCKRUFF

#if P_FAMILY_WISHIWASHI
static const u16 sWishiwashiEggMoveLearnset[] = {
    MOVE_MUDDY_WATER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WISHIWASHI

#if P_FAMILY_MAREANIE
static const u16 sMareanieEggMoveLearnset[] = {
    MOVE_STOCKPILE,
    MOVE_SWALLOW,
    MOVE_SPIT_UP,
    MOVE_HAZE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MAREANIE

#if P_FAMILY_MUDBRAY
static const u16 sMudbrayEggMoveLearnset[] = {
    MOVE_BODY_SLAM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MUDBRAY

#if P_FAMILY_DEWPIDER
static const u16 sDewpiderEggMoveLearnset[] = {
    MOVE_STICKY_WEB,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DEWPIDER

#if P_FAMILY_FOMANTIS
static const u16 sFomantisEggMoveLearnset[] = {
    MOVE_WEATHER_BALL,
    MOVE_GIGA_DRAIN,
    MOVE_AROMATHERAPY,
    MOVE_DEFOG,
    MOVE_LEAF_STORM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FOMANTIS

#if P_FAMILY_MORELULL
static const u16 sMorelullEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MORELULL

#if P_FAMILY_SALANDIT
static const u16 sSalanditEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SALANDIT

#if P_FAMILY_STUFFUL
static const u16 sStuffulEggMoveLearnset[] = {
    MOVE_FORCE_PALM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_STUFFUL

#if P_FAMILY_BOUNSWEET
static const u16 sBounsweetEggMoveLearnset[] = {
    MOVE_PLAY_ROUGH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BOUNSWEET

#if P_FAMILY_COMFEY
static const u16 sComfeyEggMoveLearnset[] = {
    MOVE_AMNESIA,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_COMFEY

#if P_FAMILY_ORANGURU
static const u16 sOranguruEggMoveLearnset[] = {
    MOVE_EXTRASENSORY,
    MOVE_WONDER_ROOM,
    MOVE_PSYCHIC_TERRAIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ORANGURU

#if P_FAMILY_PASSIMIAN
static const u16 sPassimianEggMoveLearnset[] = {
    MOVE_SEISMIC_TOSS,
    MOVE_VITAL_THROW,
    MOVE_QUICK_GUARD,
    MOVE_IRON_HEAD,
    MOVE_QUICK_ATTACK,
    MOVE_FEINT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PASSIMIAN

#if P_FAMILY_WIMPOD
static const u16 sWimpodEggMoveLearnset[] = {
    MOVE_SPIKES,
    MOVE_METAL_CLAW,
    MOVE_WIDE_GUARD,
    MOVE_HARDEN,
    MOVE_AQUA_JET,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WIMPOD

#if P_FAMILY_SANDYGAST
static const u16 sSandygastEggMoveLearnset[] = {
    MOVE_ANCIENT_POWER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SANDYGAST

#if P_FAMILY_PYUKUMUKU
static const u16 sPyukumukuEggMoveLearnset[] = {
    MOVE_ENDURE,
    MOVE_VENOM_DRENCH,
    MOVE_BESTOW,
    MOVE_TICKLE,
    MOVE_SPITE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PYUKUMUKU

#if P_FAMILY_KOMALA
static const u16 sKomalaEggMoveLearnset[] = {
    MOVE_CHARM,
    MOVE_WISH,
    MOVE_PLAY_ROUGH,
    MOVE_SING,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KOMALA

#if P_FAMILY_TURTONATOR
static const u16 sTurtonatorEggMoveLearnset[] = {
    MOVE_FIRE_SPIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TURTONATOR

#if P_FAMILY_TOGEDEMARU
static const u16 sTogedemaruEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TOGEDEMARU

#if P_FAMILY_MIMIKYU
static const u16 sMimikyuEggMoveLearnset[] = {
    MOVE_DESTINY_BOND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MIMIKYU

#if P_FAMILY_BRUXISH
static const u16 sBruxishEggMoveLearnset[] = {
    MOVE_WATER_PULSE,
    MOVE_POISON_FANG,
    MOVE_ICE_FANG,
    MOVE_RAGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BRUXISH

#if P_FAMILY_DRAMPA
static const u16 sDrampaEggMoveLearnset[] = {
    MOVE_HURRICANE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DRAMPA

#if P_FAMILY_JANGMO_O
static const u16 sJangmoOEggMoveLearnset[] = {
    MOVE_REVERSAL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_JANGMO_O

#if P_FAMILY_GROOKEY
static const u16 sGrookeyEggMoveLearnset[] = {
    MOVE_LEECH_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GROOKEY

#if P_FAMILY_SCORBUNNY
static const u16 sScorbunnyEggMoveLearnset[] = {
    MOVE_HIGH_JUMP_KICK,
    MOVE_SAND_ATTACK,
    MOVE_SUCKER_PUNCH,
    MOVE_SUPER_FANG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SCORBUNNY

#if P_FAMILY_SOBBLE
static const u16 sSobbleEggMoveLearnset[] = {
    MOVE_AQUA_JET,
    MOVE_DOUBLE_TEAM,
    MOVE_AQUA_RING,
    MOVE_MIST,
    MOVE_HAZE,
    MOVE_ICE_SHARD,
    MOVE_FELL_STINGER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SOBBLE

#if P_FAMILY_SKWOVET
static const u16 sSkwovetEggMoveLearnset[] = {
    MOVE_ROLLOUT,
    MOVE_DEFENSE_CURL,
    MOVE_LAST_RESORT,
    MOVE_BELLY_DRUM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SKWOVET

#if P_FAMILY_ROOKIDEE
static const u16 sRookideeEggMoveLearnset[] = {
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROOKIDEE

#if P_FAMILY_BLIPBUG
static const u16 sBlipbugEggMoveLearnset[] = {
    MOVE_RECOVER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BLIPBUG

#if P_FAMILY_NICKIT
static const u16 sNickitEggMoveLearnset[] = {
    MOVE_KNOCK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NICKIT

#if P_FAMILY_GOSSIFLEUR
static const u16 sGossifleurEggMoveLearnset[] = {
    MOVE_GROWTH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GOSSIFLEUR

#if P_FAMILY_WOOLOO
static const u16 sWoolooEggMoveLearnset[] = {
    MOVE_COUNTER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WOOLOO

#if P_FAMILY_CHEWTLE
static const u16 sChewtleEggMoveLearnset[] = {
    MOVE_DRAGON_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHEWTLE

#if P_FAMILY_YAMPER
static const u16 sYamperEggMoveLearnset[] = {
    MOVE_FLAME_CHARGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_YAMPER

#if P_FAMILY_ROLYCOLY
static const u16 sRolycolyEggMoveLearnset[] = {
    MOVE_MUD_SLAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ROLYCOLY

#if P_FAMILY_APPLIN
static const u16 sApplinEggMoveLearnset[] = {
    MOVE_SUCKER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_APPLIN

#if P_FAMILY_SILICOBRA
static const u16 sSilicobraEggMoveLearnset[] = {
    MOVE_DRAGON_RUSH,
    MOVE_MUD_SLAP,
    MOVE_LAST_RESORT,
    MOVE_BELCH,
    MOVE_POISON_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SILICOBRA

#if P_FAMILY_CRAMORANT
static const u16 sCramorantEggMoveLearnset[] = {
    MOVE_DEFOG,
    MOVE_AERIAL_ACE,
    MOVE_FEATHER_DANCE,
    MOVE_AQUA_RING,
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CRAMORANT

#if P_FAMILY_ARROKUDA
static const u16 sArrokudaEggMoveLearnset[] = {
    MOVE_NIGHT_SLASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ARROKUDA

#if P_FAMILY_TOXEL
static const u16 sToxelEggMoveLearnset[] = {
    MOVE_METAL_SOUND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TOXEL

#if P_FAMILY_SIZZLIPEDE
static const u16 sSizzlipedeEggMoveLearnset[] = {
    MOVE_STRUGGLE_BUG,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SIZZLIPEDE

#if P_FAMILY_CLOBBOPUS
static const u16 sClobbopusEggMoveLearnset[] = {
    MOVE_POWER_UP_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CLOBBOPUS

#if P_FAMILY_HATENNA
static const u16 sHatennaEggMoveLearnset[] = {
    MOVE_NUZZLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_HATENNA

#if P_FAMILY_MILCERY
static const u16 sMilceryEggMoveLearnset[] = {
    MOVE_BABY_DOLL_EYES,
    MOVE_LAST_RESORT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MILCERY

#if P_FAMILY_PINCURCHIN
static const u16 sPincurchinEggMoveLearnset[] = {
    MOVE_MEMENTO,
    MOVE_SUCKER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PINCURCHIN

#if P_FAMILY_SNOM
static const u16 sSnomEggMoveLearnset[] = {
    MOVE_FAIRY_WIND,
    MOVE_MIRROR_COAT,
    MOVE_BUG_BITE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SNOM

#if P_FAMILY_STONJOURNER
static const u16 sStonjournerEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_STONJOURNER

#if P_FAMILY_EISCUE
static const u16 sEiscueEggMoveLearnset[] = {
    MOVE_SOAK,
    MOVE_AQUA_RING,
    MOVE_BELLY_DRUM,
    MOVE_DOUBLE_EDGE,
    MOVE_ICICLE_CRASH,
    MOVE_HEAD_SMASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_EISCUE

#if P_FAMILY_INDEEDEE
static const u16 sIndeedeeEggMoveLearnset[] = {
    MOVE_PSYCH_UP,
    MOVE_FAKE_OUT,
    MOVE_EXTRASENSORY,
    MOVE_UNAVAILABLE,
};

static const u16 sIndeedeeFEggMoveLearnset[] = {
    MOVE_PSYCH_UP,
    MOVE_FAKE_OUT,
    MOVE_PSYCHO_SHIFT,
    MOVE_HEAL_PULSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_INDEEDEE

#if P_FAMILY_MORPEKO
static const u16 sMorpekoEggMoveLearnset[] = {
    MOVE_SWAGGER,
    MOVE_SUPER_FANG,
    MOVE_CHARGE,
    MOVE_TICKLE,
    MOVE_RAPID_SPIN,
    MOVE_QUASH,
    MOVE_PARTING_SHOT,
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MORPEKO

#if P_FAMILY_CUFANT
static const u16 sCufantEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CUFANT

#if P_FAMILY_DURALUDON
static const u16 sDuraludonEggMoveLearnset[] = {
    MOVE_SLASH,
    MOVE_NIGHT_SLASH,
    MOVE_MIRROR_COAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DURALUDON

#if P_FAMILY_DREEPY
static const u16 sDreepyEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_GRUDGE,
    MOVE_CONFUSE_RAY,
    MOVE_DOUBLE_TEAM,
    MOVE_DISABLE,
    MOVE_DRAGON_TAIL,
    MOVE_SUCKER_PUNCH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DREEPY

#if P_FAMILY_SPRIGATITO
static const u16 sSprigatitoEggMoveLearnset[] = {
    MOVE_COPYCAT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SPRIGATITO

#if P_FAMILY_FUECOCO
static const u16 sFuecocoEggMoveLearnset[] = {
    MOVE_SLACK_OFF,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FUECOCO

#if P_FAMILY_QUAXLY
static const u16 sQuaxlyEggMoveLearnset[] = {
    MOVE_RAPID_SPIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_QUAXLY

#if P_FAMILY_LECHONK
static const u16 sLechonkEggMoveLearnset[] = {
    MOVE_ENDEAVOR,
    MOVE_SPIT_UP,
    MOVE_STOCKPILE,
    MOVE_STUFF_CHEEKS,
    MOVE_SWALLOW,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_LECHONK

#if P_FAMILY_TAROUNTULA
static const u16 sTarountulaEggMoveLearnset[] = {
    MOVE_LUNGE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TAROUNTULA

#if P_FAMILY_NYMBLE
static const u16 sNymbleEggMoveLearnset[] = {
    MOVE_SKITTER_SMACK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NYMBLE

#if P_FAMILY_PAWMI
static const u16 sPawmiEggMoveLearnset[] = {
    MOVE_FAKE_OUT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_PAWMI

#if P_FAMILY_TANDEMAUS
static const u16 sTandemausEggMoveLearnset[] = {
    MOVE_AFTER_YOU,
    MOVE_BATON_PASS,
    MOVE_BITE,
    MOVE_FEINT,
    MOVE_SWITCHEROO,
    MOVE_TICKLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TANDEMAUS

#if P_FAMILY_FIDOUGH
static const u16 sFidoughEggMoveLearnset[] = {
    MOVE_WISH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FIDOUGH

#if P_FAMILY_SMOLIV
static const u16 sSmolivEggMoveLearnset[] = {
    MOVE_WEATHER_BALL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SMOLIV

#if P_FAMILY_SQUAWKABILLY
static const u16 sSquawkabillyEggMoveLearnset[] = {
    MOVE_DOUBLE_EDGE,
    MOVE_FINAL_GAMBIT,
    MOVE_FLATTER,
    MOVE_PARTING_SHOT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SQUAWKABILLY

#if P_FAMILY_NACLI
static const u16 sNacliEggMoveLearnset[] = {
    MOVE_ANCIENT_POWER,
    MOVE_CURSE,
    MOVE_FISSURE,
    MOVE_POWER_GEM,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_NACLI

#if P_FAMILY_CHARCADET
static const u16 sCharcadetEggMoveLearnset[] = {
    MOVE_DESTINY_BOND,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CHARCADET

#if P_FAMILY_TADBULB
static const u16 sTadbulbEggMoveLearnset[] = {
    MOVE_MUDDY_WATER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TADBULB

#if P_FAMILY_WATTREL
static const u16 sWattrelEggMoveLearnset[] = {
    MOVE_FEATHER_DANCE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WATTREL

#if P_FAMILY_MASCHIFF
static const u16 sMaschiffEggMoveLearnset[] = {
    MOVE_PLAY_ROUGH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_MASCHIFF

#if P_FAMILY_SHROODLE
static const u16 sShroodleEggMoveLearnset[] = {
    MOVE_PARTING_SHOT,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_SHROODLE

#if P_FAMILY_BRAMBLIN
static const u16 sBramblinEggMoveLearnset[] = {
    MOVE_BEAT_UP,
    MOVE_BLOCK,
    MOVE_LEECH_SEED,
    MOVE_SHADOW_SNEAK,
    MOVE_STRENGTH_SAP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BRAMBLIN

#if P_FAMILY_TOEDSCOOL
static const u16 sToedscoolEggMoveLearnset[] = {
    MOVE_ACUPRESSURE,
    MOVE_KNOCK_OFF,
    MOVE_LEECH_SEED,
    MOVE_MIRROR_COAT,
    MOVE_RAGE_POWDER,
    MOVE_RAPID_SPIN,
    MOVE_TICKLE,
    MOVE_TOXIC,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TOEDSCOOL

#if P_FAMILY_KLAWF
static const u16 sKlawfEggMoveLearnset[] = {
    MOVE_CRABHAMMER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_KLAWF

#if P_FAMILY_CAPSAKID
static const u16 sCapsakidEggMoveLearnset[] = {
    MOVE_INGRAIN,
    MOVE_LEECH_SEED,
    MOVE_RAGE_POWDER,
    MOVE_ROLLOUT,
    MOVE_WORRY_SEED,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CAPSAKID

#if P_FAMILY_RELLOR
static const u16 sRellorEggMoveLearnset[] = {
    MOVE_COSMIC_POWER,
    MOVE_MEMENTO,
    MOVE_RECOVER,
    MOVE_WEATHER_BALL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_RELLOR

#if P_FAMILY_FLITTLE
static const u16 sFlittleEggMoveLearnset[] = {
    MOVE_ALLY_SWITCH,
    MOVE_HYPNOSIS,
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FLITTLE

#if P_FAMILY_TINKATINK
static const u16 sTinkatinkEggMoveLearnset[] = {
    MOVE_ICE_HAMMER,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TINKATINK

#if P_FAMILY_WIGLETT
static const u16 sWiglettEggMoveLearnset[] = {
    MOVE_FINAL_GAMBIT,
    MOVE_MEMENTO,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_WIGLETT

#if P_FAMILY_BOMBIRDIER
static const u16 sBombirdierEggMoveLearnset[] = {
    MOVE_ROOST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_BOMBIRDIER

#if P_FAMILY_FINIZEN
static const u16 sFinizenEggMoveLearnset[] = {
    MOVE_BOOMBURST,
    MOVE_BOUNCE,
    MOVE_COUNTER,
    MOVE_HAZE,
    MOVE_TICKLE,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FINIZEN

#if P_FAMILY_VAROOM
static const u16 sVaroomEggMoveLearnset[] = {
    MOVE_TOXIC,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VAROOM

#if P_FAMILY_CYCLIZAR
static const u16 sCyclizarEggMoveLearnset[] = {
    MOVE_AQUA_TAIL,
    MOVE_IRON_TAIL,
    MOVE_KNOCK_OFF,
    MOVE_POWER_WHIP,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CYCLIZAR

#if P_FAMILY_ORTHWORM
static const u16 sOrthwormEggMoveLearnset[] = {
    MOVE_COIL,
    MOVE_CURSE,
    MOVE_METAL_BURST,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_ORTHWORM

#if P_FAMILY_GLIMMET
static const u16 sGlimmetEggMoveLearnset[] = {
    MOVE_EXPLOSION,
    MOVE_MEMENTO,
    MOVE_TOXIC,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GLIMMET

#if P_FAMILY_GREAVARD
static const u16 sGreavardEggMoveLearnset[] = {
    MOVE_YAWN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_GREAVARD

#if P_FAMILY_FLAMIGO
static const u16 sFlamigoEggMoveLearnset[] = {
    MOVE_DOUBLE_TEAM,
    MOVE_QUICK_GUARD,
    MOVE_SKY_ATTACK,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FLAMIGO

#if P_FAMILY_CETODDLE
static const u16 sCetoddleEggMoveLearnset[] = {
    MOVE_ICICLE_CRASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_CETODDLE

#if P_FAMILY_VELUZA
static const u16 sVeluzaEggMoveLearnset[] = {
    MOVE_RECOVER,
    MOVE_THRASH,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_VELUZA

#if P_FAMILY_DONDOZO
static const u16 sDondozoEggMoveLearnset[] = {
    MOVE_CURSE,
    MOVE_FISSURE,
    MOVE_THRASH,
    MOVE_YAWN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_DONDOZO

#if P_FAMILY_TATSUGIRI
static const u16 sTatsugiriEggMoveLearnset[] = {
    MOVE_BATON_PASS,
    MOVE_COUNTER,
    MOVE_RAPID_SPIN,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_TATSUGIRI

#if P_FAMILY_FRIGIBAX
static const u16 sFrigibaxEggMoveLearnset[] = {
    MOVE_AQUA_TAIL,
    MOVE_UNAVAILABLE,
};
#endif //P_FAMILY_FRIGIBAX

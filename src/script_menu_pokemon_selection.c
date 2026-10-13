#include "global.h"
#include "script.h"
#include "random.h"
#include "script_menu.h"
#include "string_util.h"
#include "strings.h"
#include "pokemon.h"
#include "constants/species.h"
#include "constants/pokemon.h"
#include "data/pokemon/form_species_tables.h"
#include "constants/flags.h"
#include "event_data.h"

static const u8 sText_Random[] = _("Random");
static const u8 sText_RandTeam[] = _("Random Team");
static const u8 sText_MysteryEgg[] = _("Mystery Egg");

enum GiftMonPool
{
    GIFT_POOL_FLANNERY,
    GIFT_POOL_JUAN,
    GIFT_POOL_NORMAN,
    GIFT_POOL_BRAWLY,
    GIFT_POOL_COUNT,
    GIFT_POOL_NONE = 0xFF,
};

struct GiftPokemon
{
    u16 species;
    u8 cost;
    u8 pool;
    u8 type1;
    u8 type2;
};

static const struct GiftPokemon sGiftPokemonList[] = {
    {SPECIES_AMAURA, 6, GIFT_POOL_NONE, TYPE_ROCK, TYPE_ICE},
    {SPECIES_ANORITH, 6, GIFT_POOL_NONE, TYPE_ROCK, TYPE_BUG},
    {SPECIES_APPLIN, 14, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_DRAGON},
    {SPECIES_ARCHEN, 16, GIFT_POOL_NORMAN, TYPE_ROCK, TYPE_FLYING},
    {SPECIES_ARON, 10, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_ROCK},
    {SPECIES_BAGON, 12, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_NONE},
    {SPECIES_BASCULIN_WHITE_STRIPED, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_BELDUM, 12, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_PSYCHIC},
    {SPECIES_BINACLE, 8, GIFT_POOL_FLANNERY, TYPE_ROCK, TYPE_WATER},
    {SPECIES_BLIPBUG, 8, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_PSYCHIC},
    {SPECIES_BLITZLE, 4, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_BONSLY, 6, GIFT_POOL_NONE, TYPE_ROCK, TYPE_NONE},
    {SPECIES_BOUNSWEET, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_BRONZOR, 10, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_PSYCHIC},
    {SPECIES_BUDEW, 14, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_POISON},
    {SPECIES_BUIZEL, 6, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_BULBASAUR, 14, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_POISON},
    {SPECIES_BUNEARY, 6, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_BUNNELBY, 8, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_BURMY, 6, GIFT_POOL_JUAN, TYPE_BUG, TYPE_NONE},
    {SPECIES_CACNEA, 8, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_CARVANHA, 8, GIFT_POOL_NONE, TYPE_WATER, TYPE_DARK},
    {SPECIES_CASTFORM, 16, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_CETODDLE, 8, GIFT_POOL_NONE, TYPE_ICE, TYPE_NONE},
    {SPECIES_CHARCADET, 14, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_CHARMANDER, 12, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_CHERUBI, 6, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_CHESPIN, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_CHEWTLE, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_ROCK},
    {SPECIES_CHIMCHAR, 14, GIFT_POOL_NONE, TYPE_FIRE, TYPE_FIGHTING},
    {SPECIES_CHINCHOU, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_ELECTRIC},
    {SPECIES_CHINGLING, 8, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_CLAMPERL, 8, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_CLAUNCHER, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_CLOBBOPUS, 6, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_CORPHISH, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_CORSOLA, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_ROCK},
    {SPECIES_COTTONEE, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_FAIRY},
    {SPECIES_CROAGUNK, 12, GIFT_POOL_NONE, TYPE_POISON, TYPE_FIGHTING},
    {SPECIES_CUBONE, 6, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_CUFANT, 10, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_NONE},
    {SPECIES_CUTIEFLY, 12, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_FAIRY},
    {SPECIES_CYNDAQUIL, 12, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_DEERLING, 10, GIFT_POOL_JUAN, TYPE_NORMAL, TYPE_GRASS},
    {SPECIES_DEWPIDER, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_BUG},
    {SPECIES_DIGLETT, 6, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_DRATINI, 12, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_NONE},
    {SPECIES_DRIFLOON, 6, GIFT_POOL_BRAWLY, TYPE_GHOST, TYPE_FLYING},
    {SPECIES_DRILBUR, 16, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_DUCKLETT, 8, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_FLYING},
    {SPECIES_DUSKULL, 8, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_NONE},
    {SPECIES_EKANS, 8, GIFT_POOL_NORMAN, TYPE_POISON, TYPE_NONE},
    {SPECIES_ELECTRIKE, 8, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_ELEKID, 8, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_ELGYEM, 6, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_EMOLGA, 10, GIFT_POOL_BRAWLY, TYPE_ELECTRIC, TYPE_FLYING},
    {SPECIES_ESPURR, 10, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_EXEGGCUTE, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_PSYCHIC},
    {SPECIES_FARFETCHD_GALAR, 10, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_FEEBAS, 8, GIFT_POOL_NONE, TYPE_WATER, TYPE_NONE},
    {SPECIES_FENNEKIN, 16, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_FIDOUGH, 12, GIFT_POOL_BRAWLY, TYPE_FAIRY, TYPE_NONE},
    {SPECIES_FLABEBE, 10, GIFT_POOL_BRAWLY, TYPE_FAIRY, TYPE_NONE},
    {SPECIES_FLETCHLING, 8, GIFT_POOL_BRAWLY, TYPE_FIRE, TYPE_FLYING},
    {SPECIES_FRIGIBAX, 10, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_ICE},
    {SPECIES_FRILLISH, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_GHOST},
    {SPECIES_FROAKIE, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_FUECOCO, 14, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_GASTLY, 8, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_POISON},
    {SPECIES_GEODUDE, 8, GIFT_POOL_NONE, TYPE_ROCK, TYPE_GROUND},
    {SPECIES_GIBLE, 16, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_GROUND},
    {SPECIES_GOOMY, 10, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_NONE},
    {SPECIES_GOSSIFLEUR, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_GOTHITA, 6, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_GREAVARD, 10, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_NONE},
    {SPECIES_GROWLITHE, 10, GIFT_POOL_NORMAN, TYPE_FIRE, TYPE_NONE},
    {SPECIES_GRUBBIN, 8, GIFT_POOL_NONE, TYPE_BUG, TYPE_NONE},
    {SPECIES_HATENNA, 8, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_HELIOPTILE, 10, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NORMAL},
    {SPECIES_HIPPOPOTAS, 10, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_HONEDGE, 16, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_GHOST},
    {SPECIES_HORSEA, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_HOUNDOUR, 10, GIFT_POOL_NONE, TYPE_DARK, TYPE_FIRE},
    {SPECIES_IMPIDIMP, 8, GIFT_POOL_NONE, TYPE_DARK, TYPE_FAIRY},
    {SPECIES_INKAY, 8, GIFT_POOL_NONE, TYPE_DARK, TYPE_PSYCHIC},
    {SPECIES_JANGMO_O, 12, GIFT_POOL_NONE, TYPE_DRAGON, TYPE_NONE},
    {SPECIES_JOLTIK, 6, GIFT_POOL_NONE, TYPE_BUG, TYPE_ELECTRIC},
    {SPECIES_KLINK, 10, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_NONE},
    {SPECIES_LARVITAR, 10, GIFT_POOL_NONE, TYPE_ROCK, TYPE_GROUND},
    {SPECIES_LILLIPUP, 8, GIFT_POOL_NORMAN, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_LITLEO, 8, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NORMAL},
    {SPECIES_LITTEN, 12, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_LITWICK, 16, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_FIRE},
    {SPECIES_LOTAD, 12, GIFT_POOL_JUAN, TYPE_WATER, TYPE_GRASS},
    {SPECIES_MACHOP, 8, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_MAGBY, 8, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_MAGNEMITE, 16, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_STEEL},
    {SPECIES_MAKUHITA, 10, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_MANKEY, 12, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_MANTYKE, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_FLYING},
    {SPECIES_MAREEP, 8, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_MASCHIFF, 12, GIFT_POOL_NORMAN, TYPE_DARK, TYPE_NONE},
    {SPECIES_MAWILE, 12, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_FAIRY},
    {SPECIES_MEDITITE, 10, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_PSYCHIC},
    {SPECIES_MEOWTH_GALAR, 8, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_NONE},
    {SPECIES_MIME_JR, 10, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_FAIRY},
    {SPECIES_MINCCINO, 6, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_MINIOR_CORE, 14, GIFT_POOL_NORMAN, TYPE_ROCK, TYPE_FLYING},
    {SPECIES_MINUN, 8, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_MISDREAVUS, 10, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_NONE},
    {SPECIES_MORELULL, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_FAIRY},
    {SPECIES_MUDBRAY, 16, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_MUDKIP, 16, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_MUNCHLAX, 12, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_MURKROW, 8, GIFT_POOL_NONE, TYPE_DARK, TYPE_FLYING},
    {SPECIES_NICKIT, 8, GIFT_POOL_NONE, TYPE_DARK, TYPE_NONE},
    {SPECIES_NINCADA, 12, GIFT_POOL_NONE, TYPE_BUG, TYPE_GROUND},
    {SPECIES_NOIBAT, 6, GIFT_POOL_NONE, TYPE_FLYING, TYPE_DRAGON},
    {SPECIES_NOSEPASS, 10, GIFT_POOL_NORMAN, TYPE_ROCK, TYPE_NONE},
    {SPECIES_NUMEL, 8, GIFT_POOL_NONE, TYPE_FIRE, TYPE_GROUND},
    {SPECIES_NYMBLE, 8, GIFT_POOL_NONE, TYPE_BUG, TYPE_NONE},
    {SPECIES_ODDISH, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_POISON},
    {SPECIES_ONIX, 10, GIFT_POOL_NORMAN, TYPE_ROCK, TYPE_GROUND},
    {SPECIES_OSHAWOTT, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_PANCHAM, 8, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_PANSEAR, 6, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_PARAS, 6, GIFT_POOL_JUAN, TYPE_BUG, TYPE_GRASS},
    {SPECIES_PHANTUMP, 10, GIFT_POOL_JUAN, TYPE_GHOST, TYPE_GRASS},
    {SPECIES_PHANPY, 10, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_PLUSLE, 8, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_PICHU, 10, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_PIKIPEK, 8, GIFT_POOL_BRAWLY, TYPE_NORMAL, TYPE_FLYING},
    {SPECIES_PINECO, 6, GIFT_POOL_NONE, TYPE_BUG, TYPE_NONE},
    {SPECIES_PIPLUP, 14, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_POLIWAG, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_PONYTA, 10, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_POOCHYENA, 10, GIFT_POOL_NORMAN, TYPE_DARK, TYPE_NONE},
    {SPECIES_POPPLIO, 16, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_PORYGON, 16, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_PSYDUCK, 8, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_PURRLOIN, 6, GIFT_POOL_NONE, TYPE_DARK, TYPE_NONE},
    {SPECIES_RALTS, 18, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_FAIRY},
    {SPECIES_REMORAID, 6, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_RIOLU, 16, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_ROCKRUFF, 8, GIFT_POOL_NONE, TYPE_ROCK, TYPE_NONE},
    {SPECIES_ROGGENROLA, 6, GIFT_POOL_NONE, TYPE_ROCK, TYPE_NONE},
    {SPECIES_ROLYCOLY, 8, GIFT_POOL_NONE, TYPE_ROCK, TYPE_NONE},
    {SPECIES_ROOKIDEE, 10, GIFT_POOL_BRAWLY, TYPE_FLYING, TYPE_NONE},
    {SPECIES_ROTOM, 18, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_GHOST},
    {SPECIES_ROWLET, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_FLYING},
    {SPECIES_RUFFLET, 10, GIFT_POOL_BRAWLY, TYPE_NORMAL, TYPE_FLYING},
    {SPECIES_SABLEYE, 8, GIFT_POOL_NORMAN, TYPE_DARK, TYPE_GHOST},
    {SPECIES_SALANDIT, 10, GIFT_POOL_NONE, TYPE_POISON, TYPE_FIRE},
    {SPECIES_SANDILE, 14, GIFT_POOL_NORMAN, TYPE_GROUND, TYPE_DARK},
    {SPECIES_SANDSHREW_ALOLA, 8, GIFT_POOL_NORMAN, TYPE_ICE, TYPE_STEEL},
    {SPECIES_SANDYGAST, 8, GIFT_POOL_NORMAN, TYPE_GHOST, TYPE_GROUND},
    {SPECIES_SCATTERBUG, 10, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_NONE},
    {SPECIES_SCRAGGY, 12, GIFT_POOL_NORMAN, TYPE_DARK, TYPE_FIGHTING},
    {SPECIES_SCYTHER, 16, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_FLYING},
    {SPECIES_SEWADDLE, 8, GIFT_POOL_JUAN, TYPE_BUG, TYPE_GRASS},
    {SPECIES_SHELLDER, 4, GIFT_POOL_NONE, TYPE_WATER, TYPE_ICE},
    {SPECIES_SHELLOS_EAST, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_SHINX, 10, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_SHROODLE, 8, GIFT_POOL_NONE, TYPE_POISON, TYPE_NORMAL},
    {SPECIES_SHROOMISH, 14, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_FIGHTING},
    {SPECIES_SHUPPET, 6, GIFT_POOL_NONE, TYPE_GHOST, TYPE_NONE},
    {SPECIES_SILICOBRA, 8, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_SIZZLIPEDE, 10, GIFT_POOL_NONE, TYPE_FIRE, TYPE_BUG},
    {SPECIES_SKIDDO, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_SKORUPI, 10, GIFT_POOL_NONE, TYPE_POISON, TYPE_BUG},
    {SPECIES_SKRELP, 6, GIFT_POOL_NONE, TYPE_POISON, TYPE_WATER},
    {SPECIES_SKWOVET, 10, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_SLAKOTH, 8, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_SLOWPOKE_GALAR, 8, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_SLUGMA, 8, GIFT_POOL_NORMAN, TYPE_FIRE, TYPE_NONE},
    {SPECIES_SMEARGLE, 4, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_SMOLIV, 8, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NORMAL},
    {SPECIES_SNEASEL, 10, GIFT_POOL_NONE, TYPE_DARK, TYPE_ICE},
    {SPECIES_SNIVY, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_SNORUNT, 6, GIFT_POOL_NONE, TYPE_ICE, TYPE_NONE},
    {SPECIES_SNOVER, 6, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_ICE},
    {SPECIES_SNUBBULL, 8, GIFT_POOL_NORMAN, TYPE_FAIRY, TYPE_NONE},
    {SPECIES_SOLOSIS, 6, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_SPHEAL, 10, GIFT_POOL_FLANNERY, TYPE_ICE, TYPE_WATER},
    {SPECIES_SPOINK, 6, GIFT_POOL_BRAWLY, TYPE_PSYCHIC, TYPE_NONE},
    {SPECIES_SPRITZEE, 12, GIFT_POOL_BRAWLY, TYPE_FAIRY, TYPE_NONE},
    {SPECIES_SQUIRTLE, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_STANTLER, 10, GIFT_POOL_NORMAN, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_STARLY, 12, GIFT_POOL_NORMAN, TYPE_NORMAL, TYPE_FLYING},
    {SPECIES_STARYU, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_STUFFUL, 10, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_FIGHTING},
    {SPECIES_SURSKIT, 10, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_WATER},
    {SPECIES_SWINUB, 12, GIFT_POOL_NONE, TYPE_ICE, TYPE_GROUND},
    {SPECIES_SWIRLIX, 10, GIFT_POOL_BRAWLY, TYPE_FAIRY, TYPE_NONE},
    {SPECIES_TADBULB, 12, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_TANGELA, 12, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_TAROUNTULA, 6, GIFT_POOL_NONE, TYPE_BUG, TYPE_NONE},
    {SPECIES_TEDDIURSA, 12, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_TENTACOOL, 10, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_POISON},
    {SPECIES_TIMBURR, 8, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_TINKATINK, 12, GIFT_POOL_NORMAN, TYPE_FAIRY, TYPE_STEEL},
    {SPECIES_TIRTOUGA, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_ROCK},
    {SPECIES_TORCHIC, 14, GIFT_POOL_NONE, TYPE_FIRE, TYPE_NONE},
    {SPECIES_TOTODILE, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_TRAPINCH, 12, GIFT_POOL_NONE, TYPE_GROUND, TYPE_NONE},
    {SPECIES_TREECKO, 10, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_TRUBBISH, 4, GIFT_POOL_NONE, TYPE_POISON, TYPE_NONE},
    {SPECIES_TURTWIG, 14, GIFT_POOL_JUAN, TYPE_GRASS, TYPE_NONE},
    {SPECIES_TYMPOLE, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_TYNAMO, 8, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_TYROGUE, 10, GIFT_POOL_NONE, TYPE_FIGHTING, TYPE_NONE},
    {SPECIES_TYRUNT, 10, GIFT_POOL_NORMAN, TYPE_ROCK, TYPE_DRAGON},
    {SPECIES_VAROOM, 14, GIFT_POOL_NORMAN, TYPE_STEEL, TYPE_POISON},
    {SPECIES_VENIPEDE, 6, GIFT_POOL_NONE, TYPE_BUG, TYPE_POISON},
    {SPECIES_VOLTORB_HISUI, 10, GIFT_POOL_JUAN, TYPE_ELECTRIC, TYPE_GRASS},
    {SPECIES_VULPIX_ALOLA, 12, GIFT_POOL_NONE, TYPE_ICE, TYPE_NONE},
    {SPECIES_WATTREL, 12, GIFT_POOL_BRAWLY, TYPE_ELECTRIC, TYPE_FLYING},
    {SPECIES_WAILMER, 8, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_WEEDLE, 6, GIFT_POOL_NONE, TYPE_BUG, TYPE_POISON},
    {SPECIES_WINGULL, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_FLYING},
    {SPECIES_WISHIWASHI, 12, GIFT_POOL_FLANNERY, TYPE_WATER, TYPE_NONE},
    {SPECIES_WOOLOO, 8, GIFT_POOL_NONE, TYPE_NORMAL, TYPE_NONE},
    {SPECIES_WOOPER_PALDEA, 10, GIFT_POOL_NONE, TYPE_POISON, TYPE_GROUND},
    {SPECIES_YAMPER, 6, GIFT_POOL_NONE, TYPE_ELECTRIC, TYPE_NONE},
    {SPECIES_YANMA, 8, GIFT_POOL_BRAWLY, TYPE_BUG, TYPE_FLYING},
    {SPECIES_ZIGZAGOON_GALAR, 18, GIFT_POOL_NONE, TYPE_DARK, TYPE_NORMAL},
    {SPECIES_ZORUA, 8, GIFT_POOL_NONE, TYPE_DARK, TYPE_NONE},
    {SPECIES_ZUBAT, 8, GIFT_POOL_BRAWLY, TYPE_POISON, TYPE_FLYING},
    {SPECIES_EGG, 16, GIFT_POOL_NONE, TYPE_NONE, TYPE_NONE},
};

static const struct GiftPokemon sGiftPokemonList2[] = {
    {SPECIES_EEVEE, 10},
    {SPECIES_ABSOL, 10},
    {SPECIES_ALOMOMOLA, 10},
    {SPECIES_BOMBIRDIER, 10},
    {SPECIES_BOUFFALANT, 10},
    {SPECIES_CARNIVINE, 10},
    {SPECIES_COMFEY, 10},
    {SPECIES_CRYOGONAL, 10},
    {SPECIES_DHELMISE, 10},
    {SPECIES_DRAMPA, 10},
    {SPECIES_DURANT, 10},
    {SPECIES_FALINKS, 10},
    {SPECIES_HAWLUCHA, 10},
    {SPECIES_HEATMOR, 10},
    {SPECIES_HERACROSS, 10},
    {SPECIES_KANGASKHAN, 10},
    {SPECIES_LAPRAS, 10},
    {SPECIES_MILTANK, 10},
    {SPECIES_MIMIKYU, 10},
    {SPECIES_PINSIR, 10},
    {SPECIES_RELICANTH, 10},
    {SPECIES_SEVIPER, 10},
    {SPECIES_SKARMORY, 10},
    {SPECIES_STONJOURNER, 10},
    {SPECIES_TOGEDEMARU, 10},
    {SPECIES_TORKOAL, 10},
    {SPECIES_TROPIUS, 10},
    {SPECIES_TURTONATOR, 10},
    {SPECIES_ZANGOOSE, 10}
};

u8 GetGiftMonCost(u16 species)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList); i++)
    {
        if (sGiftPokemonList[i].species == species)
            return sGiftPokemonList[i].cost;
    }
    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList2); i++)
    {
        if (sGiftPokemonList2[i].species == species)
            return sGiftPokemonList2[i].cost;
    }
    return 0;
}

// This function builds the list of Pokémon for the multichoice menu.
void BuildGiftPokemonMenu(void)
{
    u32 i;
    u16 species;

    ScriptMenu_ClearDynMultichoice();

    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList); i++)
    {
        species = sGiftPokemonList[i].species;
        if (species == SPECIES_MINIOR_CORE)
        {
            species = SPECIES_MINIOR_CORE_RED + (Random() % (SPECIES_MINIOR_CORE_VIOLET - SPECIES_MINIOR_CORE_RED + 1));
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[SPECIES_MINIOR].speciesName, species, 0);
        }
        else if (species == SPECIES_FLABEBE)
        {
            species = sFlabebeFormSpeciesIdTable[Random() % (ARRAY_COUNT(sFlabebeFormSpeciesIdTable) - 1)];
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[SPECIES_FLABEBE].speciesName, species, 0);
        }
        else if (species == SPECIES_SCATTERBUG)
        {
            species = sScatterbugFormSpeciesIdTable[Random() % (ARRAY_COUNT(sScatterbugFormSpeciesIdTable) - 1)];
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[SPECIES_SCATTERBUG].speciesName, species, 0);
        }
        else if (species == SPECIES_DEERLING)
        {
            species = sDeerlingFormSpeciesIdTable[Random() % (ARRAY_COUNT(sDeerlingFormSpeciesIdTable) - 1)];
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[SPECIES_DEERLING].speciesName, species, 0);
        }
        else if (species == SPECIES_EGG)
        {
            ScriptMenu_AddDynmultichoice(sText_MysteryEgg, species, 0);
            ScriptMenu_AddDynmultichoice(sText_Random, GIFT_MON_RANDOM_ID, 0);
            ScriptMenu_AddDynmultichoice(sText_RandTeam, GIFT_MON_RAND_TEAM_ID, 0);
        }
        else
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[species].speciesName, species, 0);
    }

    ScriptMenu_AddDynmultichoice(gText_Finished, GIFT_MON_FINISH_ID, -1);
}

void BuildGiftPokemonMenu2(void)
{
    u32 i;

    ScriptMenu_ClearDynMultichoice();

    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList2); i++)
        ScriptMenu_AddDynmultichoice(gSpeciesInfo[sGiftPokemonList2[i].species].speciesName, sGiftPokemonList2[i].species, 0);

    ScriptMenu_AddDynmultichoice(gText_Finished, GIFT_MON_FINISH_ID, -1);
}

#define GIFT_TEAM_MIN_COST 78
#define GIFT_TEAM_MAX_COST 82
#define GIFT_TEAM_MAX_ATTEMPTS 48
#define GIFT_TEAM_NODE_LIMIT 200000
#define GIFT_TEAM_MAX_UNITS 260

struct GiftTeamUnit
{
    u16 species[2];
    u8 slots;
    u8 cost;
    u8 pool;
    u8 types[2];
};

static EWRAM_DATA struct GiftTeamUnit sGiftTeamUnits[GIFT_TEAM_MAX_UNITS];
static u16 sGiftTeamUnitCount;
static EWRAM_DATA u8 sGiftTeamOrder[GIFT_TEAM_MAX_UNITS];
static u8 sGiftTeamTypeCount[NUMBER_OF_MON_TYPES];
static u8 sGiftTeamPoolCount[GIFT_POOL_COUNT];
static u8 sGiftTeamChoice[GIFT_MON_TEAM_SIZE];
static u8 sGiftTeamChoiceCount;
static u32 sGiftTeamNodes;
static u8 sGiftTeamMinCost[GIFT_MON_TEAM_SIZE + 1];
static u8 sGiftTeamMaxCost[GIFT_MON_TEAM_SIZE + 1];

// Maps a menu species (which may be a randomized form) back to its entry in sGiftPokemonList.
static s32 GetGiftEntryIndex(u16 species)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList); i++)
    {
        if (sGiftPokemonList[i].species == species)
            return (s32)i;
    }

    if (species >= SPECIES_MINIOR_CORE_RED && species <= SPECIES_MINIOR_CORE_VIOLET)
        return GetGiftEntryIndex(SPECIES_MINIOR_CORE);

    for (i = 0; i + 1 < ARRAY_COUNT(sFlabebeFormSpeciesIdTable); i++)
        if (sFlabebeFormSpeciesIdTable[i] == species)
            return GetGiftEntryIndex(SPECIES_FLABEBE);

    for (i = 0; i + 1 < ARRAY_COUNT(sScatterbugFormSpeciesIdTable); i++)
        if (sScatterbugFormSpeciesIdTable[i] == species)
            return GetGiftEntryIndex(SPECIES_SCATTERBUG);

    for (i = 0; i + 1 < ARRAY_COUNT(sDeerlingFormSpeciesIdTable); i++)
        if (sDeerlingFormSpeciesIdTable[i] == species)
            return GetGiftEntryIndex(SPECIES_DEERLING);

    return -1;
}

static u8 GiftTeam_MissingPools(void)
{
    u8 i;
    u8 missing = 0;

    for (i = 0; i < GIFT_POOL_COUNT; i++)
    {
        if (sGiftTeamPoolCount[i] == 0)
            missing++;
    }
    return missing;
}

static bool8 GiftTeam_Search(u16 start, u8 slots, u8 cost)
{
    u16 i;

    if (++sGiftTeamNodes > GIFT_TEAM_NODE_LIMIT)
        return FALSE;

    if (slots == 0)
    {
        return (cost >= GIFT_TEAM_MIN_COST && cost <= GIFT_TEAM_MAX_COST)
            && GiftTeam_MissingPools() == 0;
    }

    if (cost + sGiftTeamMinCost[slots] > GIFT_TEAM_MAX_COST)
        return FALSE;
    if (cost + sGiftTeamMaxCost[slots] < GIFT_TEAM_MIN_COST)
        return FALSE;
    if (GiftTeam_MissingPools() > slots)
        return FALSE;

    for (i = start; i < sGiftTeamUnitCount; i++)
    {
        struct GiftTeamUnit *unit = &sGiftTeamUnits[sGiftTeamOrder[i]];
        u8 type0Count = 1;
        u8 type1Count = 1;
        u8 newSlots;
        u8 newCost;

        if (unit->slots > slots)
            continue;

        newSlots = slots - unit->slots;
        newCost = cost + unit->cost;

        if (newCost + sGiftTeamMinCost[newSlots] > GIFT_TEAM_MAX_COST)
            continue;
        if (newCost + sGiftTeamMaxCost[newSlots] < GIFT_TEAM_MIN_COST)
            continue;

        // No type may appear on more than two team members.
        if (unit->types[0] != TYPE_NONE)
        {
            if (unit->types[1] == unit->types[0])
                type0Count = 2;
            if (sGiftTeamTypeCount[unit->types[0]] + type0Count > 2)
                continue;
        }
        if (unit->types[1] != TYPE_NONE && unit->types[1] != unit->types[0])
        {
            if (sGiftTeamTypeCount[unit->types[1]] + type1Count > 2)
                continue;
        }

        if (unit->types[0] != TYPE_NONE)
            sGiftTeamTypeCount[unit->types[0]] += type0Count;
        if (unit->types[1] != TYPE_NONE && unit->types[1] != unit->types[0])
            sGiftTeamTypeCount[unit->types[1]] += type1Count;
        if (unit->pool != GIFT_POOL_NONE)
            sGiftTeamPoolCount[unit->pool]++;

        sGiftTeamChoice[sGiftTeamChoiceCount++] = sGiftTeamOrder[i];

        if (GiftTeam_Search(i + 1, newSlots, newCost))
            return TRUE;

        sGiftTeamChoiceCount--;

        if (unit->pool != GIFT_POOL_NONE)
            sGiftTeamPoolCount[unit->pool]--;
        if (unit->types[1] != TYPE_NONE && unit->types[1] != unit->types[0])
            sGiftTeamTypeCount[unit->types[1]] -= type1Count;
        if (unit->types[0] != TYPE_NONE)
            sGiftTeamTypeCount[unit->types[0]] -= type0Count;
    }

    return FALSE;
}

// Builds a random 8-Pokémon team from the current menu, respecting cost, pool and type limits.
u8 GenerateRandomGiftTeam(struct ListMenuItem *items, u32 numItems, u16 *outTeam)
{
    u32 i;
    u16 plusleSpecies = SPECIES_NONE;
    u16 minunSpecies = SPECIES_NONE;
    u8 plusleCost = 0;
    u8 minunCost = 0;
    u8 attempt;
    u8 k;

    sGiftTeamUnitCount = 0;

    for (i = 0; i < numItems && sGiftTeamUnitCount < GIFT_TEAM_MAX_UNITS - 1; i++)
    {
        u16 id = items[i].id;
        const struct GiftPokemon *entry;
        s32 idx;

        if (id == SPECIES_EGG || id == GIFT_MON_FINISH_ID
         || id == GIFT_MON_RANDOM_ID || id == GIFT_MON_RAND_TEAM_ID)
            continue;

        idx = GetGiftEntryIndex(id);
        if (idx < 0)
            continue;
        entry = &sGiftPokemonList[idx];

        // Plusle and Minun are only ever offered together.
        if (id == SPECIES_PLUSLE)
        {
            plusleSpecies = id;
            plusleCost = entry->cost;
            continue;
        }
        if (id == SPECIES_MINUN)
        {
            minunSpecies = id;
            minunCost = entry->cost;
            continue;
        }

        sGiftTeamUnits[sGiftTeamUnitCount].species[0] = id;
        sGiftTeamUnits[sGiftTeamUnitCount].species[1] = id;
        sGiftTeamUnits[sGiftTeamUnitCount].slots = 1;
        sGiftTeamUnits[sGiftTeamUnitCount].cost = entry->cost;
        sGiftTeamUnits[sGiftTeamUnitCount].pool = entry->pool;
        sGiftTeamUnits[sGiftTeamUnitCount].types[0] = entry->type1;
        sGiftTeamUnits[sGiftTeamUnitCount].types[1] = entry->type2;
        sGiftTeamUnitCount++;
    }

    if (plusleSpecies != SPECIES_NONE && minunSpecies != SPECIES_NONE)
    {
        sGiftTeamUnits[sGiftTeamUnitCount].species[0] = plusleSpecies;
        sGiftTeamUnits[sGiftTeamUnitCount].species[1] = minunSpecies;
        sGiftTeamUnits[sGiftTeamUnitCount].slots = 2;
        sGiftTeamUnits[sGiftTeamUnitCount].cost = plusleCost + minunCost;
        sGiftTeamUnits[sGiftTeamUnitCount].pool = GIFT_POOL_NONE;
        sGiftTeamUnits[sGiftTeamUnitCount].types[0] = TYPE_ELECTRIC;
        sGiftTeamUnits[sGiftTeamUnitCount].types[1] = TYPE_ELECTRIC;
        sGiftTeamUnitCount++;
    }

    if (sGiftTeamUnitCount < GIFT_MON_TEAM_SIZE)
        return 0;

    // Precompute cheap-team and expensive-team cost bounds for pruning.
    {
        u8 costs[GIFT_TEAM_MAX_UNITS];
        u8 count = 0;
        u8 a;
        u8 b;

        for (i = 0; i < sGiftTeamUnitCount; i++)
        {
            if (sGiftTeamUnits[i].slots == 1)
                costs[count++] = sGiftTeamUnits[i].cost;
        }

        for (a = 1; a < count; a++)
        {
            u8 key = costs[a];
            b = a;
            while (b > 0 && costs[b - 1] > key)
            {
                costs[b] = costs[b - 1];
                b--;
            }
            costs[b] = key;
        }

        sGiftTeamMinCost[0] = 0;
        sGiftTeamMaxCost[0] = 0;
        for (a = 1; a <= GIFT_MON_TEAM_SIZE; a++)
        {
            sGiftTeamMinCost[a] = sGiftTeamMinCost[a - 1] + (a <= count ? costs[a - 1] : 0);
            sGiftTeamMaxCost[a] = sGiftTeamMaxCost[a - 1] + (a <= count ? costs[count - a] : 0);
        }
    }

    for (attempt = 0; attempt < GIFT_TEAM_MAX_ATTEMPTS; attempt++)
    {
        u8 count = 0;

        for (i = 0; i < sGiftTeamUnitCount; i++)
            sGiftTeamOrder[i] = i;
        for (i = sGiftTeamUnitCount; i > 1; i--)
        {
            u8 r = Random() % i;
            u8 tmp = sGiftTeamOrder[i - 1];
            sGiftTeamOrder[i - 1] = sGiftTeamOrder[r];
            sGiftTeamOrder[r] = tmp;
        }

        memset(sGiftTeamTypeCount, 0, sizeof(sGiftTeamTypeCount));
        memset(sGiftTeamPoolCount, 0, sizeof(sGiftTeamPoolCount));
        sGiftTeamChoiceCount = 0;
        sGiftTeamNodes = 0;

        if (!GiftTeam_Search(0, GIFT_MON_TEAM_SIZE, 0))
            continue;

        for (k = 0; k < sGiftTeamChoiceCount; k++)
        {
            struct GiftTeamUnit *unit = &sGiftTeamUnits[sGiftTeamChoice[k]];
            u8 s;

            for (s = 0; s < unit->slots; s++)
                outTeam[count++] = unit->species[s];
        }
        return count;
    }

    return 0;
}

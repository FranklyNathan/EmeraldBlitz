#include "global.h"
#include "script.h"
#include "random.h"
#include "script_menu.h"
#include "string_util.h"
#include "strings.h"
#include "pokemon.h"
#include "constants/species.h"
#include "data/pokemon/form_species_tables.h"
#include "constants/flags.h"
#include "event_data.h"

static const u8 sText_Random[] = _("Random");
static const u8 sText_MysteryEgg[] = _("Mystery Egg");

struct GiftPokemon
{
    u16 species;
    u8 cost;
};

static const struct GiftPokemon sGiftPokemonList[] = {
    {SPECIES_AMAURA, 6},
    {SPECIES_ANORITH, 6},
    {SPECIES_APPLIN, 14},
    {SPECIES_ARCHEN, 18},
    {SPECIES_ARON, 10},
    {SPECIES_BAGON, 12},
    {SPECIES_BELDUM, 12},
    {SPECIES_BINACLE, 10},
    {SPECIES_BLIPBUG, 8},
    {SPECIES_BLITZLE, 4},
    {SPECIES_BONSLY, 6},
    {SPECIES_BOUNSWEET, 10},
    //{SPECIES_BRONZOR, 10},
    {SPECIES_BUDEW, 14},
    {SPECIES_BUIZEL, 6},
    {SPECIES_BULBASAUR, 12},
    {SPECIES_BUNEARY, 6},
    {SPECIES_BUNNELBY, 8},
    {SPECIES_BURMY, 6},
    {SPECIES_CACNEA, 8},
    {SPECIES_CARVANHA, 8},
    {SPECIES_CASTFORM, 18},
    {SPECIES_CETODDLE, 8},
    {SPECIES_CHARCADET, 14},
    {SPECIES_CHARMANDER, 12},
    //{SPECIES_CHERUBI, 6},
    {SPECIES_CHESPIN, 12},
    {SPECIES_CHEWTLE, 14},
    {SPECIES_CHIMCHAR, 14},
    {SPECIES_CHINCHOU, 14},
    {SPECIES_CHINGLING, 8},
    {SPECIES_CLAMPERL, 8},
    {SPECIES_CLAUNCHER, 10},
    {SPECIES_CLOBBOPUS, 6},
    {SPECIES_CORPHISH, 10},
    {SPECIES_CORSOLA, 10},
    {SPECIES_COTTONEE, 12},
    {SPECIES_CROAGUNK, 12},
    {SPECIES_CUBONE, 6},
    {SPECIES_CUFANT, 10},
    {SPECIES_CUTIEFLY, 12},
    {SPECIES_CYNDAQUIL, 14},
    {SPECIES_DEERLING, 6},
    {SPECIES_DEWPIDER, 10},
    {SPECIES_DIGLETT, 6},
    {SPECIES_DRATINI, 12},
    {SPECIES_DRIFLOON, 8},
    {SPECIES_DRILBUR, 18},
    {SPECIES_DUCKLETT, 6},
    {SPECIES_DUSKULL, 10},
    {SPECIES_EKANS, 8},
    {SPECIES_ELECTRIKE, 8},
    {SPECIES_ELEKID, 8},
    {SPECIES_ELGYEM, 6},
    {SPECIES_EMOLGA, 10},
    {SPECIES_ESPURR, 10},
    {SPECIES_EXEGGCUTE, 12},
    {SPECIES_FARFETCHD_GALAR, 10},
    {SPECIES_FEEBAS, 10},
    {SPECIES_FENNEKIN, 16},
    {SPECIES_FIDOUGH, 12},
    {SPECIES_FLABEBE, 10},
    {SPECIES_FLETCHLING, 12},
    {SPECIES_FRIGIBAX, 10},
    {SPECIES_FRILLISH, 14},
    {SPECIES_FROAKIE, 14},
    {SPECIES_FUECOCO, 14},
    {SPECIES_GASTLY, 8},
    {SPECIES_GEODUDE, 8},
    {SPECIES_GIBLE, 18},
    {SPECIES_GOOMY, 10},
    {SPECIES_GOSSIFLEUR, 10},
    {SPECIES_GOTHITA, 6},
    {SPECIES_GREAVARD, 10},
    {SPECIES_GROWLITHE, 10},
    {SPECIES_GRUBBIN, 8},
    {SPECIES_HATENNA, 8},
    {SPECIES_HELIOPTILE, 10},
    {SPECIES_HIPPOPOTAS, 10},
    {SPECIES_HONEDGE, 16},
    {SPECIES_HORSEA, 10},
    {SPECIES_HOUNDOUR, 10},
    {SPECIES_IMPIDIMP, 10},
    {SPECIES_INKAY, 10},
    {SPECIES_JANGMO_O, 12},
    {SPECIES_JOLTIK, 6},
    {SPECIES_LARVITAR, 12},
    {SPECIES_LILLIPUP, 12},
    {SPECIES_LITLEO, 8},
    {SPECIES_LITTEN, 12},
    {SPECIES_LITWICK, 18},
    {SPECIES_LOTAD, 12},
    {SPECIES_MACHOP, 8},
    {SPECIES_MAGBY, 8},
    {SPECIES_MAGNEMITE, 16},
    {SPECIES_MAKUHITA, 10},
    {SPECIES_MANKEY, 12},
    {SPECIES_MANTYKE, 10},
    {SPECIES_MAREEP, 8},
    {SPECIES_MAWILE, 12},
    {SPECIES_MEDITITE, 12},
    {SPECIES_MEOWTH_GALAR, 8},
    {SPECIES_MIME_JR, 10},
    {SPECIES_MINCCINO, 6},
    {SPECIES_MINIOR_CORE, 16},
    {SPECIES_MINUN, 8},
    {SPECIES_MISDREAVUS, 12},
    {SPECIES_MORELULL, 10},
    {SPECIES_MUDBRAY, 16},
    {SPECIES_MUDKIP, 18},
    {SPECIES_MUNCHLAX, 12},
    {SPECIES_MURKROW, 8},
    {SPECIES_NICKIT, 6},
    {SPECIES_NINCADA, 10},
    {SPECIES_NOIBAT, 8},
    {SPECIES_NOSEPASS, 10},
    {SPECIES_NUMEL, 8},
    {SPECIES_NYMBLE, 8},
    {SPECIES_ODDISH, 10},
    {SPECIES_ONIX, 10},
    {SPECIES_OSHAWOTT, 14},
    {SPECIES_PANCHAM, 8},
    {SPECIES_PANSEAR, 6},
    {SPECIES_PARAS, 6},
    {SPECIES_PHANTUMP, 10},
    {SPECIES_PHANPY, 10},
    {SPECIES_PLUSLE, 8},
    {SPECIES_PICHU, 10},
    {SPECIES_PIKIPEK, 8},
    {SPECIES_PINECO, 8},
    {SPECIES_PIPLUP, 14},
    {SPECIES_POLIWAG, 12},
    {SPECIES_PONYTA, 10},
    {SPECIES_POOCHYENA, 10},
    {SPECIES_POPPLIO, 16},
    {SPECIES_PORYGON, 16},
    {SPECIES_PSYDUCK, 10},
    {SPECIES_PURRLOIN, 6},
    {SPECIES_RALTS, 20},
    {SPECIES_REMORAID, 8},
    {SPECIES_RIOLU, 16},
    {SPECIES_ROCKRUFF, 8},
    {SPECIES_ROGGENROLA, 6},
    {SPECIES_ROLYCOLY, 8},
    {SPECIES_ROOKIDEE, 10},
    {SPECIES_ROTOM, 18},
    {SPECIES_ROWLET, 12},
    {SPECIES_RUFFLET, 10},
    {SPECIES_SABLEYE, 8},
    {SPECIES_SALANDIT, 10},
    {SPECIES_SANDILE, 14},
    {SPECIES_SANDSHREW_ALOLA, 8},
    {SPECIES_SANDYGAST, 8},
    {SPECIES_SCATTERBUG, 10},
    {SPECIES_SCRAGGY, 10},
    {SPECIES_SCYTHER, 12},
    {SPECIES_SEWADDLE, 10},
    {SPECIES_SHELLDER, 6},
    {SPECIES_SHELLOS_EAST, 12},
    {SPECIES_SHINX, 10},
    {SPECIES_SHROODLE, 8},
    {SPECIES_SHROOMISH, 14},
    {SPECIES_SHUPPET, 6},
    {SPECIES_SIZZLIPEDE, 10},
    {SPECIES_SKIDDO, 10},
    {SPECIES_SKORUPI, 10},
    {SPECIES_SKRELP, 6},
    {SPECIES_SKWOVET, 10},
    {SPECIES_SLAKOTH, 8},
    {SPECIES_SLOWPOKE_GALAR, 10},
    {SPECIES_SMEARGLE, 6},
    {SPECIES_SMOLIV, 10},
    {SPECIES_SNEASEL, 10},
    {SPECIES_SNIVY, 12},
    {SPECIES_SNORUNT, 6},
    {SPECIES_SNOVER, 6},
    {SPECIES_SNUBBULL, 8},
    {SPECIES_SOLOSIS, 6},
    {SPECIES_SPHEAL, 12},
    {SPECIES_SPOINK, 8},
    {SPECIES_SPRITZEE, 12},
    {SPECIES_SQUIRTLE, 12},
    {SPECIES_STANTLER, 10},
    {SPECIES_STARLY, 12},
    {SPECIES_STARYU, 10},
    {SPECIES_STUFFUL, 10},
    {SPECIES_SURSKIT, 10},
    {SPECIES_SWINUB, 12},
    {SPECIES_SWIRLIX, 10},
    {SPECIES_TADBULB, 12},
    {SPECIES_TAROUNTULA, 6},
    {SPECIES_TEDDIURSA, 12},
    {SPECIES_TENTACOOL, 10},
    {SPECIES_TIMBURR, 8},
    {SPECIES_TINKATINK, 12},
    {SPECIES_TIRTOUGA, 12},
    {SPECIES_TORCHIC, 14},
    {SPECIES_TOTODILE, 12},
    {SPECIES_TRAPINCH, 12},
    {SPECIES_TREECKO, 10},
    {SPECIES_TRUBBISH, 6},
    {SPECIES_TURTWIG, 14},
    {SPECIES_TYMPOLE, 12},
    {SPECIES_TYNAMO, 8},
    {SPECIES_TYROGUE, 10},
    {SPECIES_TYRUNT, 8},
    {SPECIES_VAROOM, 14},
    {SPECIES_VENIPEDE, 10},
    {SPECIES_VOLTORB_HISUI, 10},
    {SPECIES_VULPIX_ALOLA, 12},
    {SPECIES_WATTREL, 12},
    {SPECIES_WAILMER, 10},
    {SPECIES_WEEDLE, 6},
    {SPECIES_WINGULL, 12},
    {SPECIES_WISHIWASHI, 12},
    {SPECIES_WOOPER_PALDEA, 10},
    {SPECIES_YAMPER, 6},
    {SPECIES_YANMA, 8},
    {SPECIES_ZIGZAGOON_GALAR, 16},
    {SPECIES_ZORUA, 8},
    {SPECIES_ZUBAT, 8},
    {SPECIES_EGG, 18}
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
            ScriptMenu_AddDynmultichoice(sText_Random, 1000, 0);
        }
        else
            ScriptMenu_AddDynmultichoice(gSpeciesInfo[species].speciesName, species, 0);
    }

    ScriptMenu_AddDynmultichoice(gText_Finished, 999, -1);
}

void BuildGiftPokemonMenu2(void)
{
    u32 i;

    ScriptMenu_ClearDynMultichoice();

    for (i = 0; i < ARRAY_COUNT(sGiftPokemonList2); i++)
        ScriptMenu_AddDynmultichoice(gSpeciesInfo[sGiftPokemonList2[i].species].speciesName, sGiftPokemonList2[i].species, 0);

    ScriptMenu_AddDynmultichoice(gText_Finished, 999, -1);
}

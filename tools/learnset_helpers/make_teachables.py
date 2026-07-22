#!/usr/bin/env python3

"""
Usage: python3 make_teachable.py SOURCE_LEARNSETS_JSON

Build a C-header defining the set of teachable moves for each configured-on
species-family based on the learnable moves defined in SOURCE_LEARNSETS_JSON.

A move is "teachable" if it is:
    1. Can be taught by some Move Tutor in the overworld, which is identified by
       using the ChooseMonForMoveTutor special in a script and setting VAR_0x8005
       to the offered MOVE constant. (e.g., MOVE_SWAGGER)
    2. Assigned to some TM or HM in include/constants/tms_hms.h using the
       FOREACH_TM macro.
    3. Not a universal move, as defined by sUniversalMoves in src/pokemon.c.

For a given species, a move is considered teachable to that species if:
    1. The species is not NONE -- which learns nothing -- nor MEW -- which
       learns everything.
    2. The species can learn the move via *any* method within any Expansion-
       supported game.
"""

from itertools import chain
from textwrap import dedent

import glob
import json
import pathlib
import re
import sys
import typing


CONFIG_ENABLED_PAT = re.compile(r"#define P_LEARNSET_HELPER_TEACHABLE\s+(?P<cfg_val>[^ ]*)")
INCFILE_HAS_TUTOR_PAT = re.compile(r"special ChooseMonForMoveTutor")
INCFILE_MOVE_PAT = re.compile(r"setvar VAR_0x8005, (MOVE_.*)")
TMHM_MACRO_PAT = re.compile(r"F\((\w+)\)")
UNIVERSAL_MOVES_PAT = re.compile(r"static const u16 sUniversalMoves\[\]\s*=\s*{((.|\n)*?)\n};")
TEACHABLE_ARRAY_DECL_PAT = re.compile(r"(?P<decl>static const u16 s(?P<name>\w+)TeachableLearnset\[\]) = {[\s\S]*?};")
SNAKIFY_PAT = re.compile(r"(?!^)([A-Z]+)")
TUTOR_ARRAY_ENABLED_PAT = re.compile(r"#define\s+P_TUTOR_MOVES_ARRAY\s+(?P<cfg_val>[^ ]*)")

# Moves to exclude from teachable learnsets
EXCLUDED_MOVES = {
    "MOVE_CUT",
    "MOVE_DIG",
    "MOVE_TORMENT",
    "MOVE_SECRET_POWER",
    "MOVE_ATTRACT",
    "MOVE_SKILL_SWAP",
    "MOVE_FLASH",
    "MOVE_BODY_SLAM",
    "MOVE_COUNTER",
    "MOVE_DEFENSE_CURL",
    "MOVE_DREAM_EATER",
    "MOVE_DYNAMIC_PUNCH",
    "MOVE_ENDURE",
    "MOVE_MEGA_KICK",
    "MOVE_MEGA_PUNCH",
    "MOVE_MIMIC",
    "MOVE_MUD_SLAP",
    "MOVE_PSYCH_UP",
    "MOVE_SEISMIC_TOSS",
    "MOVE_SLEEP_TALK",
    "MOVE_SNORE",
    "MOVE_SOFT_BOILED",
    "MOVE_SWAGGER",
    "MOVE_SWIFT",
    "MOVE_SWORDS_DANCE",
    "MOVE_THUNDER_WAVE",
}

# Per-species move exclusions: species -> moves to remove from that species only
EXCLUDED_MOVES_BY_SPECIES = {
    "EEVEE": ["MOVE_CALM_MIND"],
    "LEAFEON": ["MOVE_CALM_MIND"],
    "GLACEON": ["MOVE_CALM_MIND"],
    "VAPOREON": ["MOVE_CALM_MIND"],
    "FLAREON": ["MOVE_CALM_MIND"],
    "JOLTEON": ["MOVE_CALM_MIND"],
    "UMBREON": ["MOVE_CALM_MIND"],
    "PIKACHU": ["MOVE_CALM_MIND"],
    "RAICHU": ["MOVE_CALM_MIND"],
    "IGGLYBUFF": ["MOVE_CALM_MIND"],
    "JIGGLYPUFF": ["MOVE_CALM_MIND"],
    "WIGGLYTUFF": ["MOVE_CALM_MIND"],
    "EXEGGUTOR_ALOLA": ["MOVE_CALM_MIND"],
    "SCYTHER": ["MOVE_CALM_MIND"],
    "CLEFFA": ["MOVE_CALM_MIND"],
    "TOGEPI": ["MOVE_CALM_MIND"],
    "TOGETIC": ["MOVE_CALM_MIND"],
    "TOGEKISS": ["MOVE_CALM_MIND"],
    "SCIZOR": ["MOVE_CALM_MIND"],
    "MILOTIC": ["MOVE_CALM_MIND"],
    "MEOWTH_GALAR": ["MOVE_BULK_UP"],
    "ELECTABUZZ": ["MOVE_BULK_UP"],
    "SABLEYE": ["MOVE_BULK_UP"],
    "STARAPTOR": ["MOVE_BULK_UP"],
    "ELECTIVIRE": ["MOVE_BULK_UP"],
    "MALAMAR": ["MOVE_BULK_UP"],
    "PERRSERKER": ["MOVE_BULK_UP"],
    "TINKATUFF": ["MOVE_BULK_UP"],
    "TINKATON": ["MOVE_BULK_UP"],
    "SWAMPERT": ["MOVE_BULK_UP"],
}

# Special teachable rules: species -> moves to always add
SPECIAL_TEACHABLE_BY_SPECIES = {
    "SHUPPET": ["MOVE_POUNCE"],
    "BANETTE": ["MOVE_POUNCE"],
    "ELECTRIKE": ["MOVE_POUNCE"],
    "MANECTRIC": ["MOVE_POUNCE"],
    "LILLIPUP": ["MOVE_POUNCE"],
    "HERDIER": ["MOVE_POUNCE"],
    "STOUTLAND": ["MOVE_POUNCE"],
    "BUNEARY": ["MOVE_POUNCE"],
    "LOPUNNY": ["MOVE_POUNCE"],
    "BEEDRILL": ["MOVE_POUNCE"],
    "SCOLIPEDE": ["MOVE_POUNCE"],
    "WHIRLIPEDE": ["MOVE_POUNCE"],
    "VENIPEDE": ["MOVE_POUNCE"],
    "EMOLGA": ["MOVE_POUNCE"],
    "HELIOLISK": ["MOVE_POUNCE"],
    "HELIOPTILE": ["MOVE_POUNCE"],
    "CLAWITZER": ["MOVE_POUNCE"],
    "CLAWNCER": ["MOVE_POUNCE"],
    "SKORUPI": ["MOVE_POUNCE"],
    "DRAPION": ["MOVE_POUNCE"],
    "ZIGZAGOON": ["MOVE_POUNCE"],
    "LINOONE": ["MOVE_POUNCE"],
    "OBSTAGOON": ["MOVE_POUNCE"],
    "BLIPBUG": ["MOVE_POUNCE"],
    "DOTTLER": ["MOVE_POUNCE"],
    "ORBEETLE": ["MOVE_POUNCE"],
    "NICKIT": ["MOVE_POUNCE"],
    "THIEVUL": ["MOVE_POUNCE"],
    "YAMPER": ["MOVE_POUNCE"],
    "BOLTUND": ["MOVE_POUNCE"],
}


def enabled() -> bool:
    """
    Check if the user has explicitly enabled this opt-in helper.
    """
    with open("./include/config/pokemon.h", "r") as cfg_pokemon_fp:
        cfg_pokemon = cfg_pokemon_fp.read()
        cfg_defined = CONFIG_ENABLED_PAT.search(cfg_pokemon)
        return cfg_defined is not None and cfg_defined.group("cfg_val") in ("TRUE", "1")


def extract_repo_tutors() -> typing.Generator[str, None, None]:
    """
    Yield MOVE constants which are *likely* assigned to a move tutor. This isn't
    foolproof, but it's suitable.
    """
    for inc_fname in chain(glob.glob("./data/scripts/*.inc"), glob.glob("./data/maps/*/scripts.inc")):
        with open(inc_fname, "r") as inc_fp:
            incfile = inc_fp.read()
            if not INCFILE_HAS_TUTOR_PAT.search(incfile):
                continue

            for move in INCFILE_MOVE_PAT.finditer(incfile):
                yield move.group(1)


def extract_repo_tms() -> typing.Generator[str, None, None]:
    """
    Yield MOVE constants assigned to a TM or HM in the user's repo.
    """
    with open("./include/constants/tms_hms.h", "r") as tmshms_fp:
        tmshms = tmshms_fp.read()
        match_it = TMHM_MACRO_PAT.finditer(tmshms)
        if not match_it:
            return

        for match in match_it:
            yield f"MOVE_{match.group(1)}"


def extract_repo_universals() -> list[str]:
    """
    Return a list of MOVE constants which are deemed to be universal and can
    thus be learned by any species.
    """
    with open("./src/pokemon.c", "r") as pokemon_fp:
        if match := UNIVERSAL_MOVES_PAT.search(pokemon_fp.read()):
            return list(filter(lambda s: s, map(lambda s: s.strip(), match.group(1).split(','))))
        return list()

def prepare_output(all_learnables: dict[str, set[str]], repo_teachables: set[str], header: str) -> str:
    """
    Build the file content for teachable_learnsets.h.
    """
    with open("./src/data/pokemon/teachable_learnsets.h", "r") as teachables_fp:
        old = teachables_fp.read()

    cursor = 0
    new = header + dedent("""
    static const u16 sNoneTeachableLearnset[] = {
        MOVE_UNAVAILABLE,
    };
    """)

    joinpat = ",\n    "
    for species in TEACHABLE_ARRAY_DECL_PAT.finditer(old):
        match_b, match_e = species.span()
        species_upper = SNAKIFY_PAT.sub(r"_\1", species.group("name")).upper()
        if species_upper == "NONE":
            # NONE is hard-coded to be at the start of the file to keep this code simple.
            cursor = match_e + 1
            continue

        if species_upper == "MEW":
            new += old[cursor:match_e + 1] # copy the original content and skip.
            cursor = match_e + 1
            continue

        species_excluded = set(EXCLUDED_MOVES_BY_SPECIES.get(species_upper, []))
        repo_species_teachables = filter(
            lambda m: m in repo_teachables and m not in species_excluded,
            all_learnables[species_upper]
        )

        new += old[cursor:match_b]
        new += "\n".join([
            f"{species.group('decl')} = {{",
            f"    {joinpat.join(chain(repo_species_teachables, ('MOVE_UNAVAILABLE',)))},",
            "};\n",
        ])
        cursor = match_e + 1

    new += old[cursor:]

    return new


def create_tutor_moves_array(tutors: list[str]) -> None:
    """
    Generate gTutorMoves[] if P_TUTOR_MOVES_ARRAY is enabled.
    """
    # Check if the config is enabled
    with open("./include/config/pokemon.h", "r") as cfg_pokemon_fp:
        cfg_pokemon = cfg_pokemon_fp.read()
        cfg_defined = TUTOR_ARRAY_ENABLED_PAT.search(cfg_pokemon)
        if not (cfg_defined and cfg_defined.group("cfg_val") in ("TRUE", "1")):
            return

    # If enabled, generate the tutor moves array
    header = dedent("""\
        // DO NOT MODIFY THIS FILE! It is auto-generated by tools/learnset_helpers/make_teachables.py
        // Set the config P_TUTOR_MOVES_ARRAY in include/config/pokemon.h to TRUE to enable this array!
        // Also need by tutor moves relearner!

        const u16 gTutorMoves[] = {
    """)

    lines = [f"    {move}," for move in sorted(tutors)]
    lines.append("    MOVE_UNAVAILABLE\n};\n")

    with open("./src/data/tutor_moves.h", "w") as f:
        f.write(header + "\n".join(lines))


def prepare_header(h_align: int, tmshms: list[str], tutors: list[str], universals: list[str]) -> str:
    universals_title = "Near-universal moves found from sUniversalMoves:"
    tmhm_title = "TM/HM moves found in \"include/constants/tms_hms.h\":"
    tutor_title = "Tutor moves found from map scripts:"
    h_align = max(h_align, len(universals_title), len(tmhm_title), len(tutor_title))

    lines = [
         "//",
         "// DO NOT MODIFY THIS FILE! It is auto-generated by tools/learnset_helpers/make_teachables.py",
         "//",
         "",
        f"// {'*' * h_align} //",
        f"// {tmhm_title: >{h_align}} //",
    ]
    lines.extend([f"// - {move: <{h_align - 2}} //" for move in tmshms])
    lines.extend([
        f"// {'*' * h_align} //",
        f"// {tutor_title: <{h_align}} //",
    ])
    lines.extend([f"// - {move: <{h_align - 2}} //" for move in sorted(tutors)])
    lines.extend([
        f"// {'*' * h_align} //",
        f"// {universals_title: <{h_align}} //",
    ])
    lines.extend([f"// - {move: <{h_align - 2}} //" for move in universals])
    lines.extend([
        f"// {'*' * h_align} //",
         "",
    ])

    return "\n".join(lines)


def main():
    if not enabled():
        quit()

    if len(sys.argv) < 2:
        print("Missing required arguments", file=sys.stderr)
        print(__doc__, file=sys.stderr)
        quit(1)

    SOURCE_LEARNSETS_JSON = pathlib.Path(sys.argv[1])

    assert SOURCE_LEARNSETS_JSON.exists(), f"{SOURCE_LEARNSETS_JSON=} does not exist"
    assert SOURCE_LEARNSETS_JSON.is_file(), f"{SOURCE_LEARNSETS_JSON=} is not a file"

    repo_universals = extract_repo_universals()
    repo_tms = list(extract_repo_tms())
    repo_tutors = list(extract_repo_tutors())
    repo_teachables = set(filter(
        lambda move: move not in set(repo_universals) and move not in EXCLUDED_MOVES,
        chain(repo_tms, repo_tutors)
    ))

    create_tutor_moves_array(repo_tutors)

    h_align = max(map(lambda move: len(move), chain(repo_universals, repo_teachables))) + 2
    header = prepare_header(h_align, repo_tms, repo_tutors, repo_universals)

    with open(SOURCE_LEARNSETS_JSON, "r") as source_fp:
        all_learnables = json.load(source_fp)

    content = prepare_output(all_learnables, repo_teachables, header)
    with open("./src/data/pokemon/teachable_learnsets.h", "w") as teachables_fp:
        teachables_fp.write(content)


if __name__ == "__main__":
    main()

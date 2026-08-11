#!/bin/bash
rm -f build/emerald/src/party_menu.o
make -j"$(nproc)" modern 2>&1 | grep -iE 'party_menu|error:|undefined' | head -20
echo "BUILD_DONE"
ls tools/mgba* 2>/dev/null
ls tools/mgba 2>/dev/null

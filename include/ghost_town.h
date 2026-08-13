#ifndef GUARD_GHOST_TOWN_H
#define GUARD_GHOST_TOWN_H

#include "global.h"

struct ObjectEvent;
struct ObjectEventTemplate;

void GhostTownUpdate(void);
const u8 *GhostTownGetInteractScript(u8 objectEventId);
bool8 GhostTownIsGhostObject(const struct ObjectEvent *obj);
bool8 GhostTownIsGhostTemplate(const struct ObjectEventTemplate *template);
bool8 GhostTownIsGymGhostTemplate(const struct ObjectEventTemplate *template);

#endif // GUARD_GHOST_TOWN_H

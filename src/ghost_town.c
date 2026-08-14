#include "global.h"
#include "ghost_town.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "sprite.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/species.h"

#define GHOST_GRID_RADIUS      2
#define GHOST_FLICKER_DURATION 20
#define GHOST_FLICKER_INTERVAL 2

#define GHOST_STATE_NONE        0
#define GHOST_STATE_SOLID       1
#define GHOST_STATE_FLICKER_IN  2
#define GHOST_STATE_FLICKER_OUT 3

// Base localId for spawned ghosts. Ghosts are given localIds that no map
// template uses so that script/movement commands targeting real localIds
// never touch them. Must stay below the reserved follower/player localIds.
#define SHUPPET_LOCALID_BASE      200
#define SHUPPET_LOCALID_MAX       230
#define SHUPPET_GYM_LOCALID_BASE  230

extern const u8 EventScript_GhostTown_ShuppetInteract[];
extern const u8 EventScript_GymShuppetInteract[];

// Flicker state is kept here rather than in sprite->data, because
// data[0]/data[1] of object event sprites are sObjEventId/sTypeFuncId
// and are required by the movement system.
struct GhostFlickerState
{
    u8 localId; // localId of the ghost occupying this slot; 0 if unused
    u8 state;
    u8 timer;
};

static EWRAM_DATA struct GhostFlickerState sGhostFlickerStates[OBJECT_EVENTS_COUNT] = {0};

static bool8 IsGhostShuppet(const struct ObjectEvent *obj)
{
    if (!obj->active)
        return FALSE;
    if (obj->localId < SHUPPET_LOCALID_BASE || obj->localId >= OBJ_EVENT_ID_NPC_FOLLOWER)
        return FALSE;
    if (!(obj->graphicsId & OBJ_EVENT_MON))
        return FALSE;
    return (obj->graphicsId & OBJ_EVENT_MON_SPECIES_MASK) == SPECIES_SHUPPET;
}

static bool8 IsGymGhostShuppet(const struct ObjectEvent *obj)
{
    if (!obj->active)
        return FALSE;
    if (obj->localId < SHUPPET_GYM_LOCALID_BASE || obj->localId >= OBJ_EVENT_ID_NPC_FOLLOWER)
        return FALSE;
    if (!(obj->graphicsId & OBJ_EVENT_MON))
        return FALSE;
    return (obj->graphicsId & OBJ_EVENT_MON_SPECIES_MASK) == SPECIES_BANETTE;
}

bool8 GhostTownIsGhostObject(const struct ObjectEvent *obj)
{
    return IsGhostShuppet(obj) || IsGymGhostShuppet(obj);
}

bool8 GhostTownIsGhostTemplate(const struct ObjectEventTemplate *template)
{
    if (!(template->graphicsId & OBJ_EVENT_MON))
        return FALSE;
    if ((template->graphicsId & OBJ_EVENT_MON_SPECIES_MASK) != SPECIES_SHUPPET)
        return FALSE;
    return template->script == EventScript_GhostTown_ShuppetInteract;
}

bool8 GhostTownIsGymGhostTemplate(const struct ObjectEventTemplate *template)
{
    if (!(template->graphicsId & OBJ_EVENT_MON))
        return FALSE;
    if ((template->graphicsId & OBJ_EVENT_MON_SPECIES_MASK) != SPECIES_BANETTE)
        return FALSE;
    return template->script == EventScript_GymShuppetInteract;
}

static s16 AbsS16(s16 v)
{
    return v < 0 ? -v : v;
}

static void SetGhostVisibility(struct ObjectEvent *obj, struct Sprite *sprite, bool8 visible)
{
    obj->invisible = !visible;
    sprite->invisible = !visible;
}

static void ClearGhostState(u8 objId)
{
    sGhostFlickerStates[objId].localId = 0;
    sGhostFlickerStates[objId].state = GHOST_STATE_NONE;
    sGhostFlickerStates[objId].timer = 0;
}

static struct GhostFlickerState *GetGhostState(u8 objId)
{
    if (objId >= OBJECT_EVENTS_COUNT)
        return NULL;
    if (!IsGhostShuppet(&gObjectEvents[objId]) && !IsGymGhostShuppet(&gObjectEvents[objId]))
        return NULL;
    if (sGhostFlickerStates[objId].localId != gObjectEvents[objId].localId)
        return NULL;
    return &sGhostFlickerStates[objId];
}

static void RemoveGhostShuppet(u8 objId)
{
    RemoveObjectEvent(&gObjectEvents[objId]);
    ClearGhostState(objId);
}

static void SpawnShuppet(const struct ObjectEventTemplate *template, u8 localId)
{
    u8 i;
    u8 objId;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active
            && gObjectEvents[i].localId == localId
            && gObjectEvents[i].mapNum == gSaveBlock1Ptr->location.mapNum
            && gObjectEvents[i].mapGroup == gSaveBlock1Ptr->location.mapGroup)
            return;
    }

    objId = SpawnSpecialObjectEventParameterized(
        template->graphicsId,
        template->movementType,
        localId,
        template->x + MAP_OFFSET,
        template->y + MAP_OFFSET,
        template->elevation);

    if (objId < OBJECT_EVENTS_COUNT)
    {
        struct ObjectEvent *obj = &gObjectEvents[objId];
        struct Sprite *sprite = &gSprites[obj->spriteId];

        // SpawnSpecialObjectEventParameterized applies the camera scroll offset
        // to the sprite position, so while riding a bike the ghost would render
        // up to a tile away from its assigned tile. Reposition it exactly on the
        // tile so it can never be shifted by camera movement.
        MoveObjectEventToMapCoords(obj, obj->currentCoords.x, obj->currentCoords.y);

        sGhostFlickerStates[objId].localId = localId;
        sGhostFlickerStates[objId].state = GHOST_STATE_SOLID;
        sGhostFlickerStates[objId].timer = 0;

        obj->invisible = TRUE;
        sprite->invisible = TRUE;
    }
}

static void StartGhostFlicker(u8 objId, u8 state)
{
    sGhostFlickerStates[objId].state = state;
    sGhostFlickerStates[objId].timer = GHOST_FLICKER_DURATION;
}

static void UpdateGhostFlicker(u8 objId)
{
    struct ObjectEvent *obj = &gObjectEvents[objId];
    struct Sprite *sprite;
    struct GhostFlickerState *state = &sGhostFlickerStates[objId];

    if (obj->spriteId >= MAX_SPRITES)
        return;

    sprite = &gSprites[obj->spriteId];

    if (state->timer != 0)
    {
        state->timer--;
        SetGhostVisibility(obj, sprite, ((state->timer / GHOST_FLICKER_INTERVAL) & 1) == 0);
    }

    if (state->timer == 0)
    {
        if (state->state == GHOST_STATE_FLICKER_IN)
        {
            state->state = GHOST_STATE_SOLID;
            SetGhostVisibility(obj, sprite, TRUE);
        }
        else
        {
            RemoveGhostShuppet(objId);
        }
    }
}

static bool8 IsPlayerFacingObject(s16 dx, s16 dy, u8 facingDirection)
{
    s16 absDx, absDy;

    if (dx == 0 && dy == 0)
        return FALSE;

    absDx = AbsS16(dx);
    absDy = AbsS16(dy);

    if (absDx > absDy)
    {
        if (facingDirection == DIR_EAST)
            return dx > 0;
        if (facingDirection == DIR_WEST)
            return dx < 0;
        return FALSE;
    }

    if (facingDirection == DIR_SOUTH)
        return dy > 0;
    if (facingDirection == DIR_NORTH)
        return dy < 0;
    return FALSE;
}

// Gym ghosts (Banette) only appear when the player is looking at them;
// regular ghosts (Shuppet) appear by proximity alone.
static bool8 IsGhostInDisplayGrid(const struct ObjectEvent *obj, s16 playerX, s16 playerY, u8 playerFacingDirection)
{
    s16 dx, dy;

    dx = obj->currentCoords.x - playerX;
    dy = obj->currentCoords.y - playerY;

    if (AbsS16(dx) > GHOST_GRID_RADIUS || AbsS16(dy) > GHOST_GRID_RADIUS)
        return FALSE;

    if (IsGymGhostShuppet(obj))
        return IsPlayerFacingObject(dx, dy, playerFacingDirection);

    return TRUE;
}

void GhostTownUpdate(void)
{
    u8 i;
    u8 count;
    s16 playerX, playerY;
    u8 playerFacingDirection;
    const struct ObjectEventTemplate *templates;
    struct ObjectEvent *playerObj;

    if (gMapHeader.events == NULL)
        return;
    if (gPlayerAvatar.objectEventId >= OBJECT_EVENTS_COUNT)
        return;

    playerObj = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!playerObj->active)
        return;

    playerX = playerObj->currentCoords.x;
    playerY = playerObj->currentCoords.y;
    playerFacingDirection = GetPlayerFacingDirection();
    templates = gSaveBlock1Ptr->objectEventTemplates;
    count = gMapHeader.events->objectEventCount;

    // Remove regular ghosts if SHUPPET GUIDES is enabled
    if (gSaveBlock2Ptr->optionsShuppetGuides)
    {
        for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        {
            if (!IsGymGhostShuppet(&gObjectEvents[i]) && IsGhostShuppet(&gObjectEvents[i]))
                RemoveGhostShuppet(i);
        }
    }
    else
    {
        // Spawn regular ghosts (controlled by SHUPPET GUIDES)
        u8 shuppetCount = 0;
        for (i = 0; i < count; i++)
        {
            const struct ObjectEventTemplate *template = &templates[i];

            if (!GhostTownIsGhostTemplate(template))
                continue;
            if (template->flagId != 0 && FlagGet(template->flagId))
            {
                shuppetCount++;
                continue;
            }
            if (AbsS16(template->x + MAP_OFFSET - playerX) > GHOST_GRID_RADIUS
             || AbsS16(template->y + MAP_OFFSET - playerY) > GHOST_GRID_RADIUS)
            {
                shuppetCount++;
                continue;
            }
            if (SHUPPET_LOCALID_BASE + shuppetCount >= SHUPPET_LOCALID_MAX)
            {
                shuppetCount++;
                continue;
            }

            SpawnShuppet(template, SHUPPET_LOCALID_BASE + shuppetCount);
            shuppetCount++;
        }
    }

    // Spawn gym ghosts (always active, inverted flag logic: show when flag IS set)
    {
        u8 gymCount = 0;
        for (i = 0; i < count; i++)
        {
            const struct ObjectEventTemplate *template = &templates[i];

            if (!GhostTownIsGymGhostTemplate(template))
                continue;
            if (template->flagId == 0 || !FlagGet(template->flagId))
            {
                gymCount++;
                continue;
            }
            if (AbsS16(template->x + MAP_OFFSET - playerX) > GHOST_GRID_RADIUS
             || AbsS16(template->y + MAP_OFFSET - playerY) > GHOST_GRID_RADIUS)
            {
                gymCount++;
                continue;
            }
            if (SHUPPET_GYM_LOCALID_BASE + gymCount >= OBJ_EVENT_ID_NPC_FOLLOWER)
            {
                gymCount++;
                continue;
            }

            SpawnShuppet(template, SHUPPET_GYM_LOCALID_BASE + gymCount);
            gymCount++;
        }
    }

    // Update all ghosts (both regular and gym)
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        struct ObjectEvent *obj = &gObjectEvents[i];
        struct GhostFlickerState *state;
        bool8 inGrid;

        if (!IsGhostShuppet(obj) && !IsGymGhostShuppet(obj))
            continue;

        state = GetGhostState(i);
        if (state == NULL)
            continue;

        inGrid = IsGhostInDisplayGrid(obj, playerX, playerY, playerFacingDirection);

        if (state->state == GHOST_STATE_FLICKER_OUT)
        {
            if (inGrid)
            {
                state->state = GHOST_STATE_FLICKER_IN;
                continue;
            }
        }

        if (state->state == GHOST_STATE_FLICKER_IN || state->state == GHOST_STATE_FLICKER_OUT)
        {
            UpdateGhostFlicker(i);
            continue;
        }

        if (inGrid && obj->invisible)
            StartGhostFlicker(i, GHOST_STATE_FLICKER_IN);
        else if (!inGrid && !obj->invisible)
            StartGhostFlicker(i, GHOST_STATE_FLICKER_OUT);
    }
}

const u8 *GhostTownGetInteractScript(u8 objectEventId)
{
    struct GhostFlickerState *state;

    if (objectEventId >= OBJECT_EVENTS_COUNT)
        return NULL;
    if (!IsGhostShuppet(&gObjectEvents[objectEventId]) && !IsGymGhostShuppet(&gObjectEvents[objectEventId]))
        return NULL;
    if (gObjectEvents[objectEventId].invisible)
        return NULL;

    state = GetGhostState(objectEventId);
    if (state == NULL || state->state != GHOST_STATE_SOLID)
        return NULL;

    if (IsGymGhostShuppet(&gObjectEvents[objectEventId]))
        return EventScript_GymShuppetInteract;

    return EventScript_GhostTown_ShuppetInteract;
}

#include "Game.h"
#include "Core/Constants.h"
#include "Utils/Math.h"
#include "Input/Input.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

WrGame* CreateGame(void) {
    WrGame* g = calloc(1, sizeof *g);
    if (!g) return NULL;

    if (!InitDefaultMap(&g->map)) {
        free(g);

        return NULL;
    }

    InitPlayer(&g->player, &g->map);

    return g;
}

void DestroyGame(WrGame* g) {
    if (!g) return;

    TerminateMap(&g->map);
    free(g);
}

static void MovePlayer(WrPlayer* p, const WrMap* m, float dx, float dy, bool isForward);

void UpdateGame(WrGame* g, WrInput* in, float dt) {
    WrMap* m = &g->map;
    WrPlayer* p = &g->player;

    if (in->keys[WR_KEY_A]) {
        RotateVector(&p->dir, -WR_PLAYER_TURN_SPEED * dt);
    }

    if (in->keys[WR_KEY_D]) {
        RotateVector(&p->dir, WR_PLAYER_TURN_SPEED * dt);
    }

    NormalizeVector(&p->dir);

    float playerMoveDeltaX = p->dir.x * WR_PLAYER_MOVE_SPEED * dt;
    float playerMoveDeltaY = p->dir.y * WR_PLAYER_MOVE_SPEED * dt;

    if (in->keys[WR_KEY_W]) {
        MovePlayer(p, m, playerMoveDeltaX, playerMoveDeltaY, true);
    }

    if (in->keys[WR_KEY_S]) {
        MovePlayer(p, m, playerMoveDeltaX, playerMoveDeltaY, false);
    }
}

static void MovePlayer(WrPlayer* p, const WrMap* m, float dx, float dy, bool isForward) {
    int sign = isForward ? 1 : -1;

    float newX = p->pos.x + sign * dx;
    float cx = newX + sign * WR_SIGN(dx) * WR_PLAYER_COLLISION_RADIUS;
    if (!IsMapCellSolid(m, (int)floorf(cx), (int)floorf(p->pos.y - WR_PLAYER_COLLISION_RADIUS)) &&
        !IsMapCellSolid(m, (int)floorf(cx), (int)floorf(p->pos.y + WR_PLAYER_COLLISION_RADIUS))) {
        p->pos.x = newX;
    }

    float newY = p->pos.y + sign * dy;
    float cy = newY + sign * WR_SIGN(dy) * WR_PLAYER_COLLISION_RADIUS;
    if (!IsMapCellSolid(m, (int)floorf(p->pos.x - WR_PLAYER_COLLISION_RADIUS), (int)floorf(cy)) &&
        !IsMapCellSolid(m, (int)floorf(p->pos.x + WR_PLAYER_COLLISION_RADIUS), (int)floorf(cy))) {
        p->pos.y = newY;
    }
}

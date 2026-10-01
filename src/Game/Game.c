#include "Game.h"
#include "Core/Constants.h"
#include "Utils/Math.h"

#include <stdlib.h>
#include <math.h>
#include <raylib.h>

Game* CreateGame(void) {
    Game* g = calloc(1, sizeof* g);
    if (!g) return NULL;

    if (!InitDefaultMap(&g->map)) {
        free(g);
        g = NULL;

        return NULL;
    }

    InitPlayer(&g->player, &g->map);

    return g;
}

void DestroyGame(Game* g) {
    if (!g) return;

    TerminateMap(&g->map);
    free(g);
    g = NULL;
}

void UpdateGame(Game* g, float dt) {
    Map* m = &g->map;
    Player* p = &g->player;

    if (IsKeyDown(KEY_A)) {
        RotateVector(&p->dir, -WR_PLAYER_TURN_SPEED * dt);
    }

    if (IsKeyDown(KEY_D)) {
        RotateVector(&p->dir, WR_PLAYER_TURN_SPEED * dt);
    }

    NormalizeVector(&p->dir);

    float playerMoveDeltaX = p->dir.x * WR_PLAYER_MOVE_SPEED * dt;
    float playerMoveDeltaY = p->dir.y * WR_PLAYER_MOVE_SPEED * dt;
    float playerCollisionRadius = 0.2f;

    if (IsKeyDown(KEY_W)) {
        float newX = p->pos.x + playerMoveDeltaX;
        if (!IsMapCellSolid(m, (int)floorf(newX + SIGN(playerMoveDeltaX) * playerCollisionRadius), (int)floorf(p->pos.y))) p->pos.x = newX;

        float newY = p->pos.y + playerMoveDeltaY;
        if (!IsMapCellSolid(m, (int)floorf(p->pos.x), (int)floorf(newY + SIGN(playerMoveDeltaY) * playerCollisionRadius))) p->pos.y = newY;
    }

    if (IsKeyDown(KEY_S)) {
        float newX = p->pos.x - playerMoveDeltaX;
        if (!IsMapCellSolid(m, (int)floorf(newX - SIGN(playerMoveDeltaX) * playerCollisionRadius), (int)floorf(p->pos.y))) p->pos.x = newX;

        float newY = p->pos.y - playerMoveDeltaY;
        if (!IsMapCellSolid(m, (int)floorf(p->pos.x), (int)floorf(newY - SIGN(playerMoveDeltaY) * playerCollisionRadius))) p->pos.y = newY;
    }
}
#include "Game.h"
#include "Core/Constants.h"
#include "Utils/Math.h"

#include <stdlib.h>
#include <raylib.h>

Game* CreateGame(void) {
    Game* g = (Game*)calloc(1, sizeof(Game));
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
        if (GetMapCell(m, (int)(newX + SIGN(playerMoveDeltaX) * playerCollisionRadius), (int)p->pos.y) == 0) p->pos.x = newX;

        float newY = p->pos.y + playerMoveDeltaY;
        if (GetMapCell(m, (int)p->pos.x, (int)(newY + SIGN(playerMoveDeltaY) * playerCollisionRadius)) == 0) p->pos.y = newY;
    }

    if (IsKeyDown(KEY_S)) {
        float newX = p->pos.x - playerMoveDeltaX;
        if (GetMapCell(m, (int)(newX - SIGN(playerMoveDeltaX) * playerCollisionRadius), (int)p->pos.y) == 0) p->pos.x = newX;

        float newY = p->pos.y - playerMoveDeltaY;
        if (GetMapCell(m, (int)p->pos.x, (int)(newY - SIGN(playerMoveDeltaY) * playerCollisionRadius)) == 0) p->pos.y = newY;
    }
}
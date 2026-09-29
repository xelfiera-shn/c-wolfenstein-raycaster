#include "Game.h"

#include <stdlib.h>
#include "Core/Constants.h"
#include "Platform/Platform.h"

Game* CreateGame(void) {
    Game* g = (Game*)calloc(1, sizeof(Game));
    if (!g) return NULL;

    InitConfig(&g->config);

    if (!InitDefaultMap(&g->map)) {
        free(g);

        return NULL;
    }

    InitPlayer(&g->player, &g->map);

    return g;
}

void DestroyGame(Game* g) {
    if (!g) return;

    TerminateMap(&g->map);
    free(g);
}

void UpdateGame(Game* g, float dt) {
    Config* c = &g->config;

    if (PlatformIsKeyPressed(PLATFORM_KEY_M)) c->renderer.isMinimapEnabled = !c->renderer.isMinimapEnabled;
    if (PlatformIsKeyPressed(PLATFORM_KEY_P)) c->renderer.isMinimapPlayerEnabled = !c->renderer.isMinimapPlayerEnabled;
    if (PlatformIsKeyPressed(PLATFORM_KEY_R)) c->renderer.isMinimapRaysEnabled = !c->renderer.isMinimapRaysEnabled;

    Map* m = &g->map;
    Player* p = &g->player;

    if (PlatformIsKeyDown(PLATFORM_KEY_A)) {
        RotateVector(&p->dir, -WR_PLAYER_TURN_SPEED * dt);
    }

    if (PlatformIsKeyDown(PLATFORM_KEY_D)) {
        RotateVector(&p->dir, WR_PLAYER_TURN_SPEED * dt);
    }

    NormalizeVector(&p->dir);

    float playerMoveDeltaX = p->dir.x * WR_PLAYER_MOVE_SPEED * dt;
    float playerMoveDeltaY = p->dir.y * WR_PLAYER_MOVE_SPEED * dt;

    if (PlatformIsKeyDown(PLATFORM_KEY_W)) {
        float newX = p->pos.x + playerMoveDeltaX;
        if (GetMapCell(m, (int)newX, (int)p->pos.y) == 0) p->pos.x = newX;

        float newY = p->pos.y + playerMoveDeltaY;
        if (GetMapCell(m, (int)p->pos.x, (int)newY) == 0) p->pos.y = newY;
    }

    if (PlatformIsKeyDown(PLATFORM_KEY_S)) {
        float newX = p->pos.x - playerMoveDeltaX;
        if (GetMapCell(m, (int)newX, (int)p->pos.y) == 0) p->pos.x = newX;

        float newY = p->pos.y - playerMoveDeltaY;
        if (GetMapCell(m, (int)p->pos.x, (int)newY) == 0) p->pos.y = newY;
    }
}
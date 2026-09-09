#include "Game.h"

#include <stdlib.h>
#include <math.h>

#include "Core/Constants.h"
#include "Platform/Platform.h"

Game* CreateGame(void) {
    Game* g = (Game*)calloc(1, sizeof(Game));
    if (!g) return NULL;

    InitializeConfig(&g->config);

    if (!InitializeMap(&g->map)) {
        free(g);

        return NULL;
    }
    
    InitializePlayer(&g->player);

    return g;
}

void DestroyGame(Game* g) {
    if (!g) return;

    TerminateMap(&g->map);
    free(g);
}

static bool IsBlocked(const Map* m, float x, float y);

void UpdateGame(Game* g, float dt) {
    Config* c = &g->config;
    c->minimap.isEnabled = PlatformIsKeyPressed(PLATFORM_KEY_M);
    c->minimap.isPlayerEnabled = PlatformIsKeyPressed(PLATFORM_KEY_N);
    c->minimap.isRaysEnabled = PlatformIsKeyPressed(PLATFORM_KEY_B);

    Map* m = &g->map;
    int mapPxW = m->w * WR_MAP_CELL_SIZE;
    int mapPxH = m->h * WR_MAP_CELL_SIZE;

    Player* p = &g->player;

    if (PlatformIsKeyDown(PLATFORM_KEY_A)) {
        RotateVector2D(&p->dir, WR_PLAYER_TURN_DELTA);
    }

    if (PlatformIsKeyDown(PLATFORM_KEY_D)) {
        RotateVector2D(&p->dir, -WR_PLAYER_TURN_DELTA);
    }

    float playerMoveDeltaX = p->dir.x * WR_PLAYER_MOVE_DELTA * dt;
    float playerMoveDeltaY = p->dir.y * WR_PLAYER_MOVE_DELTA * dt;

    if (PlatformIsKeyDown(PLATFORM_KEY_W)) {
        float nx = p->pos.x + playerMoveDeltaX;
        if (!IsBlocked(m, nx + WR_MAP_CELL_COLLISION_RADIUS, p->pos.y)) p->pos.x = nx;

        float ny = p->pos.y + playerMoveDeltaY;
        if (!IsBlocked(m, p->pos.x, ny + WR_MAP_CELL_COLLISION_RADIUS)) p->pos.y = ny;
    }

    if (PlatformIsKeyDown(PLATFORM_KEY_S)) {
        float nx = p->pos.x - playerMoveDeltaX;
        if (!IsBlocked(m, nx - WR_MAP_CELL_COLLISION_RADIUS, p->pos.y)) p->pos.x = nx;

        float ny = p->pos.y - playerMoveDeltaY;
        if (!IsBlocked(m, p->pos.x, ny - WR_MAP_CELL_COLLISION_RADIUS)) p->pos.y = ny;
    }
}

static bool IsBlocked(const Map* m, float x, float y) {
    if (x < 0.f || y < 0.f) return true;

    int cx = (int)(x / WR_MAP_CELL_SIZE);
    int cy = (int)(y / WR_MAP_CELL_SIZE);

    if (cx >= m->w || cy >= m->h) return true;

    return m->data[cy * m->w + cx] != 0;
}
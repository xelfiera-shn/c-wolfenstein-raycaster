#include "Renderer.h"
#include "Raycast/Raycast.h"

#include <stdlib.h>
#include <raylib.h>

Renderer* CreateRenderer(void) {
    Renderer* r = calloc(1, sizeof *r);
    if (!r) return NULL;

    r->screenWidth = GetScreenWidth();
    r->screenHeight = GetScreenHeight();
    r->rayCount = r->screenWidth;
    r->rays = calloc(r->rayCount, sizeof *r->rays);
    
    if (!r->rays) {
        free(r);
        r = NULL;
    }

    return r;
}

void DestroyRenderer(Renderer* r) {
    if (!r) return;

    free(r->rays);
    free(r);
}

void UpdateRenderer(Renderer* r, const Game* g) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    if (r->screenWidth != sw) {
        WrRay* tmp = realloc(r->rays, (size_t)sw * sizeof *tmp);
        if (!tmp) return;

        r->rays = tmp;
        r->rayCount = sw;
        r->screenWidth = sw;
    }
    
    if (r->screenHeight != sh) r->screenHeight = sh;
    
    CastRays(r->rays, r->rayCount, &g->map, &g->player);
}

static void RenderView(const WrRay* rays, int count, int sw, int sh);
static void RenderMinimap(const Renderer* r, const Game* g);

void RenderGame(const Renderer* r, const Game* g) {
    BeginDrawing();

    RenderView(r->rays, r->rayCount, r->screenWidth, r->screenHeight);
    RenderMinimap(r, g);

    DrawFPS(10, 10);
    EndDrawing();
}

static void RenderView(const WrRay* rays, int count, int sw, int sh) {
    DrawRectangle(0, 0, sw, sh / 2, SKYBLUE);
    DrawRectangle(0, sh / 2, sw, sh / 2, BEIGE);

    for (int i = 0; i < count; i++) {
        const WrRay* ray = &rays[i];

        float h = sh / ray->dist;
        if (h > sh) h = (float)sh;

        int rectStartY = (int)(sh - h) / 2;
        Color col = ray->hit == WR_HIT_VERTICAL ? DARKPURPLE : PURPLE;

        DrawRectangle(i, rectStartY, 1, (int)h, col);
    }
}

static void RenderMinimap(const Renderer* r, const Game* g) {
    const Map* m = &g->map;
    const Player* p = &g->player;

    int padding = 2;
    float minimapScale = 1.f / 30.f;

    // Render minimap bg
    int minimapCellSize = (int)((r->screenWidth < r->screenHeight ? r->screenWidth : r->screenHeight) * minimapScale);
    int minimapWidth = m->width * (minimapCellSize + padding) - padding;
    int minimapHeight = m->height * (minimapCellSize + padding) - padding;

    int minimapStartX = r->screenWidth - minimapWidth - padding;
    int minimapStartY = r->screenHeight - minimapHeight - padding;

    DrawRectangle(minimapStartX - padding, minimapStartY - padding, minimapWidth + 2 * padding, minimapHeight + 2 * padding, BLACK);
    
    for (int y = 0; y < m->height; y++) {
        for (int x = 0; x < m->width; x++) {
            int cellX = minimapStartX + x * (minimapCellSize + padding);
            int cellY = minimapStartY + y * (minimapCellSize + padding);
            Color col = IsMapCellSolid(m, x, y) ? PINK : GRAY;
            
            DrawRectangle(cellX, cellY, minimapCellSize, minimapCellSize, col);
        }
    }

    // Render player
    float playerX = minimapStartX + p->pos.x * (minimapCellSize + padding);
    float playerY = minimapStartY + p->pos.y * (minimapCellSize + padding);

    DrawCircle((int)playerX, (int)playerY, 3.f, SKYBLUE);

    float playerDirX = playerX + p->dir.x * minimapCellSize / 2.f;
    float playerDirY = playerY + p->dir.y * minimapCellSize / 2.f;

    DrawLine((int)playerX, (int)playerY, (int)playerDirX, (int)playerDirY, DARKBLUE);

    // Render rays
    for (int i = 0; i < r->rayCount; i++) {
        const WrRay* ray = &r->rays[i];

        float rayX = playerX + (ray->pos.x - p->pos.x) * (minimapCellSize + padding);
        float rayY = playerY + (ray->pos.y - p->pos.y) * (minimapCellSize + padding);

        DrawLine((int)playerX, (int)playerY, (int)rayX, (int)rayY, DARKGREEN);
    }
}
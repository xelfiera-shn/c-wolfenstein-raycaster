#include "Renderer.h"

#include <stdlib.h>
#include "Platform/Platform.h"
#include "Raycast/Raycast.h"

Renderer* CreateRenderer(void) {
    Renderer* r = (Renderer*)calloc(1, sizeof(Renderer));
    if (!r) return NULL;

    r->screenWidth = PlatformGetScreenWidth();
    r->screenHeight = PlatformGetScreenHeight();
    r->rayCount = r->screenWidth;
    r->rays = (WrRay*)calloc(r->rayCount, sizeof(WrRay));
    
    if (!r->rays) {
        free(r);
        r = NULL;
    }

    return r;
}

void DestroyRenderer(Renderer* r) {
    if (!r) return;

    if (r->rays) {
        free(r->rays);
        r->rays = NULL;
    }

    free(r);
    r = NULL;
}

void UpdateRenderer(Renderer* r, Game* g) {
    int sw = PlatformGetScreenWidth();
    int sh = PlatformGetScreenHeight();

    if (r->screenWidth != sw) {
        r->screenWidth = sw;
        r->rayCount = sw;

        free(r->rays);
        r->rays = (WrRay*)calloc(r->rayCount, sizeof(WrRay));
        if (!r->rays) return;
    }
    
    if (r->screenHeight != sh) r->screenHeight = sh;
    
    CastRays(r->rays, r->rayCount, &g->map, &g->player);
}

void RenderGame(Renderer* r, Game* g) {
    Config* c = &g->config;
    Map* m = &g->map;
    Player* p = &g->player;

    PlatformDrawRectangle(0, 0, r->screenWidth, r->screenHeight / 2, PLATFORM_SKYBLUE);
    PlatformDrawRectangle(0, r->screenHeight / 2, r->screenWidth, r->screenHeight / 2, PLATFORM_BEIGE);

    for (int i = 0; i < r->rayCount; i++) {
        WrRay* ray = &r->rays[i];

        float h = r->screenHeight / ray->dist;
        if (h > r->screenHeight) h = (float)r->screenHeight;

        int rectStartY = (int)(r->screenHeight - h) / 2;
        WrColor col = ray->hit == WR_HIT_VERTICAL ? PLATFORM_DARKPURPLE : PLATFORM_PURPLE;

        PlatformDrawRectangle(i, rectStartY, 1, (int)h, col);
    }

    if (c->renderer.isMinimapEnabled) {
        int padding = 2;
        int minimapScale = 30;

        int minimapCellSize = (r->screenWidth < r->screenHeight ? r->screenWidth : r->screenHeight) / minimapScale;

        int minimapWidth = m->width * (minimapCellSize + padding) - padding;
        int minimapHeight = m->height * (minimapCellSize + padding) - padding;

        int minimapStartX = r->screenWidth - minimapWidth - padding;
        int minimapStartY = r->screenHeight - minimapHeight - padding;

        PlatformDrawRectangle(minimapStartX - padding, minimapStartY - padding, minimapWidth + 2 * padding, minimapHeight + 2 * padding, PLATFORM_BLACK);
        
        for (int y = 0; y < m->height; y++) {
            for (int x = 0; x < m->width; x++) {
                int cellX = minimapStartX + x * (minimapCellSize + padding);
                int cellY = minimapStartY + y * (minimapCellSize + padding);

                WrColor col = GetMapCell(m, x, y) > 0 ? PLATFORM_PINK : PLATFORM_GRAY;

                PlatformDrawRectangle(cellX, cellY, minimapCellSize, minimapCellSize, col);
            }
        }

        if (c->renderer.isMinimapPlayerEnabled) {
            float playerX = minimapStartX + p->pos.x * (minimapCellSize + padding);
            float playerY = minimapStartY + p->pos.y * (minimapCellSize + padding);

            PlatformDrawCircle((int)playerX, (int)playerY, 3.f, PLATFORM_SKYBLUE);

            float playerDirX = playerX + p->dir.x * minimapCellSize / 2.f;
            float playerDirY = playerY + p->dir.y * minimapCellSize / 2.f;

            PlatformDrawLine((int)playerX, (int)playerY, (int)playerDirX, (int)playerDirY, PLATFORM_DARKBLUE);

            if (c->renderer.isMinimapRaysEnabled) {
                for (int i = 0; i < r->rayCount; i++) {
                    WrRay* ray = &r->rays[i];

                    float rayX = playerX + (ray->pos.x - p->pos.x) * (minimapCellSize + padding);
                    float rayY = playerY + (ray->pos.y - p->pos.y) * (minimapCellSize + padding);

                    PlatformDrawLine((int)playerX, (int)playerY, (int)rayX, (int)rayY, PLATFORM_DARKGREEN);
                }
            }
        }
    }
}
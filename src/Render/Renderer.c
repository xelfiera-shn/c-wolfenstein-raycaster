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
    r->rays = (Ray*)calloc(r->rayCount, sizeof(Ray));
    
    if (!r->rays) {
        free(r);

        return NULL;
    }

    return r;
}

void DestroyRenderer(Renderer* r) {
    if (!r) return;

    if (r->rays) {
        free(r->rays);
    }

    free(r);
}

void UpdateRenderer(Renderer* r, Game* g) {
    int sw = PlatformGetScreenWidth();
    int sh = PlatformGetScreenHeight();

    if (r->screenWidth != sw) {
        r->screenWidth = sw;
        r->rayCount = sw;
        r->rays = (Ray*)calloc(r->rayCount, sizeof(Ray));
    }
    
    if (r->screenHeight != sh) r->screenHeight = sh;
    
    CastRays(r, g);
}

void RenderGame(Renderer* r, Game* g) {
    Config* c = &g->config;
    Map* m = &g->map;
    Player* p = &g->player;

    for (int i = 0; i < r->rayCount; i++) {
        Ray* ray = &r->rays[i];

        float h = r->screenWidth / ray->dist;
        int rectStartY = (int)(r->screenWidth - h) / 2;
        WrColor col = ray->hit == WR_HIT_VERTICAL ? PLATFORM_PURPLE : PLATFORM_MAGENTA;

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
            int playerX = (int)(minimapStartX + (p->pos.x + 1.f) * (minimapCellSize + padding));
            int playerY = (int)(minimapStartY + (p->pos.y + 1.f) * (minimapCellSize + padding));

            PlatformDrawCircle(playerX, playerY, 3.f, PLATFORM_SKYBLUE);

            if (c->renderer.isMinimapRaysEnabled) {
                int playerDirX = (int)(playerX + p->dir.x * minimapCellSize / 2.f);
                int playerDirY = (int)(playerY + p->dir.y * minimapCellSize / 2.f);

                PlatformDrawLine(playerX, playerY, playerDirX, playerDirY, PLATFORM_DARKBLUE);
            }
        }
    }
}
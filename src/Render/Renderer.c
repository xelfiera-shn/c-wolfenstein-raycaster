#include "Renderer.h"
#include "Core/Constants.h"
#include "Raycast/Ray.h"
#include "Raycast/Raycast.h"
#include "Game/Game.h"

#include <stdlib.h>
#include <raylib.h>

struct WrRenderer {
    int screenWidth;  // Width of window screen
    int screenHeight; // Height of window screen

    int rayCount; // Count of rays (same as inner width but that's understandable then)
    WrRay* rays;

    int innerWidth;
    int innerHeight;
    Color* pixels; // Unsigned char R, G, B, A
    Texture2D frame;
};

WrRenderer* CreateRenderer(void) {
    WrRenderer* r = calloc(1, sizeof *r);
    if (!r) return NULL;

    r->screenWidth = GetScreenWidth();
    r->screenHeight = GetScreenHeight();
    r->rayCount = WR_INNER_WIDTH;

    r->rays = calloc(r->rayCount, sizeof *r->rays);
    if (!r->rays) {
        free(r);

        return NULL;
    }

    r->innerWidth = WR_INNER_WIDTH;
    r->innerHeight = WR_INNER_HEIGHT;

    r->pixels = calloc(r->innerWidth * r->innerHeight, sizeof *r->pixels);
    if (!r->pixels) {
        free(r->rays);
        free(r);

        return NULL;
    }

    Image img = GenImageColor(r->innerWidth, r->innerHeight, BLACK);
    r->frame = LoadTextureFromImage(img);

    UnloadImage(img);

    return r;
}

void DestroyRenderer(WrRenderer* r) {
    if (!r) return;

    UnloadTexture(r->frame);
    free(r->pixels);
    free(r->rays);
    free(r);
}

void UpdateRenderer(WrRenderer* r, const WrGame* g) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    if (sw <= 0 || sh <= 0) return;

    if (r->screenWidth != sw) r->screenWidth = sw;
    if (r->screenHeight != sh) r->screenHeight = sh;

    CastRays(r->rays, r->rayCount, &g->map, &g->player);
}

static void RenderView(const WrRay* rays, int count, int sw, int sh);
static void RenderMinimap(const WrRenderer* r, const WrGame* g);

void RenderGame(const WrRenderer* r, const WrGame* g) {
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

        int rectStartY = (int)((sh - h) / 2.f);
        Color col = ray->hit == WR_HIT_VERTICAL ? DARKPURPLE : PURPLE;

        DrawRectangle(i, rectStartY, 1, (int)h, col);
    }
}

static void RenderMinimap(const WrRenderer* r, const WrGame* g) {
    const WrMap* m = &g->map;
    const WrPlayer* p = &g->player;

    int padding = 2;
    float minimapScale = 1.f / 30.f;

    // Render minimap bg
    int minimapCellSize = (int)((r->screenWidth < r->screenHeight ? r->screenWidth : r->screenHeight) * minimapScale);
    int minimapWidth = m->width * (minimapCellSize + padding) - padding;
    int minimapHeight = m->height * (minimapCellSize + padding) - padding;

    int minimapStartX = r->screenWidth - minimapWidth - padding;
    int minimapStartY = r->screenHeight - minimapHeight - padding;

    DrawRectangle(minimapStartX - padding, minimapStartY - padding, minimapWidth + 2 * padding,
                  minimapHeight + 2 * padding, BLACK);

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

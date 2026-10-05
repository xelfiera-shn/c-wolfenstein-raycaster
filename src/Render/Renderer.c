#include "Renderer.h"
#include "Core/Constants.h"
#include "Raycast/Ray.h"
#include "Raycast/Raycast.h"
#include "Framebuffer.h"
#include "Game/Game.h"

#include <stdlib.h>
#include <raylib.h>

struct WrRenderer {
    int screenWidth;  // Width of window screen
    int screenHeight; // Height of window screen

    int rayCount; // Count of rays (same as inner width but that's understandable then)
    WrRay* rays;

    Framebuffer fb;
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

    r->fb.width = WR_INNER_WIDTH;
    r->fb.height = WR_INNER_HEIGHT;

    r->fb.buffer = calloc(r->fb.width * r->fb.height, sizeof *r->fb.buffer);
    if (!r->fb.buffer) {
        free(r->rays);
        free(r);

        return NULL;
    }

    Image img = GenImageColor(r->fb.width, r->fb.height, BLACK);
    r->fb.frame = LoadTextureFromImage(img);
    UnloadImage(img);

    SetTextureFilter(r->fb.frame, TEXTURE_FILTER_POINT);

    return r;
}

void DestroyRenderer(WrRenderer* r) {
    if (!r) return;

    UnloadTexture(r->fb.frame);
    free(r->fb.buffer);
    free(r->rays);
    free(r);
}

static void DrawViewToFramebuffer(Color* buffer, int width, int height, const WrRay* rays, int count);

void UpdateRenderer(WrRenderer* r, const WrGame* g) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    if (sw <= 0 || sh <= 0) return;

    if (r->screenWidth != sw) r->screenWidth = sw;
    if (r->screenHeight != sh) r->screenHeight = sh;

    CastRays(r->rays, r->rayCount, &g->map, &g->player);

    DrawViewToFramebuffer(r->fb.buffer, r->fb.width, r->fb.height, r->rays, r->rayCount);
    UpdateTexture(r->fb.frame, r->fb.buffer);
}

static void RenderMinimap(const WrRenderer* r, const WrGame* g);

void RenderGame(const WrRenderer* r, const WrGame* g) {
    BeginDrawing();

    DrawTexturePro(r->fb.frame, (Rectangle){0.f, 0.f, (float)r->fb.width, (float)r->fb.height},
                   (Rectangle){0.f, 0.f, (float)r->screenWidth, (float)r->screenHeight}, (Vector2){0.f, 0.f}, 0.f,
                   WHITE);

    RenderMinimap(r, g);

    DrawFPS(10, 10);
    EndDrawing();
}

static void DrawViewToFramebuffer(Color* buffer, int width, int height, const WrRay* rays, int count) {
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * width + x] = SKYBLUE;
        }
    }

    for (int y = height / 2; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * width + x] = BEIGE;
        }
    }

    for (int i = 0; i < count; i++) {
        const WrRay* ray = &rays[i];

        float h = height / ray->dist;
        if (h > height) h = (float)height;

        int rectStartY = (int)((height - h) / 2.f);
        Color col = ray->hit == WR_HIT_VERTICAL ? DARKPURPLE : PURPLE;

        for (int y = rectStartY; y < rectStartY + h; y++) {
            buffer[y * width + i] = col;
        }
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

#include "Renderer.h"
#include "Core/Constants.h"
#include "Raycast/Ray.h"
#include "Raycast/Raycast.h"
#include "Game/Game.h"

#include <stdlib.h>
#include <raylib.h>

static void InitTextures(WrTexture* textures);

bool InitRenderer(WrRenderer* r) {
    r->screenWidth = GetScreenWidth();
    r->screenHeight = GetScreenHeight();
    r->rayCount = WR_INNER_WIDTH;

    r->rays = calloc(r->rayCount, sizeof *r->rays);
    if (!r->rays) return false;

    InitTextures(r->textures);

    if (!InitFramebuffer(&r->fb, WR_INNER_WIDTH, WR_INNER_HEIGHT)) {
        free(r->rays);
        r->rays = NULL;

        return false;
    }

    return true;
}

void TerminateRenderer(WrRenderer* r) {
    if (!r) return;

    TerminateFramebuffer(&r->fb);
    free(r->rays);
    r->rays = NULL;
}

static void DrawViewToFramebuffer(Color* buffer, int width, int height, const WrRay* rays, int count);

void UpdateRenderer(WrRenderer* r, const WrGame* g) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    if (sw <= 0 || sh <= 0) return;

    if (r->screenWidth != sw || r->screenHeight != sh) {
        r->screenWidth = sw;
        r->screenHeight = sh;
    }

    CastRays(r->rays, r->rayCount, &g->map, &g->player);

    DrawViewToFramebuffer(r->fb.buffer, r->fb.width, r->fb.height, r->rays, r->rayCount);
    UpdateTexture(r->fb.frame, r->fb.buffer);
}

static void RenderMinimap(const WrRenderer* r, const WrGame* g);

void RenderGame(const WrRenderer* r, const WrGame* g) {
    BeginDrawing();
    ClearBackground(BLACK);

    float scale = WR_MIN((float)r->screenWidth / r->fb.width, (float)r->screenHeight / r->fb.height);
    float dstWidth = r->fb.width * scale;
    float dstHeight = r->fb.height * scale;
    Rectangle src = {0.f, 0.f, (float)r->fb.width, (float)r->fb.height};
    Rectangle dst = {(r->screenWidth - dstWidth) / 2.f, (r->screenHeight - dstHeight) / 2.f, dstWidth, dstHeight};
    DrawTexturePro(r->fb.frame, src, dst, (Vector2){0.f, 0.f}, 0.f, WHITE);

    RenderMinimap(r, g);

    DrawFPS(10, 10);
    EndDrawing();
}

static void InitTextures(WrTexture* textures) {
    InitTexture(&textures[WR_TEXTURE_BRICK_1], "res/texture/Brick/Brick01.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_2], "res/texture/Brick/Brick02.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_3], "res/texture/Brick/Brick03.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_4], "res/texture/Brick/Brick04.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_5], "res/texture/Brick/Brick05.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_6], "res/texture/Brick/Brick06.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_7], "res/texture/Brick/Brick07.png");
    InitTexture(&textures[WR_TEXTURE_BRICK_8], "res/texture/Brick/Brick08.png");

    InitTexture(&textures[WR_TEXTURE_CURSED_1], "res/texture/Cursed/Cursed01.png");
    InitTexture(&textures[WR_TEXTURE_CURSED_2], "res/texture/Cursed/Cursed02.png");
    InitTexture(&textures[WR_TEXTURE_CURSED_3], "res/texture/Cursed/Cursed03.png");
    InitTexture(&textures[WR_TEXTURE_CURSED_4], "res/texture/Cursed/Cursed04.png");
    InitTexture(&textures[WR_TEXTURE_CURSED_5], "res/texture/Cursed/Cursed05.png");
    InitTexture(&textures[WR_TEXTURE_CURSED_6], "res/texture/Cursed/Cursed06.png");

    InitTexture(&textures[WR_TEXTURE_DOORS_1], "res/texture/Doors/Doors01.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_2], "res/texture/Doors/Doors02.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_3], "res/texture/Doors/Doors03.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_4], "res/texture/Doors/Doors04.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_5], "res/texture/Doors/Doors05.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_6], "res/texture/Doors/Doors06.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_7], "res/texture/Doors/Doors07.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_8], "res/texture/Doors/Doors08.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_9], "res/texture/Doors/Doors09.png");
    InitTexture(&textures[WR_TEXTURE_DOORS_10], "res/texture/Doors/Doors10.png");

    InitTexture(&textures[WR_TEXTURE_SCENERY_1], "res/texture/Scenery/Scenery01.png");
    InitTexture(&textures[WR_TEXTURE_SCENERY_2], "res/texture/Scenery/Scenery02.png");

    InitTexture(&textures[WR_TEXTURE_STONE_1], "res/texture/Stone/Stone01.png");
    InitTexture(&textures[WR_TEXTURE_STONE_2], "res/texture/Stone/Stone02.png");
    InitTexture(&textures[WR_TEXTURE_STONE_3], "res/texture/Stone/Stone03.png");
    InitTexture(&textures[WR_TEXTURE_STONE_4], "res/texture/Stone/Stone04.png");
    InitTexture(&textures[WR_TEXTURE_STONE_5], "res/texture/Stone/Stone05.png");
    InitTexture(&textures[WR_TEXTURE_STONE_6], "res/texture/Stone/Stone06.png");
    InitTexture(&textures[WR_TEXTURE_STONE_7], "res/texture/Stone/Stone07.png");
    InitTexture(&textures[WR_TEXTURE_STONE_8], "res/texture/Stone/Stone08.png");
    InitTexture(&textures[WR_TEXTURE_STONE_9], "res/texture/Stone/Stone09.png");
    InitTexture(&textures[WR_TEXTURE_STONE_10], "res/texture/Stone/Stone10.png");
    InitTexture(&textures[WR_TEXTURE_STONE_11], "res/texture/Stone/Stone11.png");

    InitTexture(&textures[WR_TEXTURE_TILES_1], "res/texture/Tiles/Tiles01.png");
    InitTexture(&textures[WR_TEXTURE_TILES_2], "res/texture/Tiles/Tiles02.png");
    InitTexture(&textures[WR_TEXTURE_TILES_3], "res/texture/Tiles/Tiles03.png");
    InitTexture(&textures[WR_TEXTURE_TILES_4], "res/texture/Tiles/Tiles04.png");
    InitTexture(&textures[WR_TEXTURE_TILES_5], "res/texture/Tiles/Tiles05.png");
    InitTexture(&textures[WR_TEXTURE_TILES_6], "res/texture/Tiles/Tiles06.png");
    InitTexture(&textures[WR_TEXTURE_TILES_7], "res/texture/Tiles/Tiles07.png");
    InitTexture(&textures[WR_TEXTURE_TILES_8], "res/texture/Tiles/Tiles08.png");
    InitTexture(&textures[WR_TEXTURE_TILES_9], "res/texture/Tiles/Tiles09.png");
    InitTexture(&textures[WR_TEXTURE_TILES_10], "res/texture/Tiles/Tiles10.png");
    InitTexture(&textures[WR_TEXTURE_TILES_11], "res/texture/Tiles/Tiles11.png");

    InitTexture(&textures[WR_TEXTURE_WOOD_1], "res/texture/Wood/Wood01.png");
    InitTexture(&textures[WR_TEXTURE_WOOD_2], "res/texture/Wood/Wood02.png");
    InitTexture(&textures[WR_TEXTURE_WOOD_3], "res/texture/Wood/Wood03.png");
    InitTexture(&textures[WR_TEXTURE_WOOD_4], "res/texture/Wood/Wood04.png");
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

#include "Renderer.h"
#include "Core/Constants.h"
#include "Raycast/Ray.h"
#include "Raycast/Raycast.h"
#include "Game/Game.h"

#include <stdlib.h>
#include <math.h>
#include <raylib.h>

bool InitRenderer(WrRenderer* r) {
    r->screenWidth = GetScreenWidth();
    r->screenHeight = GetScreenHeight();

    r->rays = calloc(WR_INNER_WIDTH, sizeof *r->rays);
    if (!r->rays) return false;

    InitTextures(r->textures);

    if (!InitFramebuffer(&r->fb, WR_INNER_WIDTH, WR_INNER_HEIGHT, r->screenWidth, r->screenHeight)) {
        free(r->rays);
        r->rays = NULL;

        TerminateTextures(r->textures);

        return false;
    }

    return true;
}

void TerminateRenderer(WrRenderer* r) {
    if (!r) return;

    TerminateFramebuffer(&r->fb);
    free(r->rays);
    r->rays = NULL;

    TerminateTextures(r->textures);
}

static void DrawWallsToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrMap* m);
static void DrawCeilToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrPlayer* p);
static void DrawFloorToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrPlayer* p);

void UpdateRenderer(WrRenderer* r, const WrGame* g) {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    if (sw <= 0 || sh <= 0) return;

    if (r->screenWidth != sw || r->screenHeight != sh) {
        r->screenWidth = sw;
        r->screenHeight = sh;
        UpdateFramebufferScale(&r->fb, r->screenWidth, r->screenHeight);
    }

    CastRays(r->rays, r->fb.width, &g->map, &g->player);

    DrawWallsToFramebuffer(&r->fb, r->rays, r->textures, &g->map);
    DrawCeilToFramebuffer(&r->fb, r->rays, r->textures, &g->player);
    DrawFloorToFramebuffer(&r->fb, r->rays, r->textures, &g->player);

    UpdateTexture(r->fb.frame, r->fb.buffer);
}

static void RenderMinimap(const WrRenderer* r, const WrGame* g);

void RenderGame(const WrRenderer* r, const WrGame* g) {
    BeginDrawing();
    ClearBackground(BLACK);

    float dstWidth = r->fb.width * r->fb.scale;
    float dstHeight = r->fb.height * r->fb.scale;
    Rectangle src = {0.f, 0.f, (float)r->fb.width, (float)r->fb.height};
    Rectangle dst = {(r->screenWidth - dstWidth) / 2.f, (r->screenHeight - dstHeight) / 2.f, dstWidth, dstHeight};
    DrawTexturePro(r->fb.frame, src, dst, (Vector2){0.f, 0.f}, 0.f, WHITE);

    RenderMinimap(r, g);

    DrawFPS(10, 10);
    EndDrawing();
}

static void DrawWallsToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrMap* m) {
    for (int i = 0; i < fb->width; i++) {
        const WrRay* ray = &rays[i];
        if (ray->face == WR_WALL_FACE_NONE) continue;

        const WrTexture* texture = GetTexture(textures, GetMapCell(m, ray->cellX, ray->cellY));

        float h = fb->height / ray->dist;
        bool isVerticalHit = IsVerticalHit(ray->face);

        float wallX = isVerticalHit ? ray->pos.y - floorf(ray->pos.y) : ray->pos.x - floorf(ray->pos.x);
        if (ray->face == WR_WALL_FACE_EAST || ray->face == WR_WALL_FACE_NORTH) wallX = 1.f - wallX;

        int textureColumn = (int)(wallX * texture->width);
        if (textureColumn >= texture->width) textureColumn = texture->width - 1;

        float brightness = 1.f - ray->dist / WR_FOG_DISTANCE;
        brightness = WR_CLAMP(brightness, WR_FOG_MIN_BRIGHTNESS_FACTOR, 1.f);
        if (isVerticalHit) brightness *= WR_VERTICAL_HIT_BRIGHTNESS_FACTOR;

        int startY = (int)((fb->height - h) / 2.f);
        int endY = startY + (int)h;

        int drawStart = startY < 0 ? 0 : startY;
        int drawEnd = endY > fb->height ? fb->height : endY;

        for (int y = drawStart; y < drawEnd; y++) {
            int textureRow = (int)((y - startY) * texture->height / h);
            if (textureRow >= texture->height) textureRow = texture->height - 1;

            Color col = texture->data[textureRow * texture->width + textureColumn];
            col = (Color){(unsigned char)(col.r * brightness), (unsigned char)(col.g * brightness), (unsigned char)(col.b * brightness), col.a};

            fb->buffer[y * fb->width + i] = col;
        }

        fb->wallStarts[i] = drawStart;
        fb->wallEnds[i] = drawEnd;
    }
}

static void DrawCeilToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrPlayer* p) {
    const WrTexture* texture = GetTexture(textures, WR_TEXTURE_TILES_4);

    for (int i = 0; i < fb->width; i++) {
        int start = fb->wallStarts[i];
        int half = fb->height / 2;
        if (start >= half) start = half - 1;

        const WrRay* ray = &rays[i];
        float rayX = ray->pos.x - p->pos.x;
        float rayY = ray->pos.y - p->pos.y;

        for (int y = start; y >= 0; y--) {
            float d = half - (float)y; // Pixel dist from horizon
            float ceilDist = half / d; // Perpendicular dist from player

            float scale = ceilDist / ray->dist;
            float ceilX = p->pos.x + rayX * scale;
            float ceilY = p->pos.y + rayY * scale;

            float brightness = 1.f - ceilDist / WR_FOG_DISTANCE;
            brightness = WR_CLAMP(brightness, WR_FOG_MIN_BRIGHTNESS_FACTOR, 1.f);

            int textureColumn = (int)((ceilX - floorf(ceilX)) * texture->width);
            if (textureColumn == texture->width) textureColumn = texture->width - 1;

            int textureRow = (int)((ceilY - floorf(ceilY)) * texture->height);
            if (textureRow == texture->height) textureRow = texture->height - 1;

            Color col = texture->data[textureRow * texture->width + textureColumn];
            col = (Color){(unsigned char)(col.r * brightness), (unsigned char)(col.g * brightness), (unsigned char)(col.b * brightness), col.a};

            fb->buffer[y * fb->width + i] = col;
        }
    }
}

static void DrawFloorToFramebuffer(WrFramebuffer* fb, const WrRay* rays, const WrTexture* textures, const WrPlayer* p) {
    const WrTexture* texture = GetTexture(textures, WR_TEXTURE_TILES_4);

    for (int i = 0; i < fb->width; i++) {
        int start = fb->wallEnds[i];
        int half = fb->height / 2;
        if (start <= half) start = half + 1;

        const WrRay* ray = &rays[i];
        float rayX = ray->pos.x - p->pos.x;
        float rayY = ray->pos.y - p->pos.y;

        for (int y = start; y < fb->height; y++) {
            float d = (float)y - half;  // Pixel dist from horizon
            float floorDist = half / d; // Perpendicular dist from player

            float scale = floorDist / ray->dist;
            float floorX = p->pos.x + rayX * scale;
            float floorY = p->pos.y + rayY * scale;

            float brightness = 1.f - floorDist / WR_FOG_DISTANCE;
            brightness = WR_CLAMP(brightness, WR_FOG_MIN_BRIGHTNESS_FACTOR, 1.f);

            int textureColumn = (int)((floorX - floorf(floorX)) * texture->width);
            if (textureColumn == texture->width) textureColumn = texture->width - 1;

            int textureRow = (int)((floorY - floorf(floorY)) * texture->height);
            if (textureRow == texture->height) textureRow = texture->height - 1;

            Color col = texture->data[textureRow * texture->width + textureColumn];
            col = (Color){(unsigned char)(col.r * brightness), (unsigned char)(col.g * brightness), (unsigned char)(col.b * brightness), col.a};

            fb->buffer[y * fb->width + i] = col;
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
    for (int i = 0; i < r->fb.width; i++) {
        const WrRay* ray = &r->rays[i];

        float rayX = playerX + (ray->pos.x - p->pos.x) * (minimapCellSize + padding);
        float rayY = playerY + (ray->pos.y - p->pos.y) * (minimapCellSize + padding);

        DrawLine((int)playerX, (int)playerY, (int)rayX, (int)rayY, DARKGREEN);
    }
}

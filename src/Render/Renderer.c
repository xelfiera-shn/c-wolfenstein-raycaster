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
        TerminateTextures(r->textures);

        free(r->rays);
        r->rays = NULL;

        return false;
    }

    r->wallStarts = calloc(r->fb.width, sizeof *r->wallStarts);
    r->wallEnds = calloc(r->fb.width, sizeof *r->wallEnds);
    r->fcTable = calloc(r->fb.height, sizeof *r->fcTable);

    if (!r->wallStarts || !r->wallEnds || !r->fcTable) {
        TerminateRenderer(r);

        return false;
    }

    int horizon = r->fb.height / 2;
    for (int y = 0; y < r->fb.height; y++) {
        float d = fabsf(y + 0.5f - horizon);
        r->fcTable[y].dist = horizon / d;

        float brightness = 1.f - r->fcTable[y].dist / WR_FOG_DISTANCE;
        brightness = WR_CLAMP(brightness, WR_FOG_MIN_BRIGHTNESS_FACTOR, 1.f);

        r->fcTable[y].brightness = brightness;
    }

    return true;
}

void TerminateRenderer(WrRenderer* r) {
    if (!r) return;

    free(r->fcTable);
    r->fcTable = NULL;

    free(r->wallEnds);
    r->wallEnds = NULL;

    free(r->wallStarts);
    r->wallStarts = NULL;

    TerminateFramebuffer(&r->fb);
    TerminateTextures(r->textures);

    free(r->rays);
    r->rays = NULL;
}

static void DrawWallsToFramebuffer(WrRenderer* r, const WrMap* m);
static void DrawFloorAndCeilToFramebuffer(WrRenderer* r, const WrPlayer* p);

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

    DrawWallsToFramebuffer(r, &g->map);
    DrawFloorAndCeilToFramebuffer(r, &g->player);

    UpdateTexture(r->fb.frame, r->fb.buffer);
}

void RenderGame(const WrRenderer* r) {
    BeginDrawing();
    ClearBackground(BLACK);

    float dstWidth = r->fb.width * r->fb.scale;
    float dstHeight = r->fb.height * r->fb.scale;
    Rectangle src = {0.f, 0.f, (float)r->fb.width, (float)r->fb.height};
    Rectangle dst = {(r->screenWidth - dstWidth) / 2.f, (r->screenHeight - dstHeight) / 2.f, dstWidth, dstHeight};
    DrawTexturePro(r->fb.frame, src, dst, (Vector2){0.f, 0.f}, 0.f, WHITE);

    DrawFPS(10, 10);
    EndDrawing();
}

static void DrawWallsToFramebuffer(WrRenderer* r, const WrMap* m) {
    for (int i = 0; i < r->fb.width; i++) {
        const WrRay* ray = &r->rays[i];
        if (ray->face == WR_WALL_FACE_NONE) {
            r->wallStarts[i] = r->fb.height / 2;
            r->wallEnds[i] = r->fb.height / 2 - 1;

            continue;
        }

        const WrTexture* texture = GetTexture(r->textures, GetMapCell(m, ray->cellX, ray->cellY));

        float h = r->fb.height / ray->dist;
        bool isVerticalHit = IsVerticalHit(ray->face);

        float wallX = isVerticalHit ? ray->pos.y - floorf(ray->pos.y) : ray->pos.x - floorf(ray->pos.x);
        if (ray->face == WR_WALL_FACE_EAST || ray->face == WR_WALL_FACE_NORTH) wallX = 1.f - wallX;

        int textureColumn = (int)(wallX * texture->width);
        if (textureColumn >= texture->width) textureColumn = texture->width - 1;

        float brightness = 1.f - ray->dist / WR_FOG_DISTANCE;
        brightness = WR_CLAMP(brightness, WR_FOG_MIN_BRIGHTNESS_FACTOR, 1.f);
        if (isVerticalHit) brightness *= WR_VERTICAL_HIT_BRIGHTNESS_FACTOR;

        int startY = (int)((r->fb.height - h) / 2.f);
        int endY = startY + (int)h;

        int drawStart = startY < 0 ? 0 : startY;
        int drawEnd = endY > r->fb.height ? r->fb.height : endY;

        for (int y = drawStart; y < drawEnd; y++) {
            int textureRow = (int)((y - startY) * texture->height / h);
            if (textureRow >= texture->height) textureRow = texture->height - 1;

            Color col = texture->data[textureRow * texture->width + textureColumn];
            col = (Color){(unsigned char)(col.r * brightness), (unsigned char)(col.g * brightness), (unsigned char)(col.b * brightness), col.a};

            r->fb.buffer[y * r->fb.width + i] = col;
        }

        r->wallStarts[i] = drawStart;
        r->wallEnds[i] = drawEnd - 1;
    }
}

static void DrawFloorAndCeilToFramebuffer(WrRenderer* r, const WrPlayer* p) {
    const WrTexture* texture = GetTexture(r->textures, WR_TEXTURE_TILES_4);

    for (int x = 0; x < r->fb.width; x++) {
        const WrRay* ray = &r->rays[x];
        float invDist = 1.f / ray->dist;
        float rayX = ray->pos.x - p->pos.x;
        float rayY = ray->pos.y - p->pos.y;

        for (int y = 0; y < r->fb.height; y++) {
            if ((y >= 0 && y < r->wallStarts[x]) || (y > r->wallEnds[x] && y < r->fb.height)) {
                float dist = r->fcTable[y].dist;
                float brightness = r->fcTable[y].brightness;

                float scale = dist * invDist;
                float posX = p->pos.x + rayX * scale;
                float posY = p->pos.y + rayY * scale;

                int textureColumn = (int)((posX - floorf(posX)) * texture->width);
                if (textureColumn == texture->width) textureColumn = texture->width - 1;

                int textureRow = (int)((posY - floorf(posY)) * texture->height);
                if (textureRow == texture->height) textureRow = texture->height - 1;

                Color col = texture->data[textureRow * texture->width + textureColumn];
                col = (Color){(unsigned char)(col.r * brightness), (unsigned char)(col.g * brightness), (unsigned char)(col.b * brightness), col.a};

                r->fb.buffer[y * r->fb.width + x] = col;
            }
        }
    }
}

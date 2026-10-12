#ifndef WR_RENDERER_H
#define WR_RENDERER_H

#include "Raycast/Ray.h"
#include "Texture.h"
#include "Framebuffer.h"

#include <stdbool.h>

typedef struct WrGame WrGame;

typedef struct WrRenderer {
    int screenWidth;  // Width of window screen
    int screenHeight; // Height of window screen

    WrRay* rays;
    WrFramebuffer fb;
    WrTexture textures[WR_TEXTURE_COUNT];

    int* wallStarts;
    int* wallEnds;
    float* fcDists; // Perpendicular floor and ceil dists from player
} WrRenderer;

bool InitRenderer(WrRenderer* r);
void TerminateRenderer(WrRenderer* r);

void UpdateRenderer(WrRenderer* r, const WrGame* g);
void RenderGame(const WrRenderer* r);

#endif // WR_RENDERER_H

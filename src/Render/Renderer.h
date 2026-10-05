#ifndef WR_RENDERER_H
#define WR_RENDERER_H

#include "Raycast/Ray.h"
#include "Framebuffer.h"

#include <stdbool.h>

typedef struct WrGame WrGame;

typedef struct WrRenderer {
    int screenWidth;  // Width of window screen
    int screenHeight; // Height of window screen

    int rayCount; // Count of rays (same as inner width but that's understandable then)
    WrRay* rays;

    Framebuffer fb;
} WrRenderer;

bool InitRenderer(WrRenderer* r);
void TerminateRenderer(WrRenderer* r);

void UpdateRenderer(WrRenderer* r, const WrGame* g);
void RenderGame(const WrRenderer* r, const WrGame* g);

#endif // WR_RENDERER_H

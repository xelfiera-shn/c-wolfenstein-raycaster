#ifndef WR_RENDERER_H
#define WR_RENDERER_H

#include "Raycast/Ray.h"
#include "Game/Game.h"

typedef struct {
    int screenWidth; // Width of window screen
    int screenHeight; // Height of window screen
    
    Ray* rays;
    int rayCount; // Count of rays (same as screen width but that's understandable then)
} Renderer;

Renderer* CreateRenderer(void);
void DestroyRenderer(Renderer* r);

void UpdateRenderer(Renderer* r, Game* g);
void RenderGame(Renderer* r, Game* g);

#endif // WR_RENDERER_H
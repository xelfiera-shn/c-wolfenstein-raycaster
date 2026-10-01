#ifndef WR_RENDERER_H
#define WR_RENDERER_H

#include "Raycast/Ray.h"
#include "Game/Game.h"

typedef struct WrRenderer WrRenderer;

WrRenderer* CreateRenderer(void);
void DestroyRenderer(WrRenderer* r);

void UpdateRenderer(WrRenderer* r, const WrGame* g);
void RenderGame(const WrRenderer* r, const WrGame* g);

#endif // WR_RENDERER_H

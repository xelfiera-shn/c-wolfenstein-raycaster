#ifndef WR_RENDERER_H
#define WR_RENDERER_H

typedef struct WrRenderer WrRenderer;
typedef struct WrGame WrGame;

WrRenderer* CreateRenderer(void);
void DestroyRenderer(WrRenderer* r);

void UpdateRenderer(WrRenderer* r, const WrGame* g);
void RenderGame(const WrRenderer* r, const WrGame* g);

#endif // WR_RENDERER_H

#ifndef WR_RAYCAST_H
#define WR_RAYCAST_H

#include "Game/Game.h"
#include "Render/Renderer.h"

void CastRays(WrRay* rays, int count, const Map* m, const Player* p);

#endif // WR_RAYCAST_H
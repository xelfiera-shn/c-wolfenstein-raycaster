#ifndef WR_RAYCAST_H
#define WR_RAYCAST_H

#include "Game/Map/Map.h"
#include "Game/Player/Player.h"
#include "Render/Raycast/Ray.h"

void CastRays(WrRay* rays, int count, const WrMap* m, const WrPlayer* p);

#endif // WR_RAYCAST_H

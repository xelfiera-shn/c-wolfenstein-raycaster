#include "Raycast.h"
#include "Utils/Math.h"
#include "Core/Constants.h"

#include <math.h>
#include <float.h>

void CastRays(WrRay* rays, int count, const Map* m, const Player* p) {
    float planeLength = tanf(WR_PLAYER_FOV / 2.f);
    
    WrVector2 plane;
    plane.x = -p->dir.y * planeLength;
    plane.y = p->dir.x * planeLength;

    for (int i = 0; i < count; i++) {
        float cameraX = 2.f * i / (count - 1) - 1.f;

        WrVector2 rayDir;
        rayDir.x = p->dir.x + plane.x * cameraX;
        rayDir.y = p->dir.y + plane.y * cameraX;

        int mapX = (int)floorf(p->pos.x);
        int mapY = (int)floorf(p->pos.y);

        float deltaDistX = (rayDir.x == 0.f) ? 1e30f : fabsf(1.f / rayDir.x);
        float deltaDistY = (rayDir.y == 0.f) ? 1e30f : fabsf(1.f / rayDir.y);

        int stepX, stepY;
        float sideDistX, sideDistY;
        if (rayDir.x < 0.f) { stepX = -1; sideDistX = (p->pos.x - mapX) * deltaDistX; }
        else                { stepX =  1; sideDistX = (mapX + 1.f - p->pos.x) * deltaDistX; }
        if (rayDir.y < 0.f) { stepY = -1; sideDistY = (p->pos.y - mapY) * deltaDistY; }
        else                { stepY =  1; sideDistY = (mapY + 1.f - p->pos.y) * deltaDistY; }

        WrHitType side = WR_HIT_VERTICAL;
        bool hitFound = false;
        float perp = 0.f;
        for (int step = 0; step < m->width + m->height; step++) {
            if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = WR_HIT_VERTICAL; }
            else                       { sideDistY += deltaDistY; mapY += stepY; side = WR_HIT_HORIZONTAL; }

            if (IsMapCellSolid(m, mapX, mapY)) {
                perp = (side == WR_HIT_VERTICAL) ? sideDistX - deltaDistX : sideDistY - deltaDistY;
                hitFound = true;
                
                break;
            }
        }

        WrRay* ray = &rays[i];
        if (hitFound) {
            ray->dist = perp;
            ray->pos.x = (p->pos.x + rayDir.x * perp);
            ray->pos.y = (p->pos.y + rayDir.y * perp);
            ray->hit = side;
        } else {
            ray->dist = FLT_MAX;
            ray->pos.x = p->pos.x;
            ray->pos.y = p->pos.y;
            ray->hit = WR_HIT_NONE;
        }
    }
}
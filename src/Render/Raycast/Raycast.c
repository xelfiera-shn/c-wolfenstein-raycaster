#include "Raycast.h"
#include "Utils/Math.h"
#include "Core/Constants.h"

#include <math.h>
#include <float.h>

void CastRays(WrRay* rays, int count, const WrMap* m, const WrPlayer* p) {
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
        WrHitDirection sideX, sideY;
        if (rayDir.x < 0.f) {
            stepX = -1;
            sideDistX = (p->pos.x - mapX) * deltaDistX;
            sideX = WR_HIT_EAST;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.f - p->pos.x) * deltaDistX;
            sideX = WR_HIT_WEST;
        }

        if (rayDir.y < 0.f) {
            stepY = -1;
            sideDistY = (p->pos.y - mapY) * deltaDistY;
            sideY = WR_HIT_SOUTH;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.f - p->pos.y) * deltaDistY;
            sideY = WR_HIT_NORTH;
        }

        WrHitDirection side = WR_HIT_NONE;
        bool hitFound = false;
        float perp = 0.f;
        for (int step = 0; step < m->width + m->height; step++) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = sideX;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = sideY;
            }

            if (IsMapCellSolid(m, mapX, mapY)) {
                perp = (side == WR_HIT_EAST || side == WR_HIT_WEST) ? sideDistX - deltaDistX : sideDistY - deltaDistY;
                hitFound = true;

                break;
            }
        }

        WrRay* ray = &rays[i];
        if (hitFound) {
            ray->dist = perp;
            ray->pos.x = (p->pos.x + rayDir.x * perp);
            ray->pos.y = (p->pos.y + rayDir.y * perp);
            ray->side = side;
        } else {
            ray->dist = FLT_MAX;
            ray->pos.x = p->pos.x;
            ray->pos.y = p->pos.y;
            ray->side = WR_HIT_NONE;
        }
    }
}

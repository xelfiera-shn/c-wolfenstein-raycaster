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
        WrWallFace faceX, faceY;
        if (rayDir.x < 0.f) {
            stepX = -1;
            sideDistX = (p->pos.x - mapX) * deltaDistX;
            faceX = WR_WALL_FACE_EAST;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.f - p->pos.x) * deltaDistX;
            faceX = WR_WALL_FACE_WEST;
        }

        if (rayDir.y < 0.f) {
            stepY = -1;
            sideDistY = (p->pos.y - mapY) * deltaDistY;
            faceY = WR_WALL_FACE_SOUTH;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.f - p->pos.y) * deltaDistY;
            faceY = WR_WALL_FACE_NORTH;
        }

        WrWallFace face = WR_WALL_FACE_NONE;
        bool hitFound = false;
        float perp = 0.f;
        for (int step = 0; step < m->width + m->height; step++) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                face = faceX;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                face = faceY;
            }

            if (IsMapCellSolid(m, mapX, mapY)) {
                perp = IsVerticalHit(face) ? sideDistX - deltaDistX : sideDistY - deltaDistY;
                hitFound = true;

                break;
            }
        }

        WrRay* ray = &rays[i];
        if (hitFound) {
            ray->dist = perp;
            ray->pos.x = (p->pos.x + rayDir.x * perp);
            ray->pos.y = (p->pos.y + rayDir.y * perp);
            ray->face = face;
        } else {
            ray->dist = FLT_MAX;
            ray->pos.x = p->pos.x;
            ray->pos.y = p->pos.y;
            ray->face = WR_WALL_FACE_NONE;
        }
    }
}

#ifndef WR_RAY_H
#define WR_RAY_H

#include "Utils/Math.h"

#include <stdbool.h>

typedef enum {
    WR_WALL_FACE_NONE,
    WR_WALL_FACE_NORTH,
    WR_WALL_FACE_SOUTH,
    WR_WALL_FACE_EAST,
    WR_WALL_FACE_WEST,

    WR_WALL_FACE_COUNT
} WrWallFace;

typedef struct WrRay {
    WrVector2 pos;
    float dist;
    int cellX, cellY;
    WrWallFace face;
} WrRay;

static inline bool IsVerticalHit(WrWallFace hitFace) {
    return (hitFace == WR_WALL_FACE_EAST || hitFace == WR_WALL_FACE_WEST);
}

#endif // WR_RAY_H

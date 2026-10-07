#ifndef WR_RAY_H
#define WR_RAY_H

#include "Utils/Math.h"

typedef enum {
    WR_HIT_NONE,
    WR_HIT_NORTH,
    WR_HIT_SOUTH,
    WR_HIT_EAST,
    WR_HIT_WEST,

    WR_HIT_COUNT
} WrHitDirection;

typedef struct WrRay {
    WrVector2 pos;
    float dist;
    WrHitDirection side;
} WrRay;

#endif // WR_RAY_H

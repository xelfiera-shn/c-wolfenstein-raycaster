#ifndef WR_RAY_H
#define WR_RAY_H

#include "Utils/Math.h"

typedef enum {
    WR_HIT_NONE,
    WR_HIT_VERTICAL,
    WR_HIT_HORIZONTAL,

    WR_HIT_COUNT
} WrHitType;

typedef struct {
    WrVector2 pos;
    float dist;
    WrHitType hit;
} WrRay;

#endif // WR_RAY_H

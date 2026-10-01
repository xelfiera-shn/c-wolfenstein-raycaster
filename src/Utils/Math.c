#include "Math.h"

#include <math.h>

void RotateVector(WrVector2* vec, float ang) {
    float x = vec->x;
    float y = vec->y;
    float sinVal = sinf(ang);
    float cosVal = cosf(ang);

    vec->x = x * cosVal - y * sinVal;
    vec->y = x * sinVal + y * cosVal;
}

void NormalizeVector(WrVector2* vec) {
    float len = sqrtf(vec->x * vec->x + vec->y * vec->y);

    if (len == 0) return;

    vec->x /= len;
    vec->y /= len;
}

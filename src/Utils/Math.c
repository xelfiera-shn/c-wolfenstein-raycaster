#include "Math.h"
#include <math.h>

void RotateVector2D(WrVector2* vec, float ang) {
    float sinVal = sinf(ang);
    float cosVal = cosf(ang);

    float x = vec->x;
    float y = vec->y;

    vec->x = x * cosVal - y * sinVal;
    vec->y = x * sinVal + y * cosVal;
}
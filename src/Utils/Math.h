#ifndef WR_MATH_H
#define WR_MATH_H

typedef struct WrVector2 {
    float x, y;
} WrVector2;

void RotateVector2D(WrVector2* vec, float ang);

typedef struct WrColor {
    unsigned char r, g, b, a;
} WrColor;

#endif // WR_MATH_H
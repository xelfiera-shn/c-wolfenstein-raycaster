#ifndef WR_MATH_H
#define WR_MATH_H

#define WR_PI 3.1415927f

typedef struct {
    float x, y;
} WrVector2;

void RotateVector(WrVector2* vec, float ang);
void NormalizeVector(WrVector2* vec);

typedef struct {
    unsigned char r, g, b, a;
} WrColor;

#endif // WR_MATH_H
#ifndef WR_MATH_H
#define WR_MATH_H

#define WR_PI 3.1415927f
#define WR_SIGN(val) ((val) >= 0 ? 1 : -1)

typedef struct {
    float x, y;
} WrVector2;

void RotateVector(WrVector2* vec, float ang);
void NormalizeVector(WrVector2* vec);

#endif // WR_MATH_H

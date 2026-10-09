#ifndef WR_VECTOR_H
#define WR_VECTOR_H

typedef struct WrVector2 {
    float x, y;
} WrVector2;

void RotateVector(WrVector2* vec, float ang);
void NormalizeVector(WrVector2* vec);

#endif // WR_VECTOR_H

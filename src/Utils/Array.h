#ifndef WR_ARRAY_H
#define WR_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct WrArray {
    size_t capacity;
    size_t size;
    int* data;
} WrArray;

bool InitArray(WrArray* arr);
void TerminateArray(WrArray* arr);

bool ArrayPush(WrArray* arr, int item);
bool ArrayUpdate(WrArray* arr, int idx, int item);
int ArrayGet(const WrArray* arr, int idx);
bool ArrayDelete(WrArray* arr, int idx);

#endif // WR_ARRAY_H

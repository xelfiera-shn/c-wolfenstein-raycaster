#ifndef WR_ARRAY_H
#define WR_ARRAY_H

#include <stdlib.h>

typedef struct WrArray {
    size_t capacity;
    size_t size;
    int* array;
} WrArray;

WrArray* CreateArray(void);
void DestroyArray(WrArray* arr);

void Push(WrArray* arr, int item);
void Update(WrArray* arr, int idx, int item);
int Get(const WrArray* arr, int idx);
void Delete(WrArray* arr, int idx);

#endif // WR_ARRAY_H

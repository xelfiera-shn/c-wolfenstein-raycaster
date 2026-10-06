#include "Array.h"

#include <stdlib.h>

#define INITIAL_ARRAY_SIZE 8

bool InitArray(WrArray* arr) {
    arr->size = 0;
    arr->capacity = INITIAL_ARRAY_SIZE;

    arr->data = malloc(INITIAL_ARRAY_SIZE * sizeof *arr->data);
    if (!arr->data) {
        free(arr);

        return false;
    }

    return true;
}

void TerminateArray(WrArray* arr) {
    if (!arr) return;

    free(arr->data);
    free(arr);
}

bool ArrayPush(WrArray* arr, int item) {
    if (arr->size == arr->capacity) {
        size_t newCap = arr->capacity << 1;

        int* tmp = realloc(arr->data, newCap * sizeof *arr->data);
        if (!tmp) {
            return false;
        }

        arr->data = tmp;
        arr->capacity = newCap;
    }

    arr->data[arr->size++] = item;

    return true;
}

bool ArrayUpdate(WrArray* arr, int idx, int item) {
    if (idx < 0 || idx >= arr->size) return false;

    arr->data[idx] = item;

    return true;
}

int ArrayGet(const WrArray* arr, int idx) {
    if (idx < 0 || idx >= arr->size) return -1;

    return arr->data[idx];
}

bool ArrayDelete(WrArray* arr, int idx) {
    if (idx < 0 || idx >= arr->size) return false;

    for (int i = idx; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;

    return true;
}

#include "Array.h"

#define INITIAL_ARRAY_SIZE 8

WrArray* CreateArray(void) {
    WrArray* arr = malloc(sizeof *arr);
    if (!arr) return NULL;

    arr->size = 0;
    arr->capacity = INITIAL_ARRAY_SIZE;

    arr->array = malloc(INITIAL_ARRAY_SIZE * sizeof *arr->array);
    if (!arr->array) {
        free(arr);

        return NULL;
    }

    return arr;
}

void DestroyArray(WrArray* arr) {
    if (!arr) return;

    free(arr->array);
    free(arr);
}

void Push(WrArray* arr, int item) {
    if (arr->size == arr->capacity) {
        int newCap = arr->capacity << 1;

        int* tmp = realloc(arr->array, newCap * sizeof *arr->array);
        if (!tmp) {
            return;
        }

        arr->array = tmp;
        arr->capacity = newCap;
    }

    arr->array[arr->size++] = item;
}

void Update(WrArray* arr, int idx, int item) {
    if (idx < 0 || idx >= arr->size) return;

    arr->array[idx] = item;
}

int Get(const WrArray* arr, int idx) {
    if (idx < 0 || idx >= arr->size) return -1;

    return arr->array[idx];
}

void Delete(WrArray* arr, int idx) {
    if (idx < 0 || idx >= arr->size) return;

    for (int i = idx; i < arr->size - 1; i++) {
        arr->array[i] = arr->array[i + 1];
    }

    arr->size--;
}

#include "Map.h"

#include <stdlib.h>

// Default map definition just for development state
static int defaultMap[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

bool InitializeMap(Map* m) {
    m->w = 8;
    m->h = 8;

    m->data = (int*)calloc(m->w * m->h, sizeof(int));
    if (!m->data) return false;

    for (int i = 0; i < m->w * m->h; i++) {
        m->data[i] = defaultMap[i];
    }

    return true;
}

void TerminateMap(Map* m) {
    if (!m) return;

    free(m->data);
}
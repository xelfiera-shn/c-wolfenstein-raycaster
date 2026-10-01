#include "Map.h"

#include <stdlib.h>

static const int defaultMap[64] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static const int defaultMapW = 8;
static const int defaultMapH = 8;

bool InitDefaultMap(WrMap* m) {
    m->width = defaultMapW;
    m->height = defaultMapH;

    m->data = malloc(defaultMapW * defaultMapH * sizeof *m->data);
    if (!m->data) return false;

    for (int i = 0; i < m->width * m->height; i++) {
        m->data[i] = defaultMap[i];
    }

    m->playerStartPos = (WrVector2){4.f, 4.f};
    m->playerStartDir = (WrVector2){0.f, -1.f}; // Player looking up

    return true;
}

void TerminateMap(WrMap* m) {
    if (!m->data) return;

    free(m->data);
    m->data = NULL;
}

int GetMapCell(const WrMap* m, int cx, int cy) {
    if (cx < 0 || cx >= m->width || cy < 0 || cy >= m->height) return 1;

    return m->data[cy * m->width + cx];
}

bool IsMapCellSolid(const WrMap* m, int cx, int cy) {
    return (GetMapCell(m, cx, cy) > 0);
}

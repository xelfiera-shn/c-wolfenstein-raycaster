#include "Map.h"

#include <stdlib.h>

int defaultMap[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

int defaultMapW = 8;
int defaultMapH = 8;

bool InitDefaultMap(Map* m) {
    m->width = defaultMapW;
    m->height = defaultMapH;

    m->data = (int*)malloc(defaultMapW * defaultMapH * sizeof(int));
    if (!m->data) return false;

    for (int i = 0; i < m->width * m->height; i++) {
        m->data[i] = defaultMap[i];
    }

    m->playerStartPos = (WrVector2){ 4.f, 4.f };
    m->playerStartDir = (WrVector2){ 0.f, -1.f }; // Player looking up

    return true;
}

void TerminateMap(Map* m) {
    if (!m->data) return;

    free(m->data);
    m->data = NULL;
}

int GetMapCell(const Map* m, int cx, int cy) {
    if (cx < 0 || cx >= m->width || cy < 0 || cy >= m->height) return 1;

    return m->data[cy * m->width + cx];
}
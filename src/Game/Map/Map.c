#include "Map.h"

#include <stdlib.h>

// clang-format off
static const char* const WR_MAP_PATHS[WR_MAP_COUNT] = {
    [WR_MAP_NONE] = "",
    [WR_MAP_1] = "res/maps/1.wrm",
    [WR_MAP_2] = "res/maps/2.wrm",
    [WR_MAP_3] = "res/maps/3.wrm",
    [WR_MAP_4] = "res/maps/4.wrm",
    [WR_MAP_5] = "res/maps/5.wrm",
};

static const uint8_t defaultMap[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};
// clang-format on

static const int defaultMapW = 8;
static const int defaultMapH = 8;

static const WrVector2 defaultPlayerStartPos = {4.5f, 4.5f};
static const WrVector2 defaultPlayerStartDir = {0.f, -1.f}; // Player looking up

static bool InitDefaultMap(WrMap* m);
static bool InitMapFromFile(WrMap* m, const char* path);

bool InitMap(WrMap* m, WrMapType type) {
    if (!InitMapFromFile(m, WR_MAP_PATHS[type])) {
        if (!InitDefaultMap(m)) return false;
    }

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

static bool InitDefaultMap(WrMap* m) {
    m->width = defaultMapW;
    m->height = defaultMapH;

    m->data = malloc(defaultMapW * defaultMapH * sizeof *m->data);
    if (!m->data) return false;

    for (int i = 0; i < m->width * m->height; i++) {
        m->data[i] = defaultMap[i];
    }

    m->playerStartPos = defaultPlayerStartPos;
    m->playerStartDir = defaultPlayerStartDir;

    return true;
}

static bool InitMapFromFile(WrMap* m, const char* path) {
    (void*)m;
    (void*)path;

    return false;
}

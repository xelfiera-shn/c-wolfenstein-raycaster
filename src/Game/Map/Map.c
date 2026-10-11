#include "Map.h"
#include "Utils/File.h"

#include <stdlib.h>
#include <stdio.h>

#define WR_MAP_DATA_START_LINE 4

// clang-format off
static const char* const WR_MAP_PATHS[WR_MAP_COUNT] = {
    [WR_MAP_NONE] = "",
    [WR_MAP_1] = "res/maps/map1.wrm",
    [WR_MAP_2] = "res/maps/map2.wrm",
    [WR_MAP_3] = "res/maps/map3.wrm",
    [WR_MAP_4] = "res/maps/map4.wrm",
    [WR_MAP_5] = "res/maps/map5.wrm",
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

static bool ReadWidthAndHeight(WrMap* m, const WrFile* file);
static bool ReadPlayerStartPos(WrMap* m, const WrFile* file);
static bool ReadPlayerStartDir(WrMap* m, const WrFile* file);
static bool ReadMapData(WrMap* m, const WrFile* file);

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
    WrFile file;
    if (!InitFile(&file, path)) return false;

    if (!ReadWidthAndHeight(m, &file)) return false;
    if (!ReadPlayerStartPos(m, &file)) return false;
    if (!ReadPlayerStartDir(m, &file)) return false;

    m->data = calloc(m->width * m->height, sizeof *m->data);
    if (!m->data) return false;

    if (!ReadMapData(m, &file)) {
        TerminateMap(m);

        return false;
    }

    return true;
}

static bool ReadWidthAndHeight(WrMap* m, const WrFile* file) {
    char* end;
    long w = strtol(file->data[0], &end, 10);
    if (*end != ',') return false;
    long h = strtol(end + 1, &end, 10);

    m->width = (int)w;
    m->height = (int)h;

    return true;
}

static bool ReadPlayerStartPos(WrMap* m, const WrFile* file) {
    WrVector2 pos;

    char* end;
    pos.x = (float)strtol(file->data[1], &end, 10);
    if (*end != ',') return false;
    pos.y = (float)strtol(end + 1, &end, 10);

    m->playerStartPos = pos;

    return true;
}

static bool ReadPlayerStartDir(WrMap* m, const WrFile* file) {
    WrVector2 dir;

    char* end;
    dir.x = (float)strtol(file->data[2], &end, 10);
    if (*end != ',') return false;
    dir.y = (float)strtol(end + 1, &end, 10);

    m->playerStartDir = dir;

    return true;
}

static bool ReadMapData(WrMap* m, const WrFile* file) {
    for (int y = 0; y < m->height; y++) {
        char* end = file->data[y + WR_MAP_DATA_START_LINE] - 1;
        for (int x = 0; x < m->width; x++) {
            long val = strtol(end + 1, &end, 10);

            if (*end != ',') return false;

            printf("%d,", (int)val);

            m->data[y * m->width + x] = (uint8_t)val;
        }

        printf("\n");
    }

    return true;
}

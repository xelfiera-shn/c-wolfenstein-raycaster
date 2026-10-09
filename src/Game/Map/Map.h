#ifndef WR_MAP_H
#define WR_MAP_H

#include "Utils/Vector.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    WR_MAP_NONE = 0,

    WR_MAP_1,
    WR_MAP_2,
    WR_MAP_3,
    WR_MAP_4,
    WR_MAP_5,

    WR_MAP_COUNT
} WrMapType;

typedef struct WrMap {
    int width;
    int height;
    uint8_t* data;

    WrVector2 playerStartPos; // Player start position vector
    WrVector2 playerStartDir; // Player start direction vector
} WrMap;

bool InitMap(WrMap* m, WrMapType type);
void TerminateMap(WrMap* m);

int GetMapCell(const WrMap* m, int cx, int cy);
bool IsMapCellSolid(const WrMap* m, int cx, int cy);

#endif // WR_MAP_H

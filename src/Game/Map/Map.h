#ifndef WR_MAP_H
#define WR_MAP_H

#include "Utils/Vector.h"

#include <stdbool.h>

typedef struct WrMap {
    int* data;
    int width;
    int height;

    WrVector2 playerStartPos; // Player start position vector
    WrVector2 playerStartDir; // Player start direction vector
} WrMap;

bool InitDefaultMap(WrMap* m);
void TerminateMap(WrMap* m);

int GetMapCell(const WrMap* m, int cx, int cy);
bool IsMapCellSolid(const WrMap* m, int cx, int cy);

#endif // WR_MAP_H

#ifndef WR_MAP_H
#define WR_MAP_H

#include "Utils/Math.h"

#include <stdbool.h>

typedef struct {
    int* data;
    int width;
    int height;

    WrVector2 playerStartPos; // Player start position vector
    WrVector2 playerStartDir; // Player start direction vector
} Map;

bool InitDefaultMap(Map* m);
void TerminateMap(Map* m);

int GetMapCell(const Map* m, int cx, int cy);
bool IsMapCellSolid(const Map* m, int cx, int cy);

#endif // WR_MAP_H

#ifndef WR_MAP_H
#define WR_MAP_H

#include <stdbool.h>

typedef struct {
    int w, h;
    int* data;
} Map;

bool InitializeMap(Map* m);
void TerminateMap(Map* m);

#endif // WR_MAP_H
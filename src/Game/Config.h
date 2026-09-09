#ifndef WR_CONFIG_H
#define WR_CONFIG_H

#include <stdbool.h>

typedef struct {
    bool isEnabled;
    bool isPlayerEnabled;
    bool isRaysEnabled;
} MinimapConfig;

typedef struct {
    MinimapConfig minimap;
} Config;

void InitializeConfig(Config* c);

#endif // WR_CONFIG_H
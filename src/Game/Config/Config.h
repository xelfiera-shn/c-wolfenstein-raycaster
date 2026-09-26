#ifndef WR_CONFIG_H
#define WR_CONFIG_H

#include <stdbool.h>

typedef struct {
    bool isMinimapEnabled;
    bool isMinimapPlayerEnabled;
    bool isMinimapRaysEnabled;
} RendererConfig;

typedef struct {
    RendererConfig renderer; 
} Config;

void InitConfig(Config* c);

#endif // WR_CONFIG_H
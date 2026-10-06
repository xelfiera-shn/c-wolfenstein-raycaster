#ifndef WR_GAME_H
#define WR_GAME_H

#include "Map/Map.h"
#include "Player/Player.h"

#include <stdbool.h>

typedef struct WrInput WrInput;

typedef struct WrGame {
    WrMap map;
    WrPlayer player;
} WrGame;

bool InitGame(WrGame* g);
void TerminateGame(WrGame* g);

void UpdateGame(WrGame* g, const WrInput* in, float dt);

#endif // WR_GAME_H

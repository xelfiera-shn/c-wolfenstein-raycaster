#ifndef WR_GAME_H
#define WR_GAME_H

#include "Map/Map.h"
#include "Player/Player.h"

typedef struct WrGame {
    WrMap map;
    WrPlayer player;
} WrGame;

WrGame* CreateGame(void);
void DestroyGame(WrGame* g);

void UpdateGame(WrGame* g, float dt);

#endif // WR_GAME_H

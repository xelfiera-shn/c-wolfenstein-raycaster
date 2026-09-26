#ifndef WR_GAME_H
#define WR_GAME_H

#include "Config/Config.h"
#include "Map/Map.h"
#include "Player/Player.h"

typedef struct {
    Config config;
    Map map;
    Player player;
} Game;

Game* CreateGame(void);
void DestroyGame(Game* g);

void UpdateGame(Game* g, float dt);

#endif // WR_GAME_H
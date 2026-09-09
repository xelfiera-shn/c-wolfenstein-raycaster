#ifndef WR_GAME_H
#define WR_GAME_H

#include "Config.h"
#include "Map.h"
#include "Player.h"

typedef struct {
    Config config;
    Map map;
    Player player;
} Game;

Game* CreateGame(void);
void DestroyGame(Game* g);

void UpdateGame(Game* g, float delta);

#endif // WR_GAME_H
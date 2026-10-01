#ifndef WR_PLAYER_H
#define WR_PLAYER_H

#include "Utils/Math.h"
#include "Game/Map/Map.h"

typedef struct {
    WrVector2 pos;
    WrVector2 dir;
} Player;

void InitPlayer(Player* p, const Map* m);

#endif // WR_PLAYER_H

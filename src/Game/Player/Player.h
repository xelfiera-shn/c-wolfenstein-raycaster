#ifndef WR_PLAYER_H
#define WR_PLAYER_H

#include "Utils/Vector.h"
#include "Game/Map/Map.h"

typedef struct WrPlayer {
    WrVector2 pos;
    WrVector2 dir;
} WrPlayer;

void InitPlayer(WrPlayer* p, const WrMap* m);

#endif // WR_PLAYER_H

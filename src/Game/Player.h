#ifndef WR_PLAYER_H
#define WR_PLAYER_H

#include "Utils/Math.h"

typedef struct {
    WrVector2 pos;    // Player position vector
    WrVector2 dir;    // Player direction vector
} Player;

void InitializePlayer(Player* p);

#endif // WR_PLAYER_H
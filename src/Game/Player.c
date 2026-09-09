#include "Player.h"
#include "Core/Constants.h"

void InitializePlayer(Player* p) {
    p->pos.x = WR_PLAYER_START_DIRECTION_X;
    p->pos.y = WR_PLAYER_START_DIRECTION_Y;
    p->dir.x = WR_PLAYER_START_DIRECTION_X;
    p->dir.y = WR_PLAYER_START_DIRECTION_Y;
}
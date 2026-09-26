#include "Player.h"

void InitPlayer(Player* p, Map* m) {
    p->pos = m->playerStartPos;
    p->dir = m->playerStartDir;
}
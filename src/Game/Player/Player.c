#include "Player.h"

void InitPlayer(Player* p, const Map* m) {
    p->pos = m->playerStartPos;
    p->dir = m->playerStartDir;
}

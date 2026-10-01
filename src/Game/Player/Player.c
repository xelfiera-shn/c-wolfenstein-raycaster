#include "Player.h"

void InitPlayer(WrPlayer* p, const WrMap* m) {
    p->pos = m->playerStartPos;
    p->dir = m->playerStartDir;
}

#include "Game.h"

#include <stdlib.h>

Game* CreateGame(void) {
    Game* g = (Game*)calloc(1, sizeof(Game));
    if (!g) return NULL;

    InitConfig(&g->config);

    if (!InitDefaultMap(&g->map)) {
        free(g);

        return NULL;
    }

    InitPlayer(&g->player, &g->map);

    return g;
}

void DestroyGame(Game* g) {
    if (!g) return;

    TerminateMap(&g->map);
    free(g);
}

void UpdateGame(Game* g, float dt) {

}
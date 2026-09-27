#include "Renderer.h"

#include <stdlib.h>
#include "Platform/Platform.h"

Renderer* CreateRenderer(void) {
    Renderer* r = (Renderer*)calloc(1, sizeof(Renderer));
    if (!r) return NULL;

    r->screenWidth = PlatformGetScreenWidth();
    r->screenHeight = PlatformGetScreenHeight();
    r->rayCount = r->screenWidth;
    r->rays = (Ray*)calloc(r->rayCount, sizeof(Ray));
    
    if (!r->rays) {
        free(r);

        return NULL;
    }

    return r;
}

void DestroyRenderer(Renderer* r) {
    if (!r) return;

    if (r->rays) {
        free(r->rays);
    }
    
    free(r);
}

void UpdateRenderer(Renderer* r, Game* g) {

}

void RenderGame(Renderer* r, Game* g) {

}
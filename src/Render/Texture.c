#include "Texture.h"

#include <raylib.h>

bool InitTexture(WrTexture* texture, const char* path) {
    Image img = LoadImage(path);

    texture->data = LoadImageColors(img);
    if (!texture->data) return false;

    texture->width = img.width;
    texture->height = img.height;

    UnloadImage(img);

    return true;
}

void TerminateTexture(WrTexture* texture) {
    if (!texture) return;

    free(texture->data);
    texture->data = NULL;
}

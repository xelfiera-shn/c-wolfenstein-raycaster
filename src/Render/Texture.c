#include "Texture.h"

void InitTexture(WrTexture* texture, const char* path) {
    Image img = LoadImage(path);

    texture->data = LoadImageColors(img);
    if (!texture->data) {
        img = GenImageChecked(64, 64, 8, 8, BLACK, PURPLE);
        texture->data = LoadImageColors(img);
    }

    texture->width = img.width;
    texture->height = img.height;

    UnloadImage(img);
}

void TerminateTexture(WrTexture* texture) {
    if (!texture) return;

    UnloadImageColors(texture->data);
    texture->data = NULL;
}

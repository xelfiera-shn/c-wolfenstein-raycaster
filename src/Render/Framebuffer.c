#include "Framebuffer.h"
#include "Utils/Math.h"

#include <stdlib.h>

bool InitFramebuffer(WrFramebuffer* fb, int width, int height, int screenWidth, int screenHeight) {
    fb->width = width;
    fb->height = height;
    fb->scale = WR_MIN((float)screenWidth / fb->width, (float)screenHeight / fb->height);

    fb->buffer = calloc(fb->width * fb->height, sizeof *fb->buffer);
    if (!fb->buffer) return false;

    Image img = GenImageColor(fb->width, fb->height, BLACK);
    fb->frame = LoadTextureFromImage(img);
    UnloadImage(img);

    if (fb->frame.id == 0) {
        free(fb->buffer);
        fb->buffer = NULL;

        return false;
    }

    SetTextureFilter(fb->frame, TEXTURE_FILTER_POINT);

    return true;
}

void TerminateFramebuffer(WrFramebuffer* fb) {
    if (!fb) return;

    UnloadTexture(fb->frame);
    fb->frame = (Texture2D){0};
    free(fb->buffer);
    fb->buffer = NULL;
}

#include "Framebuffer.h"

#include <stdlib.h>

bool InitFramebuffer(WrFramebuffer* fb, int width, int height) {
    fb->width = width;
    fb->height = height;

    fb->buffer = calloc(fb->width * fb->height, sizeof *fb->buffer);
    if (!fb->buffer) return false;

    Image img = GenImageColor(fb->width, fb->height, BLACK);
    fb->frame = LoadTextureFromImage(img);
    UnloadImage(img);

    SetTextureFilter(fb->frame, TEXTURE_FILTER_POINT);

    return true;
}

void TerminateFramebuffer(WrFramebuffer* fb) {
    if (!fb) return;

    UnloadTexture(fb->frame);
    free(fb->buffer);
}

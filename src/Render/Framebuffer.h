#ifndef WR_FRAMEBUFFER_H
#define WR_FRAMEBUFFER_H

#include <stdbool.h>
#include <raylib.h>

typedef struct Framebuffer {
    int width;
    int height;
    Texture2D frame;
    Color* buffer;
} Framebuffer;

bool InitFramebuffer(Framebuffer* fb, int width, int height);
void TerminateFramebuffer(Framebuffer* fb);

#endif // WR_FRAMEBUFFER_H

#ifndef WR_FRAMEBUFFER_H
#define WR_FRAMEBUFFER_H

#include <stdbool.h>
#include <raylib.h>

typedef struct WrFramebuffer {
    int width;
    int height;
    float scale;
    Texture2D frame;
    Color* buffer;
} WrFramebuffer;

bool InitFramebuffer(WrFramebuffer* fb, int width, int height, int screenWidth, int screenHeight);
void TerminateFramebuffer(WrFramebuffer* fb);

#endif // WR_FRAMEBUFFER_H

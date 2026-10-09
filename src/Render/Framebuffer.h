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

    int* wallStarts;
    int* wallEnds;
} WrFramebuffer;

bool InitFramebuffer(WrFramebuffer* fb, int width, int height, int screenWidth, int screenHeight);
void TerminateFramebuffer(WrFramebuffer* fb);

void UpdateFramebufferScale(WrFramebuffer* fb, int screenWidth, int screenHeight);

#endif // WR_FRAMEBUFFER_H

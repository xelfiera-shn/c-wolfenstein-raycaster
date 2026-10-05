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

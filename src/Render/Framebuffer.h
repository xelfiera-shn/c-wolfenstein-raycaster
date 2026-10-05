#include <raylib.h>

typedef struct Framebuffer {
    int width;
    int height;
    Texture2D frame;
    Color* buffer;
} Framebuffer;

#include "Platform.h"

#include "raylib.h"

#define CONVERT_RLCOL(col) CLITERAL(Color){ col.r, col.g, col.b, col.a }

void    PlatformSetConfigFlags(unsigned int flags)             { SetConfigFlags(flags); }
void    PlatformInitWindow(int w, int h, const char* title)    { InitWindow(w, h, title); }
void    PlatformCloseWindow(void)                              { CloseWindow(); }
bool    PlatformWindowShouldClose(void)                        { return WindowShouldClose(); }
void    PlatformSetTargetFPS(int fps)                          { SetTargetFPS(fps); }
int     PlatformGetFPS(void)                                   { return GetFPS(); }
float   PlatformGetFrameTime(void)                             { return GetFrameTime(); }
int     PlatformGetScreenWidth(void)                           { return GetScreenWidth(); }
int     PlatformGetScreenHeight(void)                          { return GetScreenHeight(); }

bool    PlatformIsKeyPressed(int key)                          { return IsKeyPressed(key); }
bool    PlatformIsKeyDown(int key)                             { return IsKeyDown(key); }

void    PlatformBeginDrawing(void)                             { BeginDrawing(); }
void    PlatformEndDrawing(void)                               { EndDrawing(); }
void    PlatformClearBackground(WrColor col)                   { ClearBackground(CONVERT_RLCOL(col)); }
void    PlatformDrawFPS(int posX, int posY)                    { DrawFPS(posX, posY); }

void    PlatformDrawLine(int x1, int y1, int x2, int y2, WrColor col)        { DrawLine(x1, y1, x2, y2, CONVERT_RLCOL(col)); }
void    PlatformDrawRectangle(int tlx, int tly, int w, int h, WrColor col)   { DrawRectangle(tlx, tly, w, h, CONVERT_RLCOL(col)); }
void    PlatformDrawCircle(int cx, int cy, float radius, WrColor col)        { DrawCircle(cx, cy, radius, CONVERT_RLCOL(col)); }
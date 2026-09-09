#include "Platform.h"

#include "raylib.h"

void PlatformSetConfigFlags(unsigned char flags) {
    SetConfigFlags(flags);
}

void PlatformInitializeWindow(int w, int h, const char* title) {
    InitWindow(w, h, title);
}

void PlatformSetTargetFPS(int fps) {
    SetTargetFPS(fps);
}

bool PlatformWindowShouldClose() {
    return WindowShouldClose();
}

void PlatformCloseWindow() {
    CloseWindow();
}

void PlatformBeginDrawing() {
    BeginDrawing();
}

void PlatformEndDrawing() {
    EndDrawing();
}

void PlatformClearBackground(WrColor col) {
    ClearBackground((Color){ col.r, col.g, col.b, col.a });
}

void PlatformDrawFPS(int x, int y) {
    DrawFPS(x, y);
}

bool PlatformIsKeyDown(int key) {
    return IsKeyDown(key);
}

bool PlatformIsKeyPressed(int key) {
    return IsKeyPressed(key);
}

void PlatformDrawLine(WrVector2 p1, WrVector2 p2, WrColor col) {
    DrawLine(p1.x, p1.y, p2.x, p2.y, (Color){ col.r, col.g, col.b, col.a });
}

void PlatformDrawRectangle(WrVector2 tlp, int w, int h, WrColor col) {
    DrawRectangle(tlp.x, tlp.y, w, h, (Color){ col.r, col.g, col.b, col.a });
}

void PlatformDrawCircle(WrVector2 center, float radius, WrColor col) {
    DrawCircle(center.x, center.y, radius, (Color){ col.r, col.g, col.b, col.a });
}
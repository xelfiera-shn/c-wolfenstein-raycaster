#include "Input.h"

#include <raylib.h>

void HandleInputs(WrInput* in) {
    Vector2 mDelta = GetMouseDelta();
    in->mouseDelta.x = mDelta.x;
    in->mouseDelta.y = mDelta.y;

    in->mouseButtons[WR_LEFT_MOUSE_BUTTON] = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? true : false;
    in->mouseButtons[WR_RIGHT_MOUSE_BUTTON] = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) ? true : false;

    in->keys[WR_KEY_ESC] = IsKeyPressed(KEY_ESCAPE) ? true : false;
    in->keys[WR_KEY_W] = IsKeyDown(KEY_W) ? true : false;
    in->keys[WR_KEY_A] = IsKeyDown(KEY_A) ? true : false;
    in->keys[WR_KEY_S] = IsKeyDown(KEY_S) ? true : false;
    in->keys[WR_KEY_D] = IsKeyDown(KEY_D) ? true : false;
    in->keys[WR_KEY_E] = IsKeyPressed(KEY_E) ? true : false;
}

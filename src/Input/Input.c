#include "Input.h"

#include <raylib.h>

void HandleInputs(WrInput* in) {
    Vector2 dm = GetMouseDelta();
    in->mouseDelta.x = dm.x;
    in->mouseDelta.y = dm.y;

    in->mouseButtons[WR_MOUSE_BUTTON_LEFT] = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    in->mouseButtons[WR_MOUSE_BUTTON_RIGHT] = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

    in->pressedKeys[WR_KEY_ESC] = IsKeyPressed(KEY_ESCAPE);
    in->pressedKeys[WR_KEY_E] = IsKeyPressed(KEY_E);

    in->heldKeys[WR_KEY_W] = IsKeyDown(KEY_W);
    in->heldKeys[WR_KEY_A] = IsKeyDown(KEY_A);
    in->heldKeys[WR_KEY_S] = IsKeyDown(KEY_S);
    in->heldKeys[WR_KEY_D] = IsKeyDown(KEY_D);
}

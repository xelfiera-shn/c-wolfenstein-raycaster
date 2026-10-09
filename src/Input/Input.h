#ifndef WR_INPUT_H
#define WR_INPUT_H

#include "Utils/Vector.h"

#include <stdbool.h>

typedef enum {
    WR_MOUSE_BUTTON_LEFT = 0,
    WR_MOUSE_BUTTON_RIGHT = 1,

    WR_MOUSE_BUTTON_COUNT
} WrMouseButtons;

typedef enum {
    WR_KEY_ESC = 0,
    WR_KEY_W = 1,
    WR_KEY_A = 2,
    WR_KEY_S = 3,
    WR_KEY_D = 4,
    WR_KEY_E = 5,

    WR_KEY_COUNT
} WrKeys;

typedef struct WrInput {
    WrVector2 mouseDelta;
    bool mouseButtons[WR_MOUSE_BUTTON_COUNT];
    bool pressedKeys[WR_KEY_COUNT];
    bool heldKeys[WR_KEY_COUNT];
} WrInput;

void HandleInputs(WrInput* in);

#endif // WR_INPUT_H

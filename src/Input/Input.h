#ifndef WR_INPUT_H
#define WR_INPUT_H

#include "Utils/Math.h"

#include <stdbool.h>

#define WR_LEFT_MOUSE_BUTTON 0
#define WR_RIGHT_MOUSE_BUTTON 1

#define WR_KEY_ESC 0
#define WR_KEY_W 1
#define WR_KEY_A 2
#define WR_KEY_S 3
#define WR_KEY_D 4
#define WR_KEY_E 5

typedef struct WrInput {
    WrVector2 mouseDelta;
    bool mouseButtons[2];
    bool keys[64];
} WrInput;

void HandleInputs(WrInput* in);

#endif // WR_INPUT_H

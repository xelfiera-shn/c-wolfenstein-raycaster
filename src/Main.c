#include "Core/Constants.h"
#include "Input/Input.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <stdlib.h>
#include <raylib.h>

int main(int argc, char const* argv[]) {
    ((void)argc, (void)argv);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WR_SCREEN_DEFAULT_WIDTH, WR_SCREEN_DEFAULT_HEIGHT, "C Wolfenstein Raycaster");
    SetTargetFPS(60);

    WrInput input;

    WrGame game;
    InitGame(&game);

    WrRenderer renderer;
    InitRenderer(&renderer);

    while (!WindowShouldClose()) {
        HandleInputs(&input);

        float dt = GetFrameTime();
        if (dt > 0.1f) { // If fps less than 10, fix delta time and inputs
            float ratio = 0.1f / dt;

            input.mouseDelta.x *= ratio;
            input.mouseDelta.y *= ratio;
            dt = 0.1f;
        }

        UpdateGame(&game, &input, dt);
        UpdateRenderer(&renderer, &game);

        RenderGame(&renderer, &game);
    }

    TerminateRenderer(&renderer);
    TerminateGame(&game);

    CloseWindow();

    return 0;
}

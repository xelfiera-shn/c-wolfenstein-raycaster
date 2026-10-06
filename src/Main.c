#include "Core/Constants.h"
#include "Input/Input.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <stdlib.h>
#include <raylib.h>

int main(int argc, char const* argv[]) {
    ((void)argc, (void)argv);

    int exitCode = EXIT_FAILURE;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WR_SCREEN_DEFAULT_WIDTH, WR_SCREEN_DEFAULT_HEIGHT, "C Wolfenstein Raycaster");
    SetTargetFPS(60);

    WrInput input = {0};
    WrGame game = {0};
    WrRenderer renderer = {0};

    if (!InitGame(&game) || !InitRenderer(&renderer)) goto cleanup;

    while (!WindowShouldClose()) {
        HandleInputs(&input);

        float dt = GetFrameTime();
        if (dt > 0.1f) dt = 0.1f; // If fps less than 10, fix delta time and inputs

        UpdateGame(&game, &input, dt);
        UpdateRenderer(&renderer, &game);

        RenderGame(&renderer, &game);
    }

    exitCode = EXIT_SUCCESS;

cleanup:
    TerminateRenderer(&renderer);
    TerminateGame(&game);

    CloseWindow();

    return exitCode;
}

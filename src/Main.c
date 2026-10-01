#include "Core/Constants.h"
#include "Input/Input.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <stdlib.h>
#include <raylib.h>

int main(int argc, char const* argv[]) {
    (void)argc;
    (void)argv;
    int exitCode = EXIT_FAILURE;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WR_SCREEN_DEFAULT_WIDTH, WR_SCREEN_DEFAULT_HEIGHT, "C Wolfenstein Raycaster");
    SetTargetFPS(60);

    WrInput input;

    WrGame* game = CreateGame();
    WrRenderer* renderer = CreateRenderer();

    if (!game || !renderer) goto cleanup;

    while (!WindowShouldClose()) {
        HandleInputs(&input);

        float dt = GetFrameTime();
        if (dt > 0.1f) { // If fps less than 10, fix delta time and inputs
            float ratio = 0.1f / dt;

            input.mouseDelta.x *= ratio;
            input.mouseDelta.y *= ratio;
            dt = 0.1f;
        }

        UpdateGame(game, &input, dt);
        UpdateRenderer(renderer, game);

        RenderGame(renderer, game);
    }

    exitCode = EXIT_SUCCESS;

cleanup:
    DestroyRenderer(renderer);
    renderer = NULL;

    DestroyGame(game);
    game = NULL;

    CloseWindow();

    return exitCode;
}

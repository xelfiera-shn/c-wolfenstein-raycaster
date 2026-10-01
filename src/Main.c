#include "Core/Constants.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <raylib.h>

int main(int argc, char const* argv[]) {
    (void)argc; (void)argv;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WR_SCREEN_DEFAULT_WIDTH, WR_SCREEN_DEFAULT_HEIGHT, "C Wolfenstein Raycaster");
    SetTargetFPS(60);

    Game* game = CreateGame();
    if (!game) return -1;

    Renderer* renderer = CreateRenderer();
    if (!renderer) return -1;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.1f) dt = 0.1f; // If fps less than 10, fix delta time
        
        UpdateGame(game, dt);
        UpdateRenderer(renderer, game);
        
        RenderGame(renderer, game);
    }

    DestroyRenderer(renderer);
    renderer = NULL;

    DestroyGame(game);
    game = NULL;

    CloseWindow();

    return 0;
}
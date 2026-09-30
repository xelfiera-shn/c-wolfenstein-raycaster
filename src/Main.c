#include "Core/Constants.h"
#include "Platform/Platform.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

int main(int argc, char const* argv[]) {
    (void)argc; (void)argv;

    PlatformSetConfigFlags(PLATFORM_FLAG_WINDOW_RESIZABLE);
    PlatformInitWindow(WR_SCREEN_DEFAULT_WIDTH, WR_SCREEN_DEFAULT_HEIGHT, "C Wolfenstein Raycaster");
    PlatformSetTargetFPS(60);

    Game* game = CreateGame();
    if (!game) return -1;

    Renderer* renderer = CreateRenderer();
    if (!renderer) return -1;

    while (!PlatformWindowShouldClose()) {
        float dt = PlatformGetFrameTime();
        if (dt > 0.1f) dt = 0.1f; // If fps less than 10, fix delta time
        
        UpdateGame(game, dt);
        UpdateRenderer(renderer, game);
        
        PlatformBeginDrawing();

        RenderGame(renderer, game);

        PlatformDrawFPS(10, 10);
        PlatformEndDrawing();
    }

    DestroyRenderer(renderer);
    DestroyGame(game);

    PlatformCloseWindow();

    return 0;
}
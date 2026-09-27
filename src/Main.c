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
        PlatformBeginDrawing();

        // Begin - Game update
        float dt = PlatformGetFrameTime();

        UpdateGame(game, dt);
        UpdateRenderer(renderer, game);

        RenderGame(renderer, game);
        // End - Game update

        PlatformDrawFPS(10, 10);
        PlatformEndDrawing();
    }

    PlatformCloseWindow();

    return 0;
}
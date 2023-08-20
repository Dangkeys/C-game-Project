#include "raylib.h"
#include "Game.h"
int main(void)
{
    const int screenWidth = 1950;
    const int screenHeight = 1100;
    InitWindow(screenWidth, screenHeight, "Demon");
    
    Game game{screenWidth, screenHeight};
    

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        //start game logic
        game.Update(GetFrameTime());
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
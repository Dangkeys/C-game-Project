#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
int main()
{
    // window references
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Classyclash!");

    // map references
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{};
    const float mapScale{4.0f};
    // knight references
    Character knight{windowWidth, windowHeight};

    // prop references
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // begin game logic

        mapPosition = Vector2Scale(knight.getwindowPosition(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        //draw the prop
        for (auto prop : props)
        {
            prop.Render(knight.getwindowPosition());
        }

        //draw character
        knight.tick(GetFrameTime());

        //check map bounds
        Vector2 windowPosition = knight.getwindowPosition();
        if (windowPosition.x < 0 ||
            windowPosition.y < 0 ||
            windowPosition.x + windowWidth > map.width * mapScale ||
            windowPosition.y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        //check for collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getwindowPosition()), knight.getCollisionRec()))
                knight.undoMovement();
        }

        // end game logic
        EndDrawing();
    }
}
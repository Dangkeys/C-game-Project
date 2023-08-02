#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
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

    //enemy references
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };
    Enemy *enemies[]{
        &goblin,
        &slime
    };
    for (auto enemy : enemies)
    {
        enemy -> setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // begin game logic

        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
        // draw the map
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        //draw the prop
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPosition());
        }
        if (!knight.getAlive()) // character is dead
        {
            DrawText("Game Over", 75.f, 55.f, 40, WHITE);
            EndDrawing();
            continue;
        } else { // character is alive
            std :: string knightHealth = "Health: ";
            knightHealth.append(std :: to_string(knight.getHealth()), 0 , 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, WHITE);
        }

        //draw the enemy
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        //draw character
        knight.tick(GetFrameTime());

        //check map bounds
        Vector2 windowPosition = knight.getWorldPosition();
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
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPosition()), knight.getCollisionRec()))
                knight.undoMovement();
        }

        // end game logic
        EndDrawing();
    }
}
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "PickUps.h"
#include <string>
const int sizeOfCoin{29};
int coinCounter{};
int main()
{
    // window referencessssssssssssss
    const int windowWidth{1950};
    const int windowHeight{1180};
    InitWindow(windowWidth, windowHeight, "Classyclash!");

    // map references
    Texture2D map = LoadTexture("nature_tileset/realMap.png");
    Vector2 mapPosition{};
    const float mapScale{4.0f};
    const int tileSize{mapScale * 32};
    // knight references
    Character knight{windowWidth, windowHeight};

    // enemy references
    Enemy goblin{
        Vector2{1800.f, 2300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{
        Vector2{1500.f, 1700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    slime.setSpeed(3.f);
    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    PickUps coins[sizeOfCoin];
    const int coinOffset = 82;
    for (int i = 0; i < sizeOfCoin; i++)
    {
        // for (int j = 0; j < 28; j++)
        // {
        //     for (int k = 0; k < )
        // }
        coins[i].setMaxFrame(12);
        coins[i].setTexture(LoadTexture("nature_tileset/SPA_Coins.png"));
        coins[i].setWorldPosition(Vector2 {(10.f + i) * tileSize, 5.f * tileSize + coinOffset});
        coins[i].setFrame(i % coins[i].getMaxFrame());
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
        if (coinCounter >= sizeOfCoin)
        {
            DrawText("You win", windowWidth / 2 - 100, windowHeight /2 - 100, 64, WHITE);
            EndDrawing();
            continue;
        }

        if (!knight.getAlive()) // character is dead
        {
            DrawText("Game Over", 75.f, 55.f, 40, WHITE);
            EndDrawing();
            continue;
        }
        else
        { // character is alive
            std ::string knightHealth = "Health: ";
            knightHealth.append(std ::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 200.f, 40, WHITE);
        }

        // draw the enemy
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
        for (int i = 0; i < sizeOfCoin; i++)
        {
            coins[i].Render(knight.getWorldPosition(), GetFrameTime());
            if (CheckCollisionRecs(knight.getCollisionRec(),coins[i].getCollisionRec()) && coins[i].getActive())
            {
                coinCounter++;
                coins[i].setActive(false);
            }

        }

        // draw character
        knight.tick(GetFrameTime());

        // check map bounds
        Vector2 worldPosition = knight.getWorldPosition();
        if (worldPosition.x < 0 ||
            worldPosition.x + windowWidth > map.width * mapScale)
        {
            knight.undoMovementX();
        }
        if (worldPosition.y < 0 || worldPosition.y + windowHeight > map.height * mapScale)
        {
            knight.undoMovementY();
        }

        // end game logic
        EndDrawing();
    }
}
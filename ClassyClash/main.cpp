#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "PickUps.h"
#include "Prop.h"
#include <string>
const int coinMax{391};
const int sizeOfCoinWidth{31};
const int sizeOfCoinHeight{15};
int coinCounter{};
int coinCollected{};
const float mapScale{4.0f};
const int tileSize{mapScale * 32};
PickUps coins[coinMax];
Vector2 coinOffset{-50.f, 82.f};
int score{};
void setCoin(int i, int j);
int main()
{
    // window referencessssssssssssss
    const int windowWidth{1950};
    const int windowHeight{1180};
    InitWindow(windowWidth, windowHeight, "Classyclash!");

    // map references
    Texture2D map = LoadTexture("nature_tileset/realMap.png");
    Vector2 mapPosition{};

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
    slime.setSpeed(5.f);
    goblin.setSpeed(6.5f);
    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    // super spaghetti code ei ei
    // set coin to the right position
    for (int i = 0; i < sizeOfCoinWidth; i++)
    {
        for (int j = 0; j < sizeOfCoinHeight; j++)
        {
            // no draw the same horizontal line
            bool isValidDraw{!(
                j == 0 || j == 4 ||
                j == 8 || j == 11 ||
                j == 13 || j == 14)};
            if ((j == 0) && (i < 14 || i > 16))
                setCoin(i, j);
            else if (j == 4)
                setCoin(i, j);
            else if ((j == 6 || j == 10) && (i >= 11 && i < 20))
                setCoin(i, j);
            else if (j == 8 && ((i >= 0 && i <= 11) || (i >= sizeOfCoinWidth - 12 && i < sizeOfCoinWidth)))
                setCoin(i, j);
            else if (j == 11 && ((i >= 0 && i < 4) ||
                                 (i >= sizeOfCoinWidth - 4 && i < sizeOfCoinWidth) || i == 6 || i == sizeOfCoinWidth - 7 || i == 15))
                setCoin(i, j);
            else if (j == 13 && ((i > 5 && i < sizeOfCoinWidth - 6) || i == 3 || i == sizeOfCoinWidth - 4))
                setCoin(i, j);
            else if (j == 14 && ((i >= 3 && i <= 6) || (i > sizeOfCoinWidth - 8 && i < sizeOfCoinWidth - 3)))
                setCoin(i, j);
            else if (isValidDraw)
            {
                if ((i == 0 || i == sizeOfCoinWidth - 1) && j != 12)
                    setCoin(i, j);
                if (i == 6 || i == sizeOfCoinWidth - 7)
                    setCoin(i, j);
                if ((i == 13 || i == 17) && j <= 4)
                    setCoin(i, j);
                if ((i == 11 || i == 19) && (j == 7 || j == 9))
                    setCoin(i, j);
                if ((i == 15 || i == 3 || i == sizeOfCoinWidth - 4) && j == 12)
                    setCoin(i, j);
            }
        }
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
        if (coinCollected >= coinCounter)
        {
            DrawText("You win", windowWidth / 2 - 100, windowHeight / 2 - 100, 64, WHITE);
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
            std ::string coinCount = "Coin: ";
            coinCount.append(std ::to_string(coinCollected), 0, 3);
            coinCount.append("/", 0, 1);
            coinCount.append(std::to_string(coinCounter), 0, 3);
            DrawText(coinCount.c_str(), windowWidth - 280.f, 200.f, 40, WHITE);
            // std ::string showScore = "Score: ";
            // showScore.append(std::to_string(score), 0, 4);
            // DrawText(showScore.c_str(), windowWidth - 550.f, 200.f, 40, WHITE);
        }

        // draw the enemy
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        // draw coin
        for (int i = 0; i < coinCounter; i++)
        {
            coins[i].Render(knight.getWorldPosition(), GetFrameTime());
            if (CheckCollisionRecs(knight.getCollisionRec(), coins[i].getCollisionRec()) && coins[i].getActive())
            {
                coinCollected++;
                coins[i].setActive(false);
                score = coinCollected * 10;
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->hurt();
                    enemy->KnockBack();
                }
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
        // this code need to fix bug
        //  for (auto enemy : enemies)
        //  {
        //      if (worldPosition.x < 0 ||
        //          worldPosition.x + windowWidth > map.width * mapScale)
        //      {
        //          enemy->undoMovementX();
        //      }
        //      if (worldPosition.y < 0 || worldPosition.y + windowHeight > map.height * mapScale)
        //      {
        //          enemy->undoMovementY();
        //      }
        //  }

        // end game logic
        EndDrawing();
    }
}
void setCoin(int i, int j)
{
    coins[coinCounter].setMaxFrame(12);
    coins[coinCounter].setTexture(LoadTexture("nature_tileset/SPA_Coins.png"));
    coins[coinCounter].setWorldPosition(Vector2{(9.f + i) * tileSize + coinOffset.x,
                                                (5.f + j) * tileSize + coinOffset.y});
    coins[coinCounter].setFrame((i + j) % coins[coinCounter].getMaxFrame());
    coinCounter++;
}
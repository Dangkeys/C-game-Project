#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "PickUps.h"
#include "Prop.h"
#include "Mapbound.h"
#include <string>
const int coinMax{391};
const int sizeOfCoinWidth{31};
const int sizeOfCoinHeight{15};
int coinCounter{};
int coinCollected{};
float scoreRunningTime{};
float scoreUpdateTime{2};
bool timeStart{false};
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
    const int windowHeight{1100};
    InitWindow(windowWidth, windowHeight, "Classyclash!");

    // map references
    Texture2D map = LoadTexture("nature_tileset/realMap.png");
    Vector2 mapPosition{};

    // knight references
    Character knight{windowWidth, windowHeight};

    // enemy references
    Enemy goblin{
        Vector2{20 * tileSize, 9 * tileSize},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{
        Vector2{17 * tileSize, 11 * tileSize},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy little{
        Vector2{15 * tileSize, 5 * tileSize},
        LoadTexture("characters/littleUndead.png"),
        LoadTexture("characters/littleUndead.png")};
    Enemy super{
        Vector2{13 * tileSize, 7 * tileSize},
        LoadTexture("characters/superDemon.png"),
        LoadTexture("characters/superDemon.png")};
    Enemy runner{
        Vector2{12 * tileSize, 8 * tileSize},
        LoadTexture("characters/runnerDemon.png"),
        LoadTexture("characters/runnerDemon.png")};
    Enemy normal{
        Vector2{16 * tileSize, 6 * tileSize},
        LoadTexture("characters/normalDemon.png"),
        LoadTexture("characters/normalDemon.png")};
    Enemy strong{
        Vector2{14 * tileSize, 4 * tileSize},
        LoadTexture("characters/strongDemon.png"),
        LoadTexture("characters/strongDemon.png")};
    // the code below need to make it more clean
    runner.setScale(5.f);
    runner.setFrame(12, 8);
    runner.setMaxFrame(4);

    normal.setMaxFrame(8);
    normal.setScale(7);
    normal.setFrame(11, 6);

    little.setScale(5.f);
    little.setFrame(10, 5);

    strong.setScale(7.f);
    strong.setFrame(14, 4);

    super.setScale(10.f);
    super.setFrame(13, 7);

    knight.setMaxFrame(6.f);

    // please clean the previous code

    // slime.setMaxFrame(6.f);
    // slime.setSpeed(6.5f);
    // slime.setScale(5.5f);

    // goblin.setSpeed(8.5f);
    // goblin.setScale(5.f);
    // goblin.setMaxFrame(6.f);

    Enemy *enemies[]{
        &little,
        &runner,
        &normal,
        &strong,
        &super};
    for (auto enemy : enemies)
    {
        // enemy->setTarget(&knight);
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

    // mapbound reference
    float landWidth{33 * tileSize + 20.f};
    float landHeight{18 * tileSize};
    float sizeOfRectangle{20.f};
    Mapbound upperbound{{7 * tileSize, 4 * tileSize}, landWidth, sizeOfRectangle};
    Mapbound lowerbound{{7 * tileSize, 21 * tileSize + 50}, landWidth, sizeOfRectangle};
    Mapbound leftbound{{7 * tileSize - 20.f, 4 * tileSize}, sizeOfRectangle, landHeight};
    Mapbound rightbound{{40 * tileSize + 20.f, 4 * tileSize}, sizeOfRectangle, landHeight};
    Mapbound *mapbounds[]{&upperbound, &lowerbound, &leftbound, &rightbound};
    Mapbound *mapboundsX[]{&leftbound, &rightbound};
    Mapbound *mapboundsY[]{&upperbound, &lowerbound};

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
        {
            // character is alive
            std ::string knightHealth = "Health: ";
            knightHealth.append(std ::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 100.f, 40, WHITE);
            std ::string coinCount = "Coin: ";
            coinCount.append(std ::to_string(coinCollected), 0, 3);
            coinCount.append("/", 0, 1);
            coinCount.append(std::to_string(coinCounter), 0, 3);
            DrawText(coinCount.c_str(), windowWidth - 280.f, 100.f, 40, WHITE);
            // std ::string showScore = "Score: ";
            // showScore.append(std::to_string(score), 0, 4);
            // DrawText(showScore.c_str(), windowWidth - 550.f, 200.f, 40, WHITE);
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

        // draw the enemy
        for (auto enemy : enemies)
        {
            enemy->setScreenPosition(knight.getWorldPosition());
            enemy->tick(GetFrameTime());
            // enemy->drawDetectRadius();
            if (CheckCollisionCircleRec(
                    {enemy->getScreenPosition().x + enemy->getWidth() * enemy->getScale() / 2,
                     enemy->getScreenPosition().y + enemy->getHeight() * enemy->getScale() / 2},
                    enemy->getDetectRadius(),
                    knight.getCollisionRec()))
            {
                enemy->setZeroTimeCounter();
                enemy->setTarget(&knight);
                enemy->setSpeed(6.5f);
            }
            else
            {
                enemy->setTarget(NULL);
                enemy->setSpeed(2.f);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // timeStart = true;
            for (auto enemy : enemies)
            {

                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->hurt();
                    enemy->KnockBack();
                }
            }
        }
        // if (timeStart)
        // {
        //     scoreRunningTime += GetFrameTime();
        //     if (scoreRunningTime >= scoreUpdateTime)
        //     {
        //         scoreRunningTime = 0;
        //         timeStart = false;
        //     }
        //     knight.setInvisible(true);
        // } else {
        //     knight.setInvisible(false);
        // }

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
        if (CheckCollisionRecs(knight.getCollisionRec(), lowerbound.getCollisionRec()))
            knight.undoMovementS();
        else
            knight.doMovements();

        // mapbound mechanic
        for (auto mapbound : mapbounds)
        {
            mapbound->Render(knight.getWorldPosition());
        }
        for (auto mapbound : mapboundsX)
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), mapbound->getCollisionRec()))
                    enemy->collideWithMapboundX();
            }
        }
        for (auto mapbound : mapboundsY)
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), mapbound->getCollisionRec()))
                    enemy->collideWithMapboundY();
            }
        }
        for (auto enemy : enemies)
        {
            if (CheckCollisionRecs(enemy->getCollisionRec(), leftbound.getCollisionRec()))
                enemy->collideWithLeftbound();
            if (CheckCollisionRecs(enemy->getCollisionRec(), rightbound.getCollisionRec()))
                enemy->collideWithRightbound();
            if (CheckCollisionRecs(enemy->getCollisionRec(), lowerbound.getCollisionRec()))
                enemy->collideWithBottombound();
            else
                enemy->noCollideWithBottombound();
        }
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
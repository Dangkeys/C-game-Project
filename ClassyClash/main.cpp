#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "PickUps.h"
#include "Prop.h"
#include "Mapbound.h"
#include <string>

// coin reference
const int coinMax{391};
const int sizeOfCoinWidth{31};
const int sizeOfCoinHeight{15};
int coinCounter{};
int coinCollected{};
float scoreRunningTime{};
float scoreUpdateTime{2};
bool timeStart{false};

// map references
const float mapScale{4.0f};
const int tileSize{mapScale * 32};

// coin referemces
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
    Enemy little{
        Vector2{20 * tileSize, 5 * tileSize},
        LoadTexture("characters/littleOrc.png"),
        LoadTexture("characters/littleOrc.png")};
    Enemy super{
        Vector2{20 * tileSize, 5 * tileSize},
        LoadTexture("characters/superOrc.png"),
        LoadTexture("characters/superOrc.png")};
    Enemy runner{
        Vector2{20 * tileSize, 20 * tileSize},
        LoadTexture("characters/runnerOrc.png"),
        LoadTexture("characters/runnerOrc.png")};
    Enemy normal{
        Vector2{15 * tileSize, 10 * tileSize},
        LoadTexture("characters/normalOrc.png"),
        LoadTexture("characters/normalOrc.png")};
    Enemy strong{
        Vector2{25 * tileSize, 15 * tileSize},
        LoadTexture("characters/strongOrc.png"),
        LoadTexture("characters/strongOrc.png")};
    // the code below need to make it more clean
    little.setDamage(0.5f);
    little.setHealth(2.f);
    little.setSpeed(9.f);
    little.setScale(5.f);
    little.setDetectRadius(0.f);
    little.setKnockBackAmount(20.f);
    little.setUpdateTimeCounter(GetRandomValue(2, 6));
    little.setMaxFrame(8);
    little.setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

    normal.setDamage(1.f);
    normal.setHealth(4.f);
    normal.setSpeed(4.f);
    normal.setScale(7.f);
    normal.setDetectRadius(500.f);
    normal.setKnockBackAmount(10.f);
    normal.setUpdateTimeCounter(GetRandomValue(2, 8));
    normal.setMaxFrame(8);
    normal.setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

    runner.setDamage(2.f);
    runner.setHealth(3.f);
    runner.setSpeed(7.f);
    runner.setScale(6.f);
    runner.setDetectRadius(300.f);
    runner.setKnockBackAmount(15.f);
    runner.setUpdateTimeCounter(GetRandomValue(2, 6));
    runner.setMaxFrame(8);
    runner.setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

    strong.setDamage(1.5f);
    strong.setHealth(6.f);
    strong.setSpeed(5.5f);
    strong.setScale(8.f);
    strong.setDetectRadius(0.f);
    strong.setKnockBackAmount(5.f);
    strong.setKnockBackUpdateTime(0.1f);
    strong.setUpdateTimeCounter(GetRandomValue(2, 6));
    strong.setMaxFrame(8);
    strong.setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

    super.setDamage(4.f);
    super.setHealth(10.f);
    super.setSpeed(6.f);
    super.setScale(9.f);
    super.setDetectRadius(400.f);
    super.setKnockBackAmount(2.5f);
    super.setKnockBackUpdateTime(0.05f);
    super.setFrame(10, 5);
    super.setUpdateTimeCounter(GetRandomValue(2, 6));
    super.setMaxFrame(8);
    super.setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

    knight.setMaxFrame(6.f);

    Enemy *enemies[]{
        &little,
        &runner,
        &normal,
        &strong,
        &super};

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
            DrawText("Game Over", windowWidth / 2 - 50.f, windowHeight / 2 - 50.f, 40, WHITE);
            EndDrawing();
            continue;
        }
        else
        {
            // character is alive
            std ::string knightHealth = "Health: ";
            knightHealth.append(std ::to_string(knight.getHealth()), 0, 4);
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
        // draw character
        knight.tick(GetFrameTime());
        // draw the enemy
        for (auto enemy : enemies)
        {
            enemy->setScreenPosition(knight.getWorldPosition());
            enemy->tick(GetFrameTime());
        }

        // set the behavior for each type
        little.setTarget(&knight);

        strong.setTarget(&knight);

        if (normal.isInDetectRadius(knight.getCollisionRec()))
        {

            normal.setZeroTimeCounter();
            normal.setTarget(&knight);
            normal.setSpeed(6.f);
        }
        else
        {
            normal.setTarget(NULL);
            normal.setSpeed(4.f);
        }

        if (runner.isInDetectRadius(knight.getCollisionRec()))
        {
            runner.setTarget(&knight);
            runner.setSpeed(12.f);
        }

        if (super.isInDetectRadius(knight.getCollisionRec()))
        {
            super.setZeroTimeCounter();
            super.setTarget(&knight);
            super.setSpeed(6.f);
        }
        else
        {
            super.setTarget(NULL);
            super.setSpeed(2.f);
        }

        // set the behavior for each type

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && knight.canAttack)
        {
            knight.canAttack = false;
            // timeStart = true;
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->hurt();
                    enemy->KnockBack(enemy->getKnockBackAmount());
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
        //when player hurt red screen will appear
        //DrawRectangle(0, 0, windowWidth * 500, windowHeight * 500, {231, 41, 55, 5.f * (10 - knight.getHealth())});
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
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "PickUps.h"
#include "Prop.h"
#include "Mapbound.h"
#include <string>

// coin reference
const int MAX{391};
const int sizeOfCoinWidth{31};
const int sizeOfCoinHeight{15};
const int ENEMYMAX{50};
const int TYPEMAX{10};
int coinCounter{};
int coinCollected{};
float scoreRunningTime{};
float scoreUpdateTime{2};
bool timeStart{false};

// map references
const float mapScale{4.0f};
const int tileSize{mapScale * 32};

// coin referemces
PickUps coins[MAX];
Vector2 coinOffset{-50.f, 82.f};
int score{};
void setCoin(int i, int j);

// spawner references
float spawerRunningTime{21.f};
float nextSpawnTime{20.f};
int enemyPerWave{1};
int enemySize{0};
int enemyCounter{};

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
    Enemy little[TYPEMAX];
    Enemy super[TYPEMAX];
    Enemy runner[TYPEMAX];
    Enemy normal[TYPEMAX];
    Enemy strong[TYPEMAX];

    knight.setMaxFrame(6.f);

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

        // spawner logic
        spawerRunningTime += GetFrameTime();
        if (spawerRunningTime >= nextSpawnTime)
        {
            enemySize += enemyPerWave;
            spawerRunningTime = 0;
            for (int i = 0; i < enemySize; i++)
            {
                int randomTribeLittle{}




                little[enemySize - 1].setWorldPosition(Vector2{(float)GetRandomValue(9 * tileSize, 40 * tileSize),
                                                               (float)GetRandomValue(5 * tileSize, 20 * tileSize)});
                little[enemySize - 1].setTexture(LoadTexture("characters/littleOrc.png"));
                little[enemySize - 1].setDamage(0.5f);
                little[enemySize - 1].setHealth(2.f);
                little[enemySize - 1].setSpeed(9.f);
                little[enemySize - 1].setScale(5.f);
                little[enemySize - 1].setDetectRadius(0.f);
                little[enemySize - 1].setKnockBackAmount(20.f);
                little[enemySize - 1].setUpdateTimeCounter(GetRandomValue(2, 6));
                little[enemySize - 1].setMaxFrame(8);
                little[enemySize - 1].setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));
                normal[enemySize - 1].setWorldPosition(Vector2{(float)GetRandomValue(9 * tileSize, 40 * tileSize),
                                                               (float)GetRandomValue(5 * tileSize, 20 * tileSize)});
                normal[enemySize - 1].setTexture(LoadTexture("characters/normalOrc.png"));
                normal[enemySize - 1].setDamage(1.f);
                normal[enemySize - 1].setHealth(4.f);
                normal[enemySize - 1].setSpeed(4.f);
                normal[enemySize - 1].setScale(7.f);
                normal[enemySize - 1].setDetectRadius(500.f);
                normal[enemySize - 1].setKnockBackAmount(10.f);
                normal[enemySize - 1].setUpdateTimeCounter(GetRandomValue(2, 8));
                normal[enemySize - 1].setMaxFrame(8);
                normal[enemySize - 1].setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

                runner[enemySize - 1].setWorldPosition(Vector2{(float)GetRandomValue(9 * tileSize, 40 * tileSize),
                                                               (float)GetRandomValue(5 * tileSize, 20 * tileSize)});
                runner[enemySize - 1].setTexture(LoadTexture("characters/runnerOrc.png"));
                runner[enemySize - 1].setDamage(2.f);
                runner[enemySize - 1].setHealth(3.f);
                runner[enemySize - 1].setSpeed(7.f);
                runner[enemySize - 1].setScale(6.f);
                runner[enemySize - 1].setDetectRadius(300.f);
                runner[enemySize - 1].setKnockBackAmount(15.f);
                runner[enemySize - 1].setUpdateTimeCounter(GetRandomValue(2, 6));
                runner[enemySize - 1].setMaxFrame(8);
                runner[enemySize - 1].setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

                strong[enemySize - 1].setWorldPosition(Vector2{(float)GetRandomValue(9 * tileSize, 40 * tileSize),
                                                               (float)GetRandomValue(5 * tileSize, 20 * tileSize)});
                strong[enemySize - 1].setTexture(LoadTexture("characters/strongOrc.png"));
                strong[enemySize - 1].setDamage(1.5f);
                strong[enemySize - 1].setHealth(6.f);
                strong[enemySize - 1].setSpeed(5.5f);
                strong[enemySize - 1].setScale(8.f);
                strong[enemySize - 1].setDetectRadius(0.f);
                strong[enemySize - 1].setKnockBackAmount(5.f);
                strong[enemySize - 1].setKnockBackUpdateTime(0.1f);
                strong[enemySize - 1].setUpdateTimeCounter(GetRandomValue(2, 6));
                strong[enemySize - 1].setMaxFrame(8);
                strong[enemySize - 1].setFrame(GetRandomValue(9, 40), GetRandomValue(5, 20));

                super[enemySize - 1].setWorldPosition(Vector2{(float)GetRandomValue(9 * tileSize, 40 * tileSize),
                                                              (float)GetRandomValue(5 * tileSize, 20 * tileSize)});
                super[enemySize - 1].setTexture(LoadTexture("characters/superOrc.png"));
                super[enemySize - 1].setDamage(4.f);
                super[enemySize - 1].setHealth(10.f);
                super[enemySize - 1].setSpeed(6.f);
                super[enemySize - 1].setScale(10.f);
                super[enemySize - 1].setDetectRadius(400.f);
                super[enemySize - 1].setKnockBackAmount(0.1f);
                super[enemySize - 1].setKnockBackUpdateTime(0.05f);
                super[enemySize - 1].setFrame(10, 5);
                super[enemySize - 1].setUpdateTimeCounter(GetRandomValue(2, 6));
                super[enemySize - 1].setMaxFrame(8);
                super[enemySize - 1].setFrame(GetRandomValue(9, 40), GetRandomValue(5, 19));
            }
        }

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
        for (int i = 0; i < enemySize; i++)
        {
            little[i].setScreenPosition(knight.getWorldPosition());
            little[i].tick(GetFrameTime());
            normal[i].setScreenPosition(knight.getWorldPosition());
            normal[i].tick(GetFrameTime());
            runner[i].setScreenPosition(knight.getWorldPosition());
            runner[i].tick(GetFrameTime());
            strong[i].setScreenPosition(knight.getWorldPosition());
            strong[i].tick(GetFrameTime());
            super[i].setScreenPosition(knight.getWorldPosition());
            super[i].tick(GetFrameTime());
        }

        for (int i = 0; i < enemySize; i++)
        {
            strong[i].setTarget(&knight);
            little[i].setTarget(&knight);
        }

        for (int i = 0; i < enemySize; i++)
        {
            if (normal[i].isInDetectRadius(knight.getCollisionRec()))
            {

                normal[i].setZeroTimeCounter();
                normal[i].setTarget(&knight);
                normal[i].setSpeed(6.f);
            }
            else
            {
                normal[i].setTarget(NULL);
                normal[i].setSpeed(4.f);
            }
            if (super[i].isInDetectRadius(knight.getCollisionRec()))
            {
                super[i].setZeroTimeCounter();
                super[i].setTarget(&knight);
                super[i].setSpeed(6.f);
            }
            else
            {
                super[i].setTarget(NULL);
                super[i].setSpeed(2.f);
            }
        }
        for (int i = 0; i < enemySize; i++)
        {
            if (runner[i].isInDetectRadius(knight.getCollisionRec()))
            {
                runner[i].setTarget(&knight);
                runner[i].setSpeed(12.f);
            }
        }

        // set the behavior for each type

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && knight.canAttack)
        {
            knight.canAttack = false;
            // timeStart = true;
            for (int i = 0; i < enemySize; i++)
            {
                if (CheckCollisionRecs(little[i].getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    little[i].hurt();
                    little[i].KnockBack(little[i].getKnockBackAmount());
                }
                if (CheckCollisionRecs(normal[i].getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    normal[i].hurt();
                    normal[i].KnockBack(normal[i].getKnockBackAmount());
                }
                if (CheckCollisionRecs(runner[i].getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    runner[i].hurt();
                    runner[i].KnockBack(runner[i].getKnockBackAmount());
                }
                if (CheckCollisionRecs(strong[i].getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    strong[i].hurt();
                    strong[i].KnockBack(strong[i].getKnockBackAmount());
                }
                if (CheckCollisionRecs(super[i].getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    super[i].hurt();
                    super[i].KnockBack(super[i].getKnockBackAmount());
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
            for (int i = 0; i < enemySize; i++)
            {
                if (CheckCollisionRecs(little[i].getCollisionRec(), mapbound->getCollisionRec()))
                    little[i].collideWithMapboundX();
                if (CheckCollisionRecs(normal[i].getCollisionRec(), mapbound->getCollisionRec()))
                    normal[i].collideWithMapboundX();
                if (CheckCollisionRecs(runner[i].getCollisionRec(), mapbound->getCollisionRec()))
                    runner[i].collideWithMapboundX();
                if (CheckCollisionRecs(strong[i].getCollisionRec(), mapbound->getCollisionRec()))
                    strong[i].collideWithMapboundX();
                if (CheckCollisionRecs(super[i].getCollisionRec(), mapbound->getCollisionRec()))
                    super[i].collideWithMapboundX();
            }
        }
        for (auto mapbound : mapboundsY)
        {
            for (int i = 0; i < enemySize; i++)
            {
                if (CheckCollisionRecs(little[i].getCollisionRec(), mapbound->getCollisionRec()))
                    little[i].collideWithMapboundX();
                if (CheckCollisionRecs(normal[i].getCollisionRec(), mapbound->getCollisionRec()))
                    normal[i].collideWithMapboundX();
                if (CheckCollisionRecs(runner[i].getCollisionRec(), mapbound->getCollisionRec()))
                    runner[i].collideWithMapboundX();
                if (CheckCollisionRecs(strong[i].getCollisionRec(), mapbound->getCollisionRec()))
                    strong[i].collideWithMapboundX();
                if (CheckCollisionRecs(super[i].getCollisionRec(), mapbound->getCollisionRec()))
                    super[i].collideWithMapboundX();
            }
        }
        // if (CheckCollisionRecs(enemy->getCollisionRec(), leftbound.getCollisionRec()))
        //     enemy->collideWithLeftbound();
        // if (CheckCollisionRecs(enemy->getCollisionRec(), rightbound.getCollisionRec()))
        //     enemy->collideWithRightbound();
        // if (CheckCollisionRecs(enemy->getCollisionRec(), lowerbound.getCollisionRec()))
        //     enemy->collideWithBottombound();
        // else
        //     enemy->noCollideWithBottombound();}
        for (int i = 0; i < enemySize; i++)
        {
            if (CheckCollisionRecs(little[i].getCollisionRec(), leftbound.getCollisionRec()))
                little[i].collideWithLeftbound();
            if (CheckCollisionRecs(normal[i].getCollisionRec(), leftbound.getCollisionRec()))
                normal[i].collideWithLeftbound();
            if (CheckCollisionRecs(runner[i].getCollisionRec(), leftbound.getCollisionRec()))
                runner[i].collideWithLeftbound();
            if (CheckCollisionRecs(strong[i].getCollisionRec(), leftbound.getCollisionRec()))
                strong[i].collideWithLeftbound();
            if (CheckCollisionRecs(super[i].getCollisionRec(), leftbound.getCollisionRec()))
                super[i].collideWithLeftbound();

            if (CheckCollisionRecs(little[i].getCollisionRec(), rightbound.getCollisionRec()))
                little[i].collideWithRightbound();
            if (CheckCollisionRecs(normal[i].getCollisionRec(), rightbound.getCollisionRec()))
                normal[i].collideWithRightbound();
            if (CheckCollisionRecs(runner[i].getCollisionRec(), rightbound.getCollisionRec()))
                runner[i].collideWithRightbound();
            if (CheckCollisionRecs(strong[i].getCollisionRec(), rightbound.getCollisionRec()))
                strong[i].collideWithRightbound();
            if (CheckCollisionRecs(super[i].getCollisionRec(), rightbound.getCollisionRec()))
                super[i].collideWithRightbound();

            if (CheckCollisionRecs(super[i].getCollisionRec(), lowerbound.getCollisionRec()))
                super[i].collideWithBottombound();
            else
                super[i].noCollideWithBottombound();
        }
        // when player hurt red screen will appear
        if (knight.isHurt)
            DrawRectangle(0, 0, windowWidth * 500, windowHeight * 500, {231, 41, 55, 50});
        //  end game logic
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
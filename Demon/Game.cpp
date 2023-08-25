#include "Game.h"

Game::Game(int winWidth, int winHeight) : windowWidth(winWidth),
                                          windowHeight(winHeight)
{
    SetPositionCoin();
}
void Game::Update(float deltaTime)
{
    little.SetTarget(&player);
    if (coinCollected >= coinCounter)
        isNextWave = true;
    if (!player.GetAlive())
        isGameEnd = true;
    map.Update(player.GetWorldPosition());
    player.Update(deltaTime);
    little.Update(deltaTime);
    little.playerPosition = player.GetWorldPosition();

    AttackEnemy();
    PlayerMapboundMechanic();
    UpdateCoin(deltaTime);
    UI();
}

void Game::AttackEnemy()
{
    if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) && player.canAttack)
    {
        player.canAttack = false;
        if (CheckCollisionRecs(little.GetCollision(), player.GetDrawSwordCollision()))
        {
            little.Hurt(player.dealDamageAmount);
            // dont forget to add mapbound for enemy (every mapbound)
        }
    }
}
void Game::UpdateCoin(float deltaTime)
{
    for (int i = 0; i < COINMAX; i++)
    {
        coins[i].Update(player.GetWorldPosition(), deltaTime);
        if (CheckCollisionRecs(coins[i].GetCollision(), player.GetCollision()) && coins[i].GetActive())
        {
            coinCollected++;
            coins[i].SetActive(false);
            score = coinCollected * 10;
        }
    }
}
void Game::UI()
{
    std ::string knightHealth = "Health: ";
    knightHealth.append(std ::to_string(player.GetHealth()), 0, 4);
    DrawText(knightHealth.c_str(), 55.f, 100.f, 40, WHITE);
    // std ::string coinCount = "Coin: ";
    // coinCount.append(std ::to_string(coinCollected), 0, 3);
    // coinCount.append("/", 0, 1);
    // coinCount.append(std::to_string(coinCounter), 0, 3);
    // DrawText(coinCount.c_str(), windowWidth - 280.f, 100.f, 40, WHITE);
    std ::string showScore = "Score: ";
    showScore.append(std::to_string(score), 0, 10);
    DrawText(showScore.c_str(), 55, 150.f, 40, WHITE);
    std ::string showWave = "Wave: ";
    showWave.append(std::to_string(waveCounter), 0, 4);
    DrawText(showWave.c_str(), windowWidth - 200.f, 100.f, 40, WHITE);
}
void Game::ResetFirstFrame()
{
    waveCounter = 0;
    score = 0;
    ResetNextWave();
}
void Game::ResetNextWave()
{
    player.ResetNextWave();
    ResetCoin();
    coinCollected = 0;
}
void Game::SetCoin(int x, int y)
{
    coins[coinCounter].SetWorldPosition(Vector2{(9.f + x) * tileSize + coinOffset.x,
                                                (5.f + y) * tileSize + coinOffset.y});
    coins[coinCounter].SetFrame((x + y) % coins[coinCounter].GetMaxFrame());
    coinCounter++;
}
void Game::SetPositionCoin()
{
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
                SetCoin(i, j);
            else if (j == 4)
                SetCoin(i, j);
            else if ((j == 6 || j == 10) && (i >= 11 && i < 20))
                SetCoin(i, j);
            else if (j == 8 && ((i >= 0 && i <= 11) || (i >= sizeOfCoinWidth - 12 && i < sizeOfCoinWidth)))
                SetCoin(i, j);
            else if (j == 11 && ((i >= 0 && i < 4) ||
                                 (i >= sizeOfCoinWidth - 4 && i < sizeOfCoinWidth) || i == 6 || i == sizeOfCoinWidth - 7 || i == 15))
                SetCoin(i, j);
            else if (j == 13 && ((i > 5 && i < sizeOfCoinWidth - 6) || i == 3 || i == sizeOfCoinWidth - 4))
                SetCoin(i, j);
            else if (j == 14 && ((i >= 3 && i <= 6) || (i > sizeOfCoinWidth - 8 && i < sizeOfCoinWidth - 3)))
                SetCoin(i, j);
            else if (isValidDraw)
            {
                if ((i == 0 || i == sizeOfCoinWidth - 1) && j != 12)
                    SetCoin(i, j);
                if (i == 6 || i == sizeOfCoinWidth - 7)
                    SetCoin(i, j);
                if ((i == 13 || i == 17) && j <= 4)
                    SetCoin(i, j);
                if ((i == 11 || i == 19) && (j == 7 || j == 9))
                    SetCoin(i, j);
                if ((i == 15 || i == 3 || i == sizeOfCoinWidth - 4) && j == 12)
                    SetCoin(i, j);
            }
        }
    }
}
void Game::ResetCoin()
{
    for (int i = 0; i < COINMAX; i++)
    {
        coins[i].SetActive(true);
    }
}
void Game::PlayerMapboundMechanic()
{
    for (int i = 0; i < mapboundSize; i++)
    {
        mapbounds[i].Update(player.GetWorldPosition());
    }
    if (CheckCollisionRecs(player.GetCollision(), mapbounds[0].GetCollision()))
        player.isValidW = false;
    else
        player.isValidW = true;
    if (CheckCollisionRecs(player.GetCollision(), mapbounds[2].GetCollision()))
        player.isValidS = false;
    else
        player.isValidS = true;
    if (CheckCollisionRecs(player.GetCollision(), mapbounds[3].GetCollision()))
        player.isValidA = false;
    else
        player.isValidA = true;
    if (CheckCollisionRecs(player.GetCollision(), mapbounds[4].GetCollision()))
        player.isValidD = false;
    else
        player.isValidD = true;
}
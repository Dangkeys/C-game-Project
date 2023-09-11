#include "Game.h"
#define ENEMYMAX 100
Game::Game(int winWidth, int winHeight) : windowWidth(winWidth),
                                          windowHeight(winHeight)
{
    SetPositionCoin();
    SetSoundVolume(Coin1, 0.2);
    SetSoundVolume(Coin2, 0.2);
    SetSoundVolume(Coin3, 0.2);
    SetSoundVolume(slash1, 0.4);
    SetSoundVolume(slash2, 0.4);
    SetSoundVolume(slash3, 0.4);
    SetSoundVolume(alert, 0.4);
    SetSoundVolume(spawn, 1);
}
void Game::Update(float deltaTime)
{
    if (!player.GetAlive())
    {
        endFirstFrame = true;
        if (endFirstFrame)
            isGameEnd = true;
    }

    if (coinCollected >= coinCounter)
    {
        isNextWave = true;
        return;
    }
    map.Update(player.GetWorldPosition());
    UpdateCoin(deltaTime);
    player.Update(deltaTime);
    Spawn(deltaTime);
    AttackEnemy();
    UpdateEnemy(deltaTime);
    PlayerMapboundMechanic();
    UI(deltaTime);
}

void Game::ResetEnemy()
{
    for (int i = 0; i < enemySize; i++)
    {
        littles[i].EnemyReset();
        normals[i].EnemyReset();
        strongs[i].EnemyReset();
        runners[i].EnemyReset();
        supers[i].EnemyReset();
    }
    enemySize = 0;
}
void Game::Spawn(float deltaTime)
{
    spawnRunningTime += deltaTime;
    if (spawnRunningTime >= spawnUpdateTime)
    {
        isSpawn = true;
        PlaySound(spawn);
        int randomPositionX[5]{};
        int randomPositionY[5]{};
        spawnRunningTime = 0;
        if (enemySize <= ENEMYMAX - 6)
            enemySize++;
        littles[enemySize - 1].SetAlive(true);
        normals[enemySize - 1].SetAlive(true);
        strongs[enemySize - 1].SetAlive(true);
        runners[enemySize - 1].SetAlive(true);
        supers[enemySize - 1].SetAlive(true);
        RandomTribe();
        for (int i = 0; i < 5; i++)
        {
            do
            {
                randomPositionX[i] = GetRandomValue(9 * tileSize, 39 * tileSize);
                randomPositionY[i] = GetRandomValue(5 * tileSize, 19 * tileSize);
            } while ((randomPositionX[i] >= player.GetWorldPosition().x - supers[i].GetDrawWidth() &&
                      randomPositionX[i] <= player.GetWorldPosition().x + windowWidth) &&
                     (randomPositionY[i] >= player.GetWorldPosition().y - supers[i].GetDrawHeight() &&
                      randomPositionY[i] <= player.GetWorldPosition().y + windowHeight));
        }
        littles[enemySize - 1].SetWorldPosition(Vector2{(float)randomPositionX[0], (float)randomPositionY[0]});
        normals[enemySize - 1].SetWorldPosition(Vector2{(float)randomPositionX[1], (float)randomPositionY[1]});
        strongs[enemySize - 1].SetWorldPosition(Vector2{(float)randomPositionX[2], (float)randomPositionY[2]});
        runners[enemySize - 1].SetWorldPosition(Vector2{(float)randomPositionX[3], (float)randomPositionY[3]});
        supers[enemySize - 1].SetWorldPosition(Vector2{(float)randomPositionX[4], (float)randomPositionY[4]});
    }
}
void Game::AttackEnemy()
{
    if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) && player.canAttack)
    {
        int rand = GetRandomValue(1, 3);
        if (rand == 1)
            PlaySound(slash1);
        else if (rand == 2)
            PlaySound(slash2);
        else
            PlaySound(slash3);
        player.canAttack = false;
        for (int i = 0; i < enemySize; i++)
        {
            if (CheckCollisionRecs(littles[i].GetCollision(), player.GetDrawSwordCollision()))
                littles[i].Hurt(player.dealDamageAmount);
            if (CheckCollisionRecs(normals[i].GetCollision(), player.GetDrawSwordCollision()))
                normals[i].Hurt(player.dealDamageAmount);
            if (CheckCollisionRecs(strongs[i].GetCollision(), player.GetDrawSwordCollision()))
                strongs[i].Hurt(player.dealDamageAmount);
            if (CheckCollisionRecs(runners[i].GetCollision(), player.GetDrawSwordCollision()))
                runners[i].Hurt(player.dealDamageAmount);
            if (CheckCollisionRecs(supers[i].GetCollision(), player.GetDrawSwordCollision()))
                supers[i].Hurt(player.dealDamageAmount);
        }
    }
}
void Game::UpdateEnemy(float deltaTime)
{
    for (int i = 0; i < enemySize; i++)
    {
        littles[i].playerPosition = player.GetWorldPosition();
        littles[i].Update(deltaTime);
        normals[i].playerPosition = player.GetWorldPosition();
        normals[i].Update(deltaTime);
        strongs[i].playerPosition = player.GetWorldPosition();
        strongs[i].Update(deltaTime);
        runners[i].playerPosition = player.GetWorldPosition();
        runners[i].Update(deltaTime);
        supers[i].playerPosition = player.GetWorldPosition();
        supers[i].Update(deltaTime);

        littles[i].SetTarget(&player);
        if (CheckCollisionCircleRec(normals[i].GetCenterDetectRadius(), normals[i].GetDetectRadius(), player.GetCollision()))
            normals[i].SetTarget(&player);
        else
            normals[i].SetTarget(NULL);
        strongs[i].SetTarget(&player);
        if (CheckCollisionCircleRec(runners[i].GetCenterDetectRadius(), runners[i].GetDetectRadius(), player.GetCollision()))
        {
            runners[i].SetTarget(&player);
            if (runners[i].alertFirstFrame)
            {
                PlaySound(alert);
                runners[i].alertFirstFrame = false;
            }
        }
        else
            runners[i].alertFirstFrame = true;
        if (CheckCollisionCircleRec(supers[i].GetCenterDetectRadius(), supers[i].GetDetectRadius(), player.GetCollision()) && supers[i].GetAlive())
        {
            supers[i].SetTarget(&player);
            if (supers[i].alertFirstFrame)
            {
                PlaySound(alert);
                supers[i].alertFirstFrame = false;
            }
        }
        else
        {
            supers[i].alertFirstFrame = true;
            supers[i].SetTarget(NULL);
        }
        if (CheckCollisionRecs(littles[i].GetCollision(), mapbounds[1].GetCollision()))
            littles[i].isUpperbound = true;
        else
            littles[i].isUpperbound = false;
        if (CheckCollisionRecs(littles[i].GetCollision(), mapbounds[2].GetCollision()))
            littles[i].isLowerbound = true;
        else
            littles[i].isLowerbound = false;
        if (CheckCollisionRecs(littles[i].GetCollision(), mapbounds[3].GetCollision()))
            littles[i].isLeftbound = true;
        else
            littles[i].isLeftbound = false;
        if (CheckCollisionRecs(littles[i].GetCollision(), mapbounds[4].GetCollision()))
            littles[i].isRightbound = true;
        else
            littles[i].isRightbound = false;

        if (CheckCollisionRecs(normals[i].GetCollision(), mapbounds[1].GetCollision()))
            normals[i].isUpperbound = true;
        else
            normals[i].isUpperbound = false;
        if (CheckCollisionRecs(normals[i].GetCollision(), mapbounds[2].GetCollision()))
            normals[i].isLowerbound = true;
        else
            normals[i].isLowerbound = false;
        if (CheckCollisionRecs(normals[i].GetCollision(), mapbounds[3].GetCollision()))
            normals[i].isLeftbound = true;
        else
            normals[i].isLeftbound = false;
        if (CheckCollisionRecs(normals[i].GetCollision(), mapbounds[4].GetCollision()))
            normals[i].isRightbound = true;
        else
            normals[i].isRightbound = false;

        if (CheckCollisionRecs(strongs[i].GetCollision(), mapbounds[1].GetCollision()))
            strongs[i].isUpperbound = true;
        else
            strongs[i].isUpperbound = false;
        if (CheckCollisionRecs(strongs[i].GetCollision(), mapbounds[2].GetCollision()))
            strongs[i].isLowerbound = true;
        else
            strongs[i].isLowerbound = false;
        if (CheckCollisionRecs(strongs[i].GetCollision(), mapbounds[3].GetCollision()))
            strongs[i].isLeftbound = true;
        else
            strongs[i].isLeftbound = false;
        if (CheckCollisionRecs(strongs[i].GetCollision(), mapbounds[4].GetCollision()))
            strongs[i].isRightbound = true;
        else
            strongs[i].isRightbound = false;

        if (CheckCollisionRecs(runners[i].GetCollision(), mapbounds[1].GetCollision()))
            runners[i].isUpperbound = true;
        else
            runners[i].isUpperbound = false;
        if (CheckCollisionRecs(runners[i].GetCollision(), mapbounds[2].GetCollision()))
            runners[i].isLowerbound = true;
        else
            runners[i].isLowerbound = false;
        if (CheckCollisionRecs(runners[i].GetCollision(), mapbounds[3].GetCollision()))
            runners[i].isLeftbound = true;
        else
            runners[i].isLeftbound = false;
        if (CheckCollisionRecs(runners[i].GetCollision(), mapbounds[4].GetCollision()))
            runners[i].isRightbound = true;
        else
            runners[i].isRightbound = false;

        if (CheckCollisionRecs(supers[i].GetCollision(), mapbounds[1].GetCollision()))
            supers[i].isUpperbound = true;
        else
            supers[i].isUpperbound = false;
        if (CheckCollisionRecs(supers[i].GetCollision(), mapbounds[2].GetCollision()))
            supers[i].isLowerbound = true;
        else
            supers[i].isLowerbound = false;
        if (CheckCollisionRecs(supers[i].GetCollision(), mapbounds[3].GetCollision()))
            supers[i].isLeftbound = true;
        else
            supers[i].isLeftbound = false;
        if (CheckCollisionRecs(supers[i].GetCollision(), mapbounds[4].GetCollision()))
            supers[i].isRightbound = true;
        else
            supers[i].isRightbound = false;
    }
}
void Game::UpdateCoin(float deltaTime)
{
    for (int i = 0; i < COINMAX; i++)
    {
        coins[i].Update(player.GetWorldPosition(), deltaTime);
        if (CheckCollisionRecs(coins[i].GetCollision(), player.GetCollision()) && coins[i].GetActive())
        {
            int rand = GetRandomValue(1, 3);
            if (rand == 1)
                PlaySound(Coin1);
            else if (rand == 2)
                PlaySound(Coin2);
            else
                PlaySound(Coin3);
            coinCollected++;
            coins[i].SetActive(false);
            score += 10;
        }
    }
}
void Game::UI(float deltaTime)
{
    if (isSpawn)
    {
        DrawText("Enemies have spawned", windowWidth / 2 - 200, 100, 40, WHITE);
        isSpawnRunningTime += deltaTime;
        if (isSpawnRunningTime >= isSpawnUpdateTime)
        {
            isSpawnRunningTime = 0;
            isSpawn = false;
        }
    }
    coinRunningTime += deltaTime;
    if (coinRunningTime >= coinUpdateTime)
    {
        coinAnimationFrame++;
        coinRunningTime = 0;
        if (coinAnimationFrame > 12)
            coinAnimationFrame = 0;
    }

    coinWidth = coinUI.width / 12;
    Rectangle coinSource{coinAnimationFrame * coinWidth, 0, coinWidth, coinUI.height};
    float scale{4.f};
    Rectangle coinDest{windowWidth - 300.f, 50.f, coinWidth * scale, coinUI.height * scale};
    DrawTexturePro(coinUI, coinSource, coinDest, {0, 0}, 0, WHITE);
    std ::string knightHealth = "Health: ";
    knightHealth.append(std ::to_string(player.GetHealth()), 0, 4);
    DrawText(knightHealth.c_str(), 55.f, 100.f, 40, WHITE);
    std ::string coinCount = "";
    coinCount.append(std ::to_string(coinCollected), 0, 3);
    coinCount.append("/", 0, 1);
    coinCount.append(std::to_string(coinCounter), 0, 3);
    DrawText(coinCount.c_str(), windowWidth - 120.f, windowHeight - 80, 30, WHITE);
    std ::string showScore = "";
    showScore.append(std::to_string(score), 0, 10);
    DrawText(showScore.c_str(), windowWidth - 140.f, 100.f, 40, WHITE);
    // std ::string showWave = "Wave: ";
    // showWave.append(std::to_string(waveCounter), 0, 4);
    // DrawText(showWave.c_str(), windowWidth - 200.f, 100.f, 40, WHITE);
}
void Game::ResetFirstFrame()
{
    spawnUpdateTime = 40;
    player.SetAlive(true);
    waveCounter = 0;
    score = 0;
    ResetNextWave();
}
void Game::ResetNextWave()
{
    isSpawn = false;
    isSpawnRunningTime = 0;
    player.ResetHealth();
    spawnRunningTime = spawnUpdateTime;
    if (spawnUpdateTime >= 6)
        spawnUpdateTime -= (waveCounter)*5;
    else if (spawnUpdateTime >= 1)
        spawnUpdateTime--;
    player.ResetNextWave();
    ResetCoin();
    ResetEnemy();
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
void Game::RandomTribe()
{
    // 0 is little 1 is normal 2 is runners 3 is strongs 4 is super
    int random[5];

    for (int i = 0; i < 5; i++)
    {
        random[i] = GetRandomValue(1, 3);
    }

    if (random[0] == 1)
    {
        littles[enemySize - 1].SetTexture(littleOrc);
        littles[enemySize - 1].SetMovementSpeed(9.f);
    }
    else if (random[0] == 2)
    {
        littles[enemySize - 1].SetTexture(littleDemon);
        littles[enemySize - 1].SetMovementSpeed(10.f);
    }
    else
    {
        littles[enemySize - 1].SetTexture(littleUndead);
        littles[enemySize - 1].SetMovementSpeed(10.f);
    }

    if (random[1] == 1)
    {
        normals[enemySize - 1].SetTexture(normalOrc);
        normals[enemySize - 1].SetMovementSpeed(6.5f);
        normals[enemySize - 1].SetAnimationMaxFrame(8);
    }
    else if (random[1] == 2)
    {
        normals[enemySize - 1].SetTexture(normalDemon);
        normals[enemySize - 1].SetMovementSpeed(7.f);
        normals[enemySize - 1].SetAnimationMaxFrame(8);
    }
    else
    {
        normals[enemySize - 1].SetTexture(normalUndead);
        normals[enemySize - 1].SetMovementSpeed(6.f);
        normals[enemySize - 1].SetAnimationMaxFrame(4);
    }

    if (random[2] == 1)
    {
        runners[enemySize - 1].SetTexture(runnerOrc);
        runners[enemySize - 1].SetMovementSpeed(11.5f);
        runners[enemySize - 1].SetAnimationMaxFrame(8);
    }
    else if (random[2] == 2)
    {
        runners[enemySize - 1].SetTexture(runnerDemon);
        runners[enemySize - 1].SetMovementSpeed(12.f);
        runners[enemySize - 1].SetAnimationMaxFrame(4);
    }
    else
    {
        runners[enemySize - 1].SetTexture(runnerUndead);
        runners[enemySize - 1].SetMovementSpeed(11.f);
        runners[enemySize - 1].SetAnimationMaxFrame(8);
    }

    if (random[3] == 1)
    {
        strongs[enemySize - 1].SetTexture(strongOrc);
        strongs[enemySize - 1].SetMovementSpeed(5.5f);
    }
    else if (random[3] == 2)
    {
        strongs[enemySize - 1].SetTexture(strongDemon);
        strongs[enemySize - 1].SetMovementSpeed(6.f);
    }
    else
    {
        strongs[enemySize - 1].SetTexture(strongUndead);
        strongs[enemySize - 1].SetMovementSpeed(5.f);
    }

    if (random[4] == 1)
    {
        supers[enemySize - 1].SetTexture(superOrc);
        supers[enemySize - 1].SetMovementSpeed(4.5f);
    }
    else if (random[4] == 2)
    {
        supers[enemySize - 1].SetTexture(superDemon);
        supers[enemySize - 1].SetMovementSpeed(6.f);
    }
    else
    {
        supers[enemySize - 1].SetTexture(superUndead);
        supers[enemySize - 1].SetMovementSpeed(5.f);
    }

    littles[enemySize - 1].SetTextureWidth();
    littles[enemySize - 1].SetTextureHeight();
    normals[enemySize - 1].SetTextureWidth();
    normals[enemySize - 1].SetTextureHeight();
    runners[enemySize - 1].SetTextureWidth();
    runners[enemySize - 1].SetTextureHeight();
    strongs[enemySize - 1].SetTextureWidth();
    strongs[enemySize - 1].SetTextureHeight();
    supers[enemySize - 1].SetTextureWidth();
    supers[enemySize - 1].SetTextureHeight();
}
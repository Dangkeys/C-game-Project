#include "Enemy.h"

class Runner : public Enemy
{
public:
    Runner()
    {
        int randomTribe{GetRandomValue(1, 3)};
        if (randomTribe == 1)
        {
            texture = LoadTexture("characters/runnerOrc.png");
            movementSpeed = 11.f; // 9
        }
        else if (randomTribe == 2)
        {
            texture = LoadTexture("characters/runnerDemon.png");
            movementSpeed = 12.f; // 10
            animationMaxFrame = 4;
        }
        else
        {
            texture = LoadTexture("characters/runnerUndead.png");
            movementSpeed = 10.f; // 8
        }
        textureWidth = texture.width / animationMaxFrame;
        textureHeight = texture.height;
        dealDamageAmount = 2.f;
        maxHealth = 3.f;
        health = maxHealth;
        scale = 6.f;
        detectRadius = 200;
        knockbackAmount = movementSpeed * 5;
        hurtUpdateTime = 0.1f;
        patrolUpdateTime = GetRandomValue(1, 2);

        // this code is only for testing
        alive = true;
        worldPosition = {(float)GetRandomValue(9 * tileSize, 40 * tileSize), (float)GetRandomValue(5 * tileSize, 20 * tileSize)};
    }

private:
};

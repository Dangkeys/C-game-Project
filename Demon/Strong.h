#include "Enemy.h"

class Strong : public Enemy
{
public:
    Strong()
    {
        int randomTribe{GetRandomValue(1, 3)};
        if (randomTribe == 1)
        {
            texture = LoadTexture("characters/strongOrc.png");
            movementSpeed = 4.5f; // 9
        }
        else if (randomTribe == 2)
        {
            texture = LoadTexture("characters/strongDemon.png");
            movementSpeed = 5.5f; // 10
        }
        else
        {
            texture = LoadTexture("characters/strongUndead.png");
            movementSpeed = 4.f; // 8
        }
        textureWidth = texture.width / animationMaxFrame;
        textureHeight = texture.height;
        dealDamageAmount = 1.f;
        maxHealth = 5.f;
        health = maxHealth;
        scale = 8.f;
        detectRadius = 0;
        knockbackAmount = 5;
        hurtUpdateTime = 0.1f;
        patrolUpdateTime = GetRandomValue(2, 6);

        // this code is only for testing
        alive = true;
        worldPosition = {(float)GetRandomValue(9 * tileSize, 40 * tileSize), (float)GetRandomValue(5 * tileSize, 20 * tileSize)};
    }

private:
};

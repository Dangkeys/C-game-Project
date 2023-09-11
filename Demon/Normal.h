#include "Enemy.h"

class Normal : public Enemy
{
public:
    Normal()
    {
        // int randomTribe{GetRandomValue(1, 3)};
        // if (randomTribe == 1)
        // {
        //     texture = LoadTexture("characters/normalOrc.png");
        //     movementSpeed = 6.5f; // 9
        // }
        // else if (randomTribe == 2)
        // {
        //     texture = LoadTexture("characters/normalDemon.png");
        //     movementSpeed = 7.f; // 10
        // }
        // else
        // {
        //     texture = LoadTexture("characters/normalUndead.png");
        //     movementSpeed = 6.f; // 8
        //     animationMaxFrame = 4;
        // }
        // textureWidth = texture.width / animationMaxFrame;
        // textureHeight = texture.height;
        dealDamageAmount = 1.f;
        maxHealth = 3.f;
        health = maxHealth;
        scale = 7.f;
        detectRadius = 400;
        knockbackAmount = movementSpeed * 4;
        hurtUpdateTime = 0.3f;
        patrolUpdateTime = GetRandomValue(2, 4);

        // this code is only for testing
    }

private:
};

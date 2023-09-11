#include "Enemy.h"

class Super : public Enemy
{
public:
    Super()
    {
        // int randomTribe{GetRandomValue(1, 3)};
        // if (randomTribe == 1)
        // {
        //     texture = LoadTexture("characters/superOrc.png");
        //     movementSpeed = 5.f; // 9
        // }
        // else if (randomTribe == 2)
        // {
        //     texture = LoadTexture("characters/superDemon.png");
        //     movementSpeed = 6.f; // 10
        // }
        // else
        // {
        //     texture = LoadTexture("characters/superUndead.png");
        //     movementSpeed = 4.f; // 8
        // }
        // textureWidth = texture.width / animationMaxFrame;
        // textureHeight = texture.height;
        dealDamageAmount = 3.f;
        maxHealth = 6.f;
        health = maxHealth;
        scale = 10.f;
        detectRadius = 400;
        knockbackAmount = 0;
        hurtUpdateTime = 0.1f;
        patrolUpdateTime = GetRandomValue(2, 6);

        // this code is only for testing
        
    }

private:
};

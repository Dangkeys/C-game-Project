#ifndef LITTLE_H
#define LITTLE_H
#include "raylib.h"
#include "Enemy.h"

class Little : public Enemy
{
public:
    Little()
    {
        // int randomTribe{GetRandomValue(1, 3)};
        // if (randomTribe == 1)
        // {
        //     texture = LoadTexture("characters/littleOrc.png");
        //     movementSpeed = 9.f; // 9
        // }
        // else if (randomTribe == 2)
        // {
        //     texture = LoadTexture("characters/littleDemon.png");
        //     movementSpeed = 10.f; // 10
        // }
        // else
        // {
        //     texture = LoadTexture("characters/littleUndead.png");
        //     movementSpeed = 8.f; // 8
        // }
        // textureWidth = texture.width / animationMaxFrame;
        // textureHeight = texture.height;
        dealDamageAmount = 0.5f;
        maxHealth = 2.f;
        health = maxHealth;
        scale = 5.f;
        detectRadius = 0;
        knockbackAmount = movementSpeed * 6;
        hurtUpdateTime = 0.3f;
        patrolUpdateTime = GetRandomValue(1, 2);

        // this code is only for testing

    }

private:
};
#endif

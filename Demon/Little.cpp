#include "Little.h"
Little::Little()
{
    int randomTribe{GetRandomValue(1, 3)};
    if (randomTribe == 1)
    {
        texture = LoadTexture("characters/littleOrc.png");
        movementSpeed = 9.f;
    }
    else if (randomTribe == 2)
    {
        texture = LoadTexture("characters/littleDemon.png");
        movementSpeed = 10.f;
    }
    else
    {
        texture = LoadTexture("characters/littleUndead.png");
        movementSpeed = 8.f;
    }
    dealDamageAmount = 0.5f;
    health = 2.f;
    scale = 5.f;
    detectRadius = 0;
    knockbackAmount = 20.f;
    patrolUpdateTime = GetRandomValue(2, 8);

    //this code is only for testing
    alive = true;
    worldPosition = {(float)GetRandomValue(9 * tileSize, 40 * tileSize),(float)GetRandomValue(5 * tileSize, 20 * tileSize)};
}
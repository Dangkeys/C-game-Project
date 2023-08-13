#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{

    if (!getAlive())
        return;
    if (isKnockBack)
    {
        // update animation frame
        knockBackTime += deltaTime;
        runningTime += deltaTime;
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame)
                frame = 0;
        }
        if (knockBackTime >= knockBackUpdateTime)
        {
            isKnockBack = false;
            knockBackTime = 0.f;
        }
        worldPositionLastFrame = worldPosition;
        faceRight = faceRightLastFrame;
        velocity = Vector2Scale(Vector2Subtract(target->getScreenPosition(), getScreenPosition()), -1.f);
        if (isKnockFirstFrame)
        {
            knockback = velocity;
            isKnockFirstFrame = false;
        }
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(knockback), target->getKnockBack()));
        if (isMapboundX)
            // knockback.x *= -1;
            undoMovementX();
        if (isMapboundY)
            // knockback.y *= -1;
            undoMovementY();
        isMapboundX = false;
        isMapboundY = false;
        velocity = {};
        Rectangle source{frame * width, 0.f, faceRight * width, height};
        Rectangle dest{getScreenPosition().x, getScreenPosition().y, scale * width, scale * height};
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, PINK);
        setActive();
    }
    else
    {
        faceRightLastFrame = faceRight;
        velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());
        if (Vector2Length(velocity) < radius)
            velocity = {};
        BaseCharacter ::tick(deltaTime);
        if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
        {
            target->takeDamage(damagePerSec * deltaTime);
        }
        setActive();
    }
}
Vector2 Enemy ::getScreenPosition()
{
    return Vector2Subtract(worldPosition, target->getWorldPosition());
}

void Enemy ::setActive()
{
    if (health <= 0)
        setAlive(false);
}
void Enemy ::KnockBack()
{
    isKnockBack = true;
    isKnockFirstFrame = true;
}

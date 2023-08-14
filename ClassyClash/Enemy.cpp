#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    width = texture.width / maxFrame;
    height = texture.height;
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
        if (target == NULL)
            velocity = {};
        else
            velocity = Vector2Scale(Vector2Subtract(target->getScreenPosition(), getScreenPosition()), -1.f);
        if (isKnockFirstFrame)
        {
            knockback = velocity;
            isKnockFirstFrame = false;
        }
        if (target != NULL)
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
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, {255, 255, 255, 100});
        setActive();
    }
    else
    {
        faceRightLastFrame = faceRight;
        if (target == NULL)
        {
            timeCounter += deltaTime;
            if (isLeftbound)
            {
                timeCounter = 0;
                patrolSpeed = -50;
                isLeftbound = false;
            }
            else if (isRightbound)
            {
                timeCounter = 0;
                patrolSpeed = 50;
                isRightbound = false;
            }
            if (timeCounter >= UpdateTimeCounter)
            {
                timeCounter = 0;
                patrolSpeed *= -1;
            }
            else
            {
                velocity = {-patrolSpeed, 0.f};
            }
        }
        else
        {
            if (isBottombound)
            {
                velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());
                velocity = Vector2Add(velocity, {0, height * scale * -1});
            }
            else
            {
                velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());
            }
        }
        if (Vector2Length(velocity) < radius)
            velocity = {};
        BaseCharacter ::tick(deltaTime);
        if (target != NULL)
        {
            if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
            {
                target->takeDamage(damagePerSec * deltaTime);
            }
        }

        setActive();
    }
}
Vector2 Enemy ::getScreenPosition()
{
    if (target == NULL)
    {
        return screenPosition;
    }
    else
    {
        return Vector2Subtract(worldPosition, target->getWorldPosition());
    }
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
void Enemy::drawDetectRadius()
{
    DrawCircle(getScreenPosition().x + width * scale / 2, getScreenPosition().y + height * scale / 2, detectRadius, {230, 41, 50, 100});
}
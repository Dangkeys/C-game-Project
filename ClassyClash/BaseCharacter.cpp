#include "BaseCharacter.h"
#include "raymath.h"

void BaseCharacter::undoMovementX()
{
    worldPosition.x = worldPositionLastFrame.x;
}

void BaseCharacter::undoMovementY()
{
    worldPosition.y = worldPositionLastFrame.y;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPositionLastFrame = worldPosition;
    
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }
    if (Vector2Length(velocity) != 0.0)
    {
        // window position = windowposition + direction
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(velocity), speed));
        if (velocity.x != 0)
        {
            velocity.x < 0.f ? faceRight = -1.f : faceRight = 1.f;
        }
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // at the end of each frame set velocity to 0
    velocity = {};

    // draw the character
    Rectangle source{frame * width, 0.f, faceRight * width, height};
    Rectangle dest{getScreenPosition().x, getScreenPosition().y, scale * width, scale * height};
    if (isInvisible)
    {
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, {255, 255, 255, 100});
    }
    else if (isHurt)
    {
        hurtRunningTime += deltaTime;
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, {255, 255, 255, 100});
        if (hurtRunningTime >= hurtUpdateTIme)
        {
            hurtRunningTime = 0;
            isHurt = false;
        }
    }
    else
    {
        DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
    }
}
void BaseCharacter ::KnockBack(float setterKnockBackAmount)
{
    isKnockBack = true;
    isKnockFirstFrame = true;
    knockBackAmount = setterKnockBackAmount;
}
void BaseCharacter ::setActive()
{
    if (health <= 0)
        setAlive(false);
}

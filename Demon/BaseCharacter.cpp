#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    SetSoundVolume(death, 0.4);
    SetSoundVolume(hurt, 0.4);
}

void BaseCharacter::Update(float deltaTime)
{
    if (health <= 0)
    {
        PlaySound(death);
        alive = false;
        return;
    }
    worldPositionLastFrame = worldPosition;
    UpdateAnimation(deltaTime);
    UpdateIsHurt(deltaTime);
    worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(moveDirectionTo), movementSpeed));
    moveDirectionTo = {0, 0};
    DrawCharacter();

    // show hitbox
    // DrawRectangleLines(GetCollision().x, GetCollision().y,GetCollision().width, GetCollision().height, RED);
}

void BaseCharacter::UpdateAnimation(float deltaTime)
{
    animationRunningTime += deltaTime;
    if (animationRunningTime >= animationUpdateTime)
    {
        animationFrame++;
        animationRunningTime = 0;
        if (animationFrame >= animationMaxFrame)
            animationFrame = 0;
    }
}
void BaseCharacter::DrawCharacter()
{
    Rectangle source{animationFrame * textureWidth, 0.f, faceRight * textureWidth, textureHeight};
    Rectangle dest{drawPosition.x, drawPosition.y, GetDrawWidth(), GetDrawHeight()};
    if (isHurt)
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, FADE);
    else
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
}
void BaseCharacter::UpdateIsHurt(float deltaTime)
{
    if (!isHurt)
        return;
    hurtRunningTime += deltaTime;
    if (hurtRunningTime >= hurtUpdateTime)
    {
        hurtRunningTime = 0;
        isHurt = false;
    }
}
void BaseCharacter::Hurt(float takeDamageAmount)
{
    if (isHurt)
        return;
    PlaySound(hurt);
    health -= takeDamageAmount;
    isHurt = true;
    isHurtFirstFrame = true;
}
void BaseCharacter::ResetToFirstFrame()
{
    isHurtFirstFrame = false;
    isHurt = false;
    hurtRunningTime = 0;
    moveDirectionTo = {0, 0};
}
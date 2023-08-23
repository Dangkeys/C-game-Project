#include "BaseCharacter.h"
#include "raymath.h"

void BaseCharacter::Update(float deltaTime)
{
    worldPositionLastFrame = worldPosition;
    UpdateAnimation(deltaTime);
    UpdateIsHurt(deltaTime);
    if(health <= 0) return;
    worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(moveDirectionTo), movementSpeed));
    if (moveDirectionTo.x != 0)
        moveDirectionTo.x < 0.f ? faceRight = -1 : faceRight = 1;
    moveDirectionTo = {0, 0};
    DrawCharacter();
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
        DrawTexturePro(texture, source, dest, Vector2{0,0}, 0.f, FADE);
    else
        DrawTexturePro(texture, source, dest, Vector2{0,0}, 0.f, WHITE);

}
void BaseCharacter::UpdateIsHurt(float deltaTime)
{
    if(!isHurt) return;
    hurtRunningTime += deltaTime;
    if (hurtRunningTime >= hurtUpdateTime)
    {
        hurtRunningTime = 0;
        isHurt = false;
    }
}
void BaseCharacter::Hurt(float takeDamageAmount)
{
    if(!isHurt)
    {
        health -= takeDamageAmount;
        isHurt = true;
    }
}
void BaseCharacter::ResetToFirstFrame()
{
    isHurt = false;
    hurtRunningTime = 0;
    moveDirectionTo = {0,0};
}
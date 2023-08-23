#include "Pickups.h"

void Pickups::Update(Vector2 knightPosition, float deltaTime)
{
    if (!active)
        return;
    drawPosition = Vector2Subtract(worldPosition, knightPosition);
    animationRunningTime += deltaTime;
    if (animationRunningTime >= animationUpdateTime)
    {
        animationFrame++;
        animationRunningTime = 0;
        if (animationFrame > animationMaxFrame)
            animationFrame = 0;
    }
    Rectangle source = {animationFrame * width, 0.f, width, height};
    Rectangle dest = {drawPosition.x, drawPosition.y, GetDrawWidth(), GetDrawHeight()};
    DrawTexturePro(texture, source, dest, {0.f, 0.f}, 0.f, WHITE);
}
#include "PickUps.h"
void PickUps::Render(Vector2 knightPosition, float deltaTime)
{
    if(!active) return;
    width = texture.width / maxFrame;
    height = texture.height;
    setScreenPosition(knightPosition);

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0;
        if (frame > maxFrame) 
            frame = 0;
    }

    Rectangle source = {frame * width, 0.f, width, height};
    Rectangle dest = {getScreenPosition().x, getScreenPosition().y, width * scale, height * scale};
    DrawTexturePro(texture, source, dest, {0.f, 0.f}, 0.f, WHITE);
}
Rectangle PickUps::getCollisionRec()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale 
    };
}


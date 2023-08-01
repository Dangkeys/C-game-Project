#include "Character.h"
#include "raymath.h"
Character ::Character(int windowWidth, int windowHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;
    characterPosition = {
    static_cast<float>(windowWidth) / 2.f - scale * (0.5f * (float)texture.width / 6.f),
    static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * (float)texture.height)};
}
void Character ::tick(float deltaTime)
{
    windowPositionLastFrame = windowPosition;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    // change map position by direction if moving left map moving right the player is stat still
    if (Vector2Length(direction) != 0.0)
    {
        // window position = windowposition + direction
        windowPosition = Vector2Add(windowPosition, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? faceRight = -1.f : faceRight = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0;
        frame++;
        if (frame > maxFrame)
            frame = 0;
    }
    Rectangle source{frame * width, 0.f, faceRight * width, height};
    Rectangle dest{characterPosition.x, characterPosition.y, scale * width, scale * (float)height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
void Character:: undoMovement()
{
    windowPosition = windowPositionLastFrame;
}
Rectangle Character:: getCollisionRec()
{
    return Rectangle {
        characterPosition.x,
        characterPosition.y,
        width * scale,
        height * scale
    };
}
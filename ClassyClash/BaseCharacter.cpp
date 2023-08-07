#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter()
{
    
}


void BaseCharacter::undoMovementX()
{
    worldPosition.x = worldPositionLastFrame.x;
}

void BaseCharacter::undoMovementY()
{
    worldPosition.y = worldPositionLastFrame.y;
}

void BaseCharacter::addCollision(Rectangle rec1, Rectangle rec2)
{
    if(rec1.x + rec1.width >= rec2.x || rec1.x <= rec2.x + rec2.width) {undoMovementX();}
    else if (rec1.y + rec1.height >= rec2.y) {undoMovementY();}
}


Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{

        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale
    };
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
        velocity.x < 0.f ? faceRight = -1.f : faceRight = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    //at the end of each frame set velocity to 0
    velocity = {};

    // draw the character
    Rectangle source{frame * width, 0.f, faceRight * width, height};
    Rectangle dest{getScreenPosition().x, getScreenPosition().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
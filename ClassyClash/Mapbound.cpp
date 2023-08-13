#include "Mapbound.h"
Mapbound::Mapbound(Vector2 position, float recWidth, float recHeight):
worldPosition(position),
width(recWidth),
height(recHeight)
{

}

void Mapbound::Render(Vector2 knightPosition)
{
    setScreenPosition(knightPosition);
    //DrawRectangleLines(screenPosition.x + offset.x, screenPosition.y + offset.y, width, height, RED);
}

Rectangle Mapbound::getCollisionRec()
{
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        width,
        height
    };
}
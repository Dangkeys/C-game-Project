#include "Prop.h"
#include "raymath.h"
Prop :: Prop(Vector2 position, Texture2D tex):
    worldPosition(position),
    texture(tex)
{

}
void Prop :: Render(Vector2 knightPosition)
{
    Vector2 propPosition = Vector2Subtract(worldPosition, knightPosition);
    DrawTextureEx(texture, propPosition, 0.f, scale, WHITE);
}
Rectangle Prop :: getCollisionRec(Vector2 knightPosition)
{
    Vector2 propPosition = Vector2Subtract(worldPosition, knightPosition);
    return Rectangle{
        propPosition.x,
        propPosition.y,
        texture.width * scale,
        texture.height * scale
    };
}
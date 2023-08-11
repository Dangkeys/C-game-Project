#include "Prop.h"
#include "raymath.h"
Prop ::Prop(Vector2 position, Texture2D tex) : worldPosition(position),
                                               texture(tex)
{
}
void Prop ::Render(Vector2 knightPosition)
{
    setScreenPosition(knightPosition);
    DrawTextureEx(texture, screenPosition, 0.f, scale, WHITE);
}
Rectangle Prop ::getCollisionRec()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        texture.width * scale,
        texture.height * scale};
}
bool Prop::checkCollisionRecX(Rectangle characterRec)
{
    if ((characterRec.x + characterRec.width == getCollisionRec().x &&
        characterRec.x == getCollisionRec().x + getCollisionRec().width) &&
        characterRec.y + characterRec.height >= getCollisionRec().y &&
        characterRec.y <= getCollisionRec().y + getCollisionRec().height / 2)
    {
        return true;
    }
    return false;
}


bool Prop ::checkCollisionRecY(Rectangle characterRec)
{
    if (characterRec.x + characterRec.width > getCollisionRec().x &&
        characterRec.x < getCollisionRec().x + getCollisionRec().width &&
        characterRec.y + characterRec.height >= getCollisionRec().y &&
        characterRec.y <= getCollisionRec().y + getCollisionRec().height / 2)
    {
        return true;
    }
    return false;
}
#include "raylib.h"
#include "raymath.h"
class Mapbound
{
public:
    Mapbound(Vector2 position, float recWidth, float recHeight);
    Rectangle GetCollision() { return Rectangle{drawPosition.x, drawPosition.y, width, height}; }
    Vector2 GetDrawPosition() { return drawPosition; }
    void Update(Vector2 knightPosition){drawPosition = Vector2Subtract(worldPosition, knightPosition);}

private:
    Vector2 worldPosition{};
    Vector2 drawPosition{};
    float width{};
    float height{};
    Vector2 offset{55.f, 30.f};
    int sizeOfRectangle{20};
};

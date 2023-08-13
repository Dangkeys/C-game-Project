#include "raylib.h"
#include "raymath.h"
class Mapbound
{
public:
    Mapbound(Vector2 position, float recWidth, float recHeight);
    Rectangle getCollisionRec();
    Vector2 getScreenPosition() { return screenPosition; }
    void setScreenPosition(Vector2 knightPosition) { screenPosition = Vector2Subtract(worldPosition, knightPosition); }
    void Render(Vector2 knightPosition);
private:
    Vector2 worldPosition{};
    Vector2 screenPosition{};
    float width{};
    float height{};
    Vector2 offset{55.f,30.f};
    int sizeOfRectangle{20};
};

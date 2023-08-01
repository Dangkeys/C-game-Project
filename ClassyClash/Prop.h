#include"raylib.h"

class Prop
{
public:
    Prop(Vector2 position, Texture2D tex);
    void Render(Vector2 knightPosition);
    Rectangle getCollisionRec(Vector2 knightPosition);
private:
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale{4.0f};
};
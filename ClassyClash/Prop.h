#include"raylib.h"
#include"raymath.h"
class Prop
{
public:
    Prop(Vector2 position, Texture2D tex);
    void Render(Vector2 knightPosition);
    Rectangle getCollisionRec();
    bool checkCollisionRecX(Rectangle characterRec);
    bool checkCollisionRecY(Rectangle characterRec);
    void setScreenPosition(Vector2 knightPosition) {screenPosition = Vector2Subtract(worldPosition, knightPosition);}
    Vector2 getScreenPosition() {return screenPosition;}
private:
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale{4.0f};
    Vector2 screenPosition{};
};
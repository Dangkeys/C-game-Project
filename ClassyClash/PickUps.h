#ifndef PICKUPS_H
#define PICKUPS_H
#include "raylib.h"
#include "raymath.h"

class PickUps
{
public:
    void Render(Vector2 knightPosition, float deltaTime);
    bool getActive(){return active;}
    void setActive(bool isActive){active = isActive;}
    void setScale(float scaler) {scale = scaler;}
    void setMaxFrame(int setMaxFrame) {maxFrame = setMaxFrame;}
    void setWorldPosition(Vector2 position) {worldPosition = position;}
    void setTexture(Texture2D tex) {texture = tex;}
    void setFrame(int setFrame) {frame = setFrame;}
    int getMaxFrame() {return maxFrame;}
    Rectangle getCollisionRec();
    Vector2 getScreenPosition() {return screenPosition;}
    void setScreenPosition(Vector2 knightPosition) {screenPosition = Vector2Subtract(worldPosition, knightPosition);}
protected:
    Texture2D texture{};
    float runningTime{};
    int frame{};
    int maxFrame{};
    float updateTime{1.0f / 12.0f};
    float scale{2.0f};
    float width{};
    float height{};
    Vector2 worldPosition{};
    Vector2 screenPosition{};
private:
    bool active{true};
};
#endif
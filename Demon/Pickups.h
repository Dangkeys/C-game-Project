#ifndef PICKUPS_H
#define PICKUPS_H
#include "raylib.h"
#include "raymath.h"

class Pickups
{
public:
    void SetWorldPosition(Vector2 setter) {worldPosition = setter;}
    int GetMaxFrame() {return animationMaxFrame;}
    void SetFrame(int setter) {animationFrame = setter;}
    Rectangle GetCollision(){return Rectangle{drawPosition.x, drawPosition.y, GetDrawWidth(), GetDrawHeight()};}
    void Update(Vector2 knightPosition, float deltaTime);
    void SetActive(bool setter) {active = setter;}
    bool GetActive() {return active;}
protected:
    Texture2D texture{};
    float animationRunningTime{};
    int animationFrame{};
    int animationMaxFrame{12};
    float animationUpdateTime{1.f/12.f};
    float scale{2.f};
    float width{texture.width / animationMaxFrame};
    float height{texture.height};
    float GetDrawWidth(){return width * scale;}
    float GetDrawHeight() {return height * scale;}
    Vector2 worldPosition{};
    Vector2 drawPosition{};
    bool active{false};
private:
};




#endif
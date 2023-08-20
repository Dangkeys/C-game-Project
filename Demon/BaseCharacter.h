#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    virtual void Update(float deltaTime);
    Rectangle GetCollision() { return Rectangle{drawPosition.x, drawPosition.y, GetDrawWidth(), GetDrawHeight()}; }
    Vector2 GetWorldPosition() {return worldPosition;}

protected:

    //texture references
    Texture2D texture{};
    float textureWidth{};
    float textureHeight{};
    float scale{1};

    float movementSpeed{1};
    float health{1};
    float takeDamageAmount{1};
    bool alive{false};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    Vector2 moveDirectionTo{};
    // animation
    int faceRight{1};
    int animationFrame{};
    int animationMaxFrame{8};
    float animationRunningTime{};
    float animationUpdateTime{1/12.f};
    float hurtRunningTime{};
    float hurtUpdateTime{0.2f};
    // draw character
    void DrawCharacter();
    Vector2 drawPosition{};
    float GetDrawWidth() { return textureWidth * scale; }
    float GetDrawHeight() { return textureHeight * scale; }
    Color FADE{255, 255, 255, 100};
    //method
    void Hurt(float takeDamageAmount);

private:
    void UpdateIsHurt(float deltaTime); 
    void UpdateAnimation(float deltaTime);
    bool isHurt{false};
};
#endif

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    void Hurt(float takeDamageAmount);
    virtual void Update(float deltaTime);
    float GetHealth() { return health; }
    bool GetAlive() { return alive; }
    Vector2 GetDrawPosition() {return drawPosition;}
    Rectangle GetCollision() { return Rectangle{drawPosition.x, drawPosition.y, GetDrawWidth(), GetDrawHeight()}; }
    Vector2 GetWorldPosition() { return worldPosition; }
    virtual void ResetToFirstFrame();
    bool isHurt{false};
    float dealDamageAmount{1};

protected:
    void UpdateIsHurt(float deltaTime);
    void UpdateAnimation(float deltaTime);
    // texture references
    Texture2D texture{};
    float textureWidth{};
    float textureHeight{};
    float scale{1};

    float movementSpeed{8};
    float health{1};
    bool alive{false};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    Vector2 moveDirectionTo{};
    // animation
    int faceRightLastFrame{};
    int faceRight{1};
    int animationFrame{};
    int animationMaxFrame{8};
    float animationRunningTime{};
    float animationUpdateTime{1 / 12.f};
    float hurtRunningTime{};
    float hurtUpdateTime{0.2f};
    // draw character
    void DrawCharacter();
    Vector2 drawPosition{};
    float GetDrawWidth() { return textureWidth * scale; }
    void UndoMovementX() { worldPosition.x = worldPositionLastFrame.x; }
    void UndoMovementY() { worldPosition.y = worldPositionLastFrame.y; }
    float GetDrawHeight() { return textureHeight * scale; }
    Color FADE{255, 255, 255, 100};
    // method
    bool isHurtFirstFrame{false};
private:
};
#endif

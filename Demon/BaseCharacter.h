#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    BaseCharacter();
    void SetTextureWidth() { textureWidth = texture.width / animationMaxFrame; }
    void SetTextureHeight() { textureHeight = texture.height; }
    void SetTexture(Texture2D sprite) { texture = sprite; }
    void ResetHealth() { health = maxHealth; }
    void Hurt(float takeDamageAmount);
    virtual void Update(float deltaTime);
    float GetHealth() { return health; }
    bool GetAlive() { return alive; }
    Vector2 GetDrawPosition() { return drawPosition; }
    Rectangle GetCollision() { return Rectangle{drawPosition.x + 4 * scale, drawPosition.y, GetDrawWidth() - 8 * scale, GetDrawHeight()}; }
    Vector2 GetWorldPosition() { return worldPosition; }
    virtual void ResetToFirstFrame();
    bool isHurt{false};
    float dealDamageAmount{1};
    float GetDrawWidth() { return textureWidth * scale; }
    float hurtUpdateTime{0.2f};
    float GetDrawHeight() { return textureHeight * scale; }
    void SetAlive(bool setter) { alive = setter; }

protected:
    void UpdateIsHurt(float deltaTime);
    void UpdateAnimation(float deltaTime);
    // texture references
    Texture2D texture{};
    float textureWidth{};
    float textureHeight{};
    float scale{1};

    float movementSpeed{8};
    float maxHealth{1};
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
    float hurtRunningTime{0};
    // draw character
    void DrawCharacter();
    Vector2 drawPosition{};
    void UndoMovementX() { worldPosition.x = worldPositionLastFrame.x; }
    void UndoMovementY() { worldPosition.y = worldPositionLastFrame.y; }

    Color FADE{255, 255, 255, 100};
    // method
    bool isHurtFirstFrame{false};

private:
    Sound death{LoadSound("SFX/DeathSFX.wav")};
    Sound hurt{LoadSound("SFX/Hurt.wav")};
};
#endif

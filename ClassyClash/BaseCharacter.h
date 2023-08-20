#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    bool isHurt{false};
    Vector2 getWorldPosition() { return worldPosition; }
    void undoMovementX();
    void undoMovementY();
    Rectangle getCollisionRec();
    void setSpeed(float characterSpeed) { speed = characterSpeed; }
    virtual void tick(float deltaTime);
    void setMaxFrame(int setMax) { maxFrame = setMax; }
    virtual Vector2 getScreenPosition() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
    float getFaceRight() { return faceRight; }
    float getScale() { return scale; }
    void setUpdateTime(float time) { updateTime = time; }
    void setFrame(int x, int y) { frame = (x + y) % maxFrame; }
    void KnockBack(float setterKnockBackAmount);
    void setKnockBackUpdateTime(float setter) {knockBackUpdateTime = setter;}
    float getKnockBackAmount() { return knockBackAmount; }
    void setKnockBackAmount(float setter) {knockBackAmount = setter;}
    void setHealth(float setter) {health = setter;}
    void setActive();

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    // 1 : facing right, -1 : facing left
    float faceRight{1.f};
    // animation variables
    float health{3};
    float runningTime{};
    int frame{};
    int maxFrame{8};
    float updateTime{1.f / 12.f};
    float speed{8.f};
    float width{};
    float height{};
    float scale{7.f};
    Vector2 velocity{};
    bool isInvisible{false};

    float hurtRunningTime{};
    float hurtUpdateTIme{0.2f};

    //use only in enemy
    bool isKnockBack{};
    float knockBackTime{};
    float knockBackUpdateTime{1.f / 4.f};
    bool isKnockFirstFrame{false};
    float faceRightLastFrame{};
    float dealKnockBack{10.f};
    Vector2 knockbackVelocity{};
    float knockBackAmount{20.f};

private:
    bool alive{false};
};

#endif +

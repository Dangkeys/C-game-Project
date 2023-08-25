#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "raymath.h"
#define NULL 00L
/*
    enemy need health pass
    knockback pass
        fix in KnockBack function there should be no deltatime
        knockback is negative the velocity for .5 seconds (0.5 is offset)
    create the spawn enemy function
    delete constructor and then set varialbe and method it in spawn() by random value


*/
class Enemy : public BaseCharacter
{
public:
    Enemy();
    virtual void tick(float deltaTime) override;
    void setTarget(Character *character) { target = character; }
    void hurt() { health--; };

    void setScale(float setScale) { scale = setScale; }
    void setScreenPosition(Vector2 knightPosition) { screenPosition = Vector2Subtract(worldPosition, knightPosition); }
    virtual Vector2 getScreenPosition() override;
    void collideWithMapboundX() { isMapboundX = true; }
    void collideWithMapboundY() { isMapboundY = true; }
    void collideWithLeftbound() { isLeftbound = true; }
    // void noCollideWithLeftbound() { isLeftbound = false; }
    // void noCollideWithRightbond() { isRightbound = false; }
    void collideWithRightbound() { isRightbound = true; }
    void collideWithBottombound() { isBottombound = true; }
    void noCollideWithBottombound() { isBottombound = false; }
    void drawDetectRadius();
    void setZeroTimeCounter() { timeCounter = 0.f; }
    void setDetectRadius(float setter) { detectRadius = setter; }
    bool isInDetectRadius(Rectangle knightRec);
    void setUpdateTimeCounter(float setter) { UpdateTimeCounter = setter; }
    void addHurtTimeCounter(float deltaTime) { hurtTimeCounter += deltaTime; }
    float getHurtTimeCounter() { return hurtTimeCounter; }
    float getHurtUpdateTimeCounter() { return hurtUpdateTime; }
    float getDamage() { return damage; }
    void setDamage(float setter) { damage = setter; }
    float getDealKnockBack() { return dealKnockBack; }
    Character *getTarget() { return target; }
    void setZeroHurtTimeCounter() { hurtTimeCounter = 0; }
    void setDetectRaduis(float setter) { detectRadius = setter; }
    void setWorldPosition(Vector2 setter) {worldPosition = setter;}
    void setTexture(Texture2D setter) {texture = setter;}
    // void setDamageHealthSpeed(float dam)
protected:
    float getDetectCenterX() { return screenPosition.x + width * scale / 2; }
    float getDectectCenterY() { return screenPosition.y + height * scale / 2; }
    Character *target{NULL};
    float damage{1};
    float radius{10.f * scale};

    bool isMapboundX{false};
    bool isMapboundY{false};
    bool isLeftbound{false};
    bool isRightbound{false};
    bool isBottombound{false};

    Vector2 screenPosition{worldPosition};
    float detectRadius{300.f};
    float timeCounter{};
    float UpdateTimeCounter{};
    float patrolSpeed{10000000.f};

    int patrolFirstFrame{};
    float hurtTimeCounter{};
    float hurtUpdateTime{0.2f};

private:
    float tileSize{32 * 4};
};
#endif
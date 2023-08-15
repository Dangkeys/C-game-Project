#ifndef ENEMY_H
#define ENEMY_h
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
    Enemy(Vector2 position, Texture2D idle, Texture2D run);
    virtual void tick(float deltaTime) override;
    void setTarget(Character *character) { target = character; }
    Character *getTarget() { return target; }
    void hurt() { health--; };
    void setActive();
    void KnockBack();
    void setScale(float setScale) { scale = setScale; }
    void setScreenPosition(Vector2 knightPosition) { screenPosition = Vector2Subtract(worldPosition, knightPosition); }
    virtual Vector2 getScreenPosition() override;
    void collideWithMapboundX() { isMapboundX = true; }
    void collideWithMapboundY() { isMapboundY = true; }
    void collideWithLeftbound() { isLeftbound = true; }
    void collideWithRightbound() { isRightbound = true; }
    void collideWithBottombound() { isBottombound = true; }
    void noCollideWithBottombound() { isBottombound = false; }
    void drawDetectRadius();
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getDetectRadius() { return detectRadius; }
    void setZeroTimeCounter() { timeCounter = 0.f; }
    void reversePatrolSpeed() { patrolSpeed *= -1;}

protected:
    Character *target{NULL};
    float damagePerSec{10.f};
    float radius{50.f};
    int health{3};
    float faceRightLastFrame{};
    bool isKnockBack{};
    float knockBackTime{};
    float knockBackUpdateTime{1.f / 4.f};
    bool isKnockFirstFrame{false};
    bool isMapboundX{false};
    bool isMapboundY{false};
    bool isLeftbound{false};
    bool isRightbound{false};
    bool isBottombound{false};
    Vector2 knockbackVelocity{};
    Vector2 screenPosition{worldPosition};
    float detectRadius{300.f};
    float timeCounter{};
    float UpdateTimeCounter{};
    float patrolSpeed{50.f};
    float knockBack{15.f};
    int patrolFirstFrame{};
private:
};
#endif
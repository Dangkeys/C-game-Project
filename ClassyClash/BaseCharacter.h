#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPosition() {return worldPosition;}
    void undoMovement();
    void undoMovementX();
    void undoMovementY();
    void addCollision(Rectangle rec1, Rectangle rec2);
    Rectangle getCollisionRec();
    void setSpeed(float characterSpeed) {speed = characterSpeed;}
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPosition() = 0;
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    // 1 : facing right, -1 : facing left
    float faceRight{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif




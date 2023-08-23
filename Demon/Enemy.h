#ifndef ENEMY_H
#define ENEMY_h
#include "raylib.h"
#include "BaseCharacter.h"
#include "Player.h"
#include "raymath.h"
#define NULL 00L

class Enemy: public BaseCharacter
{
public:
    virtual void Update(float deltaTime) override;
    void SetTarget(Player *setter) {target = setter;}
protected:
    float detectRadius{250};
    float patrolRunningTime{};
    float patrolUpdateTime{1};
    Player *target{NULL};
private:
};
#endif
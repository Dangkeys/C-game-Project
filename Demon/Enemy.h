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
    Enemy();
    bool isUpperbound{false};
    bool isLowerbound{false};
    bool isLeftbound{false};
    bool isRightbound{false};
    virtual void Update(float deltaTime) override;
    void SetTarget(Player *setter) {target = setter;}
protected:
    float knockbackAmount{1.f};
    float detectRadius{250};
    float patrolUpdateTime{1};
    int patrolFirstFrame{};
    Vector2 patrolMoveDirectionTo{movementSpeed,0};
    Vector2 knockBackMoveDirectionTo{};
private:
    Player *target{NULL};
    void UpdateKnockBack();
    void MapboundXMechanic();
    void MapboundYMechanic();
    void LeftboundPatrolMechanic();
    void RightboundPatrolMechanic();
    void ChaseMechanic();
    void AttackPlayer(float deltaTime);
    void PatrolMechanic(float deltaTime);
    float patrolRunningTime{};
};
#endif
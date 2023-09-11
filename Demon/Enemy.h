#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Player.h"
#include "raymath.h"
#define NULL 00L

class Enemy: public BaseCharacter
{
public:
    void SetMovementSpeed(float speed) {movementSpeed = speed;}
    void SetAnimationMaxFrame(int max) {animationMaxFrame = max;}


    bool alertFirstFrame{true};
    void EnemyReset();
    float GetDetectRadius(){return detectRadius;}
    Vector2 playerPosition{};
    float GetHurtRunningTime(){return hurtRunningTime;}
    Enemy();
    Vector2 GetCenterDetectRadius(){return Vector2{drawPosition.x + GetDrawWidth()/2, drawPosition.y + GetDrawHeight()/2};}
    bool isUpperbound{false};
    bool isLowerbound{false};
    bool isLeftbound{false};
    bool isRightbound{false};
    virtual void Update(float deltaTime) override;
    void SetTarget(Player *setter) {target = setter;}
    void SetWorldPosition(Vector2 position) {worldPosition = position;}
protected:
    float knockbackAmount{10.f};
    float detectRadius{250};
    float patrolUpdateTime{};
    int patrolFirstFrame{};
    float patrolAmount{movementSpeed - 2};
    Vector2 knockBackMoveDirectionTo{};
    int tileSize{32 * 4};
private:
    Player *target{NULL};
    float dealDamageRunningTime{};
    float dealDamageUpdateTime{0.25};

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
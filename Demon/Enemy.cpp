#include "Enemy.h"
Enemy::Enemy()
{
    animationFrame = GetRandomValue(0,8);
    animationMaxFrame = 8;
    patrolFirstFrame = GetRandomValue(0, 1);
    if (patrolFirstFrame == 0)
        Vector2Scale(patrolMoveDirectionTo, -1);
}
void Enemy::Update(float deltaTime)
{
    if (!GetAlive())
        return;
    ChaseMechanic();
    UpdateKnockBack();
    PatrolMechanic(deltaTime);
    BaseCharacter::Update(deltaTime);
    AttackPlayer(deltaTime);
}
void Enemy::UpdateKnockBack()
{
    if (!isHurt || !GetAlive())
        return;
    faceRight = faceRightLastFrame;
    if (target != NULL)
        moveDirectionTo = Vector2Scale(Vector2Subtract(target->GetDrawPosition(), drawPosition), -1);
    if (isHurtFirstFrame)
    {
        isHurtFirstFrame = false;
        knockBackMoveDirectionTo = moveDirectionTo;
    }
    moveDirectionTo = Vector2Scale(knockBackMoveDirectionTo, knockbackAmount);
    MapboundXMechanic();
    MapboundYMechanic();
}
void Enemy::AttackPlayer(float deltaTime)
{
    if (target == NULL)
        return;
    if (CheckCollisionRecs(target->GetCollision(), GetCollision()) && !(target->isHurt))
    {
        hurtRunningTime += deltaTime;
        if (hurtRunningTime >= hurtUpdateTime)
        {
            target->Hurt(dealDamageAmount);
            target->isHurt = true;
            hurtRunningTime = 0;
        }
        else
            hurtRunningTime = 0;
    }
}
void Enemy::MapboundXMechanic()
{
    if (!(isLeftbound || isRightbound))
        return;
    UndoMovementX();
}
void Enemy::MapboundYMechanic()
{
    if (!(isLowerbound || isUpperbound))
        return;
    UndoMovementY();
}
void Enemy::PatrolMechanic(float deltaTime)
{
    if (target != NULL)
        return;
    patrolRunningTime += deltaTime;
    LeftboundPatrolMechanic();
    RightboundPatrolMechanic();
    if (patrolRunningTime >= patrolUpdateTime)
    {
        patrolRunningTime = 0;
        Vector2Scale(patrolMoveDirectionTo, -1.f);
    }
    moveDirectionTo = patrolMoveDirectionTo;
}
void Enemy::LeftboundPatrolMechanic()
{
    if (!isLeftbound)
        return;
    patrolRunningTime = 0;
    patrolMoveDirectionTo.x = movementSpeed;
    isLeftbound = false;
}
void Enemy::RightboundPatrolMechanic()
{
    if (!isRightbound)
        return;
    patrolRunningTime = 0;
    patrolMoveDirectionTo.x = -movementSpeed;
    isRightbound = false;
}
void Enemy::ChaseMechanic()
{
    if (target == NULL)
        return;
    moveDirectionTo = Vector2Subtract(target->GetDrawPosition(), drawPosition);
    if (isLowerbound)
        moveDirectionTo = Vector2Add(moveDirectionTo, {0, GetDrawHeight()});
    if (Vector2Length(moveDirectionTo) < 2 * scale)
        moveDirectionTo = {};
}
#include "Enemy.h"
Enemy::Enemy()
{
    animationFrame = GetRandomValue(0, 8);
    animationMaxFrame = 8;
    patrolFirstFrame = GetRandomValue(0, 1);
    if (patrolFirstFrame == 0)
        patrolAmount *= -1;
}
void Enemy::Update(float deltaTime)
{
    if (!GetAlive())
        return;
    // draw detect radius
    //  DrawCircle(GetCenterDetectRadius().x,GetCenterDetectRadius().y, detectRadius, {255,0,0,50});

    faceRightLastFrame = faceRight;
    if (target != NULL)
    {
        drawPosition = Vector2Subtract(worldPosition, target->GetWorldPosition());
        ChaseMechanic();
        if (moveDirectionTo.x != 0)
            moveDirectionTo.x < 0.f ? faceRight = -1 : faceRight = 1;
        AttackPlayer(deltaTime);
        UpdateKnockBack();
        BaseCharacter::Update(deltaTime);
    }
    else
    {
        drawPosition = Vector2Subtract(worldPosition, playerPosition);
        PatrolMechanic(deltaTime);
        if (moveDirectionTo.x != 0)
            moveDirectionTo.x < 0.f ? faceRight = -1 : faceRight = 1;
        knockBackMoveDirectionTo = moveDirectionTo;
        UpdateKnockBack();
        BaseCharacter::Update(deltaTime);
    }
}
void Enemy::AttackPlayer(float deltaTime)
{
    if (target == NULL)
        return;

    if (CheckCollisionRecs(target->GetCollision(), GetCollision()) && !(target->isHurt))
    {
        dealDamageRunningTime += deltaTime;
        if (dealDamageRunningTime >= dealDamageUpdateTime)
        {
            target->Hurt(dealDamageAmount);
            target->isHurt = true;
        }
    }
    else
        dealDamageRunningTime = 0;
}
void Enemy::UpdateKnockBack()
{
    if (!isHurt || !GetAlive())
        return;
    faceRight = faceRightLastFrame;
    if (target != NULL)
        moveDirectionTo = Vector2Scale(Vector2Subtract(target->GetDrawPosition(), drawPosition), -1);
    else
        moveDirectionTo = Vector2Scale(Vector2Subtract(playerPosition, drawPosition), -1);
    if (isHurtFirstFrame)
    {
        isHurtFirstFrame = false;
        knockBackMoveDirectionTo = moveDirectionTo;
    }
    moveDirectionTo = Vector2Scale(knockBackMoveDirectionTo, knockbackAmount);
    MapboundXMechanic();
    MapboundYMechanic();
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
        patrolAmount *= -1; // Reverse patrol direction
    }

    moveDirectionTo = {patrolAmount, 0.f};
}
void Enemy::LeftboundPatrolMechanic()
{
    if (!isLeftbound)
        return;
    patrolRunningTime = 0;
    patrolAmount = movementSpeed;
    isLeftbound = false;
}
void Enemy::RightboundPatrolMechanic()
{
    if (!isRightbound)
        return;
    patrolRunningTime = 0;
    patrolAmount = -movementSpeed;
    isRightbound = false;
}
void Enemy::ChaseMechanic()
{
    if (target == NULL)
        return;
    moveDirectionTo = Vector2Subtract(target->GetDrawPosition(), drawPosition);
    if (isLowerbound)
        moveDirectionTo = Vector2Add(moveDirectionTo, {0, -GetDrawHeight()});
    else if (isUpperbound)
        moveDirectionTo = Vector2Add(moveDirectionTo, {0, GetDrawHeight()});
    if (Vector2Length(moveDirectionTo) < 5 * scale)
        moveDirectionTo = {};
}

void Enemy::EnemyReset()
{
    target = NULL;
    isHurtFirstFrame = false;
    isHurt = false;
    hurtRunningTime = 0;
    ResetHealth();
    SetAlive(false);
}
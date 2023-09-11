#include "Player.h"
#include "raymath.h"
Player::Player(int winWidth, int winHeight, Texture2D sprite)
{
    windowWidth = winWidth;
    windowHeight = winHeight;
    animationMaxFrame = 6.f;
    texture = sprite;
    textureWidth = texture.width / animationMaxFrame;
    textureHeight = texture.height;
    scale = 7.f;
    maxHealth = 10.f;
    health = maxHealth;
    alive = true;
    hurtUpdateTime = 0.3f;
    dealDamageAmount = 1.f;
    movementSpeed = 8.f;
    drawPosition = {static_cast<float>(windowWidth) / 2 - GetDrawWidth() / 2, static_cast<float>(windowHeight) / 2 - GetDrawHeight() / 2};
    swordScale = scale - 1.f;
    swordOffset = {-5 * swordScale, 0};
    swordCollision = {
        drawPosition.x + GetDrawWidth() * faceRight + swordOffset.x,
        drawPosition.y + GetDrawSwordHeight() * (0.8f),
        GetDrawSwordWidth(),
        GetDrawSwordHeight()};
    swordColor = WHITE;
    SetSoundVolume(footstep,0.1);
}
Rectangle Player::GetDrawSwordCollision()
{
    if (faceRight > 0.f)
    {
        return Rectangle{swordCollision.x - GetDrawWidth()/4, swordCollision.y - GetDrawSwordHeight() - swordOffsetY,swordCollision.width + GetDrawWidth()/4,swordCollision.height + GetDrawHeight()/4 + swordOffsetY * 2};
    }
    return Rectangle{swordCollision.x - GetDrawSwordWidth(), swordCollision.y - GetDrawSwordHeight() - swordOffsetY,swordCollision.width + GetDrawWidth()/4,swordCollision.height + GetDrawHeight()/4 + swordOffsetY * 2};
}

void Player::Update(float deltaTime)
{
    UpdateMovement();
    if (moveDirectionTo.x != 0)
        moveDirectionTo.x < 0.f ? faceRight = -1 : faceRight = 1;
    ChangeAnimationState();
    SetAttackAnimation(deltaTime);
    BaseCharacter::Update(deltaTime);
    DrawSword();
    
    if (isHurt)
        DrawRectangle(0, 0, 5000, 5000, {255, 0, 0, 50});
}
void Player::UpdateMovement()
{
    if (IsKeyDown(KEY_A) && isValidA)
        moveDirectionTo.x -= 1.0;
    if (IsKeyDown(KEY_D) && isValidD)
        moveDirectionTo.x += 1.0;
    if (IsKeyDown(KEY_W) && isValidW)
        moveDirectionTo.y -= 1.0;
    if (IsKeyDown(KEY_S) && isValidS)
        moveDirectionTo.y += 1.0;
}
void Player::ChangeAnimationState()
{
    if (Vector2Length(moveDirectionTo) != 0.0)
    {
        if(!IsSoundPlaying(footstep))
            PlaySound(footstep);
        texture = run;
    }
    else{
        StopSound(footstep);
        texture = idle;
    }
}

void Player::DrawSword()
{

    if (faceRight > 0.f)
    {
        swordCollision.x = drawPosition.x + GetDrawWidth() + swordOffset.x;
        swordOrigin = {0.f, GetDrawSwordHeight()};
    }

    else
    {
        swordCollision.x = drawPosition.x - swordOffset.x;
        swordOrigin = {GetDrawSwordWidth(), GetDrawSwordHeight()};
    }

    Rectangle source{0.f, 0.f, sword.width * faceRight, sword.height};
    Rectangle dest{swordCollision};
    DrawTexturePro(sword, source, dest, swordOrigin, swordRotation, swordColor);
    //draw player sword collision
    //DrawRectangleLines(GetDrawSwordCollision().x, GetDrawSwordCollision().y, GetDrawSwordCollision().width, GetDrawSwordCollision().height, RED);
}
void Player::SetAttackAnimation(float deltaTime)
{
    if (canAttack)
        return;
    canAttackRunningTime += deltaTime;
    swordColor = FADE;
    faceRight > 0.f ? swordRotation = 3 *swordScale : swordRotation = -3 * swordScale;
    if (canAttackRunningTime >= canAttackUpdateTime)
    {
        canAttack = true;
        canAttackRunningTime = 0;
        swordColor = WHITE;
        swordRotation = 0.f;
    }
}

void Player::ResetToFirstFrame()
{
    ResetHealth();
    alive = true;
    ResetNextWave();
}
void Player::ResetNextWave()
{
    isHurt = false;
    hurtRunningTime = 0;
    scale = 7.f;
    movementSpeed = 8.f;
    worldPosition = {};
    worldPositionLastFrame = {};
    moveDirectionTo = {};
    drawPosition = {static_cast<float>(windowWidth) / 2 - GetDrawWidth() / 2, static_cast<float>(windowHeight) / 2 - GetDrawHeight() / 2};
}

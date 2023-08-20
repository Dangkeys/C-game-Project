#include "Player.h"
#include "raymath.h"
Player::Player(int winWidth, int winHeight, Texture2D sprite)
{
    windowWidth = winWidth;
    windowHeight = winHeight;
    animationMaxFrame = 6;
    texture = sprite;
    textureWidth = texture.width / animationMaxFrame;
    textureHeight = texture.height;
    scale = 7.f;
    health = 10.f;
    alive = true;
    movementSpeed = 8.f;
    swordScale = scale - 1.f;
    swordOffset = {-5 * swordScale, 0};
    drawPosition = {static_cast<float>(windowWidth) / 2 - GetDrawWidth() / 2, static_cast<float>(windowHeight)/ 2 - GetDrawHeight() / 2};
    swordCollision = {
            drawPosition.x + GetDrawWidth() * faceRight + swordOffset.x,
            drawPosition.y + GetDrawSwordHeight()*(0.8f),
            GetDrawSwordWidth(),
            GetDrawSwordHeight()};
}
void Player::Update(float deltaTime)
{
    UpdateMovement();
    ChangeAnimationState();
    BaseCharacter::Update(deltaTime);
    DrawSword();
}
void Player::UpdateMovement()
{
    if (IsKeyDown(KEY_A))
        moveDirectionTo.x -= 1.0;
    if (IsKeyDown(KEY_D))
        moveDirectionTo.x += 1.0;
    if (IsKeyDown(KEY_W))
        moveDirectionTo.y -= 1.0;
    if (IsKeyDown(KEY_S))
        moveDirectionTo.y += 1.0;
}
void Player::ChangeAnimationState()
{
    if (Vector2Length(moveDirectionTo) != 0.0)
        texture = run;
    else
        texture = idle;
}

void Player::DrawSword()
{
    Vector2 origin{};
    float rotatation{};
    if (faceRight > 0.f)
    {
        swordCollision.x = drawPosition.x + GetDrawWidth()+ swordOffset.x;
        origin = {0.f, GetDrawSwordHeight()};
    }
        
    else
    {
        swordCollision.x = drawPosition.x - swordOffset.x;
        origin = {GetDrawSwordWidth(), GetDrawSwordHeight()};
    }
    
    
    Rectangle source{0.f, 0.f,  sword.width* faceRight, sword.height};
    Rectangle dest{swordCollision};
    DrawTexturePro(sword, source, dest, origin, rotatation, WHITE);
}
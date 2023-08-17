#include "Character.h"
#include "raymath.h"
Character ::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                     windowHeight(winHeight)
{
    health = 10.f;
}
Vector2 Character ::getScreenPosition()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}
void Character ::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}
void Character ::tick(float deltaTime)
{

    width = texture.width / maxFrame;
    height = texture.height;
    swordScale = scale - 1;
    if (!getAlive())
        return;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S) && validMoveMentS)
    {
        velocity.y += 1.0;
    }

    BaseCharacter ::tick(deltaTime);
    Vector2 origin{};
    float rotation{};
    if (!canAttack)
    {
        flipRunningTime += deltaTime;
        attackRunningTime += deltaTime;    
        if (attackRunningTime >= attackDuration)
        {
            attackRunningTime = 0;
            canAttack = true;
            rotation += 30;
            rotation = 0;
        }
        if (faceRight > 0.f)
        {
            if (flipRunningTime >= attackDuration/24)
            {
                flipRunningTime = 0;
                rotation += 30;
            }
        } else
        {
            if (flipRunningTime >= attackDuration/24)
            {
                flipRunningTime = 0;
                rotation -= 30;
            }
        }
    }
    if (faceRight > 0.f)
    {
        origin = {0.f, swordScale * weapon.height};
        swordOffset = swordOffsetRight;
        weaponCollisionRec = {
            getScreenPosition().x + swordOffset.x,
            getScreenPosition().y + swordOffset.y - weapon.height * swordScale,
            weapon.width * swordScale,
            weapon.height * swordScale};
        // rotation = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canAttack ? 35.f : 0.f;
    }
    else
    {
        origin = {swordScale * weapon.width, swordScale * weapon.height};
        swordOffset = swordOffsetLeft;
        weaponCollisionRec = {
            getScreenPosition().x + swordOffset.x - weapon.width * swordScale,
            getScreenPosition().y + swordOffset.y - weapon.height * swordScale,
            weapon.width * swordScale,
            weapon.height * swordScale};
        // rotation = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && canAttack ? -35.f : 0.f;
    }
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * faceRight, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPosition().x + swordOffset.x, getScreenPosition().y + swordOffset.y, swordScale * weapon.width, swordScale * weapon.height};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}
#include "Character.h"
#include "raymath.h"
Character ::Character(int winWidth, int winHeight):
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;
}
Vector2 Character :: getScreenPosition()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}
void Character :: takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
} 
void Character ::tick(float deltaTime)
{
    if (!getAlive()) return;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
    BaseCharacter :: tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotataion{};
    if (faceRight > 0.f)
    {
        origin = {0.f, scale * weapon.height};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPosition().x + offset.x,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale 
        };
        rotataion = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    } else {
        origin = {scale * weapon.width, scale * weapon.height};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPosition().x + offset.x - weapon.width * scale,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotataion = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }
    Rectangle source {0.f, 0.f, static_cast<float>(weapon.width) * faceRight, static_cast<float>(weapon.height)};
    Rectangle dest {getScreenPosition().x + offset.x, getScreenPosition().y + offset.y, scale * weapon.width, scale * weapon.height};
    DrawTexturePro(weapon, source, dest, origin, rotataion, WHITE);
    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}
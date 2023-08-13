#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int windowWidth, int windowHeight);
    void tick(float deltaTime);
    virtual Vector2 getScreenPosition() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() const {return health;}
    void takeDamage(float damage);
    float getKnockBack() {return knockBack;}
    void undoMovementS() {validMoveMentS = false;}
    void doMovements() {validMoveMentS = true;}
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    int coinCounter{};
    float health{100.f};
    float knockBack{15.f};
    float swordScale{6.f};
    bool validMoveMentS{true};
};
#endif
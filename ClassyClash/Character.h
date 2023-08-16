#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

#define NULL 00L
class Character : public BaseCharacter
{
public:
    Character(int windowWidth, int windowHeight);
    void tick(float deltaTime);
    virtual Vector2 getScreenPosition() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() const {return health;}
    void takeDamage(float damage);
    void undoMovementS() {validMoveMentS = false;}
    void doMovements() {validMoveMentS = true;}
    void setScale(float setScale) {scale = setScale;}
    void setInvisible(bool invisible){isInvisible = invisible;}
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    int coinCounter{};
    float health{10};

    float swordScale{6.f};
    bool validMoveMentS{true};
    Vector2 swordOffset{};
    Vector2 swordOffsetRight{79.f, 83.f};;
    Vector2 swordOffsetLeft{30.f, 83.f};

};
#endif
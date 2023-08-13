#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
/*
    enemy need health pass
    knockback pass
        fix in KnockBack function there should be no deltatime
        knockback is negative the velocity for .5 seconds (0.5 is offset)
    create the spawn enemy function
    delete constructor and then set varialbe and method it in spawn() by random value


*/
class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 position, Texture2D idle, Texture2D run);
    virtual void tick(float deltaTime) override;
    void setTarget(Character *character) { target = character; }
    void hurt() { health--; };
    void setActive();
    void KnockBack();
    void setScale(float setScale) {scale = setScale;}
    virtual Vector2 getScreenPosition() override;
    void collideWithMapboundX(){isMapboundX = true;}
    void collideWithMapboundY(){isMapboundY = true;}

private:
    Character *target;
    float damagePerSec{10.f};
    float radius{50.f};
    int health{3};
    float faceRightLastFrame{};
    bool isKnockBack{};
    float knockBackTime{};
    float knockBackUpdateTime{1.f / 4.f};
    bool isKnockFirstFrame{false};
    bool isMapboundX{false};
    bool isMapboundY{false};
    Vector2 knockback{};
};
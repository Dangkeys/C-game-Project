#include "BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    virtual void Update(float deltatime) override;
    Player(int winWidth, int winHeight, Texture2D sprite);


private:
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    void UpdateMovement();
    void ChangeAnimationState();
    int windowWidth{};
    int windowHeight{};
    // attack mechanic and animation
    bool canAttack{true};
    float canAttackRunningTime{};
    float canAttackUpdateTime{0.3f};
    //weapon references
    Texture2D sword{LoadTexture("characters/weapon_sword.png")};
    float swordScale{scale - 1.f};
    Vector2 swordOffset{-3 * swordScale, 0};
    Rectangle swordCollision{};
    float GetDrawSwordWidth(){return static_cast<float>(sword.width) * swordScale;}
    float GetDrawSwordHeight(){return static_cast<float>(sword.height) * swordScale;}
    void DrawSword();
    
};

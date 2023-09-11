#ifndef PLAYER_H
#define PLAYER_H
#include "BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    virtual void Update(float deltatime) override;
    Player(int winWidth, int winHeight, Texture2D sprite);
    bool isValidS{true};
    bool isValidW{true};
    bool isValidA{true};
    bool isValidD{true};
    virtual void ResetToFirstFrame() override;
    void ResetNextWave();
    bool canAttack{true};
    Rectangle GetDrawSwordCollision();
private:
    Sound footstep{LoadSound("SFX/Footstep.wav")};
    //score mechanic

    float playerScale{7.f};
    float playerSpeed{8.f};
    float playerMaxFrame{6};
    float MaxHealth{10.f};


    //movement ref
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    void UpdateMovement();
    void ChangeAnimationState();
    int windowWidth{};
    int windowHeight{};
    // attack mechanic and animation
    float canAttackRunningTime{0};
    float canAttackUpdateTime{0.4f};
    // weapon references
    int swordOffsetY{20};
    Texture2D sword{LoadTexture("characters/weapon_sword.png")};
    float swordScale{scale - 1.f};
    Vector2 swordOffset{-3 * swordScale, 0};
    Rectangle swordCollision{};
    float GetDrawSwordWidth() { return static_cast<float>(sword.width) * swordScale; }
    float GetDrawSwordHeight() { return static_cast<float>(sword.height) * swordScale; }
    void DrawSword();
    void SetAttackAnimation(float deltaTime);
    Vector2 swordOrigin{};
    float swordRotation{};
    Color swordColor{WHITE};
};
#endif
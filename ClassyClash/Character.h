#include "raylib.h"
class Character
{
public:
    Character(int windowWidth, int windowHeight);
    Vector2 getwindowPosition() { return windowPosition; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 characterPosition{};
    Vector2 windowPosition{};
    Vector2 windowPositionLastFrame{};
    float faceright{-1.0f};
    float runningTime{};
    float updateTime{1.f / 12.f};
    float faceRight{1.0f};
    int frame{};
    float speed{4.0f};
    float scale{4.0f};
    int maxFrame{6};
    float width{};
    float height{};
};
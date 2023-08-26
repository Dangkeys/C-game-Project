#include "Player.h"
#include "Map.h"
#include "Mapbound.h"
#include "Coin.h"
#include "Little.h"
#include "Super.h"
#include "Normal.h"
#include "Runner.h"
#include "Strong.h"
#include <string>
#define COINMAX 189
#define ENEMYMAX 100
class Game
{
public:
    int GetScore(){return score;}
    Game(int winWidth, int winHeight);
    void Update(float deltaTime);
    int getWindowWidth() { return windowWidth; }
    int getWindowHeight() { return windowHeight; }
    void ResetFirstFrame();
    void ResetNextWave();
    bool isGameEnd{false};
    int waveCounter{};
    bool isNextWave{false};
    bool endFirstFrame{false};


private:

    Sound spawn{LoadSound("SFX/SpawnSFX.wav")};
    Sound alert{LoadSound("SFX/Alert.wav")};
    Sound slash1{LoadSound("SFX/slash1SFX.wav")};
    Sound slash2{LoadSound("SFX/slash2SFX.wav")};
    Sound slash3{LoadSound("SFX/slash3SFX.wav")};
    Sound Coin1{LoadSound("SFX/Coin.wav")};
    Sound Coin2{LoadSound("SFX/Coin2.wav")};
    Sound Coin3{LoadSound("SFX/Coin3.wav")};
    float coinWidth{};
    int coinAnimationFrame{};
    float coinRunningTime{};
    float coinUpdateTime{1.f/9.f};
    int enemySize{};
    float hurtRunningTime{0};
    void ResetEnemy();
    void Spawn(float deltaTime);
    void UpdateEnemy(float deltaTime);
    void AttackEnemy();
    void UI(float deltaTime);
    void ResetCoin();
    void UpdateCoin(float deltaTime);
    void PlayerMapboundMechanic();
    void SetCoin(int x, int y);
    void SetPositionCoin();
    float spawnUpdateTime{30};
    float spawnRunningTime{spawnUpdateTime};
    const int sizeOfCoinWidth{31};
    const int sizeOfCoinHeight{15};
    int windowWidth{1900};
    int windowHeight{1000};
    const float tileSize{4 * 32};
    float landWidth{33.f * tileSize + 20.f};
    float landHeight{18.f * tileSize};
    float sizeOfRectangle{50.f};
    int mapboundSize{5};
    int score{};
    int coinCollected{};
    int coinCounter{};
    Vector2 coinOffset{-50.f, 82.f};
    Little littles[ENEMYMAX];
    Runner runners[ENEMYMAX];
    Normal normals[ENEMYMAX];
    Strong strongs[ENEMYMAX];
    Super supers[ENEMYMAX];

    // 0 is playerbound 1 is upper 2 is lower 3 is left 4 is right
    Mapbound mapbounds[5]{
        {Vector2{7.f * tileSize + 55, 4.f * tileSize - 70}, landWidth, sizeOfRectangle},
        {Vector2{7.f * tileSize + 55, 4.f * tileSize - 20}, landWidth, sizeOfRectangle},
        {Vector2{7.f * tileSize + 55, 21.f * tileSize + 70}, landWidth, sizeOfRectangle},
        {Vector2{7.f * tileSize + 20, 4.f * tileSize}, sizeOfRectangle, landHeight},
        {Vector2{40.f * tileSize + 70.f, 4.f * tileSize}, sizeOfRectangle, landHeight}};
    Coin coins[COINMAX];
    Player player{getWindowWidth(), getWindowHeight(), LoadTexture("characters/knight_idle_spritesheet.png")};
    Map map{LoadTexture("nature_tileset/realMap.png"), {0, 0}};
};
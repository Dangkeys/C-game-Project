#include "Player.h"
#include "Map.h"
#include "Mapbound.h"
#include "Coin.h"
#include "Little.h"
#include <string>
#define COINMAX 189
class Game
{
public:
    Game(int winWidth, int winHeight);
    void Update(float deltaTime);
    int getWindowWidth() { return windowWidth; }
    int getWindowHeight() { return windowHeight; }
    void ResetFirstFrame();
    void ResetNextWave();
    bool isGameEnd{false};
    int waveCounter{};
    bool isNextWave{false};

private:
    void AttackEnemy();
    void UI();
    void ResetCoin();
    void UpdateCoin(float deltaTime);
    void PlayerMapboundMechanic();
    void SetCoin(int x, int y);
    void SetPositionCoin();
    const int sizeOfCoinWidth{31};
    const int sizeOfCoinHeight{15};
    int windowWidth{1900};
    int windowHeight{1000};
    const int tileSize{4 * 32};
    float landWidth{33 * tileSize + 20.f};
    float landHeight{18 * tileSize};
    float sizeOfRectangle{20.f};
    int mapboundSize{5};

    int score{};
    int coinCollected{};
    int coinCounter{};
    Little little;
    Vector2 coinOffset{-50.f, 82.f};

    // player bound
    // 0 is playerbound 1 is upper 2 is lower 3 is left 4 is right
    Mapbound mapbounds[5]{
        {{7 * tileSize + 55, 4 * tileSize - 30}, landWidth, sizeOfRectangle},
        {{7 * tileSize + 55, 4 * tileSize + 40}, landWidth, sizeOfRectangle},
        {{7 * tileSize + 55, 21 * tileSize + 70}, landWidth, sizeOfRectangle},
        {{7 * tileSize + 30, 4 * tileSize}, sizeOfRectangle, landHeight},
        {{40 * tileSize + 70.f, 4 * tileSize}, sizeOfRectangle, landHeight}};

    Coin coins[COINMAX];
    Player player{getWindowWidth(), getWindowHeight(), LoadTexture("characters/knight_idle_spritesheet.png")};
    Map map{LoadTexture("nature_tileset/realMap.png"), {0, 0}};
};
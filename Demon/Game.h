#include "Player.h"
#include "Map.h"
class Game
{
public:
    Game(int winWidth, int winHeight);
    void Update(float deltaTime);
    int getWindowWidth() { return windowWidth; }
    int getWindowHeight() { return windowHeight; }

private:
    int windowWidth{1900};
    int windowHeight{1000};
    Player player{getWindowWidth(), getWindowHeight(), LoadTexture("characters/knight_idle_spritesheet.png")};
    Map map{LoadTexture("nature_tileset/realMap.png"),{0,0}};
};
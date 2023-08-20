#include "Game.h"

Game::Game(int winWidth, int winHeight):
windowWidth(winWidth),
windowHeight(winHeight)
{

}
void Game::Update(float deltaTime)
{
    map.Update(player.GetWorldPosition());
    player.Update(deltaTime);
}
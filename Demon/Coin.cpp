#include "Coin.h"

Coin::Coin()
{
    texture = LoadTexture("nature_tileset/SPA_Coins.png");
    animationMaxFrame = 12;
    width = texture.width / animationMaxFrame;
    height = texture.height;
    active = true;
}
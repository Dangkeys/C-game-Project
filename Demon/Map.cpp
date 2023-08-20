#include "Map.h"
#include "raymath.h"
Map::Map(Texture2D map, Vector2 position):
    texture(map),
    worldPosition(position)
{
    
}
void Map::Update(Vector2 playerPosition)
{
    worldPosition = Vector2Scale(playerPosition, -1.f);
    DrawTextureEx(texture, worldPosition, 0.0, mapScale, WHITE);
}
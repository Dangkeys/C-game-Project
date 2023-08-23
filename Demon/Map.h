#include "raylib.h"

class Map
{
public:
    Map(Texture2D map, Vector2 position);
    float getMapScale() { return mapScale; }
    void Update(Vector2 playerPosition);

private:
    Texture2D texture{};
    Vector2 worldPosition{};
    const float mapScale{4.0f};
    
};
/*
    mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
    DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

*/
#include"raylib.h"
#include"raymath.h"
int main()
{
    //window references
    const int windowWidth{384};
    const int windowHeight{384};
    const int centerWindowWidth{windowWidth / 2};
    const int centerWindowHeight{windowHeight / 2};
    InitWindow(windowWidth, windowHeight, "Classyclash!");

    //map references
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    float scale{4.0f};
    Vector2 mapPosition{0.0, 0.0};
    float speed{4.0};

    //knight references
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPosition{
        centerWindowWidth - scale * (0.5f * (float)knight.width / 6.0),
        centerWindowHeight - scale * (0.5f * (float)knight.height)
    };
    float faceRight{1.0f};
    float runningTime{};
    const float updateTime{1.0 / 12.0};
    const int maxFrame{6};
    int frame{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //begin game logic
        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;

        //change map position by direction if moving left map moving right the player is stat still
        if (Vector2Length(direction) != 0.0)
        {
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? faceRight = -1.f : faceRight = 1.f;
            knight = knight_run;
        } else {
            knight = knight_idle;
        }

        //draw the map
        DrawTextureEx(map, mapPosition, 0.0, scale, WHITE);

        //update animation
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            runningTime = 0.f;
            frame++;
            if (frame > maxFrame) frame = 0;
        }


        //draw the character
        Rectangle source{frame * (float)knight.width/6.f, 0.f, faceRight * knight.width / 6, knight.height};
        Rectangle dest{knightPosition.x, knightPosition.y, scale * (float)knight.width / 6.0, scale * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);
        //end game logic
        EndDrawing();
    }
}
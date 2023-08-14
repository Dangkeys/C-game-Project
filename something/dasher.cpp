#include "raylib.h"
struct Animdata
{
    Rectangle rec;
    Vector2 pos;
    int frame{};
    float updateTime;
    float runningTime;
};

int main()
{
    //window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    //initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    //physics dimensions
    const int gravity{1000};
    
    //animation frame
    // int frame{};
    // //amount of time before update the animation frame
    // const float updateTime{1.0 / 12.0};
    // float runningTime{};

    //player dimensions
    bool isOnAir{};

    Texture2D scarfy = LoadTexture("textures/0x72_DungeonTilesetII_v1.6.png");
    Animdata scarfyData;
    scarfyData.rec.height = 14;
    scarfyData.rec.width = 122 / 8;
    scarfyData.rec.x = 372;
    scarfyData.rec.y = 432;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0;
    // Rectangle scarfyRec;
    // scarfyRec.height = scarfy.height;
    // scarfyRec.width = scarfy.width / 6;
    // scarfyRec.x = 0;
    // scarfyRec.y = 0;
    // Vector2 scarfyPos;
    // scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    // scarfyPos.y = windowHeight - scarfyRec.height;
    int velocity{};
    const int jumpVel{-600};

    //nebula references
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    // Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    // int nebFrame{};
    // const float nebUpdateTime{1.0/ 12.0};
    // float nebRunningTime{};
    int nebVel{-200};
    Animdata nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, 
        {windowWidth, windowHeight - nebula.height/8}, 
        0, 
        1.0 / 12.0,
        0.0
        };
    Animdata neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {windowWidth + 300, windowHeight - nebula.height / 8},
        0,
        1.0 / 12.0,
        0.0f
    };
    //nebula 2 references
    // Rectangle neb2Rec{0.0, 0.0, nebula.width/ 8, nebula.height / 8};
    // Vector2 neb2Pos{windowWidth + 300, windowHeight - neb2Rec.height};
    // int neb2Frame{};
    // const float neb2UpdateTime{1.0 / 18.0};
    // float neb2RunningTime{};
    int neb2Vel{-200};



    //close when click x mark and set fps to 60
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //start game logic

        //declare delta time
        const float dt{GetFrameTime()};

        //check is on ground 
        if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
        {
            isOnAir = false;
            velocity = 0;
        } else {
            isOnAir = true;
            //add accelaration to velocity
            velocity += gravity * dt;
        }

        //jump check
        if(IsKeyPressed(KEY_SPACE) && !isOnAir)
        {
            velocity += jumpVel; 
        }
        //update nebula position
        nebData.pos.x += nebVel * dt;
        //update nebula 2 position
        neb2Data.pos.x += neb2Vel * dt;
        //update scarfy position
        scarfyData.pos.y += velocity * dt;

        //update scarfy running time 
        scarfyData.runningTime += dt;
        //update nebula runnig time
        nebData.runningTime += dt;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }
        //update nebula 2 running time
        neb2Data.runningTime += dt;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }
        //update animation frame
        if (scarfyData.runningTime >= scarfyData.updateTime && !isOnAir)
        {
            scarfyData.runningTime = 0;
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width + 372;
            scarfyData.frame++;
            if (scarfyData.frame >= 8)
            {
                scarfyData.frame = 0;
            }
        }

        //draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // draw nebula 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        //draw player
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        DrawTextureEx(scarfy,{0,0},0,1,WHITE);
        //end game logic
        EndDrawing();
    }
    //close texture safely
    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    //close window safely
    CloseWindow();
}
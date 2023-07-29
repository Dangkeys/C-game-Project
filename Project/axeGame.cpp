#include"raylib.h"
int main()
{
    //Window References
    int windowWidth{300};
    int windowHeight{200};
    int windowCenterX{windowWidth / 2};
    int windowCenterY{windowHeight / 2};

    //Circle References
    float radius{25};
    int circleX{windowCenterX};
    int circleY{windowCenterY};
    int circleSpeed{10};
    int LeftCircle{circleX - radius};
    int RightCircle{circleX + radius};
    int TopCircle{circleY + radius};
    int BottomCircle{circleY - radius};
    bool isCollision{false};

    //Rectangle Refeneces
    int rectangleWidth{50};
    int rectangleHeight{50};
    int rectangleX{windowWidth - rectangleWidth};
    int rectangleY{windowCenterY};
    int rectangleSpeed{5};
    int Leftrectangle{rectangleX};
    int RightRectangle{rectangleX + rectangleWidth};
    int TopRectangle{rectangleY};
    int BottomRectangle{rectangleY + rectangleHeight};


    InitWindow(windowWidth, windowHeight, "hello");

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        //start game logic
        
        //update variables
        LeftCircle = circleX - radius;
        RightCircle = circleX + radius;
        TopCircle = circleY + radius;
        BottomCircle = circleY - radius;
        Leftrectangle= rectangleX;
        RightRectangle = rectangleX + rectangleWidth;
        TopRectangle = rectangleY;
        BottomRectangle = rectangleY + rectangleHeight;
        isCollision = 
                        (BottomRectangle >= TopCircle) &&
                        (TopRectangle  <= BottomCircle) &&
                        (RightRectangle >= LeftCircle) &&
                        (Leftrectangle <= RightCircle);
        //create player
        if (isCollision)
        {
            DrawText("Game Over!", windowCenterX - 50 , windowCenterY, 32, RED);
        } else {

            DrawCircle(circleX, circleY, radius, BLUE);
            if(IsKeyDown(KEY_A) && circleX >= radius)
            {
                circleX -= circleSpeed;
            }
            if(IsKeyDown(KEY_D) && circleX <= windowWidth - radius)
            {
                circleX += circleSpeed;
            }

            //create enemy
            DrawRectangle(rectangleX, rectangleY, rectangleWidth, rectangleHeight, RED);
            if (rectangleY <= 0 || rectangleY >= windowHeight- rectangleHeight)
            {
                rectangleSpeed = -rectangleSpeed;
            }
            rectangleY += rectangleSpeed;
        }
        //end game logic

        EndDrawing();
    }
    CloseWindow();
}
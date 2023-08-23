#include "raylib.h"
#include "Game.h"
bool startGame{false};
bool pleaseEnterName{false};
const int screenWidth = 1950;
const int screenHeight = 1100;
std::string userInput;
bool cursorVisible = false;
double cursorTimer = 0.0;
bool hasInput = false;
void MainMenu();
int main(void)
{

    InitWindow(screenWidth, screenHeight, "Demon");
    Game game{screenWidth, screenHeight};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        if (!startGame)
        {
            MainMenu();
        }
        else if (game.isGameEnd)
        {
            DrawText("Game has ended", screenWidth / 2, screenHeight / 3, 70, BLACK);
            DrawText("Press Enter to play", screenWidth / 2, screenHeight / 2, 50, BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                game.isGameEnd = false;
                game.ResetFirstFrame();
            }
        }
        else if (game.isNextWave)
        {
            game.waveCounter++;
            game.isNextWave = false;
            game.ResetNextWave();
        }
        else
            game.Update(GetFrameTime());
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
// ... (other code)

void MainMenu()
{
    DrawTextureEx(LoadTexture("nature_tileset/realMap.png"), {-2500, 0}, 0.f, 4, WHITE);
    DrawText("Demon", screenWidth / 2 - 350, screenHeight / 3, 70, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !startGame && !pleaseEnterName)
    {
        pleaseEnterName = true;
    }
    else if (!startGame && pleaseEnterName)
    {
        DrawText(("Name: " + userInput + (cursorVisible ? "|" : "")).c_str(), screenWidth / 2 - 250, screenHeight / 2 + 50, 50, WHITE);

        if (IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
        {
            userInput.pop_back(); // Remove the last character
        }
        else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
        {
            if (!userInput.empty())
            {
                startGame = true; // Start the game if there's input and Enter is pressed
            }
            else
            {
                hasInput = false; // No input, show error message
            }
        }
        else
        {
            int key = GetCharPressed();
            if (key > 0 && key != KEY_BACKSPACE && key != KEY_ENTER && key != KEY_KP_ENTER)
            {
                hasInput = true;                     // User is inputting characters
                userInput += static_cast<char>(key); // Add the pressed character to the input string
            }
        }

        // Update the cursor blink timer
        cursorTimer += GetFrameTime();
        if (cursorTimer >= 0.5)
        {
            cursorTimer = 0;
            cursorVisible = !cursorVisible;
        }
    }
    else
    {
        DrawText("Press spacebar to play", screenWidth / 2 - 250, screenHeight / 2 + 50, 50, WHITE);
    }
}

// ... (other code)

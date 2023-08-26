#include "raylib.h"
#include "Game.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

bool startGame{false};
bool pleaseEnterName{false};
const int screenWidth = 1950;
const int screenHeight = 1100;
std::string userInput;
int score{};
bool cursorVisible = false;
double cursorTimer = 0.0;
bool hasInput = false;
void MainMenu();
void EndgameUI();
void ScoreboardMechanic(std::string &name, int score);
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
            DrawTextureEx(LoadTexture("nature_tileset/realMap.png"), {-2500, 0}, 0.f, 4, WHITE);
            if (game.endFirstFrame)
            {
                score = game.GetScore();
                // write scoreboard
                ScoreboardMechanic(userInput, score);
                game.endFirstFrame = false;
            }
            EndgameUI();
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
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

void MainMenu()
{
    DrawTextureEx(LoadTexture("nature_tileset/realMap.png"), {-2500, 0}, 0.f, 4, WHITE);
    DrawText("Demon", screenWidth / 2 - 350, screenHeight / 3, 70, WHITE);
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !startGame && !pleaseEnterName)
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
        else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
        {
            if (!userInput.empty())
                startGame = true; // Start the game if there's input and Enter is pressed
        }
        else
        {
            int key = GetCharPressed();
            if (key > 0 && key != KEY_BACKSPACE && key != KEY_ENTER && key != KEY_KP_ENTER && userInput.length() < 30)
                userInput += static_cast<char>(key); // Add the pressed character to the input string
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
        DrawText("press spacebar to play", screenWidth / 2 - 250, screenHeight / 2 + 50, 50, WHITE);
    }
}
void ScoreboardMechanic(std::string &name, int score)
{
    FILE *fPointer;
    fPointer = fopen("scores.txt", "a+");
    fprintf(fPointer, "%s %d\n", name.c_str(), score);

    fclose(fPointer);
}
void EndgameUI()
{
    float woodscaleX{10.f};
    float woodscaleY{5.f};
    Texture2D wood{LoadTexture("UI/woodBackgroundUI.png")};
    Rectangle source{0, 0, wood.width, wood.height};
    Rectangle dest{screenWidth / 2 - wood.width * woodscaleX / 2, 100, wood.width * woodscaleX, wood.height * woodscaleY};

    Texture2D scoreboard{LoadTexture("UI/scoreboard.png")};
    Rectangle scoreboardSource{0, 0, scoreboard.width, scoreboard.height};
    Rectangle scoreboardDest{screenWidth / 5, screenHeight / 4, screenWidth * 3 / 5, screenHeight * 2 / 4};

    DrawTexturePro(wood, source, dest, {0, 0}, 0, WHITE);
    DrawText("Scoreboard", screenWidth / 2 - 180, 150, 60, WHITE);
    DrawTexturePro(scoreboard, scoreboardSource, scoreboardDest, {0, 0}, 0, WHITE);
    int yOffset = screenHeight / 4 + 100;

    struct ScoreData
    {
        char *name;
        int score;
    };

    std::vector<ScoreData> fileScores;

    FILE *scoreFile = fopen("scores.txt", "rb");
    if (scoreFile != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), scoreFile))
        {
            char name[100];
            int score;
            if (sscanf(line, "%s %d", name, &score) == 2)
            {
                fileScores.push_back({strdup(name), score});
            }
        }
        fclose(scoreFile);

        // Sort the scores in descending order
        std::sort(fileScores.begin(), fileScores.end(), [](const ScoreData &a, const ScoreData &b)
                  { return a.score > b.score; });

        // Display the top 8 scores in the scoreboard
        int scoresToDisplay = std::min(static_cast<int>(fileScores.size()), 8); // Display up to 8 scores
        DrawText("Name", screenWidth / 5 + 100, yOffset - 50, 50, BROWN);
        DrawText("Score", screenWidth * 3 / 5 + 100, yOffset - 50, 50, BROWN);
        for (int i = 0; i < scoresToDisplay; ++i)
        {
            DrawText(fileScores[i].name, screenWidth / 5 + 100, yOffset, 50, BROWN);
            DrawText(std::to_string(fileScores[i].score).c_str(), screenWidth * 3 / 5 + 100, yOffset, 50, BROWN);
            yOffset += 50;
        }

        // Free the memory allocated for name
        for (auto &scoreData : fileScores)
        {
            free(scoreData.name);
        }
    }
    DrawText("press spacebar to try again", screenWidth / 2 - 325, screenHeight * 4 / 5, 50, WHITE);
}

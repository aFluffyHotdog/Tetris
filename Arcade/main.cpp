#include "raylib.h"
#include "Game.h"
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    const double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

typedef enum GameScreen { START = 0, GAMEPLAY, ENDING } GameScreen;
Shader scanLines = LoadShader(0, TextFormat("crt-pi.glsl", GLSL_VERSION));

int main() {
    constexpr int scrWidth = 600;
    constexpr int scrHeight = 600;
    InitWindow(scrWidth, scrHeight, "Tetris");
    GameScreen currScreen = START;
    SetTargetFPS(60);
    Game g = Game(scrWidth, scrHeight);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (currScreen) {
            case START: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currScreen = GAMEPLAY;
                    break;
                }
            }
            case GAMEPLAY: {
                if (g.gameOver) {
                    g = Game(scrWidth, scrHeight);
                    currScreen = ENDING;
                }
            }
            case ENDING: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currScreen = GAMEPLAY;
                    break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (currScreen) {
            case START: {
                DrawText("Hello Mr. Geoffreaky Hinton", 150, 200, 24,  WHITE);
                DrawText("Press ENTER to start", 150, 300, 16,  WHITE);
                break;
            }

            case GAMEPLAY: {
                DrawText("hello", 200, 200, 12,  WHITE);
                g.Draw();
                g.HandleInput();
                if (EventTriggered(0.4)) {
                    g.MoveDown();
                }
                break;
            }
            case ENDING: {
                DrawText("Hah! You lost!", 150, 200, 24,  WHITE);
                DrawText("Press ENTER to try again", 150, 300, 16,  WHITE);
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
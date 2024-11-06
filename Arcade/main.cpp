#include <iostream>
#include <ostream>
#include <sys/socket.h>
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

bool EventTriggered(const double interval)
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
Shader scanLines = LoadShader(nullptr, TextFormat("crt-pi.glsl", GLSL_VERSION));

int main() {
    constexpr int scrWidth = 600;
    constexpr int scrHeight = 600;
    InitWindow(scrWidth, scrHeight, "Tetris");

    //For debugging audio
    InitAudioDevice();
    Music theme = LoadMusicStream("/Users/thitwutpattanasuttinont/CLionProjects/Tetris/Arcade/sounds/retroTheme.mp3");
    std::cout << IsAudioDeviceReady() << std::endl;
    std::cout << IsMusicReady(theme) << std::endl;

    GameScreen currScreen = START;
    SetTargetFPS(60);
    auto g = Game(scrWidth, scrHeight);
    PlayMusicStream(theme);
    std::cout << IsMusicStreamPlaying(theme) << std::endl;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // first switch to decide which state to go into based on inputs
        switch (currScreen) {
            case START: {
                // Send to gameplay if screen is pressed or screen is clicked
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currScreen = GAMEPLAY;

                    break;
                }
            }
            case GAMEPLAY: {
                if (g.gameOver) // Check game over state
                {
                    g = Game(scrWidth, scrHeight);
                    StopMusicStream(theme);
                    currScreen = ENDING;
                }
            }
            case ENDING: {

                //Send back to gameplay if player clicks the screen or presses Enter
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currScreen = GAMEPLAY;
                    break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // Second switch to handle logic of each state
        switch (currScreen) {
            case START: {
                DrawText("Hello Mr. Geoffreaky Hinton", 150, 200, 24,  WHITE);
                DrawText("Press ENTER to start", 150, 300, 16,  WHITE);
                break;
            }

            case GAMEPLAY: {
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
    UnloadMusicStream(theme);
    CloseWindow();
    CloseAudioDevice();
    return 0;
}
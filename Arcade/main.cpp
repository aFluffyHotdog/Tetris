#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <unistd.h>
#include "raylib.h"
#include "Game.h"
#include "NetworkHandler.h"
#include <signal.h> // For kill
#include "Button.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
double lastUpdateTime = 0;
#define NUM_FRAMES  1
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

const char* shaderLoc = "/Users/thitwutpattanasuttinont/CLionProjects/Tetris/Arcade/scanlines.fs";
typedef enum GameScreen { START = 0, SINGLE_PLAYER, ENDING, MULTI_HOST, MULTI_GUEST, MULTI_SELECT } GameScreen;



pid_t runPythonScript(const char* scriptName) {
    pid_t pid = fork(); // Create a new process

    if (pid == -1) {
        // Error occurred while forking
        perror("Failed to fork");
        return -1;
    }

    if (pid == 0) {
        // Child process: Replace this process with the Python script
        execlp("python3", "python3", scriptName, nullptr);
        // If execlp fails
        perror("Failed to execute Python script");
        exit(EXIT_FAILURE);
    }

    // Parent process: Return the child's PID
    std::cout << "Python script started with PID: " << pid << "\n";
    return pid;
}

void stopPythonScript(pid_t pid) {
    if (kill(pid, SIGTERM) == 0) {
        std::cout << "Python script stopped successfully.\n";
    } else {
        perror("Failed to stop Python script");
    }
}

int main() {
    // const char* scriptName = "/Users/thitwutpattanasuttinont/CLionProjects/Tetris/P2P/basicBitchServer.py";
    // pid_t pythonPid = runPythonScript(scriptName);
    // sleep(50);
    // // Stop the Python script
    // stopPythonScript(pythonPid);
    constexpr int scrWidth = 400;
    constexpr int scrHeight = 600;
    InitWindow(scrWidth, scrHeight, "Tetris");
    Shader scanLines = LoadShader(nullptr, shaderLoc);
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

    Image image = LoadImage("/Users/thitwutpattanasuttinont/CLionProjects/Tetris/Arcade/resources/logo.png");
    Texture2D logo = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM


    int textWidth;
    std::vector<Button> startMenuButtons = {
        Button(scrWidth/2.0, 400, "Single Player", true),
        Button(scrWidth/2.0, 450, "Multiplayer", false)
    };

    std::vector<Button> multiplayerMenuButtons = {
        Button(scrWidth/2.0, 400, "Start a new game", true),
        Button(scrWidth/2.0, 450, "Join a game", false),
        Button(scrWidth/2.0, 500, "<- Back", false)
    };


    int startMenuButtonIndex = 0;
    int multiplayerMenuButtonIndex = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // first switch to decide which state to go into based on inputs
        switch (currScreen) {
            case START: {

                if (IsKeyReleased(KEY_UP) | IsKeyReleased(KEY_DOWN)) {
                    startMenuButtons[startMenuButtonIndex].setSelected(false);
                    startMenuButtonIndex = (startMenuButtonIndex + 1) % 2;
                    startMenuButtons[startMenuButtonIndex].setSelected(true);

                }

                if (IsKeyPressed(KEY_ENTER) )
                {
                   if (startMenuButtonIndex == 0) {
                       currScreen = SINGLE_PLAYER;
                   }
                   else if (startMenuButtonIndex == 1) {
                        currScreen = MULTI_SELECT;
                    }
                    break;
                }

                break;

            }


            case SINGLE_PLAYER: {
                if (g.gameOver) // Check game over state
                {
                    g = Game(scrWidth, scrHeight);
                    StopMusicStream(theme);
                    currScreen = ENDING;
                }
                break;
            }
            case MULTI_SELECT: {
                if (IsKeyReleased(KEY_UP)) {
                multiplayerMenuButtons[multiplayerMenuButtonIndex].setSelected(false);
                multiplayerMenuButtonIndex = (multiplayerMenuButtonIndex - 1 + 3) % 3;
                multiplayerMenuButtons[multiplayerMenuButtonIndex].setSelected(true);
                }
                if (IsKeyReleased(KEY_DOWN)) {
                    multiplayerMenuButtons[multiplayerMenuButtonIndex].setSelected(false);
                    multiplayerMenuButtonIndex = (multiplayerMenuButtonIndex + 1) % 3;
                    multiplayerMenuButtons[multiplayerMenuButtonIndex].setSelected(true);
                }
                if (IsKeyPressed(KEY_ENTER) )
                {
                    switch (startMenuButtonIndex) {
                        case 0: {
                            currScreen = MULTI_HOST;
                            break;
                        }
                        case 1: {
                            currScreen = MULTI_GUEST;
                            break;
                        }
                        case 2: {
                            currScreen = START;
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    break;
                }
            }

            case ENDING: {

                //Send back to gameplay if player clicks the screen or presses Enter
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currScreen = START;
                    break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // Second switch to handle logic of each state
        switch (currScreen) {
            case START: {
                ClearBackground(GetColor(0x0085ffff));
                DrawTextureEx(logo, (Vector2){100, 75},0, 0.5, WHITE);
                textWidth = MeasureText("Hello Mr. Geoffreaky Hinton", 24);
                DrawText("Hello Mr. Geoffreaky Hinton",
                        (scrWidth - textWidth)/2,  // Center horizontally
                        300,
                        24,
                        WHITE);

                textWidth = MeasureText("Please select a game mode: ", 16);
                DrawText("Please select a game mode: ", (scrWidth - textWidth)/2, 350, 16,  WHITE);
                for (int i = 0; i < startMenuButtons.size(); i++) {
                    startMenuButtons[i].Draw();
                }
                break;
            }

            case SINGLE_PLAYER: {
                BeginShaderMode(scanLines);
                g.Draw();
                g.HandleInput();
                if (EventTriggered(0.4)) {
                    g.MoveDown();
                }
                EndShaderMode();
                break;
            }
            case ENDING: {
                DrawText("Hah! You lost!", 150, 200, 24,  WHITE);
                DrawText("Press ENTER to try again", 150, 300, 16,  WHITE);
                break;
            }

            case MULTI_SELECT: {
                ClearBackground(GetColor(0xff5b00ff));
                textWidth = MeasureText("Start or join a game: ", 20);
                DrawText("Start or join a game", (scrWidth - textWidth)/2, 150, 20,  WHITE);
                for (int i = 0; i < multiplayerMenuButtons.size(); i++) {
                    multiplayerMenuButtons[i].Draw();
                }
                break;
            }
            case MULTI_HOST: {
                textWidth = MeasureText("TODO: finish websocekt code ", 20);
                DrawText("TODO: finish websocekt code ", (scrWidth - textWidth)/2, 150, 20,  WHITE);
                break;
            }
            case MULTI_GUEST: {
                textWidth = MeasureText("TODO: finish websocekt code ", 20);
                DrawText("TODO: finish websocekt code ", (scrWidth - textWidth)/2, 150, 20,  WHITE);
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
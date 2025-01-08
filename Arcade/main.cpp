#include <iostream>
#include <ostream>
#include <unistd.h>
#include "raylib.h"
#include "Game.h"
#include <csignal>
#include "Button.h"
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cctype>
#include <thread>

void runPythonScriptThread(const char* scriptName) {
    system(("python3 " + std::string(scriptName)).c_str());
}

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define SUBHEADING_FONT_SIZE 20
#define HEADING_FONT_SIZE 32
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
typedef enum GameScreen { START = 0, SINGLE_PLAYER, ENDING, MULTI_HOST, MULTI_GUEST, MULTI_GAMEPLAY, MULTI_SELECT } GameScreen;



int connectToWifi(const std::string& ssid, const std::string& password) {
    // Path to the wpa_supplicant configuration file
    const std::string wpaConfigPath = "/etc/wpa_supplicant/wpa_supplicant.conf";

    // Create or modify the wpa_supplicant configuration file
    std::string command = "sudo bash -c \"echo -e 'network={\\n"
                          "ssid=\n"
                          "psk=\\\"" + password + "\\\"\\n"
                          "}' >> " + wpaConfigPath + "\"";

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to write Wi-Fi configuration." << std::endl;
        return 1;
    }

    // Restart the wpa_supplicant service to apply changes
    result = std::system("sudo systemctl restart wpa_supplicant");
    if (result != 0) {
        std::cerr << "Failed to restart wpa_supplicant service." << std::endl;
        return 1;
    }

    // Reconnect to the network
    result = std::system("sudo dhclient wlan0");
    if (result != 0) {
        std::cerr << "Failed to obtain an IP address." << std::endl;
        return 1;
    }

    std::cout << "Connected to Wi-Fi network: " << ssid << std::endl;
    return 0;
}



int main() {
    constexpr int scrWidth = 600;
    constexpr int scrHeight = 1024;
    InitWindow(scrWidth, scrHeight, "Tetris");
    //ToggleFullscreen();
    Shader scanLines = LoadShader(nullptr, shaderLoc);

    // Loading Textures
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    //For debugging audio
    InitAudioDevice();
    Music theme = LoadMusicStream("/Users/thitwutpattanasuttinont/CLionProjects/Tetris/Arcade/sounds/retroTheme.mp3");
    PlayMusicStream(theme);

    // Loading Textures
    Image image = LoadImage("/home/arcade/Tetris/Arcade/resources/logo.png");
    Texture2D logo = LoadTextureFromImage(image);
    UnloadImage(image);

    // Server stuff declarations
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(65432);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
    char buffer[1024] = {0};
    bool player2Ready = false;

    // Setting up menu buttons
    int textWidth;
    std::vector<Button> startMenuButtons = {
        Button(scrWidth/2.0, 600, "Single Player", true),
        Button(scrWidth/2.0, 650, "Multiplayer", false)
    };

    std::vector<Button> multiplayerMenuButtons = {
        Button(scrWidth/2.0, 600, "Start a new game", true),
        Button(scrWidth/2.0, 650, "Join a game", false),
        Button(scrWidth/2.0, 700, "<- Back", false)
    };

    int startMenuButtonIndex = 0;
    int multiplayerMenuButtonIndex = 0;

    // Game Setup
    GameScreen currScreen = START;
    SetTargetFPS(60);
    auto g = Game(scrWidth, scrHeight);
    pid_t pythonPid;

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
                    std::cout << multiplayerMenuButtonIndex << std::endl;
                }
                if (IsKeyPressed(KEY_ENTER) )
                {
                    switch (multiplayerMenuButtonIndex) {
                        case 0: { // Start a game
                            BeginDrawing();
                            textWidth = MeasureText("starting server...", SUBHEADING_FONT_SIZE);
                            DrawText("starting server...",
                                (scrWidth - textWidth) /2,  // Center horizontally
                                300,
                                SUBHEADING_FONT_SIZE,
                                WHITE);
                            EndDrawing();
                            usleep(2000000);
                            std::cout << "first wait was fine?" << std::endl;
                            system("sudo nmcli device disconnect wlan0");
                            system("sudo nmcli device wifi hotspot ssid arcade-hotspot password techteambestteam ifname wlan0");
                            std::thread pythonThread(runPythonScriptThread, "../P3P/testing_purposes/server.py");
                            pythonThread.detach();
                            //system("python3 server.py");
                            std::cout << "server started!" << std::endl;
                            usleep(2000000);
                            // if server couldn't connect
                            if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                                BeginDrawing();
                                textWidth = MeasureText("Failed to start server", SUBHEADING_FONT_SIZE);
                                DrawText("Failed to start server",
                                    (scrWidth - textWidth) /2,  // Center horizontally
                                    300,
                                    SUBHEADING_FONT_SIZE,
                                    WHITE);
                                usleep(2000000);
                                std::cout << "Failed to start server" << std::endl;
                                EndDrawing();
                                break;
                            }

                            int flags = fcntl(clientSocket, F_GETFL, 0);

                            if (flags == -1) {
                                return -1;
                            }

                            if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
                                return -1;
                            }
                            cout << "it's non blocking now?" << endl;
                            currScreen = MULTI_HOST;
                            break;
                        }
                        case 1: {  // Join a game
                            int wifiSuccess = connectToWifi("arcade-hotspot", "techteambestteam");
                            if (wifiSuccess != 0) {
                                BeginDrawing();
                                textWidth = MeasureText("Failed to connect to host wifi", SUBHEADING_FONT_SIZE);
                                DrawText("Failed to connect to host wifi",
                                    (scrWidth - textWidth) /2,  // Center horizontally
                                    300,
                                    SUBHEADING_FONT_SIZE,
                                    WHITE);
                            }
                            if (inet_pton(AF_INET, "10.42.0.1", &serverAddress.sin_addr) <= 0) {
                                perror("Invalid address or address not supported");
                                close(clientSocket);
                                break;
                            }

                            if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                                BeginDrawing();
                                textWidth = MeasureText("Failed to join server", SUBHEADING_FONT_SIZE);
                                DrawText("Failed to join server",
                                    (scrWidth - textWidth) /2,  // Center horizontally
                                    300,
                                    SUBHEADING_FONT_SIZE,
                                    WHITE);
                                EndDrawing();

                                break;
                            }

                            int flags = fcntl(clientSocket, F_GETFL, 0);

                            if (flags == -1) {
                                return -1;
                            }

                            if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
                                return -1;
                            }
                            cout << "it's non blocking now?" << endl;
                            const char* message = "Client 2 connected";
                            send(clientSocket, message, strlen(message), 0);
                            currScreen = MULTI_GAMEPLAY;
                            break;
                        }
                        case 2: { // back button
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
            default:
                break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // Second switch to handle logic of each state
        switch (currScreen) {
            case START: {
                ClearBackground(GetColor(0x0085ffff));
                DrawTextureEx(logo, (Vector2){200, 200},0, 0.5, WHITE);
                textWidth = MeasureText("IEEE 2024 Fall Project",HEADING_FONT_SIZE);
                DrawText("IEEE 2024 Fall Project",
                        (scrWidth - textWidth)/2,  // Center horizontally
                        500,
                       HEADING_FONT_SIZE,
                        WHITE);

                textWidth = MeasureText("Please select a game mode: ", SUBHEADING_FONT_SIZE);
                DrawText("Please select a game mode: ", (scrWidth - textWidth)/2, 550, SUBHEADING_FONT_SIZE,  WHITE);
                for (const auto & startMenuButton : startMenuButtons) {
                    startMenuButton.Draw();
                }
                break;
            }

            case SINGLE_PLAYER: {
                //BeginShaderMode(scanLines);
                g.Draw();
                int rows_full = g.HandleInput();
                if (rows_full > 0) {
                    std::cout << rows_full << std::endl;
                }
                if (EventTriggered(0.4)) {
                    g.MoveDown();
                }
                //EndShaderMode();
                break;
            }
            case ENDING: {
                ClearBackground(RED);
                textWidth = MeasureText("HAH! You Lost, try again",HEADING_FONT_SIZE);
                DrawText("HAH! You Lost, try again",
                        (scrWidth - textWidth)/2,  // Center horizontally
                        300,
                       HEADING_FONT_SIZE,
                        WHITE);
                break;
            }

            case MULTI_SELECT: {
                ClearBackground(GetColor(0xff5b00ff));
                textWidth = MeasureText("Start or join a game: ", HEADING_FONT_SIZE);
                DrawText("Start or join a game", (scrWidth - textWidth)/2, 150, HEADING_FONT_SIZE,  WHITE);
                for (const auto & multiplayerMenuButton : multiplayerMenuButtons) {
                    multiplayerMenuButton.Draw();
                }
                break;
            }

            case MULTI_HOST: {
                ClearBackground(BLACK);
                textWidth = MeasureText("Waiting for other player to join...", 20);
                DrawText("Waiting for other player to join...", (scrWidth - textWidth)/2, 150, 20,  WHITE);

                // Check if other player is ready.
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

                if (bytesReceived < 0) {
                    continue;
                }
                buffer[bytesReceived] = '\0';
                if (strncmp(buffer, "Client 2 connected", sizeof(buffer)) == 0) {
                    cout << "received " << buffer << endl;
                    player2Ready = true;
                    currScreen = MULTI_GAMEPLAY;

                }
                break;
            }

            case MULTI_GAMEPLAY: {
                if (g.gameOver) // Check game over state
                {
                    g = Game(scrWidth, scrHeight);
                }
                g.Draw();
                int rows_cleared = g.HandleInput();
                if (EventTriggered(0.4)) {
                    g.MoveDown();
                }
                if (rows_cleared > 0) {
                    const char* message = std::to_string(rows_cleared).c_str();
                    send(clientSocket, message, strlen(message), 0);
                }

                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

                if (bytesReceived > 0) {
                    buffer[bytesReceived] = '\0'; // Null-terminate the buffer
                    std::cout << "Raw data received:\n";
                    for (int i = 0; i < bytesReceived; ++i) {
                        std::cout << "buffer[" << i << "]: " << static_cast<int>(buffer[i])
                                  << " ('" << buffer[i] << "')\n";
                    }
                    std::string sanitizedBuffer(buffer, bytesReceived);

                     sanitizedBuffer.erase(
                        std::remove_if(sanitizedBuffer.begin(), sanitizedBuffer.end(),
                                       [](unsigned char c) { return !std::isdigit(c); }),
                        sanitizedBuffer.end());
                        
                    // Check for valid numeric input
                    if (!sanitizedBuffer.empty() && 
                        std::all_of(sanitizedBuffer.begin(), sanitizedBuffer.end(), ::isdigit)) {
                        try {
                            int number = std::stoi(sanitizedBuffer); // Convert to integer
                            std::cout << "Received number: " << number << std::endl;
                            g.board.ShiftRowsUp(number);
                        } catch (const std::exception& e) {
                            std::cerr << "Conversion error: " << e.what() << std::endl;
                        }
                    } else {
                        std::cerr << "Invalid data received: \"" << sanitizedBuffer << "\"\n";
                    }
                }
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

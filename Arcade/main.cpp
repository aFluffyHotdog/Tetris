#include "raylib.h"
#include "Game.h"

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

int main()

{
    constexpr int scrWidth = 600;
    constexpr int scrHeight = 600;
    InitWindow(scrWidth, scrHeight, "Tetris");
    SetTargetFPS(60);
    auto g = Game();
    while (!WindowShouldClose()) {
        //
        BeginDrawing();
        g.Draw();
        g.HandleInput();
        if (EventTriggered(0.4)) {
            g.MoveDown();
        }
        EndDrawing();
        g.ClearRows();
        
        
    }
    CloseWindow();
    return 0;
}
#include "raylib.h"
#include "Game.h"
#include "Board.h"
#include "Tetromino.h"
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)

{
    const int scrWidth = 600;
    const int scrHeight = 1024;
    InitWindow(scrWidth, scrHeight, "Tetris");
    SetTargetFPS(60);
    Game g = Game();
    while (!WindowShouldClose()) {
        //
        BeginDrawing();
        g.Draw();
        g.HandleInput();
        EndDrawing();
        g.ClearRows();
        
        
    }
    CloseWindow();
    return 0;
}
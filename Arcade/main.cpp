#include "raylib.h"
#include "Game.h"
#include "Board.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)

{
    const int scrWidth = 600;
    const int scrHeight = 1024;
    InitWindow(scrWidth, scrHeight, "Tetris");
    Board b = Board();
    while (!WindowShouldClose()) {
        BeginDrawing();
        b.Draw(scrWidth, scrHeight);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
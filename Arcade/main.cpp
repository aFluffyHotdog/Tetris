#include "raylib.h"
#include "Game.h"
#include "Board.h"
#include "Tetromino.h"
#include <chrono>
#include <thread>
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)

{
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
    using std::chrono::system_clock;
    const int scrWidth = 600;
    const int scrHeight = 1024;
    InitWindow(scrWidth, scrHeight, "Tetris");
    SetTargetFPS(60);
    Board boad = Board();
    Hero h = Hero();
    int i = 1;
    while (!WindowShouldClose()) {
        // 
       // std::cout << "before move" << std::endl;
        //
        
        /*sleep_for(1s);*/
       // std::cout << "after move" << std::endl;
        
       
        if (IsKeyDown(KEY_RIGHT)) h.MoveRight(boad);
        if (IsKeyDown(KEY_LEFT)) h.MoveLeft(boad);
        if (IsKeyDown(KEY_DOWN)) h.MoveDown(boad);
        BeginDrawing();
          
        boad.Draw(scrWidth, scrHeight);
        h.Draw(boad);
        boad.PrintRow(0);
        //sleep_for(200ms);
            
        //sleep_for(200ms);
            
            
        std::cout << "" << std::endl;
        //boad.Clear();
        EndDrawing();

        
        //h.Draw(boad);
        i++;
        
        
    }
    CloseWindow();
    return 0;
}
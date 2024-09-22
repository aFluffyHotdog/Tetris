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
    Game game{scrWidth,scrHeight, "Hello there", 60 };
    
    while (!game.GameShouldClose()) {
        game.Tick();
    }
    
    return 0;
}
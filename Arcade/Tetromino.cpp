#include "Tetromino.h"
#include "Board.h"
#include <iostream>

Tetromino::Tetromino() {

}
Tetromino::Tetromino( int new_id) { 
    active = false;
    id = new_id;
    rotationState = 0;


}

bool Tetromino::CheckCollision(Board& b) {

    return true; 
}

void Tetromino::Rotate(Board& b) {

    for (const auto& block : rotationStates[rotationState+1])
    {
        if (!(((block.first + originXPos - 1) >= 0) && ((block.first + originXPos - 1) <= 19) && 
            ((block.second + originXPos - 1) >= 0) && ((block.second + originXPos - 1) <= 9)))
        {
            std::cout << "invalid" << std::endl;
            return;
        }
    }

    for (const auto& block : rotationStates[rotationState]) {
        b.Clear(block.first + originYPos, block.second + originXPos);
    }
    rotationState = (rotationState + 1) % 4;
}

void Tetromino::Draw(Board& b) {
    for (const auto &block : rotationStates[rotationState]) {
        b.SetColor(block.first + originYPos, block.second + originXPos, c);
    }
}

// All Tetrominoes


using namespace std;

Hero::Hero()
{   
    rotationState = 1; //Spawns vertical
    c = SKYBLUE;
    rotationStates[0] = {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(1,3)}; //rotation state 1 - 4
    rotationStates[1] = {make_pair(0,2), make_pair(1,2), make_pair(2,2), make_pair(3,2)};
    rotationStates[2] = {make_pair(2,0), make_pair(2,1), make_pair(2,2), make_pair(2,3)};
    rotationStates[3] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(3,1)};
}

B_Ricky::B_Ricky()
{
    rotationState = 0; //Spawns horizontal
    c = DARKBLUE;
    rotationStates[0] = {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(1,2)}; //rotation state 1 - 4
    rotationStates[1] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(0,2)};
    rotationStates[2] = {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(2,2)};
    rotationStates[3] = {make_pair(2,0), make_pair(2,1), make_pair(1,1), make_pair(0,1)};

}

O_Ricky::O_Ricky()
{
    rotationState = 0; //Spawns horizontal
    c = ORANGE;
    rotationStates[0] = { make_pair(0,2), make_pair(1,0), make_pair(1,1), make_pair(1,2)}; //rotation state 1 - 4
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(2,2)};
    rotationStates[2] = { make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(2,0)};
    rotationStates[3] = { make_pair(0,0), make_pair(2,1), make_pair(1,1), make_pair(0,1)};

}

SmashBoi::SmashBoi()
{
    rotationState = 0;
    c = YELLOW;
    rotationStates[0] = {make_pair(0,0), make_pair(0,1), make_pair(1,0), make_pair(1,1)};  // has no rotation state

}

TeeWee::TeeWee()
{
    rotationState = 0;
    c = PURPLE;
    rotationStates[0] = { make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(1,2), make_pair(2,1)};
    rotationStates[2] = { make_pair(2,1), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[3] = { make_pair(0,1), make_pair(1,1), make_pair(1,0), make_pair(2,1)};
}

Cleveland_Z::Cleveland_Z()
{
    rotationState = 0;
    c = GREEN;
    rotationStates[0] = { make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(0,2) };
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(1,2), make_pair(2,2) };
    rotationStates[2] = { make_pair(2,1), make_pair(2,0), make_pair(1,1), make_pair(1,2) };
    rotationStates[3] = { make_pair(0,0), make_pair(1,1), make_pair(1,0), make_pair(2,1) };
}

Rhode_Z::Rhode_Z()
{
    rotationState = 0;
    c = RED;
    rotationStates[0] = { make_pair(0,0), make_pair(0,1), make_pair(1,1), make_pair(1,2) };
    rotationStates[1] = { make_pair(0,2), make_pair(1,1), make_pair(1,2), make_pair(2,1) };
    rotationStates[2] = { make_pair(1,0), make_pair(1,1), make_pair(2,1), make_pair(2,2) };
    rotationStates[3] = { make_pair(0,1), make_pair(1,1), make_pair(1,0), make_pair(2,0) };
}

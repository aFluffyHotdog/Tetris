#include "Tetromino.h"
#include "Board.h"
#include <iostream>

Tetromino::Tetromino() {
    originXPos = 0;
    originYPos = 0;
    rotationState = 0;
}

// All Tetrominoes


using namespace std;

Hero::Hero()
{   
    rotationState = 0; //Spawns vertical
    color = SKYBLUE;
    //rotation state 1 - 4
    rotationStates[0] = {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(1,3)};
    rotationStates[1] = {make_pair(0,2), make_pair(1,2), make_pair(2,2), make_pair(3,2)};
    rotationStates[2] = {make_pair(2,0), make_pair(2,1), make_pair(2,2), make_pair(2,3)};
    rotationStates[3] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(3,1)};
}

B_Ricky::B_Ricky()
{
    rotationState = 0; //Spawns horizontal
    color = DARKBLUE;
    //rotation state 1 - 4
    rotationStates[0] = {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[1] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(0,2)};
    rotationStates[2] = {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(2,2)};
    rotationStates[3] = {make_pair(2,0), make_pair(2,1), make_pair(1,1), make_pair(0,1)};

}

O_Ricky::O_Ricky()
{
    rotationState = 0; //Spawns horizontal
    color = ORANGE;//rotation state 1 - 4
    rotationStates[0] = { make_pair(0,2), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(2,2)};
    rotationStates[2] = { make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(2,0)};
    rotationStates[3] = { make_pair(0,0), make_pair(2,1), make_pair(1,1), make_pair(0,1)};

}

SmashBoi::SmashBoi()
{
    rotationState = 0;
    color = YELLOW;
    rotationStates[0] = {make_pair(0,0), make_pair(0,1), make_pair(1,0), make_pair(1,1)};  // has no rotation state

}

TeeWee::TeeWee()
{
    rotationState = 0;
    color = PURPLE;
    rotationStates[0] = { make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(1,2), make_pair(2,1)};
    rotationStates[2] = { make_pair(2,1), make_pair(1,0), make_pair(1,1), make_pair(1,2)};
    rotationStates[3] = { make_pair(0,1), make_pair(1,1), make_pair(1,0), make_pair(2,1)};
}

Cleveland_Z::Cleveland_Z()
{
    rotationState = 0;
    color = GREEN;
    rotationStates[0] = { make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(0,2) };
    rotationStates[1] = { make_pair(0,1), make_pair(1,1), make_pair(1,2), make_pair(2,2) };
    rotationStates[2] = { make_pair(2,1), make_pair(2,0), make_pair(1,1), make_pair(1,2) };
    rotationStates[3] = { make_pair(0,0), make_pair(1,1), make_pair(1,0), make_pair(2,1) };
}

Rhode_Z::Rhode_Z()
{
    rotationState = 0;
    color = RED;
    rotationStates[0] = { make_pair(0,0), make_pair(0,1), make_pair(1,1), make_pair(1,2) };
    rotationStates[1] = { make_pair(0,2), make_pair(1,1), make_pair(1,2), make_pair(2,1) };
    rotationStates[2] = { make_pair(1,0), make_pair(1,1), make_pair(2,1), make_pair(2,2) };
    rotationStates[3] = { make_pair(0,1), make_pair(1,1), make_pair(1,0), make_pair(2,0) };
}

#include "Tetromino.h"
#include "Board.h"
#include <iostream>

Tetromino::Tetromino() {

}
Tetromino::Tetromino( int new_id) { 
    active = true;
    id = new_id;
    rotationState = 0;


}

bool Tetromino::CheckCollision(Board& b) {
    return true; // TODO: finish this
}

void Tetromino::Rotate(Board& b) {
    if (CheckCollision(b)) {
        for (const auto& block : rotationStates[rotationState]) {
            b.Clear(block.first + originYPos, block.second + originXPos);
        }
        rotationState = (rotationState + 1) % 4;
    }
    
}

void Tetromino::Draw(Board& b) {
    for (const auto &block : rotationStates[rotationState]) {
        b.SetColor(block.first + originYPos, block.second + originXPos, c);
    }
}

void Tetromino::MoveLeft(Board& b) {
    // check if move is valid first
    for (const auto& block : rotationStates[rotationState]) 
    {
        if (!(((block.second + originXPos -1) >= 0) && ((block.second + originXPos -1) <= 9)))
        {
            std::cout << "invalid" << std::endl;
            return; 
        }
    }
    // if it's valid, then clear and move
    for (const auto& block : rotationStates[rotationState]) 
    {
            b.Clear(block.first + originYPos, block.second + originXPos);
    }
    originXPos -= 1;
}

void Tetromino::MoveRight(Board& b) {
    // check if move is valid first
    for (const auto& block : rotationStates[rotationState]) {

        if (!(((block.second + originXPos + 1) >= 0) && ((block.second + originXPos + 1) <= 9)))
        {
            std::cout << "invalid" << std::endl;
            return;
        }
    }
    // if it's valid, then clear and move
    for (const auto& block : rotationStates[rotationState]) {
            b.Clear(block.first + originYPos, block.second + originXPos);
    }

    originXPos += 1;



}

void Tetromino::MoveDown(Board& b) {
    // check if move is valid first
    for (const auto& block : rotationStates[rotationState]) {

        if (!(((block.first + originYPos + 1) >= 0) && ((block.first + originYPos + 1) <= 19)))
        {
            std::cout << "invalid" << std::endl;
            return;
        }
    }
    // if it's valid, then clear and move
    for (const auto& block : rotationStates[rotationState]) {
            b.Clear(block.first + originYPos, block.second + originXPos);

    }

    originYPos += 1;



}


using namespace std;

Hero::Hero()
{   
    originXPos = 0;
    originYPos = 0;
    rotationState = 1; //Spawns vertical
    c = SKYBLUE;
    rotationStates[0] = {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(1,3) }; //rotation state 1 - 4
    rotationStates[1] = {make_pair(0,2), make_pair(1,2), make_pair(2,2), make_pair(3,2) };
    rotationStates[2] = {make_pair(2,0), make_pair(2,1), make_pair(2,2), make_pair(2,3) };
    rotationStates[3] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(3,1) };
}

B_Ricky::B_Ricky()
{
    originXPos = 0;
    originYPos = 0;
    rotationState = 0; //Spawns horizontal
    c = DARKBLUE;
    rotationStates[0] = {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(1,3) }; //rotation state 1 - 4
    rotationStates[1] = {make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(3,1), make_pair(0,3) };
    rotationStates[3] = { make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(3,1), make_pair(0,3) };

}
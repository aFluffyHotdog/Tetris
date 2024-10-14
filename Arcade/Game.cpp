#include "Game.h"
#include <random>
#include "raylib.h"
#include <random>
#include <vector>
#include <iostream>
#include "Tetromino.h"

Game::Game() {
	board = Board();
	tetrominoes = GetAllTetrominoes();
	SetActive();

}

std::vector<Tetromino> Game::GetAllTetrominoes() {
	Hero h = Hero();
	B_Ricky b = B_Ricky();
	O_Ricky o = O_Ricky();
	SmashBoi s = SmashBoi();
	Cleveland_Z c = Cleveland_Z();
	Rhode_Z r = Rhode_Z();
	TeeWee t = TeeWee();
	return { h,b,o,s,c,r,t };
}

void Game::SetActive(){
	if (tetrominoes.empty()) {
		tetrominoes = Game::GetAllTetrominoes();
	}
	int randomIndex = std::rand() % tetrominoes.size();
	activePiece = tetrominoes[randomIndex];
	tetrominoes.erase(tetrominoes.begin() + randomIndex);
	activePiece.active = true;
}

void Game::Draw() {
	board.Draw(600,1024);
	Game::DrawActive();
}
void Game::DrawActive() {
	for (const auto &block : activePiece.rotationStates[activePiece.rotationState]) {
		board.SetColor(block.first + activePiece.originYPos, block.second + activePiece.originXPos, activePiece.c);
	}
}
void Game::HandleInput() {
	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_LEFT:
		Game::MoveLeft();
		break;
	case KEY_RIGHT:
		Game::MoveRight();
		break;
	case KEY_UP:
		Game::Rotate();
		break;
	case KEY_DOWN:
		Game::MoveDown();
		//CheckAndLockBlock();
		break;
	case KEY_SPACE:
		Game::Drop();
		LockBlock();
		break;
	default:
		/*Game::MoveDown(); FINISH THE SLOW DROPPING
		delay()*/
		break;
	}
	

}

// Checks if block is still in the board.
bool Game::CheckBounds(int rotationState, int y_offset, int x_offset) 
{
	rotationState = (rotationState) % activePiece.rotationStates.size();
	for (const auto& block : activePiece.rotationStates[rotationState])
	{
		if (!(((block.first + activePiece.originYPos + y_offset) >= 0) && ((block.first + activePiece.originYPos + y_offset) <= 19) && // check vertical bounds
			((block.second + activePiece.originXPos + x_offset) >= 0) && ((block.second + activePiece.originXPos + x_offset) <= 9))) // check horizontal bounds
		{
			std::cout << block.first + activePiece.originYPos + y_offset << std::endl;
			std::cout << block.second + activePiece.originXPos + x_offset<< std::endl;
			std::cout << "bounds invalid" << std::endl;
			return false;
		}
	}
	return true;
}

// Check if there are any other blocks there.
bool Game::CheckCollision(int rotationState, int y_offset, int x_offset)
{	
	rotationState = (rotationState) % activePiece.rotationStates.size();
	for (const auto& block : activePiece.rotationStates[rotationState])
	{	// this method is to make sure it only checks the cells that this block is not already taking up.
		if (CheckInternalBlock(std::make_pair(block.first + activePiece.originYPos + y_offset, block.second + activePiece.originXPos + x_offset))) { 
			if ((board.grid[block.first + activePiece.originYPos + y_offset][block.second + activePiece.originXPos + x_offset]->exists))
			{

				std::cout << block.first + activePiece.originYPos + y_offset << std::endl;
				std::cout << block.second + activePiece.originXPos + x_offset << std::endl;
				std::cout << "collision invalid" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool Game::CheckInternalBlock(const pair<int, int>& p) {
	vector<pair<int, int>> internal_pos;
	for (const auto& block : activePiece.rotationStates[activePiece.rotationState])
	{
		internal_pos.push_back(std::make_pair(block.first + activePiece.originYPos, block.second + activePiece.originXPos));
	}
	for (const auto& pairInList : internal_pos) {
		if (p == pairInList) {
			/*std::cout << p.first + "was inside" << std::endl;
			std::cout << p.second + "was inside" << std::endl;*/
			return false; // Pair is found, so it's in the list
		}
	}
	return true; // Pair is not found, so it's not in the list
}

bool Game::CheckRowFull(int row) {
	for (const auto& cell : Game::board.grid[row]) {
		if (!cell->exists) {
			return false;
		}
	}
	return true;

}

void Game::ClearRows() {
	for (int i = 19; i >= 0; i--) {
		if (CheckRowFull(i)) {
			for (int j = 0; j < 9; i++) {
				board.grid[i][j] = board.grid[i - 1][j];
			}
		}
	}
}
void Game::LockBlock(){
		board.PrintRow(19);
		//activePiece.active = false;
		//board.PrintRow(19);
		SetActive();
	
}
void Game::Rotate() {

	if (Game::CheckCollision(activePiece.rotationState + 1, 0, 0) && Game::CheckBounds(activePiece.rotationState + 1, 0, 0)) {
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		/*if (activePiece.rotationState + 1 > size(activePiece.rotationStates)) {*/
			// std::cout << "next rotation state" << std::endl;
			// std::cout << size(activePiece.rotationStates) << std::endl;
			// std::cout << (activePiece.rotationState + 1) % (size(activePiece.rotationStates)) << std::endl;
		// }
		activePiece.rotationState = (activePiece.rotationState + 1) % activePiece.rotationStates.size();
		activePiece.Draw(board);
	}
}

void Game::MoveDown() {
	if (Game::CheckCollision(activePiece.rotationState, 1, 0) && Game::CheckBounds(activePiece.rotationState, 1, 0)) 
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originYPos++;
		DrawActive();
	}
}

void Game::MoveLeft() {
	if (Game::CheckBounds(activePiece.rotationState, 0, -1) && Game::CheckCollision(activePiece.rotationState, 0, -1))
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originXPos--;
		activePiece.Draw(board);
	}
}

void Game::MoveRight() {
	if (Game::CheckBounds(activePiece.rotationState, 0, 1) && Game::CheckCollision(activePiece.rotationState, 0, 1))
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originXPos++;
		activePiece.Draw(board);
	}
}

void Game::Drop() {
	while (Game::CheckBounds(activePiece.rotationState, 1, 0) && Game::CheckCollision(activePiece.rotationState, 1, 0) ) {
		Game::MoveDown();
	}
}




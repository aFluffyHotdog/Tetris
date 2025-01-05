#include "Game.h"

#include <iostream>
#include <ostream>
#include <random>
#include "raylib.h"
#include <vector>
#include "Tetromino.h"

Game::Game() {
	board = Board();
	tetrominoes = GetAllTetrominoes();
	SetActive();
	screenWidth = 600;
	screenHeight = 600;
	cellSize = 30;
}

Game::Game(const int newWidth, const int newHeight) {
	board = Board();
	tetrominoes = GetAllTetrominoes();
	SetActive();
	screenWidth = newWidth;
	screenHeight = newHeight;
	gameOver = false;
	cellSize = 30;
}




std::vector<Tetromino> Game::GetAllTetrominoes() {
	auto h = Hero();
	auto b = B_Ricky();
	auto o = O_Ricky();
	auto s = SmashBoi();
	auto c = Cleveland_Z();
	auto r = Rhode_Z();
	auto t = TeeWee();
	return { h,b,o,s,c,r,t };
}

void Game::SetActive(){
	if (tetrominoes.empty()) {
		tetrominoes = Game::GetAllTetrominoes();
	}
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> int_distribution(0, tetrominoes.size()-1); // define the range
	const int randomIndex = int_distribution(gen);
	activePiece = tetrominoes[randomIndex];
	tetrominoes.erase(tetrominoes.begin() + randomIndex);
	if (!SpawnCheck()) {
		gameOver = true;
	}
}

void Game::Draw() {
	//board.Draw(screenWidth,screenHeight);
	DrawBoard();
	DrawActive();
}
void Game::DrawActive() {
	for (const auto &block : activePiece.rotationStates[activePiece.rotationState]) {
		board.SetColor(block.first + activePiece.originYPos, block.second + activePiece.originXPos, activePiece.color);
	}
}

void Game::DrawBoard() {
	int start_y = (screenHeight - (cellSize * 20)) / 2;
	for (const auto & i : board.grid) {
		int start_x = (screenWidth - (cellSize * 10)) / 2;
		for (auto j : i) {
			DrawRectangle(start_x, start_y, cellSize, cellSize, BLACK);
			DrawRectangleLines(start_x, start_y, cellSize, cellSize, WHITE);
			if (j->exists == true) {
				DrawRectangle(start_x, start_y, cellSize - 3, cellSize - 3, j->GetColor());
			}
			start_x += cellSize;
		}
		start_y += cellSize;
	}
}

int Game::HandleInput() {
	const int keyPressed = GetKeyPressed();
	int cleared_shit;
	switch (keyPressed)
	{
	case KEY_LEFT:
		Game::MoveLeft();
		return 0;
	case KEY_RIGHT:
		Game::MoveRight();
		return 0;
	case KEY_UP:
		Game::Rotate();
		return 0;
	case KEY_DOWN:
		Game::MoveDown();
		cleared_shit = board.CheckFullRowsAndSlide();
		return cleared_shit;
	case KEY_SPACE:
		Game::Drop();
		cleared_shit = board.CheckFullRowsAndSlide();
		return cleared_shit;
	case KEY_X:
		board.ShiftRowsUp(3);
		return 0;
	default:
		return 0;
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
				return false;
			}
		}
	}
	return true;
}

//Check if the block that is about to spawn can be spawned in, used for checking gameOver status.
bool Game::SpawnCheck()
{
	for (const auto& block : activePiece.rotationStates[activePiece.rotationState])
	{
		if((board.grid[block.first + activePiece.originYPos][block.second + activePiece.originXPos]->exists))
			{
			    board.PrintRow(block.first + activePiece.originYPos);
				return false;
			}

	}
	return true;
}

bool Game::CheckInternalBlock(const pair<int, int>& p) {
	vector<pair<int, int>> internal_pos;
	for (const auto& block : activePiece.rotationStates[activePiece.rotationState])
	{
		internal_pos.emplace_back(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
	}
	for (const auto& pairInList : internal_pos) {
		if (p == pairInList) {
			return false; // Pair is found, so it's in the list
		}
	}
	return true; // Pair is not found, so it's not in the list
}





void Game::Rotate() {
	// Check for in bound + collision
	if (Game::CheckBounds(activePiece.rotationState + 1, 0, 0) && Game::CheckCollision(activePiece.rotationState + 1, 0, 0) ) {
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.rotationState = (activePiece.rotationState + 1) % activePiece.rotationStates.size();
		DrawActive();
	}
}


void Game::MoveDown() {
	// Check for in bound + collision
	if ((Game::CheckBounds(activePiece.rotationState, 1, 0)) && (Game::CheckCollision(activePiece.rotationState, 1, 0)))
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originYPos++;
		DrawActive();
	}
	else {
		board.CheckFullRowsAndSlide();
		SetActive();
	}

}

void Game::MoveLeft() {
	// Check for in bound + collision
	if (Game::CheckBounds(activePiece.rotationState, 0, -1) && Game::CheckCollision(activePiece.rotationState, 0, -1))
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originXPos--;
		DrawActive();
	}
}

void Game::MoveRight() {
	// Check for in bound + collision
	if (Game::CheckBounds(activePiece.rotationState, 0, 1) && Game::CheckCollision(activePiece.rotationState, 0, 1))
	{
		for (const auto& block : activePiece.rotationStates[activePiece.rotationState]) {
			board.Clear(block.first + activePiece.originYPos, block.second + activePiece.originXPos);
		}
		activePiece.originXPos++;
		DrawActive();
	}
}

void Game::Drop() {
	while (Game::CheckBounds(activePiece.rotationState, 1, 0) && Game::CheckCollision(activePiece.rotationState, 1, 0) ) {
		Game::MoveDown();
	}
}





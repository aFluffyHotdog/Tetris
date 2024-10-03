#pragma once
#include <string>
#include <raylib.h>
#include "board.h"
#include "Tetromino.h"
class Game
{
public:
	Game();
	void Draw();
	Board board;
	void HandleInput();
private:
	std::vector<Tetromino> tetrominoes;
	Tetromino currentBlock;
};
#pragma once
#include <string>
#include <raylib.h>
#include "Tetromino.h"
class Game
{
public:
	Game();

	Game(int newWidth, int newHeight);

	static std::vector<Tetromino> GetAllTetrominoes();
	void Draw();

	void DrawActive();

	void HandleInput();
	void SetActive();
	bool CheckBounds(int rotationState, int y_offset, int x_offset);
	bool CheckCollision(int rotationState, int y_offset, int x_offset);
	bool CheckInternalBlock(const pair<int, int>& p);
	bool CheckRowFull(int row);
	bool CheckGameOver();
	void ClearRows();
	void LockBlock();
	void Rotate();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Drop();



	Board board;
private:
	std::vector<Tetromino> tetrominoes;
	Tetromino activePiece;
	int screenWidth, screenHeight;
};
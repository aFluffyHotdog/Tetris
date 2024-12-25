#pragma once
#include "Tetromino.h"
class Game
{
public:
	Game();

	Game(int newWidth, int newHeight);

	static std::vector<Tetromino> GetAllTetrominoes();
	/// Using information contained in grid, draws the board on the window
	void Draw();
	/// Updates the grid to match the active piece's location
	void DrawActive();
	/// Draws the board on the window.
	void DrawBoard();

	/// Handle rotation, moving left, right, and down
	void HandleInput();
	/// Selects a random block to be an active block.
	void SetActive();

	/// Checks if tetromino is moving outside of grid
	bool CheckBounds(int rotationState, int y_offset, int x_offset);
	/// Checks another block is already there, where the tetromino is moving to
	bool CheckCollision(int rotationState, int y_offset, int x_offset);
	/// Helper for CheckBounds + CheckCollision. Makes sure it doesn't check space that a block is already taking
	bool CheckInternalBlock(const pair<int, int>& p);
	/// Checks if a block has room to spawn, if not.
	bool SpawnCheck();

	/// Rotates the active piece if space permits
	void Rotate();
	/// Moves the active piece down if space permits.
	void MoveDown();
	/// Moves the active piece left if space permits.
	void MoveLeft();
	/// Moves the active piece down if space permits.
	void MoveRight();
	/// Drops the active piece down as low as it could possibly be dropped.
	void Drop();

	Board board;
	bool gameOver;
	int cellSize;

private:
	/// the 7 tetrominoes we use to randomize during game loop
	std::vector<Tetromino> tetrominoes;
	/// The current piece the player is in control of
	Tetromino activePiece;
	int screenWidth, screenHeight;
};
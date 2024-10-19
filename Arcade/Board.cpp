#include "Board.h"
#include <iostream>
Board::Board()
{
	numRow = 20;
	numCol = 10;
	cellSize = 30;
	Initialize();
}

void Board::Initialize()
{
	for (int i = 0; i < numRow; i++) {
		for (int j = 0; j < numCol; j++) {
			grid[i][j] = new Cell();
			grid[i][j]->c = RAYWHITE;
			grid[i][j]->exists = false;
		}
	}
}

void Board::SetColor(int row, int col, Color c) {
	grid[row][col]->SetColor(c);
}
void Board::Clear(int row, int col) {
	grid[row][col]->Clear();
}

void Board::ShiftRows(int startRow) {
	for (int i = startRow; i > 0; i--) {
		for (int j = 0; j < numCol; j++) {
			grid[i][j]->c = grid[i-1][j]->c;
			grid[i][j]->exists = grid[i-1][j]->exists;
		}
	}
}

void Board::ClearRow(int row) {
	for (int i = 0; i < 10; i++) {
		grid[row][i]->Clear();
	}
}
Board::Cell::Cell() {
	c = WHITE;
}

void Board::Cell::SetColor(Color c_in) {
	c = c_in;
	exists = true;
}
void Board::Cell::Clear() {
	exists = false;
	c = BLACK;
}

Color Board::Cell::GetColor() {
	return c;
}


void Board::Draw(const int screenWidth, const int screenHeight){
	float start_x = (screenWidth - (cellSize * 10)) / 2;
	float start_y = (screenHeight - (cellSize * 20)) / 2;
	for (int i = 0; i < numRow; i++) {
		start_x = (screenWidth - (cellSize * 10)) / 2;
		for (int j = 0; j < numCol; j++) {
			DrawRectangle(start_x, start_y, cellSize, cellSize, BLACK);
			DrawRectangleLines(start_x, start_y, cellSize, cellSize, WHITE);
			if (grid[i][j]->exists == true) {
				DrawRectangle(start_x, start_y, cellSize - 3, cellSize - 3, grid[i][j]->GetColor());
			}
			start_x += cellSize;
		}
		start_y += cellSize;
	}
}

void Board::PrintRow(int row) {
		for (int j = 0; j < numCol; j++) {
			std::cout << grid[row][j]->exists;
		}
		std::cout << std::endl;
	}

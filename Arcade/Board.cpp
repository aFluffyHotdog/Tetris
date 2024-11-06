#include "Board.h"
#include <iostream>
Board::Board()
{
	numRow = 20;
	numCol = 10;
	cellSize = 30;
	for (int i = 0; i < numRow; i++) {
		for (int j = 0; j < numCol; j++) {
			grid[i][j] = new Cell();
			grid[i][j]->c = RAYWHITE;
			grid[i][j]->exists = false;
		}
	}
}



void Board::SetColor(const int row, const int col, const Color c) {
	grid[row][col]->SetColor(c);
}
void Board::Clear(const int row, const int col) {
	grid[row][col]->Clear();
}

void Board::ShiftRows(const int startRow) {
	for (int i = startRow; i > 0; i--) {
		for (int j = 0; j < numCol; j++) {
			grid[i][j]->c = grid[i-1][j]->c;
			grid[i][j]->exists = grid[i-1][j]->exists;
		}
	}
}

void Board::ClearRow(const int row) {
	for (int i = 0; i < 10; i++) {
		grid[row][i]->Clear();
	}
}

bool Board::CheckRowFull(int row) {
	//TODO replace with std::all_of()
	for (const auto& cell : grid[row]) {
		if (!cell->exists) {
			return false;
		}
	}
	return true;

}

void Board::CheckRowsAndSlide() {
	int i = 19;
	while(i > 0) {
		if(CheckRowFull(i)) {
			ShiftRows(i);
		}
		else {
			i--;
		}
	}
}
Board::Cell::Cell() {
	c = WHITE;
	exists = false;
}

void Board::Cell::SetColor(Color c_in) {
	c = c_in;
	exists = true;
}
void Board::Cell::Clear() {
	exists = false;
	c = BLACK;
}

Color Board::Cell::GetColor() const {
	return c;
}


void Board::Draw(const int screenWidth, const int screenHeight) const {
	int start_x = (screenWidth - (cellSize * 10)) / 2;
	int start_y = (screenHeight - (cellSize * 20)) / 2;
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

void Board::PrintRow(const int row) const {
		for (int j = 0; j < numCol; j++) {
			std::cout << grid[row][j]->exists;
		}
		std::cout << std::endl;
}

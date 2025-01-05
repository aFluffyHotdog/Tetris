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

void Board::AddRows(int numRows) {

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

int Board::CheckFullRowsAndSlide() {
	int i = 19;
	int rowsFull = 0;
	while(i > 0) {
		if(CheckRowFull(i)) {
			rowsFull++;
			ShiftRows(i);
		}
		else {
			i--;
		}
	}
	return rowsFull;
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




void Board::PrintRow(const int row) const {
		for (int j = 0; j < numCol; j++) {
			std::cout << grid[row][j]->exists;
		}
		std::cout << std::endl;
}

Color Board::getColor(const int row, const int col) const {
	return grid[row][col]->GetColor();
}

Board::~Board() {
	// for (int i = 0; i < numRow; i++) {
	// 	for (int j = 0; j < numCol; j++) {
	// 		delete grid[i][j]; // Delete each dynamically allocated Cell
	// 		grid[i][j] = nullptr; // Set the pointer to nullptr for safety
	// 	}
	// }
}

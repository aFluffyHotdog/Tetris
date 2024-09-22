#include "Board.h"

Board::Cell::Cell() // defined cell class here
	:
	bExists(false),
	c(BLACK)
	{}

Color Board::Cell::GetColor() const {
	return c;
}
void Board::Cell::SetColor(Color c_in) {
	//c = c_in;  potentially breaks stuff
	//bExists = true;
}
void Board::Cell::RemoveColor() {

	bExists = false;

}

int Board::getCellSize() {
	return Board::cellSize;
}

Board::Board(int x_Pos_in, int y_Pos_in, int width_in, int height_in, int cellSize_in)
	:
	x_Pos(x_Pos_in),
	y_Pos(y_Pos_in),
	width(width_in),
	height(height_in),
	cellSize(cellSize_in)
{
	for (int i = 0; i < sizeof(grid); i++) {
		for (int j = 0; j < sizeof(grid[0]); j++) {
			grid[i][j].SetColor(RED);
		}
	}
}


void Board::Draw(int screenWidth, int screenHeight){
	int start_x = (screenWidth - cellSize) / 2;
	int start_y = (screenHeight - cellSize) / 2;
	for (int i = 0; i < sizeof(grid); i++) {
		start_x = (screenWidth - cellSize) / 2;
		for (int j = 0; j < sizeof(grid[0]); j++) {
			DrawRectangleLines(start_x, start_y, cellSize, cellSize, RED);
			start_x += cellSize;
		}
		start_y += cellSize;
	}
}
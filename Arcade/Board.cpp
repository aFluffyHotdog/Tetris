#include "Board.h"

Board::Board()
{
	numRow = 20;
	numCol = 10;
	cellSize = 15;
	Board::Initialize();
}

void Board::Initialize()
{
	for (int i = 0; i < numRow; i++) {
		for (int j = 0; j < numCol; j++) {
			grid[i][j] = Cell();
			grid[i][j].SetColor(RAYWHITE);
		}
	}
}

Board::Cell::Cell() {
	c = WHITE;
}

void Board::Cell::SetColor(Color c_in) {
	c = c_in;
}

//Board::Board(int x_Pos_in, int y_Pos_in, int width_in, int height_in, int cellSize_in)
//	:
//	x_Pos(x_Pos_in),
//	y_Pos(y_Pos_in),
//	width(width_in),
//	height(height_in),
//	cellSize(cellSize_in)
//{
//	for (int i = 0; i < sizeof(grid); i++) {
//		for (int j = 0; j < sizeof(grid[0]); j++) {
//			grid[i][j].SetColor(RED);
//		}
//	}
//}
//
//
void Board::Draw(int screenWidth, int screenHeight){
	float start_x = (screenWidth - (cellSize * 10)) / 2;
	float start_y = (screenHeight - (cellSize * 20)) / 2;
	for (int i = 0; i < numRow; i++) {
		start_x = (screenWidth - (cellSize * 10)) / 2;
		for (int j = 0; j < numCol; j++) {
			DrawRectangleLines(start_x, start_y, cellSize, cellSize, RED);
			start_x += cellSize;
		}
		start_y += cellSize;
	}
}
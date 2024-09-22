#pragma once
#include <raylib.h>
#include <vector>
class Board 
{
private:
	class Cell
	{
	public:
		Cell();
		Color GetColor() const;
		void SetColor(Color c_in);
		void RemoveColor();
		
		
	private:
		bool bExists;
		Color c;
	};
public:
	int getCellSize();
	Board(int x_Pos, int y_Pos, int width, int height, int cellSize);
	void Draw(int screenWidth, int screenHeight);
	
private:
	
	const int width;
	const int height;
	Board::Cell grid[20][10];
	const int x_Pos;
	const int y_Pos;
	const int cellSize;
	
};

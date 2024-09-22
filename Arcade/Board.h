#pragma once
#include <raylib.h>
#include <vector>
class Board 
{

public:
	class Cell
	{
	public:
		Cell();
		void SetColor(Color c_in);
	private:
		Color c;
		
	};
public:
	Board();
	//Board(int row, int column, int cellSize);
	void Initialize();
	void Draw(int screenWidth, int screenHeight);
	Cell grid[20][10];
private:
	int numRow;
	int numCol;
	int cellSize;
		
};

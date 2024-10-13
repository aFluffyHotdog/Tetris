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
		void Clear();
		Color GetColor();
		Color c;
		bool exists;
	};
public:
	Board();
	//Board(int row, int column, int cellSize);
	void Initialize();
	void ShiftRows();
	void SetColor(int row, int col, Color c);
	void Clear(int row, int col);
	void Draw(int screenWidth, int screenHeight);
	void Clear(int row);
	void PrintRow(int row);
	Cell grid[20][10];
private:
	int numRow;
	int numCol;
	int cellSize;
		
};

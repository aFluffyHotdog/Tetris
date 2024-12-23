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
		Color GetColor() const;
		Color c{};
		bool exists;
	};
	Board();
	/// Starting from startRow, shift all the rows above it downwards
	void ShiftRows(int startRow);
	/// Sets the color of a cell
	void SetColor(int row, int col, Color c);
	/// Sets the cell back to its default state
	void Clear(int row, int col);
	///
	void Draw(int screenWidth, int screenHeight) const;
	void ClearRow(int row);
	void CheckRowsAndSlide();
	bool CheckRowFull(int row);
	void PrintRow(int row) const;
	Cell* grid[20][10];
private:
	int numRow;
	int numCol;
	int cellSize;
		
};

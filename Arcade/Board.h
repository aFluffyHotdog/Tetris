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
	/// Clears an entire row per user input
	void ClearRow(int row);
	/// Iterate through the board, if a row is filled, slide all rows above it down
	void CheckRowsAndSlide();
	/// Returns True if a row is filled
	bool CheckRowFull(int row);
	/// Prints out a string representation of a row (for debugging)
	void PrintRow(int row) const;
	/// returns the color of cell based on row and col index.
	Color getColor(int row, int col) const;

	~Board();
	Cell* grid[20][10];

	//~Board();
private:
	int numRow;
	int numCol;
	int cellSize;
		
};

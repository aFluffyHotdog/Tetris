#pragma once
#include <vector>
#include <map>
#include "Board.h"
using namespace std;
class Tetromino {
public:
	Tetromino();
	Tetromino(int new_id);
	
	int id;
	bool active;
	int originXPos;
	int originYPos;
	int cellSize;
	int rotationState;
	Color c;
	int originCoordinate;
	map<int, vector<pair<int, int>>> rotationStates;
	std::map<int, std::vector<std::pair<int, int>>> blocks; // The coordinates of each blocks inside a tetromino, relative to where its origin is.

	vector<pair<int, int>> GetBoardCoordinates(); // let me think if it's actually useful to use this function.

	bool CheckCollision(Board& b);

	void Rotate(Board& b);

	void Draw(Board& b);

	void MoveLeft(Board& b);

	void MoveRight(Board& b);

	void MoveDown(Board& b);
	


	
		
};

class Hero : public Tetromino {
public:
	Hero();
	
private:
};

class B_Ricky : public Tetromino {
public:
	B_Ricky();

private:
};
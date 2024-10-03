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
	std::map<int, std::vector<std::pair<int, int>>> blocks; // The coordinates of each blocks inside a tetromino, relative to where its origin is
	void Rotate();

	void Draw(Board& b);

	void MoveLeft(Board& b);

	void MoveRight(Board& b);

	void MoveDown(Board& b);
	


	int originXPos;
	int originYPos; 
	int cellSize;
	int rotationState;
	Color c;
	int originCoordinate;
	map<int, vector<pair<int, int>>> rotationStates;
		
};

class Hero : public Tetromino {
public:
	Hero();
	
private:
};
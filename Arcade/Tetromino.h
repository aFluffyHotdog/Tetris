#pragma once
#include <vector>
#include <map>
#include "Board.h"
using namespace std;
class Tetromino {
public:
	Tetromino();

	int originXPos;
	int originYPos;
	int rotationState;
	Color color;
	/// A mapping of all the rotation states on a 3x3 or 4x4 grid
	map<int, vector<pair<int, int>>> rotationStates;
	/// The coordinates of each blocks inside a tetromino, relative to where its origin is.
	std::map<int, std::vector<std::pair<int, int>>> blocks;

};

// Defining all 7 tetromino types
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

class O_Ricky : public Tetromino {
public:
	O_Ricky();

private:
};

class SmashBoi : public Tetromino {
public:
	SmashBoi();

private:
};

class TeeWee : public Tetromino {
public:
	TeeWee();
};

class Cleveland_Z : public Tetromino {
public:
	Cleveland_Z();
};

class Rhode_Z : public Tetromino {
public:
	Rhode_Z();
};
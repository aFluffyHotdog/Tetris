#pragma once
#include <string>
#include <raylib.h>
#include "board.h"
class Game
{
public:
	Game(int width, int height, std::string title, int targetFPS);
	bool GameShouldClose() const;
	void Tick();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game() noexcept;
private:
	int width;
	int height;
	Board board;
	void Update();
	void Draw();
};
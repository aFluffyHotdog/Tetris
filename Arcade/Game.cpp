#include "Game.h"
#include <random>
#include "raylib.h"

Game::Game() {
	board = Board();
	tetrominoes = {};
}

void Game::Draw() {
	board.Draw(600,1024);
}

void Game::HandleInput() {
	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_LEFT:
		break;
		
	}
}
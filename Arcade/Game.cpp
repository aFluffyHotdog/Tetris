#include "Game.h"
#include <raylib.h>
#include <string>
#include <assert.h>
#include "Board.h"

Game::Game(int width, int height,std::string title, int targetFPS) 

{
	assert(!IsWindowReady()); // Assertion triggered if window is already opened.
	SetTargetFPS(targetFPS);
	InitWindow(width, height, title.c_str());
}
Game::~Game() {
	// assert(!GetWindowHandle()); // Triggered if window is already closed.
	CloseWindow();
}
bool Game::GameShouldClose() const {
	return WindowShouldClose();
}

void Game::Tick() {
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::Update() {

}

void Game::Draw() {
	ClearBackground(RAYWHITE);
	DrawRectangleLines(50, 50, 50, 50, RED);
}
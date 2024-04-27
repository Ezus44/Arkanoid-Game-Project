#pragma once
#include <string>

namespace SnakeGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 40.f;
	const float APPLE_SIZE = 40.f;
	const int MIN_APPLES = 10;
	const int MAX_APPLES = 30;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 800;
	const unsigned int APPLES_GRID_CELLS_HORIZONTAL = 20;
	const unsigned int APPLES_GRID_CELLS_VERTICAL = 20;
	const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
	const float cellSizeY = (float)SCREEN_HEIGHT / APPLES_GRID_CELLS_VERTICAL;

	const int MAX_RECORDS_TABLE_SIZE = 10;
	const int GAME_OVER_RECORDS_TABLE_SIZE = 5;
}

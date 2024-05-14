#pragma once
#include <string>

namespace Arkanoid
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 40.f;
	const float BALL_RADIUS = 10.f;
	const float INITIAL_SPEED = 200.f;
	const float CORRECTION_FACTOR = 0.5f;
	const int MAX_APPLES = 80;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 800;


	const int MAX_RECORDS_TABLE_SIZE = 10;
	const int GAME_OVER_RECORDS_TABLE_SIZE = 5;

	extern const char* PLAYER_NAME;
	const std::string GAME_NAME = "Arkanoid";
}

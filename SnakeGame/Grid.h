#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"



namespace SnakeGame
{
	struct Grid
	{
		Position position;
		bool isEmpty = true;
	};

	void InitEmptyCells(Grid& cell, std::vector<Grid>& emptyCells);
	void InitGrid(std::vector<Grid>& cell);
	void MarkCell(Grid& cell, const Vector2D& objectPosition);
	void UnMarkCell(Grid& cell, const Vector2D& objectPosition);


}
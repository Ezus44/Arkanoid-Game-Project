#include "Grid.h"

namespace SnakeGame
{
	void InitEmptyCells(Grid& cell, std::vector<Grid>& emptyCells)
	{
		if (cell.isEmpty)
		{
			emptyCells.push_back(cell);
		}
	}

	void InitGrid(std::vector<Grid>& grid)
	{
		for (float x = cellSizeX / 2.f; x < (float) SCREEN_WIDTH; x += cellSizeX)
		{
			for (float y = cellSizeY / 2.f; y < (float) SCREEN_HEIGHT; y += cellSizeY)
			{
				Grid oneCell;
				oneCell.position.x = x;
				oneCell.position.y = y;
				oneCell.isEmpty = true;
				grid.push_back(oneCell);
			}
		}
	}

	void MarkCell(Grid& cell, const Vector2D& objectPosition)
	{
		if ((cell.position.x == objectPosition.x) && (cell.position.y == objectPosition.y))
		{
			cell.isEmpty = false;
		}
	}

	void UnMarkCell(Grid& cell, const Vector2D& objectPosition)
	{
		if ((cell.position.x == objectPosition.x) && (cell.position.y == objectPosition.y))
		{
			cell.isEmpty = true;
		}
	}
}
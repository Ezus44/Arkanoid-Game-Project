#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
	struct Game;
	struct Rocks
	{
		Position2D position;
		sf::Sprite sprite;
	};
	
	void InitRocks(Rocks& rocks, const Game& game);
	void SetRocksPosition(Rocks& rocks, const Position2D& position);
	Rectangle GetRocksCollider(const Rocks& rocks);
	void DrawRocks(Rocks& rocks, sf::RenderWindow& window);
	
}
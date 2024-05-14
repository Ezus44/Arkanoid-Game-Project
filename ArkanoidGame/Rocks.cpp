#include "Rocks.h"
#include "Game.h"

namespace ApplesGame
{
	void InitRocks(Rocks& rocks, const Game& game)
	{
		rocks.sprite.setTexture(game.rocksTexture);
		SetSpriteSize(rocks.sprite, ROCKS_SIZE, ROCKS_SIZE);
		SetSpriteOrigin(rocks.sprite, 0.5f, 0.5f);
	}

	void SetRocksPosition(Rocks& rocks, const Position2D& position)
	{
		rocks.position = position;
	}

	Rectangle GetRocksCollider(const Rocks& rocks)
	{
		return { { rocks.position.X - ROCKS_SIZE / 2.f, rocks.position.Y - ROCKS_SIZE / 2.f },
					{ ROCKS_SIZE, ROCKS_SIZE } };
	}
	
	void DrawRocks(Rocks& rocks, sf::RenderWindow& window)
	{
		rocks.sprite.setPosition(rocks.position.X, rocks.position.Y);
		window.draw(rocks.sprite);
	}
}
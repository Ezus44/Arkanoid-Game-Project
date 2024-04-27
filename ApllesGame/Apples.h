#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "Grid.h"


namespace ApplesGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void ResetAppleState(Apple& apple, std::vector<Grid>& emptycells);
	void DrawApple(Apple& apple, sf::RenderWindow& window);


}

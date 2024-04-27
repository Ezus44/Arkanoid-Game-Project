#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include <list>

namespace SnakeGame
{
	struct PauseMenuItem
	{
		sf::Text text;
		sf::Text hintText; 
		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;
		bool isEnabled = true;
		
	};

	struct PauseMenu
	{
		PauseMenuItem* selectedItem = nullptr;
	};

	// Links children to parent
	void SelectPauseMenuItem(PauseMenu& pauseMenu, PauseMenuItem* item);
	void DrawPauseMenu(PauseMenu& pauseMenu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
}

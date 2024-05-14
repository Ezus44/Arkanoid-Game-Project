#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"


namespace Arkanoid
{
	
	class GameStateGameOverData
	{
	public:
		void InitGameStateGameOver();
		void HandleGameStateGameOverWindowEvent(const sf::Event& event);
		void UpdateGameStateGameOver(float timeDelta);
		void DrawGameStateGameOver(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;

		// UI data
		sf::Text yourScoreText;
		sf::Text score;
		Menu menu;
		sf::Text recordsText;
		std::vector<sf::Text> recordsTableText;

		sf::RectangleShape windowBackground;

		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;
	};

	
}

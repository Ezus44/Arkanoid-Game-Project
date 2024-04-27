#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"


namespace ApplesGame
{
	struct Game;

	struct GameStateGameOverData
	{
		// Resources
		sf::Font font;

		// UI data
		sf::Text yourScoreText;
		sf::Text score;
		Menu menu;
		MenuItem restartItem;
		MenuItem backToMenuItem;
		sf::Text recordsText;
		std::vector<sf::Text> recordsTableText;

		sf::RectangleShape windowBackground;

		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;
	};

	// Returns pointer to the allocated data
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}

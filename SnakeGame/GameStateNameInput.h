#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateNameInputData
	{
		// Resources
		sf::Font font;
		sf::RectangleShape windowBackground;


		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;

		Menu menu;
		MenuItem yesItem;
		MenuItem noItem;
		MenuItem nameItem;

		sf::String playerName;

		bool isNameEntering = false;
	};

	// Returns pointer to the allocated data
	void InitGameStateNameInput(GameStateNameInputData& data, Game& game);
	void HandleGameStateNameInputWindowEvent(GameStateNameInputData& data, Game& game, const sf::Event& event);
	void UpdateGameStateNameInput(GameStateNameInputData& data, Game& game, float timeDelta);
	void DrawGameStateNameInput(GameStateNameInputData& data, Game& game, sf::RenderWindow& window);
}
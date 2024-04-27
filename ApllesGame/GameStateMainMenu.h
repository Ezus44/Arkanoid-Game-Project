#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem recordsTableItem;
		MenuItem optionsItem;
		MenuItem optionsSound;
		MenuItem optionsMusic;
		MenuItem levelItem;
		MenuItem firstDifficultyItem;
		MenuItem secondDifficultyItem;
		MenuItem thirdDifficultyItem;
		MenuItem fourthDifficultyItem;
		MenuItem fifthDifficultyItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	


		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}

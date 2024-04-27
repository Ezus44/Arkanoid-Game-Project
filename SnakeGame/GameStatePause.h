#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Pause.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePauseData
	{
		sf::Font font;

		PauseMenuItem continueGameItem;
		PauseMenuItem exitGameItem;

		PauseMenu pause;

		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;
	};

	void InitGameStatePause(GameStatePauseData& data, Game& game);
	void HandleGameStatePauseEvent(GameStatePauseData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePause(GameStatePauseData& data, Game& game, float timeDelta);
	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
}

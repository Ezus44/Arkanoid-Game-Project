#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"

namespace Arkanoid
{
	
	class GameStatePauseData
	{
	public:
		void InitGameStatePause();
		void HandleGameStatePauseWindowEvent(const sf::Event& event);
		void UpdateGameStatePause(float timeDelta);
		void DrawGameStatePause(sf::RenderWindow& window);
	
	private:
		sf::Font font;
		sf::SoundBuffer menuBuffer;
		sf::Sound menuSound;

		Menu menu;
	};
}

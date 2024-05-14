#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Ball.h"



namespace Arkanoid
{

	class GameStatePlayingData
	{
	public:
		void InitGameStatePlaying();
		void HandleGameStatePlayingWindowEvent(const sf::Event& event);
		void UpdateGameStatePlaying(float timeDelta);
		void DrawGameStatePlaying(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;
		
		sf::SoundBuffer loseBuffer;
		sf::SoundBuffer hitBuffer;
		sf::Sound loseSound;
		sf::Sound hitSound;
		sf::Music music;

		sf::RectangleShape background;

		// Game data
		Player player;
		Ball ball;
		

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;

		float timeForDelay = 0.f;
		float delay = 0.5f;
	};

}

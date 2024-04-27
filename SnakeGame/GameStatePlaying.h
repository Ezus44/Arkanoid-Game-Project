#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Apples.h"
#include "Player.h"
#include "Grid.h"



namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture headTexture;
		sf::Texture bodyTexture;
		sf::Texture appleTexture;
		sf::Font font;
		
		sf::SoundBuffer loseBuffer;
		sf::SoundBuffer hitBuffer;
		sf::Sound loseSound;
		sf::Sound hitSound;
		sf::Music music;

		sf::RectangleShape background;

		// Game data
		std::vector <Grid> grid;
		std::vector <Grid> emptyCells;

		std::vector<Body> bodies;

		Player player;
		std::vector<Apple> apples;
		

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;

		float timeSinceMoved = 0.f;
		int element = 0;
		float timeForDelay = 0.f;
		PlayerDirection newDirection = PlayerDirection::Up;

		int points = 2;
		float speed = 0.3f;
		int numNewBodies = 1;
		float delay = 0.5f;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}

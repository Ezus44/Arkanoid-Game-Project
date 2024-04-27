#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.headTexture.loadFromFile(RESOURCES_PATH + "Snake_head.png"));
		assert(data.bodyTexture.loadFromFile(RESOURCES_PATH + "Snake_Body.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.loseBuffer.loadFromFile(RESOURCES_PATH + "\\Maodin204__Lose.wav"));
		assert(data.hitBuffer.loadFromFile(RESOURCES_PATH + "\\Owlstorm__Snake_hit.wav"));
		assert(data.music.openFromFile(RESOURCES_PATH + "\\Clinthammer__Background_Music.wav"));

		data.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)); 
		data.background.setFillColor(sf::Color::Cyan);
		data.background.setPosition(0.f, 0.f); 

		data.loseSound.setBuffer(data.loseBuffer);
		data.hitSound.setBuffer(data.hitBuffer);
		data.music.setLoop(true);

		data.grid.clear();

		InitGrid(data.grid);

		data.element = 0;
		data.bodies.clear();
		data.bodies.resize(2);
		for (Body& body : data.bodies)
		{
			InitSnake(data.player, body, data.element, data.headTexture, data.bodyTexture);
			data.element++;
			for (Grid& cell : data.grid)
			{
				MarkCell(cell, body.position);
			}
		}

		data.apples.clear();
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		data.apples.resize(numApples);

		for (Apple& apple : data.apples)
		{
			data.emptyCells.clear();
			for (Grid& cell : data.grid)
			{
				InitEmptyCells(cell, data.emptyCells);
				int i = 0;
			}
			InitApple(apple, data.appleTexture);
			ResetAppleState(apple, data.emptyCells);
			for (Grid& cell : data.grid)
			{
				MarkCell(cell, apple.position);
			}
		}

		game.numEatenApples = 0;

		switch (game.level)
		{
		case DifficultyLevel::Easy:
		{
			data.points = 2;
			data.speed = 0.3f;
			break;
		}
		case DifficultyLevel::NotSoEasy:
		{
			data.points = 4;
			data.speed = 0.25f;
			break;
		}
		case DifficultyLevel::Medium:
		{
			data.points = 6;
			data.speed = 0.2f;
			break;
		}
		case DifficultyLevel::NotSoHard:
		{
			data.points = 8;
			data.speed = 0.15f;
			break;
		}
		case DifficultyLevel::Hard:
		{
			data.points = 10;
			data.speed = 0.1f;
			break;
		}
		}

		if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Music)
		{
			data.music.play();
		}

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);
		data.scoreText.setString("0");

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use WASD to move, P to pause");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 1.f, 0.f }));
		}

		void HandleGameStatePlayingWindowEvent(GameStatePlayingData & data, Game & game, const sf::Event & event)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					PushGameState(game, GameStateType::Pause, false);
				}
			}
		}

		void UpdateGameStatePlaying(GameStatePlayingData & data, Game & game, float timeDelta)
		{

			if (data.timeForDelay < data.delay)
			{
				data.timeForDelay += timeDelta;
			}
			else
			{

				data.timeSinceMoved += timeDelta;


				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (data.bodies[0].direction != PlayerDirection::Down))
				{
					data.newDirection = PlayerDirection::Up;
				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (data.bodies[0].direction != PlayerDirection::Left))
				{
					data.newDirection = PlayerDirection::Right;
				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (data.bodies[0].direction != PlayerDirection::Up))
				{
					data.newDirection = PlayerDirection::Down;
				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (data.bodies[0].direction != PlayerDirection::Right))
				{
					data.newDirection = PlayerDirection::Left;
				}

				// Update player

				if (data.timeSinceMoved >= data.speed)
				{
					for (Body& body : data.bodies)
					{
						for (Grid& cell : data.grid)
						{
							UnMarkCell(cell, body.position);
						}
					}

					data.bodies[0].direction = data.newDirection;
					for (int i = data.element - 1; i > 0; --i)
					{
						UpdateSnakeBody(data.player, data.bodies[i - 1], data.bodies[i]);
					}
					UpdateSnakeHead(data.player, data.bodies[0]);

					for (Body& body : data.bodies)
					{
						for (Grid& cell : data.grid)
						{
							MarkCell(cell, body.position);
						}
					}
					data.timeSinceMoved = 0;
				}




				for (Apple& apple : data.apples)
				{

					if (HasHeadCollisionWithBody(data.bodies[0], apple.position))
					{
						if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Sound)
						{
							data.hitSound.play();
						}
						// Move apple to a new random position
						data.emptyCells.clear();
						for (Grid& cell : data.grid)
						{
							UnMarkCell(cell, apple.position);
							InitEmptyCells(cell, data.emptyCells);
						}
						ResetAppleState(apple, data.emptyCells);
						for (Grid& cell : data.grid)
						{
							MarkCell(cell, apple.position);
						}

						// Increase eaten apples counter
						game.numEatenApples += data.points;

						//Increasing the size of the snake
						for (int i = 0; i < data.numNewBodies; ++i)
						{
							Body newbody;
							AddSnakeElement(data.player, data.bodies[data.element - 1], newbody, data.element, data.bodyTexture);
							data.bodies.push_back(newbody);
							data.element++;
						}

					}
				}

				
				// Check collision with screen border
				for (int i = 1; i <= data.element - 1; ++i)
				{
					if (HasPlayerCollisionWithScreenBorder(data.bodies[0]) || HasHeadCollisionWithBody(data.bodies[0], data.bodies[i].position))
					{
						if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Sound)
						{
							data.loseSound.play();
						}
						

						PushGameState(game, GameStateType::NameInput, false);
					}
				}
			}
		}


	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.background);
		
		// Draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		// Draw player
		for (Body& body : data.bodies)
		{
			DrawPlayer(body, window);
		}

		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);
		data.scoreText.setString(std::to_string(game.numEatenApples));

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}


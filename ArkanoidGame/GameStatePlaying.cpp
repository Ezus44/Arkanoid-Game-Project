#include "GameStatePlaying.h"
#include "Application.h"
#include "Application.h"
#include "Text.h"
#include <assert.h>

namespace Arkanoid
{
	void GameStatePlayingData::InitGameStatePlaying()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(loseBuffer.loadFromFile(RESOURCES_PATH + "Maodin204__Lose.wav"));
		assert(hitBuffer.loadFromFile(RESOURCES_PATH + "Owlstorm__Snake_hit.wav"));
		assert(music.openFromFile(RESOURCES_PATH + "Clinthammer__Background_Music.wav"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)); 
		background.setFillColor(sf::Color::Cyan);
		background.setPosition(0.f, 0.f); 

		loseSound.setBuffer(loseBuffer);
		hitSound.setBuffer(hitBuffer);
		music.setLoop(true);

		// Init player
		player.InitPlayer();
		ball.InitBall();

		

		if (Application::Instance().GetGame().IsEnableOptions(GameOptions::Music)) 
		{
			music.play();
		}

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("0");

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use WASD to move, P to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));
		}

		void GameStatePlayingData::HandleGameStatePlayingWindowEvent(const sf::Event & event)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					Application::Instance().GetGame().PushState(GameStateType::Pause, false);
				}
			}
		}

		void GameStatePlayingData::UpdateGameStatePlaying(float timeDelta)
		{
			if (timeForDelay < delay)
			{
				timeForDelay += timeDelta;
			}
			else
			{
				// Update player
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
					{
						player.SetPlayerDirection(PlayerDirection::Right); 
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
					{ 
						player.SetPlayerDirection(PlayerDirection::Left); 
					}
				
				
					if (player.HasPlayerCollisionWithScreenBorders())
					{
						player.ChangePlayerDirection();
						player.MovePlayer(timeDelta);
					}
					else
					{
						player.MovePlayer(timeDelta);
					}
					// Update ball
					if (ball.HasBallCollisionWithWall())
					{
						hitSound.play();
						ball.HandleWallCollision();
					}
					if (ball.HasBallCollisionWithPlayer(player.GetPlayerPosition()))
					{
						hitSound.play();
						ball.HandlePlayerCollision(player.GetPlayerVelocity());
					}
					ball.MoveBall(timeDelta);
					if (ball.DidBallFall())
					{
						Application::Instance().GetGame().SwitchStateTo(GameStateType::GameOver);
					}

			}
		}


	void GameStatePlayingData::DrawGameStatePlaying(sf::RenderWindow& window)
	{
		window.draw(background);
		
		player.DrawPlayer(window);
		ball.DrawBall(window); 
		 
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}


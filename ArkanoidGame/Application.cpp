
#include "Application.h"
#include <cstdlib>

namespace Arkanoid
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}
	
	Application::Application() :
		window(sf::VideoMode(Arkanoid::SCREEN_WIDTH, Arkanoid::SCREEN_HEIGHT), GAME_NAME)
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	void Application::Run()
	{
		sf::Clock game_clock;
		sf::Time lastTime = game_clock.getElapsedTime();

		// Game loop
		while (window.isOpen())
		{
			game.HandleWindowEvents(window);

			if (!window.isOpen())
			{
				break;
			}

			// Calculate time delta
			sf::Time currentTime = game_clock.getElapsedTime();
			float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
			lastTime = currentTime;
			if (game.Update(timeDelta))
			{
				// Draw everything here
			// Clear the window first
				window.clear();

				game.Draw(window);

				// End the current frame, display window contents on screen
				window.display();
			}
			else
			{
				window.close();
			}
		}
	}
}
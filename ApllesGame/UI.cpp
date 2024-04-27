#include "UI.h"
#include "Game.h"

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& textFont)
	{
		
		// Init texts
		uiState.scoreText.setFont(textFont);
		uiState.scoreText.setCharacterSize(20);
		uiState.scoreText.setFillColor(sf::Color::Blue);
		uiState.scoreText.setPosition(20.f, 10.f);

		uiState.controlsHintText.setFont(textFont);
		uiState.controlsHintText.setCharacterSize(20);
		uiState.controlsHintText.setFillColor(sf::Color::Blue);
		uiState.controlsHintText.setString("Use arrows to move, ESC to exit");
		uiState.controlsHintText.setPosition(SCREEN_WIDTH - uiState.controlsHintText.getGlobalBounds().width - 20.f, 10.f);

		uiState.gameOverText.setFont(textFont);
		uiState.gameOverText.setCharacterSize(100);
		uiState.gameOverText.setFillColor(sf::Color::Blue);
		uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.f - 250.f, SCREEN_HEIGHT / 2.f - 100.f);
		uiState.gameOverText.setString("Game Over");

		uiState.winText.setFont(textFont);
		uiState.winText.setCharacterSize(100);
		uiState.winText.setFillColor(sf::Color::Blue);
		uiState.winText.setPosition(SCREEN_WIDTH / 2.f - 200.f, SCREEN_HEIGHT / 2.f - 100.f);
		uiState.winText.setString("You Win!");

		uiState.gameOverScoreText.setFont(textFont);
		uiState.gameOverScoreText.setCharacterSize(30);
		uiState.gameOverScoreText.setFillColor(sf::Color::Blue);
		uiState.gameOverScoreText.setPosition(SCREEN_WIDTH / 2.f - uiState.controlsHintText.getGlobalBounds().width / 4.f - 25.f, SCREEN_HEIGHT / 2.f + 50.f);

		uiState.menuText.setFont(textFont);
		uiState.menuText.setCharacterSize(20);
		uiState.menuText.setFillColor(sf::Color::Blue);
		uiState.menuText.setString
		("Click 1 to to select a mode with player acceleration, Click 2 to cancel,\nClick 3 to to select a mode with infinite apples, Click 4 to cancel,\nClick Enter to start");
		uiState.menuText.setPosition(20.f, 10.f);

		uiState.accText.setFont(textFont);
		uiState.accText.setCharacterSize(15);
		uiState.accText.setFillColor(sf::Color::Blue);
		uiState.accText.setString
		("You have turned on the acceleration");
		uiState.accText.setPosition(30.f, 90.f);

		uiState.infText.setFont(textFont);
		uiState.infText.setCharacterSize(15);
		uiState.infText.setFillColor(sf::Color::Blue);
		uiState.infText.setString
		("You have turned on the infinite amount of apples");
		uiState.infText.setPosition(30.f, 110.f);

		uiState.tableText.setFont(textFont);
		uiState.tableText.setCharacterSize(15);
		uiState.tableText.setFillColor(sf::Color::Blue);
		uiState.tableText.setString
		("Game records:");
		uiState.tableText.setPosition(50.f, 140.f);


		uiState.playersText.setFont(textFont);
		uiState.playersText.setCharacterSize(15);
		uiState.playersText.setFillColor(sf::Color::Blue);
		uiState.playersText.setPosition(50.f, 180.f);

		uiState.pointsText.setFont(textFont);
		uiState.pointsText.setCharacterSize(15);
		uiState.pointsText.setFillColor(sf::Color::Blue);
		uiState.pointsText.setPosition(150.f, 180.f);

		uiState.pauseText.setFont(textFont);
		uiState.pauseText.setCharacterSize(50);
		uiState.pauseText.setFillColor(sf::Color::Blue);
		uiState.pauseText.setString
		("Do you want to exit?");
	}

	void UpdateGameStateUI(UIState& uiState, const Game& game)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
	}

	void UpdateGameOverStateUI(UIState& uiState, const Game& game)
	{
		uiState.gameOverScoreText.setString("Your score: " + std::to_string(game.numEatenApples));
	}

	void UpdateMenuStateUI(UIState& uiState, const Game& game)
	{
		uiState.playersText.setString(game.allPlayers);
		uiState.pointsText.setString(game.allPoints);
	}

	void DrawMenuUI(const UIState& uiState, const Game& game, sf::RenderWindow& window)
	{
			window.draw(uiState.menuText);
			window.draw(uiState.tableText);

			window.draw(uiState.playersText);
			window.draw(uiState.pointsText);
			if (game.GameSettings & GameSettingsBitMask::AcceleratePlayer)
			{
				window.draw(uiState.accText);
			}
			if (game.GameSettings & GameSettingsBitMask::InifiniteApples)
			{
				window.draw(uiState.infText);
			}
	}

	void DrawPlayingStateUI(const UIState& uiState, sf::RenderWindow& window)
	{
		window.draw(uiState.scoreText);
		window.draw(uiState.controlsHintText);
	}
	void DrawGameOverUI(const UIState& uiState, sf::RenderWindow& window)
	{
		window.draw(uiState.gameOverText);
		window.draw(uiState.gameOverScoreText);
	}

	void DrawWinUI(const UIState& uiState, sf::RenderWindow& window)
	{
		window.draw(uiState.winText);
		window.draw(uiState.gameOverScoreText);
	}

	void DrawPause(UIState& uiState, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
		uiState.pauseText.setPosition(windowSize / 4.f);
		window.draw(uiState.pauseText);
	}
			
}
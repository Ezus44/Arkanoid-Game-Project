#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Game;

	struct UIState
	{
		sf::Text menuText;
		sf::Text accText;
		sf::Text infText;
		sf::Text tableText;
		sf::Text playersText;
		sf::Text pointsText;
		sf::Text scoreText;
		sf::Text controlsHintText;
		sf::Text gameOverText;
		sf::Text winText;
		sf::Text gameOverScoreText;
		sf::Text pauseText;
	};

	void InitUI(UIState& uiState, const sf::Font& textFont);
	void UpdateGameStateUI(UIState& uiState, const Game& game);
	void UpdateGameOverStateUI(UIState& uiState, const Game& game);
	void UpdateMenuStateUI(UIState& uiState, const Game& game);
	void DrawMenuUI(const UIState& uiState, const Game& game, sf::RenderWindow& window);
	void DrawPlayingStateUI(const UIState& uiState, sf::RenderWindow& window);
	void DrawGameOverUI(const UIState& uiState, sf::RenderWindow& window);
	void DrawWinUI(const UIState& uiState, sf::RenderWindow& window);

	void DrawPause(UIState& uiState, Game& game, sf::RenderWindow& window);

}
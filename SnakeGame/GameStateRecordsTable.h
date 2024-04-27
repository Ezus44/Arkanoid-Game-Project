#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	struct Game;

	struct GameStateRecordsTableData
	{
		// Resources
		sf::Font font;

		// UI data
		std::vector <sf::Text> tableText;

	};

	// Returns pointer to the allocated data
	void InitGameStateRecordsTable(GameStateRecordsTableData& data, Game& game);
	void HandleGameStateRecordsTableWindowEvent(GameStateRecordsTableData& data, Game& game, const sf::Event& event);
	void UpdateGameStateRecordsTable(GameStateRecordsTableData& data, Game& game, float timeDelta);
	void DrawGameStateRecordsTable(GameStateRecordsTableData& data, Game& game, sf::RenderWindow& window);
}

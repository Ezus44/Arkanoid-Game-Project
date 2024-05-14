#pragma once
#include <SFML/Graphics.hpp>


namespace Arkanoid
{
	
	class GameStateRecordsTableData
	{
	public:
		void InitGameStateRecordsTable();
		void HandleGameStateRecordsTableWindowEvent(const sf::Event& event);
		void UpdateGameStateRecordsTable(float timeDelta);
		void DrawGameStateRecordsTable(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;

		// UI data
		std::vector <sf::Text> tableText;

	};

	
}

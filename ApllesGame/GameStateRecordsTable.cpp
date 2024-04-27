#include "GameStateRecordsTable.h"
#include <assert.h>
#include <sstream>
#include "Game.h"

namespace ApplesGame
{
	

	void InitGameStateRecordsTable(GameStateRecordsTableData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.tableText.reserve(MAX_RECORDS_TABLE_SIZE);
		std::map <int, std::string> sortedRecordsTable;
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			data.tableText.emplace_back();
			sf::Text& text = data.tableText.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(40);
		}
	}

	void HandleGameStateRecordsTableWindowEvent(GameStateRecordsTableData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateRecordsTable(GameStateRecordsTableData& data,  Game& game, float timeDelta)
	{
		
		

	}

	void DrawGameStateRecordsTable(GameStateRecordsTableData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		std::vector<sf::Text*> textsList;
		textsList.reserve(data.tableText.size());
		for (auto& text : data.tableText)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 3.f, viewSize.y / 3.f };
		DrawItemsList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });
	}
}
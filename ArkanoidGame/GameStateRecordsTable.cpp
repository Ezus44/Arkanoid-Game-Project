#include "GameStateRecordsTable.h"
#include <assert.h>
#include <sstream>
#include "Text.h"
#include "Application.h"

namespace Arkanoid
{
	

	void GameStateRecordsTableData::InitGameStateRecordsTable()
	{
		Game& game = Application::Instance().GetGame();
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		tableText.reserve(MAX_RECORDS_TABLE_SIZE);
		std::map <int, std::string> sortedRecordsTable;
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			tableText.emplace_back();
			sf::Text& text = tableText.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(40);
		}
	}

	void GameStateRecordsTableData::HandleGameStateRecordsTableWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				Application::Instance().GetGame().PopState();
			}
		}
	}

	void GameStateRecordsTableData::UpdateGameStateRecordsTable(float timeDelta)
	{
		
		

	}

	void GameStateRecordsTableData::DrawGameStateRecordsTable(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		std::vector<sf::Text*> textsList;
		textsList.reserve(tableText.size());
		for (auto& text : tableText)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 3.f, viewSize.y / 3.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });
	}
}
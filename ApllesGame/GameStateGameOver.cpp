#include "GameStateGameOver.h"
#include <assert.h>
#include <sstream>
#include "Game.h"

namespace ApplesGame
{

	void InitGameStateGameOver(GameStateGameOverData& data,  Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.menuBuffer.loadFromFile(RESOURCES_PATH + "\\Theevilsocks__menu-hover.wav"));
		data.menuSound.setBuffer(data.menuBuffer);

		data.windowBackground.setFillColor(sf::Color::Black);

		data.yourScoreText.setFont(data.font);
		data.yourScoreText.setCharacterSize(24);
		data.yourScoreText.setStyle(sf::Text::Bold);
		data.yourScoreText.setFillColor(sf::Color::Red);
		data.yourScoreText.setString("YOUR SCORE");
		data.yourScoreText.setOrigin(GetItemOrigin(data.yourScoreText, { 0.5f, 0.5f }));

		data.score.setFont(data.font);
		data.score.setCharacterSize(24);
		data.score.setStyle(sf::Text::Bold);
		data.score.setFillColor(sf::Color::Red);
		data.score.setOrigin(GetItemOrigin(data.score, { 0.5f, 0.5f }));

		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.restartItem);
		data.menu.rootItem.children.push_back(&data.backToMenuItem);

		data.restartItem.text.setFont(data.font);
		data.restartItem.text.setCharacterSize(48);
		data.restartItem.text.setString("Play");
		
		data.backToMenuItem.text.setFont(data.font);
		data.backToMenuItem.text.setCharacterSize(48);
		data.backToMenuItem.text.setString("Back to menu");
	
		data.recordsText.setFont(data.font);
		data.recordsText.setCharacterSize(24);
		data.recordsText.setFillColor(sf::Color::White);
		data.recordsText.setString("Records: ");
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 1.f }));

		

		data.recordsTableText.reserve(GAME_OVER_RECORDS_TABLE_SIZE);
		std::multimap <int, std::string> sortedRecordsTable;
		for (const auto& item : game.recordsTable)
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isPlayerInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < GAME_OVER_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			data.recordsTableText.emplace_back();
			sf::Text& text = data.recordsTableText.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(data.font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);

			if (it->second == game.playerName)
			{
				isPlayerInTable = true;
			}
			
		}

		if(!isPlayerInTable)
		{
			sf::Text& text = data.recordsTableText.back();
			std::stringstream sstream;
			sstream << GAME_OVER_RECORDS_TABLE_SIZE << ". " << game.playerName << ": ";
		}


		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.restartItem);
	}


	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		
			if (!data.menu.selectedItem)
			{
				return;
			}


			if (event.type == sf::Event::KeyPressed)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Sound)
				{
					data.menuSound.play();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (data.menu.selectedItem == &data.restartItem)
					{
						SwitchGameState(game, GameStateType::Playing);
					}
					else if (data.menu.selectedItem == &data.backToMenuItem)
					{
						SwitchGameState(game, GameStateType::MainMenu);
					}
				}


				Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
				if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
					orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
				{
					SelectPreviousMenuItem(data.menu);
				}
				else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
					orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
				{
					SelectNextMenuItem(data.menu);
				}
			}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{
		
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.windowBackground.setSize(sf::Vector2f(viewSize.x / 2.f, viewSize.y));
		data.windowBackground.setPosition(viewSize.x / 4.f, 0.f);
		window.draw(data.windowBackground);


		data.yourScoreText.setPosition(viewSize.x / 2.f, viewSize.y / 3.f);	
		window.draw(data.yourScoreText);
		
		data.score.setPosition(viewSize.x / 2.f, viewSize.y / 3.f + 40.f);
		window.draw(data.score);

		DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y- 200.f }, { 0.5f, 0.f });

		data.recordsText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f );
		window.draw(data.recordsText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(data.recordsTableText.size());
		for (auto& text : data.recordsTableText)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f  + 20.f};
		DrawItemsList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });
		
		
		
		
	}
}

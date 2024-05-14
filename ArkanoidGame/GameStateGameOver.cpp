#include "GameStateGameOver.h"
#include <assert.h>
#include <sstream>
#include "Application.h"

namespace Arkanoid
{
	const char* PLAYER_NAME = "Player";

	void GameStateGameOverData::InitGameStateGameOver()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(menuBuffer.loadFromFile(RESOURCES_PATH + "\\Theevilsocks__menu-hover.wav"));
		menuSound.setBuffer(menuBuffer);

		windowBackground.setFillColor(sf::Color::Black);

		yourScoreText.setFont(font);
		yourScoreText.setCharacterSize(24);
		yourScoreText.setStyle(sf::Text::Bold);
		yourScoreText.setFillColor(sf::Color::Red);
		yourScoreText.setString("YOUR SCORE");
		yourScoreText.setOrigin(GetTextOrigin(yourScoreText, { 0.5f, 0.5f }));

		score.setFont(font);
		score.setCharacterSize(24);
		score.setStyle(sf::Text::Bold);
		score.setFillColor(sf::Color::Red);
		score.setOrigin(GetTextOrigin(score, { 0.5f, 0.5f }));

		MenuItem restart;
		restart.SetTextParameters(font, "Play", 48); 
		restart.onPressCallback = [](MenuItem&)
		{
			Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
		};
		MenuItem backToMenu; 
		backToMenu.SetTextParameters(font, "Back to menu", 48); 
		backToMenu.onPressCallback = [](MenuItem&)
		{
			Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
		};
		MenuItem gameOverMenu;
		gameOverMenu.SetChildrenParameters(Orientation::Vertical, Alignment::Middle, 10.f);
		gameOverMenu.AddChild(restart);
		gameOverMenu.AddChild(backToMenu);
		menu.Init(gameOverMenu);

		recordsText.setFont(font);
		recordsText.setCharacterSize(24);
		recordsText.setFillColor(sf::Color::White);
		recordsText.setString("Records: ");
		recordsText.setOrigin(GetTextOrigin(recordsText, { 0.5f, 1.f }));

		

		recordsTableText.reserve(GAME_OVER_RECORDS_TABLE_SIZE);
		std::multimap <int, std::string> sortedRecordsTable;
		Game& game = Application::Instance().GetGame();
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isPlayerInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < GAME_OVER_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			recordsTableText.emplace_back();
			sf::Text& text = recordsTableText.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);

			if (it->second == PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isPlayerInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
			
		}

		if(!isPlayerInTable)
		{
			sf::Text& text = recordsTableText.back();
			std::stringstream sstream;
			int playerScores = game.GetRecordByPlayerId(PLAYER_NAME);
			sstream << GAME_OVER_RECORDS_TABLE_SIZE << ". " << PLAYER_NAME << ": " << playerScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

	}


	void GameStateGameOverData::HandleGameStateGameOverWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (Application::Instance().GetGame().IsEnableOptions(GameOptions::Sound))
			{
				menuSound.play();
			}
			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}
		}


		Orientation orientation = menu.GetCurrentContext().GetChildrenOrientation(); 
		if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W || 
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A) 
		{
			menu.SwitchToPreviousItem(); 
		}
		else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
		{
			menu.SwitchToNextItem(); 
		}
			
	}

	void GameStateGameOverData::UpdateGameStateGameOver(float timeDelta)
	{
		
	}

	void GameStateGameOverData::DrawGameStateGameOver(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		windowBackground.setSize(sf::Vector2f(viewSize.x / 2.f, viewSize.y));
		windowBackground.setPosition(viewSize.x / 4.f, 0.f);
		window.draw(windowBackground);


		yourScoreText.setPosition(viewSize.x / 2.f, viewSize.y / 3.f);	
		window.draw(yourScoreText);
		
		score.setPosition(viewSize.x / 2.f, viewSize.y / 3.f + 40.f);
		window.draw(score);

		menu.Draw(window, { viewSize.x / 2.f, viewSize.y- 200.f }, { 0.5f, 0.f });

		recordsText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f );
		window.draw(recordsText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableText.size());
		for (auto& text : recordsTableText)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f  + 20.f};
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });
		
		
		
		
	}
}

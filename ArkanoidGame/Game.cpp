#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePause.h"
#include "GameStateMainMenu.h"
#include "GameStateRecordsTable.h"


namespace Arkanoid
{
	

	void GameState::SetExclusivelyVisible(bool isVisible) 
	{
		exclusivelyVisible = isVisible;
	}
	
	Game::Game()
	{
		recordsTable =
		{
		{ "Bill", MAX_APPLES },
		{ "Bobby", MAX_APPLES * 2 },
		{ "Jasmine", MAX_APPLES * 4 },
		{ "James", MAX_APPLES * 5 },
		{ "Peter", MAX_APPLES / 2 },
		{ "Eric", MAX_APPLES / 3 },
		{ "Rose", MAX_APPLES / 5 },
		{ "Kendrick", MAX_APPLES / 6 },
		{ "Marshall", MAX_APPLES * 6 },
		{ "Hailey", MAX_APPLES * 7 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}
	
	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (!stateStack.empty())
			{
				stateStack.back()->HandleWindowEventGameState(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			
			stateStack.clear();
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			
			if (!stateStack.empty())
			{
				stateStack.pop_back();
			}
		}

		
		if (pendingGameStateType != GameStateType::None)
		{
			std::unique_ptr<GameState> newState = std::make_unique<GameState>(pendingGameStateType);
			newState->SetExclusivelyVisible(pendingGameStateIsExclusivelyVisible);
			stateStack.push_back(std::move(newState));
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		
		if (!stateStack.empty())
		{
			stateStack.back()->UpdateGameState(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		std::vector<GameState*> visibleGameStates; 
		for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
		{

			visibleGameStates.push_back(it->get());  
			if ((*it)->IsExclusivelyVisible())
			{
				break;
			}
		}
		for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
		{
			(*it)->DrawGameState(window);
		}
	}

	void Game::Shutdown()
	{
		stateStack.clear();

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}
	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}

	GameState::GameState(GameStateType newType)
	{
		type = newType;
		switch (type)
		{
		case GameStateType::MainMenu:
			data = new GameStateMainMenuData();
			static_cast<GameStateMainMenuData*>(data)->InitGameStateMainMenu();
			break;
		case GameStateType::Playing:
			data = new GameStatePlayingData();
			static_cast<GameStatePlayingData*>(data)->InitGameStatePlaying();
			break;
		case GameStateType::GameOver:
			data = new GameStateGameOverData();
			static_cast<GameStateGameOverData*>(data)->InitGameStateGameOver();
			break;
		case GameStateType::Pause:
			data = new GameStatePauseData();
			static_cast<GameStatePauseData*>(data)->InitGameStatePause();
			break;
		case GameStateType::RecordsTable:
			data = new GameStateRecordsTableData();
			static_cast<GameStateRecordsTableData*>(data)->InitGameStateRecordsTable();
			break;
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	GameState::~GameState()
	{
		switch (type)
		{
		case GameStateType::MainMenu:
			delete static_cast<GameStateMainMenuData*>(data);
			break;
		case GameStateType::Playing:
			delete static_cast<GameStatePlayingData*>(data);
			break;
		case GameStateType::GameOver:
			delete static_cast<GameStateGameOverData*>(data);
			break;
		case GameStateType::Pause:
			delete static_cast<GameStatePauseData*>(data);
			break;
		case GameStateType::RecordsTable:
			delete static_cast<GameStateRecordsTableData*>(data);
			break;
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}

		data = nullptr;
	}

	void GameState::HandleWindowEventGameState(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			static_cast<GameStateMainMenuData*>(data)->HandleGameStateMainMenuWindowEvent(event);
			break;
		}
		case GameStateType::Playing:
		{
			static_cast<GameStatePlayingData*>(data)->HandleGameStatePlayingWindowEvent(event);
			break;
		}
		case GameStateType::GameOver:
		{
			static_cast<GameStateGameOverData*>(data)->HandleGameStateGameOverWindowEvent(event);
			break;
		}
		case GameStateType::Pause:
		{
			static_cast<GameStatePauseData*>(data)->HandleGameStatePauseWindowEvent(event);
			break;
		}
		case GameStateType::RecordsTable:
		{
			static_cast<GameStateRecordsTableData*>(data)->HandleGameStateRecordsTableWindowEvent(event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::UpdateGameState(float timeDelta)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			static_cast<GameStateMainMenuData*>(data)->UpdateGameStateMainMenu(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			static_cast<GameStatePlayingData*>(data)->UpdateGameStatePlaying(timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			static_cast<GameStateGameOverData*>(data)->UpdateGameStateGameOver(timeDelta);
			break;
		}
		case GameStateType::Pause:
		{
			static_cast<GameStatePauseData*>(data)->UpdateGameStatePause(timeDelta);
			break;
		}
		case GameStateType::RecordsTable:
		{
			static_cast<GameStateRecordsTableData*>(data)->UpdateGameStateRecordsTable(timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::DrawGameState(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			static_cast<GameStateMainMenuData*>(data)->DrawGameStateMainMenu(window);
			break;
		}
		case GameStateType::Playing:
		{
			static_cast<GameStatePlayingData*>(data)->DrawGameStatePlaying(window);
			break;
		}
		case GameStateType::GameOver:
		{
			static_cast<GameStateGameOverData*>(data)->DrawGameStateGameOver(window);
			break;
		}
		case GameStateType::Pause:
		{
			static_cast<GameStatePauseData*>(data)->DrawGameStatePause(window);
			break;
		}
		case GameStateType::RecordsTable:
		{
			static_cast<GameStateRecordsTableData*>(data)->DrawGameStateRecordsTable(window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}


}

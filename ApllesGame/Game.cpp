#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePause.h"
#include "GameStateMainMenu.h"
#include "GameStateRecordsTable.h"
#include "GameStateNameInput.h"


namespace ApplesGame
{

	void InitGame(Game& game)
	{
		game.recordsTable =
		{
		{ "XYZ", MAX_APPLES },
		{ "XYZ", MAX_APPLES * 2 },
		{ "XYZ", MAX_APPLES * 4 },
		{ "XYZ", MAX_APPLES * 5 },
		{ "XYZ", MAX_APPLES / 2 },
		{ "XYZ", MAX_APPLES / 3 },
		{ "XYZ", MAX_APPLES / 4 },
		{ "XYZ", MAX_APPLES / 5 },
		{ "XYZ", MAX_APPLES * 6 },
		{ "XYZ", MAX_APPLES * 7 },
		};

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		sf::String playerName;
		while (window.pollEvent(event))
		{
			
		
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}

	bool UpdateGame(Game& game, float timeDelta)
	{
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), timeDelta);
			return true;
		}

		return false;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}

	void ShutdownGame(Game& game)
	{
		// Shutdown all game states
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case GameStateType::Pause:
		{
			state.data = new GameStatePauseData();
			InitGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case GameStateType::RecordsTable:
		{
			state.data = new GameStateRecordsTableData();
			InitGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game);
			break;
		}
		case GameStateType::NameInput:
		{
			state.data = new GameStateNameInputData();
			InitGameStateNameInput(*(GameStateNameInputData*)state.data, game);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::Pause:
		{
			delete (GameStatePauseData*)state.data;
			break;
		}
		case GameStateType::RecordsTable:
		{
			delete (GameStateRecordsTableData*)state.data;
			break;
		}
		case GameStateType::NameInput:
		{
			delete (GameStateNameInputData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}

		state.data = nullptr;
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::Pause:
		{
			HandleGameStatePauseEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}
		case GameStateType::RecordsTable:
		{
			HandleGameStateRecordsTableWindowEvent(*(GameStateRecordsTableData*)state.data, game, event); 
			break;
		}
		case GameStateType::NameInput:
		{
			HandleGameStateNameInputWindowEvent(*(GameStateNameInputData*)state.data, game, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void UpdateGameState(Game& game, GameState& state, float timeDelta)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Pause:
		{
			UpdateGameStatePause(*(GameStatePauseData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::RecordsTable:
		{
			UpdateGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::NameInput:
		{
			UpdateGameStateNameInput(*(GameStateNameInputData*)state.data, game, timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::Pause:
		{
			DrawGameStatePause(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case GameStateType::RecordsTable:
		{
			DrawGameStateRecordsTable(*(GameStateRecordsTableData*)state.data, game, window);
			break;
		}
		case GameStateType::NameInput:
		{
			DrawGameStateNameInput(*(GameStateNameInputData*)state.data, game, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

}

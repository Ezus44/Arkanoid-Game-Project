#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"


namespace ApplesGame
{
	enum class GameOptions : std::uint8_t
	{
		Sound = 1 << 0,
		Music = 1 << 1,
		Default = Sound | Music,
		Empty = 0,
	};

	enum class DifficultyLevel
	{
		Easy,
		NotSoEasy,
		Medium,
		NotSoHard,
		Hard,
	};


	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		RecordsTable,
		NameInput,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch,
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		int numEatenApples = 0;
		std::unordered_multimap < std::string, int> recordsTable;
		std::string playerName = "XYZ";
		GameOptions options = GameOptions::Default;
		DifficultyLevel level = DifficultyLevel::Easy;
	};


	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float timeDelta); // Return false if game should be closed
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float timeDelta);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}
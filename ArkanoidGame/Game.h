#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "Math.h"
#include <memory>


namespace Arkanoid
{
	enum class GameOptions : std::uint8_t
	{
		Sound = 1 << 0,
		Music = 1 << 1,
		Default = Sound | Music,
		Empty = 0,
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		RecordsTable,
	};

	class GameState
	{
	public:
		GameState(GameStateType newType);
		~GameState();
		
		bool IsExclusivelyVisible() const { return exclusivelyVisible; } 
		void SetExclusivelyVisible(bool isVisible);

		
		void HandleWindowEventGameState(sf::Event& event);
		void UpdateGameState(float timeDelta);
		void DrawGameState(sf::RenderWindow& window);
	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool exclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch,
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopState();

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);

	private:
		std::vector<std::unique_ptr<GameState>> stateStack; 
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
	};


}
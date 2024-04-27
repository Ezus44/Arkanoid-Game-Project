#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.menuBuffer.loadFromFile(RESOURCES_PATH + "\\Theevilsocks__menu-hover.wav"));
		data.menuSound.setBuffer(data.menuBuffer);

		auto setTextParameters = [&data](sf::Text& itemText, const std::string& title, int fontSize, sf::Color color = sf::Color::Transparent) {
			itemText.setString(title);
			itemText.setFont(data.font);
			itemText.setCharacterSize(fontSize);
			if (color != sf::Color::Transparent)
			{
				itemText.setFillColor(color);
			}
		};
		setTextParameters(data.menu.rootItem.hintText, "Apples Game", 48, sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.recordsTableItem);
		data.menu.rootItem.children.push_back(&data.levelItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParameters(data.startGameItem.text, "Start Game", 24);
		setTextParameters(data.recordsTableItem.text, "Records Table", 24);
		setTextParameters(data.optionsItem.text, "Options", 24);
		setTextParameters(data.optionsItem.hintText, "Options", 48, sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsSound);
		data.optionsItem.children.push_back(&data.optionsMusic);

		setTextParameters(data.optionsSound.text, "Sound: On/Off", 24);
		setTextParameters(data.optionsMusic.text, "Music: On/Off", 24);
		setTextParameters(data.levelItem.text, "Difficulty level", 24);
		setTextParameters(data.levelItem.hintText, "You have chosen the difficulty level : \n Easy", 40, sf::Color::Red);
		data.levelItem.childrenOrientation = Orientation::Vertical;
		data.levelItem.childrenAlignment = Alignment::Middle;
		data.levelItem.childrenSpacing = 10.f;
		data.levelItem.children.push_back(&data.firstDifficultyItem);
		data.levelItem.children.push_back(&data.secondDifficultyItem);
		data.levelItem.children.push_back(&data.thirdDifficultyItem);
		data.levelItem.children.push_back(&data.fourthDifficultyItem);
		data.levelItem.children.push_back(&data.fifthDifficultyItem);

		setTextParameters(data.firstDifficultyItem.text, "Easy", 24);
		setTextParameters(data.secondDifficultyItem.text, "Not so easy", 24);
		setTextParameters(data.thirdDifficultyItem.text, "Medium", 24);
		setTextParameters(data.fourthDifficultyItem.text, "Not so hard", 24);
		setTextParameters(data.fifthDifficultyItem.text, "Hard", 24);
		setTextParameters(data.exitGameItem.text, "Exit Game", 24);
		setTextParameters(data.exitGameItem.hintText, "Are you sure?", 48, sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		setTextParameters(data.yesItem.text, "Yes", 24);
		setTextParameters(data.noItem.text, "No", 24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
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
			if (event.key.code == sf::Keyboard::B)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.recordsTableItem)
				{
					SwitchGameState(game, GameStateType::RecordsTable);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsSound)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Sound);
				}
				else if (data.menu.selectedItem == &data.optionsMusic)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::Music);
				}
				else if (data.menu.selectedItem == &data.levelItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.firstDifficultyItem)
				{
					game.level = DifficultyLevel::Easy;
				}
				else if (data.menu.selectedItem == &data.secondDifficultyItem)
				{
					game.level = DifficultyLevel::NotSoEasy;
				}
				else if (data.menu.selectedItem == &data.thirdDifficultyItem)
				{
					game.level = DifficultyLevel::Medium;
				}
				else if (data.menu.selectedItem == &data.fourthDifficultyItem)
				{
					game.level = DifficultyLevel::NotSoHard;
				}
				else if (data.menu.selectedItem == &data.fifthDifficultyItem)
				{
					game.level = DifficultyLevel::Hard;
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
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

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		bool isSoundOn = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Sound) != (std::uint8_t)GameOptions::Empty;
		data.optionsSound.text.setString("Sound: " + std::string(isSoundOn ? "On" : "Off"));

		bool isMusicOn = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::Music) != (std::uint8_t)GameOptions::Empty;
		data.optionsMusic.text.setString("Music: " + std::string(isMusicOn ? "On" : "Off"));
		
		
		
		
		switch (game.level)
		{
		case DifficultyLevel::Easy:
		{
			data.levelItem.hintText.setString("You have chosen the difficulty level:\n Easy");
			break;
		}
		case DifficultyLevel::NotSoEasy:
		{
			data.levelItem.hintText.setString("You have chosen the difficulty level:\n Not so easy");
			break;
		}
		case DifficultyLevel::Medium:
		{
			data.levelItem.hintText.setString("You have chosen the difficulty level:\n Medium");
			break;
		}
		case DifficultyLevel::NotSoHard:
		{
			data.levelItem.hintText.setString("You have chosen the difficulty level:\n Not so hard");
			break;
		}
		case DifficultyLevel::Hard:
		{
			data.levelItem.hintText.setString("You have chosen the difficulty level:\n Hard");
			break;
		}
		}
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

}

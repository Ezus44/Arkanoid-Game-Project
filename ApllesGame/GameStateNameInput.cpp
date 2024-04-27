#include "GameStateNameInput.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateNameInput(GameStateNameInputData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.menuBuffer.loadFromFile(RESOURCES_PATH + "\\Theevilsocks__menu-hover.wav"));
		data.menuSound.setBuffer(data.menuBuffer);

		data.windowBackground.setFillColor(sf::Color::Black);

		data.menu.rootItem.hintText.setString("Do you want to enter your name? ");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(24);
		data.menu.rootItem.hintText.setFillColor(sf::Color::White);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.yesItem);
		data.menu.rootItem.children.push_back(&data.noItem);

		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(48);
		data.noItem.text.setString("No");

		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(48);
		data.yesItem.text.setString("Yes");
		data.yesItem.hintText.setString("Enter your name: ");
		data.yesItem.hintText.setFont(data.font);
		data.yesItem.hintText.setCharacterSize(40);
		data.yesItem.hintText.setFillColor(sf::Color::Red);
		data.yesItem.childrenOrientation = Orientation::Vertical;
		data.yesItem.childrenAlignment = Alignment::Middle;
		data.yesItem.childrenSpacing = 10.f;
		data.yesItem.children.push_back(&data.nameItem);

		data.nameItem.text.setString("");
		data.nameItem.text.setFont(data.font);
		data.nameItem.text.setCharacterSize(24);

		bool isNameEntering = false;

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.noItem);
	}

	void HandleGameStateNameInputWindowEvent(GameStateNameInputData& data, Game& game, const sf::Event& event)
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
				if (data.menu.selectedItem == &data.noItem)
				{
					PushGameState(game, GameStateType::GameOver, false);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					data.isNameEntering = true;
					ExpandSelectedItem(data.menu);

				}
				else if (data.menu.selectedItem == &data.nameItem)
				{
					game.recordsTable.insert(std::pair<std::string, int>(game.playerName, game.numEatenApples));
					PushGameState(game, GameStateType::GameOver, false);
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
		else if ((event.type == sf::Event::TextEntered ) && (data.isNameEntering == true))
		{
			if ((event.text.unicode < 128) && (data.playerName.getSize() < 10))
			{
				data.playerName += event.text.unicode;
				data.nameItem.text.setString(data.playerName);
				game.playerName = data.nameItem.text.getString();
			}
		}
	}
		
	
	
	void UpdateGameStateNameInput(GameStateNameInputData& data, Game& game, float timeDelta)
	{
	}
	void DrawGameStateNameInput(GameStateNameInputData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		data.windowBackground.setSize(sf::Vector2f(viewSize.x / 2.f, viewSize.y));
		data.windowBackground.setPosition(viewSize.x / 4.f, 0.f);
		window.draw(data.windowBackground);
		window.draw(*hintText);
		DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y - 200.f }, { 0.5f, 0.f });
		
	}
}
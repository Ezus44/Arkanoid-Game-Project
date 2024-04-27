#include "GameStatePause.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStatePause(GameStatePauseData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.menuBuffer.loadFromFile(RESOURCES_PATH + "\\Theevilsocks__menu-hover.wav"));
		data.menuSound.setBuffer(data.menuBuffer);
		
		data.continueGameItem.text.setString("Continue game");
		data.continueGameItem.text.setFont(data.font);
		data.continueGameItem.text.setCharacterSize(48);
		data.continueGameItem.text.setStyle(sf::Text::Bold);
		data.continueGameItem.text.setOrigin(GetItemOrigin(data.continueGameItem.text, { 0.5f, 0.5f }));

		data.exitGameItem.text.setString("Back to menu");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(48);
		data.exitGameItem.text.setStyle(sf::Text::Bold);
		data.exitGameItem.text.setOrigin(GetItemOrigin(data.exitGameItem.text, { 0.5f, 0.5f }));

		SelectPauseMenuItem(data.pause, &data.continueGameItem);
	}

	void HandleGameStatePauseEvent(GameStatePauseData& data, Game& game, const sf::Event& event)
	{
		if (!data.pause.selectedItem)
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
				if (data.pause.selectedItem == &data.continueGameItem)
				{
					PopGameState(game);
				}
				else if (data.pause.selectedItem == &data.exitGameItem)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
			}
			if (event.key.code == sf::Keyboard::W)
			{
				SelectPauseMenuItem(data.pause, &data.continueGameItem);
			}
			else if ( event.key.code == sf::Keyboard::S )
			{
				SelectPauseMenuItem(data.pause, &data.exitGameItem);
			}
		}
	}

	void UpdateGameStatePause(GameStatePauseData& data, Game& game, float timeDelta)
	{

	}

	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		data.continueGameItem.text.setPosition(viewSize.x / 2.f, 200.f);
		window.draw(data.continueGameItem.text);

		data.exitGameItem.text.setPosition(viewSize.x / 2.f, 350.f);
		window.draw(data.exitGameItem.text);

	}

}

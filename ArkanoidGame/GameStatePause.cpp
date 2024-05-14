#include "GameStatePause.h"
#include "Application.h"
#include <assert.h>

namespace Arkanoid
{
	void GameStatePauseData::InitGameStatePause()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(menuBuffer.loadFromFile(RESOURCES_PATH + "Theevilsocks__menu-hover.wav"));
		menuSound.setBuffer(menuBuffer);
		
		MenuItem resumeItem;
		resumeItem.SetTextParameters(font, "Return to game", 24, sf::Color::Red);
		resumeItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().PopState();
		};

		MenuItem exitItem;
		exitItem.SetTextParameters(font, "Exit to main menu", 24, sf::Color::Red);
		exitItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
		};

		MenuItem pauseMenu;
		pauseMenu.SetTextParameters(font, "Pause", 48, sf::Color::Red);
		pauseMenu.SetChildrenParameters(Orientation::Vertical, Alignment::Middle, 10.f);
		pauseMenu.AddChild(resumeItem);
		pauseMenu.AddChild(exitItem);

		menu.Init(pauseMenu);
	}

	void GameStatePauseData::HandleGameStatePauseWindowEvent(const sf::Event& event)
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
			Orientation orientation = menu.GetCurrentContext().GetChildrenOrientation();
			if (event.key.code == sf::Keyboard::W) 
			{
				menu.SwitchToPreviousItem();
			}
			else if (event.key.code == sf::Keyboard::S) 
			{
				menu.SwitchToNextItem();
			}
		}
	}

	void GameStatePauseData::UpdateGameStatePause(float timeDelta)
	{

	}

	void GameStatePauseData::DrawGameStatePause(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		menu.Draw(window, window.getView().getCenter(), { 0.5f, 0.f });

	}

}

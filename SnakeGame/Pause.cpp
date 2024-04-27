#include "Pause.h"
#include <assert.h>

namespace SnakeGame
{


	void SelectPauseMenuItem(PauseMenu& pauseMenu, PauseMenuItem* item)
	{
		if (pauseMenu.selectedItem == item)
		{
			return;
		}

		if (item && !item->isEnabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (pauseMenu.selectedItem)
		{
			pauseMenu.selectedItem->text.setFillColor(pauseMenu.selectedItem->deselectedColor);
		}

		pauseMenu.selectedItem = item;

		if (pauseMenu.selectedItem)
		{
			pauseMenu.selectedItem->text.setFillColor(pauseMenu.selectedItem->selectedColor);
		}
	}


	void DrawPauseMenu(PauseMenu& pauseMenu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{

	}

}

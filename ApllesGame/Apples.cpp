#include "Apples.h"
#include <cstdlib>
#include <assert.h>

namespace ApplesGame

{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void ResetAppleState(Apple& apple, std::vector<Grid>& emptycells)
	{
		// init apple state
		int empty = (int) emptycells.size();
		int randPosition = rand() % empty;
		apple.position.x = emptycells[randPosition].position.x;
		apple.position.y = emptycells[randPosition].position.y;
	}


}

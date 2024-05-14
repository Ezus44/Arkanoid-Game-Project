#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct Game;
	struct Sounds
	{
		sf::Sound sound;
	};

	void ApplesSound(Sounds& sounds, const Game& game);

	void DeathSound(Sounds& sounds, const Game& game);
}
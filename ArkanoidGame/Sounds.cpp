#include "Sounds.h"
#include "Game.h"

namespace ApplesGame
{
	void ApplesSound(Sounds& sounds, const Game& game)
	{
		sounds.sound.setBuffer(game.eatingSound);
		sounds.sound.play();
	}
	void DeathSound(Sounds& sounds, const Game& game)
	{
		sounds.sound.setBuffer(game.deathSound);
		sounds.sound.play();
	}
}
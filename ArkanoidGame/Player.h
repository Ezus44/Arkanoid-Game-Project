#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <list>
#include <array>

namespace Arkanoid
{
	enum class PlayerDirection
	{
		Right = 0,
		Left,
	};

	class Player
	{
	public:
		void InitPlayer();
		void MovePlayer(float timeDelta);
		void DrawPlayer(sf::RenderWindow& window);

		bool HasPlayerCollisionWithScreenBorders();
		void ChangePlayerDirection(); 
		const sf::Vector2f& GetPlayerPosition() const { return playerPosition; }
		const sf::Vector2f& GetPlayerVelocity() const;
		sf::Vector2f GetDirectionVector(PlayerDirection direction);
		void SetPlayerDirection(PlayerDirection newDirection);
		const PlayerDirection& GetPlayerDirection() const {return direction;}

	private:
		sf::RectangleShape playerShape;
		sf::Vector2f playerPosition;
		float speed = 0.f; // Pixels per second
		PlayerDirection direction = PlayerDirection::Right;

	};


}

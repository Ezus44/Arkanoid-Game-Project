#include "Player.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"

namespace Arkanoid
{

	void Player::InitPlayer()
	{
		playerPosition = { (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT - PLAYER_SIZE };
		playerShape.setSize(sf::Vector2f(PLAYER_SIZE * 4, PLAYER_SIZE));
		playerShape.setPosition(playerPosition);
		playerShape.setFillColor(sf::Color::Yellow);
		speed = INITIAL_SPEED;
		direction = PlayerDirection::Right;
	}

	void Player::MovePlayer(float timeDelta)
	{
		float shift = speed * timeDelta;
		const sf::Vector2f directionVector = GetDirectionVector(GetPlayerDirection()) * shift / PLAYER_SIZE;
		playerPosition = playerShape.getPosition() + directionVector;
		playerShape.setPosition(playerPosition); 

	}

	void Player::DrawPlayer(sf::RenderWindow& window)
	{
	
		window.draw(playerShape);
	}

	bool Player::HasPlayerCollisionWithScreenBorders()
	{
		if (playerShape.getPosition().x < 0.f || playerShape.getPosition().x >(SCREEN_WIDTH - 4 * PLAYER_SIZE))
		{
			return true;
		}
		return false;
	}

	void Player::ChangePlayerDirection()
	{
		
			if (playerShape.getPosition().x < 0.f)
			{
				direction = PlayerDirection::Right;
			}
			else
			{
				direction = PlayerDirection::Left;
			}
	}


	const sf::Vector2f& Player::GetPlayerVelocity() const
	{
		sf::Vector2f result;

		switch (direction)
		{
		case PlayerDirection::Right:
		{
			result = { speed, 0.f };
			break;
		}
		case PlayerDirection::Left:
		{
			result = { -speed, 0.f };
			break;
		}
		}

		return result;
	}

	sf::Vector2f Player::GetDirectionVector(PlayerDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case PlayerDirection::Right:
		{
			result = { PLAYER_SIZE, 0.f };
			break;
		}
		case PlayerDirection::Left:
		{
			result = { -PLAYER_SIZE, 0.f };
			break;
		}
		}

		return result;
	}
	void Player::SetPlayerDirection(PlayerDirection newDirection)
	{
		direction = newDirection;
	}
}

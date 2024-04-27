#include "Player.h"

namespace SnakeGame
{

	void InitSnake(Player& player, Body& body, int element, const sf::Texture& headTexture, const sf::Texture& bodyTexture)
	{
		// Init player state
		player.timeSinceMove = 0.f;
		body.position.x = player.headPositionX - cellSizeX / 2.f;
		body.position.y = player.headPositionY + cellSizeY * element + cellSizeY / 2.f;
		// Init sprite
		if (element == 0)
		{
			body.sprite.setTexture(headTexture);
		}
		else
		{
			body.sprite.setTexture(bodyTexture);
		}

		body.sprite.setOrigin(GetItemOrigin(body.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		body.sprite.setScale(GetSpriteScale(body.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

	}

	void AddSnakeElement(Player& player, Body& lastBody, Body& newBody, int element, const sf::Texture& bodyTexture)
	{
		
		switch (lastBody.direction)
		{
		case PlayerDirection::Up:
		{
			newBody.position.y = lastBody.position.y + cellSizeY;
			newBody.position.x = lastBody.position.x;
			break;
		}
		case PlayerDirection::Right:
		{
			newBody.position.x = lastBody.position.x - cellSizeX;
			newBody.position.y = lastBody.position.y;
			break;
		}
		case PlayerDirection::Down:
		{
			newBody.position.y = lastBody.position.y - cellSizeY;
			newBody.position.x = lastBody.position.x;
			break;
		}
		case PlayerDirection::Left:
		{
			newBody.position.x = lastBody.position.x + cellSizeX;
			newBody.position.y = lastBody.position.y;
			break;
		}
		}
		// Init sprite
		newBody.direction = lastBody.direction;
		newBody.sprite.setTexture(bodyTexture);

		newBody.sprite.setOrigin(GetItemOrigin(newBody.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		newBody.sprite.setScale(GetSpriteScale(newBody.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

	}

	void UpdateSnakeHead(Player& player, Body& head)
	{
		// Move player
		
		
	
			switch (head.direction)
			{
			case PlayerDirection::Up:
			{
				head.position.y -= cellSizeX;
				break;
			}
			case PlayerDirection::Right:
			{
				head.position.x += cellSizeX;
				break;
			}
			case PlayerDirection::Down:
			{
				head.position.y += cellSizeX;
				break;
			}
			case PlayerDirection::Left:
			{
				head.position.x -= cellSizeX;
				break;
			}
			}

	}


	void UpdateSnakeBody(Player& player, Body& firstBody, Body& secondBody)
	{

		
			if (secondBody.position.x < firstBody.position.x)
			{
				secondBody.position.x += cellSizeX;
			}
			else if (secondBody.position.x > firstBody.position.x)
			{
				secondBody.position.x -= cellSizeX;
			}
	
		
			if (secondBody.position.y < firstBody.position.y)
			{
				secondBody.position.y += cellSizeY;
			}
			else if (secondBody.position.y > firstBody.position.y)
			{
				secondBody.position.y -= cellSizeY;
			}
			
		secondBody.direction = firstBody.direction;
	}

	bool HasPlayerCollisionWithScreenBorder(const Body& body)
	{
		return !IsPointInRect(body.position, { 0.f, 0.f }, { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT });
	}

	bool HasHeadCollisionWithBody(const Body& head, const Vector2D& playerPosition)
	{
		float dx = head.position.x - playerPosition.x;
		float dy = head.position.y - playerPosition.y;
		float distance = sqrt(dx * dx + dy * dy);
		if (distance < PLAYER_SIZE)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
		

	void DrawPlayer(Body& body, sf::RenderWindow& window)
	{
		body.sprite.setPosition(OurVectorToSf(body.position));
		const sf::Vector2f spriteScale = (GetSpriteScale(body.sprite, { PLAYER_SIZE, PLAYER_SIZE }));
	

		// We need to rotate and flip sprite to match player direction
		switch (body.direction)
		{
		case PlayerDirection::Up:
		{
			body.sprite.setScale(spriteScale.x, spriteScale.y);
			body.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			body.sprite.setScale(spriteScale.x, spriteScale.y);
			body.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			body.sprite.setScale(spriteScale.x, spriteScale.y);
			body.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			body.sprite.setScale(-spriteScale.x, spriteScale.y);
			body.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(body.sprite);
	}
}

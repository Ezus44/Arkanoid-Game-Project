#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"
#include <set>

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	
	struct Body
	{
		Position position;
		sf::Sprite sprite;
		PlayerDirection direction = PlayerDirection::Up;
	};



	struct Player
	{
		float timeSinceMove = 0;
		float speed = cellSizeX / 0.2f;
		float headPositionX = (float)SCREEN_WIDTH / 2.f;
		float headPositionY = (float)SCREEN_HEIGHT / 2.f;
	};


	void InitSnake(Player& player, Body& body, int element, const sf::Texture& headTexture, const sf::Texture& bodyTexture);
	void AddSnakeElement(Player& player, Body& lastBody, Body& newBody, int element, const sf::Texture& bodyTexture);
	void UpdateSnakeHead(Player& player, Body& head);
	void UpdateSnakeBody(Player& player, Body& firstBody, Body& secondBody);

	bool HasPlayerCollisionWithScreenBorder(const Body& body);
	bool HasHeadCollisionWithBody(const Body& head, const Vector2D& playerPosition);

	void DrawPlayer(Body& body, sf::RenderWindow& window);
}
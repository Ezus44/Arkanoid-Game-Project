#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <list>
#include <array>
#include <cmath>

namespace Arkanoid
{
	class Ball
	{
    public:
        
        void InitBall();

		void MoveBall(float timeDelta);
		bool HasBallCollisionWithWall();
		void HandleWallCollision();
		bool HasBallCollisionWithPlayer(const sf::Vector2f& platformPosition);
		void HandlePlayerCollision(const sf::Vector2f& platformVelocity);
		
		float GetVectorLength(sf::Vector2f vector);
		bool DidBallFall();
        void DrawBall(sf::RenderWindow& window);

	private:
		sf::CircleShape ballShape;
		sf::Vector2f position;
		sf::Vector2f speed;
		float decayFactor;
		float decayDelay;
		float timeForDecayDelay;
	};
}
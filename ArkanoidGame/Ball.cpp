#include "Ball.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"


namespace Arkanoid
{

	Ball::Ball()
	{
        position = { (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f };
        speed = { 0.f, INITIAL_SPEED };
        decayFactor = 0.99f;
        decayDelay = 1.f;
        timeForDecayDelay = 0.f;
        ballShape.setRadius(BALL_RADIUS);
		ballShape.setPosition(position);
		ballShape.setFillColor(sf::Color::Red);
	}
    
	void Ball::MoveBall(float timeDelta)
	{

		sf::Vector2f displacement = speed * timeDelta;
		position = position + displacement; 
		ballShape.setPosition(position);

        if (timeForDecayDelay < decayDelay)
        {
            timeForDecayDelay += timeDelta;
        }
        else
        {
            speed *= decayFactor;
            timeForDecayDelay = 0.f;
        }
            
	}

    bool Ball::HasBallCollisionWithWall()
    {
        if ((position.x - BALL_RADIUS < 0) || (position.x + BALL_RADIUS > SCREEN_WIDTH) || (position.y - BALL_RADIUS < 0))
        {
            return true;
        }
        return false;
    }

    void Ball::HandleWallCollision() 
    {
        if (position.x - BALL_RADIUS < 0) 
        {
            speed.x = std::abs(speed.x); 
            
        }
        else if (position.x + BALL_RADIUS > SCREEN_WIDTH) 
        {
            speed.x = -std::abs(speed.x); 
          
        }

        
        if (position.y - BALL_RADIUS < 0) 
        {
            speed.y = std::abs(speed.y); 
           
        }
    }

    bool Ball::HasBallCollisionWithPlayer(const sf::Vector2f& platformPosition)
    {
        if (position.y + BALL_RADIUS >= platformPosition.y &&
            position.x + BALL_RADIUS >= platformPosition.x &&
            position.x - BALL_RADIUS <= platformPosition.x + 4 * PLAYER_SIZE)
        {
			return true;
        }
        return false;
    }

    void Ball::HandlePlayerCollision(const sf::Vector2f& platformVelocity)
    {
            speed.y = -std::abs(speed.y);

            // Ball speed corrector depending on platform speed
            speed.x += platformVelocity.x * CORRECTION_FACTOR;
    }

    float Ball::GetVectorLength(sf::Vector2f vector)
    {
        return sqrtf(vector.x * vector.x + vector.y * vector.y);
    }

    bool Ball::DidBallFall()
    {
        if (position.y + BALL_RADIUS > SCREEN_HEIGHT)
        {
            return true;

        }
        return false;
    }

	void Ball::DrawBall(sf::RenderWindow& window) 
	{
		window.draw(ballShape);
	}
}
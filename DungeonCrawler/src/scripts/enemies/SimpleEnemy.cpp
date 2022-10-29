#include "SimpleEnemy.h"

SimpleEnemy::SimpleEnemy()
{
}

SimpleEnemy::~SimpleEnemy()
{
}

void SimpleEnemy::start()
{
}

void SimpleEnemy::update()
{
	timeSincePositionChange += Time::getDeltaTime();

	if (timeSincePositionChange > timeBetweenPositionChanges)
	{
		findNewPosition();
		timeSincePositionChange = 0.0f;
	}

	glm::vec2 newPosition{ Math::move(transform->getPosition(), targetPosition, 1.0f) };
	glm::vec2 move{ glm::normalize(newPosition - transform->getPosition()) };
	transform->setPosition(newPosition);


	float angle{ glm::degrees(glm::angle(move, glm::vec2(1.0f, 0.0f))) * glm::sign(move.y) };
	AnimationHandler::setAnimationWebParameter("enemy_sprite", "up_right", angle > 0.0f && angle <= 90.0f);
	AnimationHandler::setAnimationWebParameter("enemy_sprite", "up_left", angle > 90.0f && angle <= 180.0f);
	AnimationHandler::setAnimationWebParameter("enemy_sprite", "down_right", angle > -90.0f && angle <= 0.0f);
	AnimationHandler::setAnimationWebParameter("enemy_sprite", "down_left", angle >= -180.0f && angle <= -90.0f);
}

void SimpleEnemy::findNewPosition()
{
	float x{ Random::between(-6.0f, 6.0f) };
	float y{ Random::between(-3.5f, 3.5f) };

	targetPosition = glm::vec2(x, y);
}

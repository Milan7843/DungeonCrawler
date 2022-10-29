#pragma once

#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/colliders/BoxCollider.h>

#include <Root/Math.h>
#include <glm/gtx/vector_angle.hpp>
#include <Root/Random.h>

class SimpleEnemy : public Component
{
public:
	SimpleEnemy();
	~SimpleEnemy();

	void start() override;

	void update() override;

	void findNewPosition();

private:
	float timeBetweenPositionChanges{ 2.0f };
	float timeSincePositionChange{ 0.0f };

	glm::vec2 targetPosition;
};

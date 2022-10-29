#pragma once

#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/colliders/BoxCollider.h>

class SimpleEnemy : public Component
{
public:
	SimpleEnemy();
	~SimpleEnemy();

	void start() override;

	void update() override;
};

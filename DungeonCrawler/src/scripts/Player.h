#pragma once

#include "scripts/Bullet.h"

#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/Input.h>

class Player : public Component
{
public:
	Player();
	~Player();

	void start() override;

	void update() override;

private:

	void shoot();

	TransformPointer weapon;
	TransformPointer firePoint;
};


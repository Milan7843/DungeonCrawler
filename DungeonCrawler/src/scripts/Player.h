#pragma once

#include "scripts/Bullet.h"

#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/Input.h>
#include <Root/colliders/Collider.h>
#include <Root/colliders/BoxCollider.h>
#include <Root/components/Rigidbody.h>
#include <Root/Audio.h>

class Player : public Component
{
public:
	Player();
	~Player();

	void start() override;

	void update() override;

private:

	float fireDelay{ 0.1f };
	float timeSinceShot{ fireDelay };

	float playerSpeed{ 2.0f };

	void shoot();

	BoxCollider bulletCollider;

	TransformPointer weapon;
	TransformPointer firePoint;
};


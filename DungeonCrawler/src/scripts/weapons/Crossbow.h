#pragma once

#include "scripts/Bullet.h"

#include <Root/Transform.h>
#include <Root/rendering/SpriteRenderer.h>

#include <Root/Audio.h>

#include <Root/colliders/BoxCollider.h>

#include <Root/animation/SetterValueAnimation.h>
#include <Root/animation/AnimationHandler.h>

#include <Root/animation/animation functions/ClassAnimationFunction.h>

class Crossbow
{
public:
	Crossbow(TransformPointer parent);

	~Crossbow();

	void shoot();

	void spawnArrow();

private:

	TransformPointer transform;
	TransformPointer firePoint;

	ColliderPointer arrowCollider;
};

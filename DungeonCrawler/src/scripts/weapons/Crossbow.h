#pragma once

#include <Root/Transform.h>
#include <Root/rendering/SpriteRenderer.h>

#include <Root/animation/SetterValueAnimation.h>
#include <Root/animation/AnimationHandler.h>

class Crossbow
{
public:
	Crossbow(TransformPointer parent);

	~Crossbow();

	void shoot();

private:

	TransformPointer transform;
};

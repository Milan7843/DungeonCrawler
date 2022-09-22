#pragma once

#include <box2d/box2d.h>

namespace PhysicsEngine
{
	void initialise();

	void setGravity(float x, float y);

	b2Body* addBody(b2BodyDef* definition);
};



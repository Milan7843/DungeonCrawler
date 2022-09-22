#pragma once

#include "Root/engine/RootEngine.h"

#include <box2d/box2d.h>

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

namespace PhysicsEngine
{
	void initialise();

	void simulate();

	void setGravity(float x, float y);

	b2Body* addBody(b2BodyDef* definition);
};



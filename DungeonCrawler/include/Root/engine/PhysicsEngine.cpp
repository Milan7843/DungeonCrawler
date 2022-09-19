#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	namespace
	{
		float gravity{};

		// Initialise the world without gravity
		b2World world{ b2World(b2Vec2(0.0f, 0.0f)) };
	}

	void initialise()
	{
	}

	void setGravity(float x, float y)
	{
		world.SetGravity(b2Vec2(x, y));
	}
};
#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	namespace
	{
		float gravity{};

		b2World world;
	}

	void initialise()
	{
		// No gravity
		b2Vec2 gravity(0.0f, 0.0f);

		// Initialising the world
		world = b2World(gravity);
	}
};
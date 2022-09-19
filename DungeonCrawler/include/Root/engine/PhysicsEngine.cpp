#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	namespace
	{
		float gravity{};
	}

	void initialise()
	{
		// No gravity
		b2Vec2 gravity(0.0f, 0.0f);

		// Initialising the world
		b2World world = b2World(gravity);
	}
};
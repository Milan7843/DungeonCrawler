#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	namespace
	{
		float gravity{};

		int32 velocityIterations{ 6 };
		int32 positionIterations{ 2 };
		float timeStep{ 1.0f / 60.0f };

		// Initialise the world without gravity
		b2World world{ b2World(b2Vec2(0.0f, 0.0f)) };
	}

	void initialise()
	{
	}

	void simulate()
	{
		while (RootEngine::isPhysicsSimulationActive())
		{
			auto t_start = std::chrono::high_resolution_clock::now();


			const std::clock_t beginTime = clock();

			// Time step here
			world.Step(timeStep, velocityIterations, positionIterations);

			float waitTime = 0.5f - (float(clock() - beginTime) / CLOCKS_PER_SEC);

			int milliseconds = (waitTime * 1000.0f);

			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

			auto t_end = std::chrono::high_resolution_clock::now();
			double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

			//std::cout << elapsed_time_ms << "ms" << std::endl;
		}
	}

	void setGravity(float x, float y)
	{
		world.SetGravity(b2Vec2(x, y));
	}

	b2Body* addBody(b2BodyDef* definition)
	{
		b2Body* body = world.CreateBody(definition);
		return body;
	}
};
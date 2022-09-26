#pragma once

#include "Root/components/Component.h" // Base class
#include "Root/Gradient.h"

#include <glm/glm.hpp>

#include <memory>

#define ParticleSystemPointer std::shared_ptr<ParticleSystem>

class Transform;

struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;
	float aliveTime;
	float lifeTime;
};

enum SimulationSpace
{
	WORLD_SPACE,
	LOCAL_SPACE
};

enum EmissionMode
{
	ARC_EMISSION,
	ORTHOGONAL_EMISSION
};

class ParticleSystem : public Component
{
public:

	static std::shared_ptr<ParticleSystem> create(std::shared_ptr<Transform> transform);

	~ParticleSystem();

	void start() override;

	void update() override;

	void render(float renderDepth) override;

	void play();

	void stop();

	/**
	 * Set the particle size which stays constant over its lifetime.
	 * 
	 * \param size: the particle size.
	 */
	void setConstantSizeOverLifeTime(float size);

	/**
	 * Set the particle size which changes over its lifetime.
	 * The lifetime is normalized to [0, 1].
	 *
	 * \param sizeOverLifeTimeGradient: the particle size gradient.
	 */
	void setSizeOverLifeTimeGradient(Gradient<float> sizeOverLifeTimeGradient);

	/**
	 * Set the particle drag which stays constant over its lifetime.
	 *
	 * \param drag: the drag gradient.
	 */
	void setConstantDragOverLifeTime(float drag);

	/**
	 * Set the particle drag which changes over its lifetime.
	 * The lifetime is normalized to [0, 1].
	 *
	 * \param dragOverLifeTimeGradient: the particle drag gradient.
	 */
	void setDragOverLifeTimeGradient(Gradient<float> dragOverLifeTimeGradient);

	/**
	 * Set the particle color which stays constant over its lifetime.
	 *
	 * \param color: the particle color.
	 */
	void setConstantColorOverLifeTime(glm::vec3 color);

	/**
	 * Set the particle color which changes over its lifetime.
	 * The lifetime is normalized to [0, 1].
	 *
	 * \param color: the particle color gradient.
	 */
	void setColorOverLifeTimeGradient(Gradient<glm::vec3> colorOverLifeTimeGradient);

private:

	ParticleSystem();

	bool looping{ true };
	SimulationSpace simulationSpace { WORLD_SPACE };
	float emissionTime{ 3.0f };

	unsigned int textureID{ 0 };

	EmissionMode emissionMode{ ARC_EMISSION };
	float emissionRadius{ 1.0f };

	glm::vec2 gravity{ 0.0f, -1.0f };
	float minLifeTime{ 1.0f };
	float maxLifeTime{ 1.0f };
	float minRotationEmissionVelocity{ 0.0f };
	float maxRotationEmissionVelocity{ 0.0f };
	float drag{ 0.1f };
	glm::vec2 wind{ 0.0f, 0.0f };

	Gradient<float> sizeOverLifeTimeGradient{ Gradient(1.0f) };
	Gradient<float> dragOverLifeTimeGradient{ Gradient(1.0f) };
	Gradient<glm::vec3> colorOverLifeTimeGradient{ Gradient(glm::vec3(1.0f)) };
};


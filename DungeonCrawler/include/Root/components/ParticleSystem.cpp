#include "ParticleSystem.h"

#include "Root/Transform.h"

std::shared_ptr<ParticleSystem> ParticleSystem::create(std::shared_ptr<Transform> transform)
{
	ParticleSystem* particleSystem = new ParticleSystem();
	std::shared_ptr<ParticleSystem> pointer{ particleSystem };
	transform->addComponent(pointer);
	return pointer;
}

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::start()
{
}

void ParticleSystem::update()
{
}

void ParticleSystem::render(float renderDepth)
{
}

void ParticleSystem::play()
{
}

void ParticleSystem::stop()
{
}

void ParticleSystem::setConstantSizeOverLifeTime(float size)
{
	std::vector<GradientPoint<float>> colorGradientPoints{ { 0.0f, size} };
	this->sizeOverLifeTimeGradient = Gradient<float>(colorGradientPoints);
}

void ParticleSystem::setSizeOverLifeTimeGradient(Gradient<float> sizeOverLifeTimeGradient)
{
	this->sizeOverLifeTimeGradient = sizeOverLifeTimeGradient;
}

void ParticleSystem::setConstantDragOverLifeTime(float drag)
{
	std::vector<GradientPoint<float>> colorGradientPoints{ { 0.0f, drag} };
	this->dragOverLifeTimeGradient = Gradient<float>(colorGradientPoints);
}

void ParticleSystem::setDragOverLifeTimeGradient(Gradient<float> dragOverLifeTimeGradient)
{
	this->dragOverLifeTimeGradient = dragOverLifeTimeGradient;
}

void ParticleSystem::setConstantColorOverLifeTime(glm::vec3 color)
{
	std::vector<GradientPoint<glm::vec3>> colorGradientPoints{{ 0.0f, color}};
	this->colorOverLifeTimeGradient = Gradient<glm::vec3>(colorGradientPoints);
}

void ParticleSystem::setColorOverLifeTimeGradient(Gradient<glm::vec3> colorOverLifeTimeGradient)
{
	this->colorOverLifeTimeGradient = colorOverLifeTimeGradient;
}

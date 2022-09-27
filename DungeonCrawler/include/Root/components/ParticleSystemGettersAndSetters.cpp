#include "ParticleSystem.h"

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
    std::vector<GradientPoint<glm::vec3>> colorGradientPoints{ { 0.0f, color} };
    this->colorOverLifeTimeGradient = Gradient<glm::vec3>(colorGradientPoints);
}

void ParticleSystem::setColorOverLifeTimeGradient(Gradient<glm::vec3> colorOverLifeTimeGradient)
{
    this->colorOverLifeTimeGradient = colorOverLifeTimeGradient;
}

void ParticleSystem::setLooping(bool looping)
{
    this->looping = looping;
}

void ParticleSystem::setParticleLimit(unsigned int particleLimit)
{
    this->particleLimit = particleLimit;
}

void ParticleSystem::setEmissionDuration(float emissionDuration)
{
    this->emissionDuration = emissionDuration;
}

void ParticleSystem::setEmissionRate(float emissionRate)
{
    this->emissionRate = emissionRate;
}

void ParticleSystem::setEmissionRadius(float emissionRadius)
{
    this->emissionRadius = emissionRadius;
}

void ParticleSystem::setArcEmissionModeMinAngle(float arcModeMinAngle)
{
    this->arcModeMinAngle = arcModeMinAngle;
}

void ParticleSystem::setArcEmissionModeMaxAngle(float arcModeMaxAngle)
{
    this->arcModeMaxAngle = arcModeMaxAngle;
}

void ParticleSystem::setOrthogonalModeAngle(float orthogonalModeAngle)
{
    this->orthogonalModeAngle = orthogonalModeAngle;
}

void ParticleSystem::setGravity(glm::vec2 gravity)
{
    this->gravity = gravity;
}

void ParticleSystem::setWind(glm::vec2 wind)
{
    this->wind = wind;
}

void ParticleSystem::setMinLifeTime(float minLifeTime)
{
    this->minLifeTime = minLifeTime;
}

void ParticleSystem::setMaxLifeTime(float maxLifeTime)
{
    this->maxLifeTime = maxLifeTime;
}

void ParticleSystem::setLifeTime(float lifeTime)
{
    setMinLifeTime(lifeTime);
    setMaxLifeTime(lifeTime);
}

void ParticleSystem::setMinEmissionVelocity(float minEmissionVelocity)
{
    this->minEmissionVelocity = minEmissionVelocity;
}

void ParticleSystem::setMaxEmissionVelocity(float maxEmissionVelocity)
{
    this->maxEmissionVelocity = maxEmissionVelocity;
}

void ParticleSystem::setEmissionVelocity(float emissionVelocity)
{
    setMinEmissionVelocity(emissionVelocity);
    setMaxEmissionVelocity(emissionVelocity);
}

void ParticleSystem::setMinRotationEmissionVelocity(float minRotationEmissionVelocity)
{
    this->minRotationEmissionVelocity = minRotationEmissionVelocity;
}

void ParticleSystem::setMaxRotationEmissionVelocity(float maxRotationEmissionVelocity)
{
    this->maxRotationEmissionVelocity = maxRotationEmissionVelocity;
}

void ParticleSystem::setRotationEmissionVelocity(float rotationEmissionVelocity)
{
    setMinRotationEmissionVelocity(rotationEmissionVelocity);
    setMaxRotationEmissionVelocity(rotationEmissionVelocity);
}

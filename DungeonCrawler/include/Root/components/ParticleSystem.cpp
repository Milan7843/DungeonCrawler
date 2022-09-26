#include "ParticleSystem.h"

#include "Root/Transform.h"
#include "Root/Random.h"

std::shared_ptr<ParticleSystem> ParticleSystem::create(std::shared_ptr<Transform> transform)
{
	ParticleSystem* particleSystem = new ParticleSystem();
	std::shared_ptr<ParticleSystem> pointer{ particleSystem };
	transform->addComponent(pointer);
	return pointer;
}

ParticleSystem::ParticleSystem()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    emitParticle();
}

ParticleSystem::~ParticleSystem()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void ParticleSystem::start()
{
}

void ParticleSystem::update()
{
}

void ParticleSystem::render(float renderDepth)
{
    writeDataToVAO();

    glBindVertexArray(VAO);

    glDrawArrays(GL_POINTS, 0, particleDrawData.size());

    glBindVertexArray(0);
}

void ParticleSystem::play()
{
}

void ParticleSystem::stop()
{
}

void ParticleSystem::writeDataToVAO()
{
    // Making sure everything gets put on this specific VAO
    glBindVertexArray(VAO);

    // Binding the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Putting the draw data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleDrawData), particleDrawData.data(), GL_STATIC_DRAW);

    // Letting OpenGL know how to interpret the data:
    // vec2 for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // vec3 for color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleSystem::emitParticle()
{
    glm::vec2 position{ transform->getPosition() };
    glm::vec2 velocity{ getRandomDirection() * Random::between(minEmissionVelocity, maxEmissionVelocity) };
    glm::vec3 color{ colorOverLifeTimeGradient.sample(0.0f) };
    float lifeTime{ Random::between(minLifeTime, maxLifeTime) };

    particleDrawData.push_back({
            position,
            color
        });
    particleUpdateData.push_back({
            velocity,
            0.0f,
            lifeTime
        });
}

glm::vec2 ParticleSystem::getRandomDirection()
{
    float emissionAngle{ 0.0f };

    switch (emissionMode) {

    case ARC_EMISSION:
        emissionAngle = Random::between(arcModeMinAngle, arcModeMaxAngle);
        break;

    case ORTHOGONAL_EMISSION:
        emissionAngle = orthogonalModeAngle;
        break;
    }

    return glm::vec2(glm::cos(glm::radians(emissionAngle)), glm::sin(glm::radians(emissionAngle)));
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

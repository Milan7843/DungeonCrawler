#include "ParticleSystem.h"

#include "Root/Transform.h"
#include "Root/Random.h"
#include "Root/engine/RootEngine.h"

std::shared_ptr<ParticleSystem> ParticleSystem::create(std::shared_ptr<Transform> transform)
{
	ParticleSystem* particleSystem = new ParticleSystem();
	std::shared_ptr<ParticleSystem> pointer{ particleSystem };
	transform->addComponent(pointer);
    particleSystem->emitParticle();
	return pointer;
}

ParticleSystem::ParticleSystem()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Making sure everything gets put on this specific VAO
    glBindVertexArray(VAO);

    // Binding the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Letting OpenGL know how to interpret the data:
    // vec2 for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // vec3 for color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    // Updating particle data
    for (unsigned int i{ 0 }; i < particleDrawData.size(); i++)
    {
        float lifePoint = particleUpdateData[i].aliveTime / particleUpdateData[i].lifeTime;

        // Gravity
        particleUpdateData[i].velocity += gravity * Time::getDeltaTime();
        // Wind
        particleUpdateData[i].velocity += wind * Time::getDeltaTime();
        // Drag
        particleUpdateData[i].velocity *= (1.0f - dragOverLifeTimeGradient.sample(lifePoint) * Time::getDeltaTime());
        // Applying velocity
        particleDrawData[i].position += particleUpdateData[i].velocity * Time::getDeltaTime();

        particleUpdateData[i].aliveTime += Time::getDeltaTime();

        if (particleUpdateData[i].aliveTime > particleUpdateData[i].lifeTime)
        {
            emitParticle(i);
        }
    }

    // Emitting new particles
    if (particlesEmittedThisRun / glm::max(currentEmissionTime, 0.0001f) < emissionRate)
        emitParticle();

    currentEmissionTime += Time::getDeltaTime();

}

void ParticleSystem::render(float renderDepth)
{
    RootEngine::getParticleRenderShader()->use();
    RootEngine::getParticleRenderShader()->setMat4("model", transform->getModelMatrix());

    RootEngine::getParticleRenderShader()->setMat4("projection", Root::getActiveCamera()->getProjectionMatrix());
    //RootEngine::getParticleRenderShader()->setInt("sprite", 0);
    RootEngine::getParticleRenderShader()->setFloat("renderDepth", renderDepth / 10000.0f);

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
    glBufferData(GL_ARRAY_BUFFER, particleDrawData.size() * sizeof(ParticleDrawData), particleDrawData.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleSystem::emitParticle()
{
    std::cout << "Emitting" << particleDrawData.size() << std::endl;
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

    particlesEmittedThisRun++;
}

void ParticleSystem::emitParticle(unsigned int index)
{
    glm::vec2 position{ transform->getPosition() };
    glm::vec2 velocity{ getRandomDirection() * Random::between(minEmissionVelocity, maxEmissionVelocity) };
    glm::vec3 color{ colorOverLifeTimeGradient.sample(0.0f) };
    float lifeTime{ Random::between(minLifeTime, maxLifeTime) };

    particleDrawData[index] = {
            position,
            color
        };
    particleUpdateData[index] = {
            velocity,
            0.0f,
            lifeTime
        };

    particlesEmittedThisRun++;
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

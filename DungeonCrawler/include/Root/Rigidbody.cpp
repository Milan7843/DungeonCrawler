#include "Rigidbody.h"

#include "Root/engine/PhysicsEngine.h"
#include "Root/Transform.h"

Rigidbody::Rigidbody(std::shared_ptr<Transform> transform, float linearDamping, float angularDamping, bool allowSleep, bool awake, bool fixedRotation, bool bullet, b2BodyType type, bool enabled, float gravityScale)
{
	glm::vec2 position{ transform->getPosition() };

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.angle = glm::radians(transform->getRotation());
	bodyDef.type = type;
	bodyDef.linearDamping = linearDamping;
	bodyDef.angularDamping = angularDamping;
	bodyDef.allowSleep = allowSleep;
	bodyDef.awake = awake;
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.bullet = bullet;
	bodyDef.enabled = enabled;
	bodyDef.gravityScale = gravityScale;

	b2PolygonShape shape;
	glm::vec2 size = transform->getScale();
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body = PhysicsEngine::addBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}

std::shared_ptr<Rigidbody> Rigidbody::create(
	std::shared_ptr<Transform> transform,
	b2BodyType type,
	float gravityScale,
	bool fixedRotation,
	bool allowSleep,
	float linearDamping,
	float angularDamping,
	bool bullet,
	bool awake,
	bool enabled)
{

	Rigidbody* rigidbody = new Rigidbody(transform, linearDamping, angularDamping, allowSleep, awake, fixedRotation, bullet, type, enabled, gravityScale);
	std::shared_ptr<Rigidbody> pointer{ rigidbody };
	transform->addComponent(pointer);
	return pointer;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::update()
{
	b2Vec2 position{ body->GetPosition() };
	this->transform->setPosition(glm::vec2(position.x, position.y));

	this->transform->setRotation(glm::degrees(body->GetAngle()));

	//std::cout << position.x << ", " << position.y << std::endl;
	//std::cout << transform->getPosition().x << ", " << transform->getPosition().y << std::endl;
}

void Rigidbody::setPosition(glm::vec2 position, bool alsoSetTransformPosition)
{
	body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());
}

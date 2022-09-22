#pragma once

#include <Root/Component.h>

#include <box2d/b2_body.h>

class Rigidbody : public Component
{
public:

	Rigidbody(float linearDamping, float angularDamping, bool allowSleep, bool awake, bool fixedRotation, bool bullet, b2BodyType type, bool enabled, float gravityScale);
	~Rigidbody();

private:

	float mass;

};

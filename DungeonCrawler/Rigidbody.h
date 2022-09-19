#pragma once

#include <Root/Component.h>

class Rigidbody : public Component
{
public:

	Rigidbody();
	~Rigidbody();

private:

	float mass;

};

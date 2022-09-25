#pragma once

#include "Root/components/Component.h" // Base class
#include "Root/Physics.h"

#define ColliderPointer std::shared_ptr<Collider>

class Collider : public Component
{
public:

	Collider();
	~Collider();



private:


};


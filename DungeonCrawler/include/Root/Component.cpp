#include "Component.h"

#include "Transform.h"

void Component::setTransform(Transform* transform)
{
	this->transform = transform;
}

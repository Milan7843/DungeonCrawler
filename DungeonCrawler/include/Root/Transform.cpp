#include "Transform.h"

Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale)
	: position(position)
	, rotation(rotation)
	, scale(scale)
{
}

Transform::~Transform()
{
	Logger::destructorMessage("Transform destroyed");
}

std::vector<std::shared_ptr<Component>>& Transform::getComponents()
{
	return components;
}

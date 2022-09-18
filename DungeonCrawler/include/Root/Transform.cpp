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

glm::mat4& Transform::getModelMatrix()
{
	glm::mat4 model{ glm::mat4(1.0f) };
	/*
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
	*/
	return model;
}

std::shared_ptr<Component> Transform::getComponentOfType(const std::type_info& type)
{
	for (std::shared_ptr<Component>& component : components)
	{
		if (typeid(*component) == type)
		{
			return components[0];
		}
	}
	return NULL;
}

void Transform::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
	component->setTransform(this);
}

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

void Transform::setParent(std::shared_ptr<Transform> parent)
{
	this->parent = parent;
}

std::vector<std::shared_ptr<Component>>& Transform::getComponents()
{
	return components;
}

glm::mat4 Transform::getModelMatrix()
{
	glm::mat4 model{ glm::mat4(1.0f) };

	if (parent != NULL) {
		model = model * parent->getModelMatrix();
	}
	
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

	//model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
	//model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
	
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

std::shared_ptr<Transform> Transform::create(glm::vec2 position, float rotation, glm::vec2 scale)
{
	Transform* transform = new Transform();
	std::shared_ptr<Transform> pointer{ transform };
	Root::addTransform(pointer);
	return pointer;
}

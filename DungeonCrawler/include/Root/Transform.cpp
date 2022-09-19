#include "Transform.h"

Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale)
	: position(position)
	, rotation(rotation)
	, scale(scale)
{
}

Transform::~Transform()
{
	std::cout << this->toString() << std::endl;
	Logger::destructorMessage("Transform destroyed");
}

std::shared_ptr<Transform> Transform::create(glm::vec2 position, float rotation, glm::vec2 scale)
{
	Transform* transform = new Transform();
	std::shared_ptr<Transform> pointer{ transform };
	Root::addTransform(pointer);
	return pointer;
}

void Transform::render()
{
	// Calling render() on each component attached to this Transform
	for (std::shared_ptr<Component>& component : getComponents())
	{
		component->render();
	}
}

std::string Transform::toString()
{
	std::stringstream stream;
	// Writing this object to the stream
	stream << "[Transform]"
		<< "\n > position: (" << position.x << ", " << position.y << ")"
		<< "\n > rotation: " << rotation
		<< "\n > scale: (" << scale.x << ", " << scale.y << ")"
		<< "\n > components: ["
		<< "\n";

	for (ComponentPointer component : components)
	{
		stream << " >" << component->toString() << "\n";
	}

	stream << "\n > children: [\n";

	for (TransformPointer child : children)
	{
		stream << " >" << child->toString() << "\n";
	}

	stream << "]" << std::endl;

	return stream.str();
}


void Transform::setParent(std::shared_ptr<Transform> parent, bool alsoAddChild)
{
	// Check if the transform already had a parent, 
	// and remove it as a child from that parent if it did
	if (this->parent != NULL)
		this->parent->removeChild(std::shared_ptr<Transform>(this));

	// Setting new parent
	this->parent = parent;

	// Possibly adding child to new parent
	if (alsoAddChild && parent != NULL)
		parent->addChild(std::shared_ptr<Transform>(this), false);
}

std::shared_ptr<Transform> Transform::getParent()
{
	return parent;
}

void Transform::addChild(std::shared_ptr<Transform> child, bool alsoSetParent)
{
	children.push_back(child);
	if (alsoSetParent)
		child->setParent(std::shared_ptr<Transform>(this), false);
}

bool Transform::removeChild(std::shared_ptr<Transform> childToRemove)
{
	for (unsigned int i{ 0 }; i < children.size(); i++)
	{
		// Comparing each current child to find one that matches
		if (children[i] == childToRemove)
		{
			// If it does, unset its parent reference,
			children[i]->parent = NULL;

			// remove it,
			children.erase(children.begin() + i);

			// and return true
			return true;
		}
	}
	return false;
}

void Transform::removeAllChildren()
{
	children.clear();
}

std::vector<std::shared_ptr<Transform>>& Transform::getChildren()
{
	return children;
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

float Transform::lookAt(glm::vec2 point)
{
	if (this == nullptr)
		Logger::logError("Transform is NULL. Check if it gets initialized.");

	glm::vec2 offset{ point - position };

	// Both zero are invalid atan2 inputs
	if (offset.x == 0.0f && offset.y == 0.0f)
		return 0.0f;

	return glm::degrees(glm::atan(offset.y, offset.x));
}

#include "Transform.h"

Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale, float renderDepth)
	: position(position)
	, rotation(rotation)
	, scale(scale)
	, renderDepth(renderDepth)
{
}

void Transform::updateTransformMatrices()
{
	// Only change the matrices if the values have changed
	if (!transformUpdated)
		return;

	// Updating the transform matrix
	transform = glm::identity<glm::mat4>();

	transform = glm::translate(transform, glm::vec3(position.x, position.y, 0.0f));

	//model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0, 0, 1));
	//model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));

	//glm::vec3 newTranslation = glm::mat3(transform) * glm::vec3(position.x, position.y, 0.0f);

	/* Could this be done more efficiently, with this method?:
	// http://www.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche0053.html
	inverseTransform = glm::mat4 {
		transform[0][0] / scale.x, transform[1][0] / scale.x, transform[2][0] / scale.x, 0.0f,
		transform[0][1] / scale.y, transform[1][1] / scale.y, transform[2][1] / scale.y, 0.0f,
		transform[0][2], transform[1][2], transform[2][2], 0.0f,
		-newTranslation.x, -newTranslation.y, -newTranslation.z, 1.0f,
	};*/
	
	// Updating the inverse transform matrix
	
	inverseTransform = glm::identity<glm::mat4>();
	
	// Scale must not be zero for this step
	if (scale.x != 0.0f && scale.y != 0.0f)
		inverseTransform = glm::scale(inverseTransform, glm::vec3(1.0f / scale.x, 1.0f / scale.y, 1.0f));

	//model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	inverseTransform = glm::rotate(inverseTransform, glm::radians(-rotation), glm::vec3(0, 0, 1));
	//model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	inverseTransform = glm::translate(inverseTransform, glm::vec3(-position.x, -position.y, 0.0f));

	//inverseTransform = glm::inverse(transform);
	
	//std::cout << "Transforms updated" << std::endl;

	// Disabling the transform changed flag
	transformUpdated = false;
}

Transform::~Transform()
{
	std::cout << this->toString() << std::endl;
	Logger::destructorMessage("Transform destroyed");
}

std::shared_ptr<Transform> Transform::create(glm::vec2 position, float rotation, glm::vec2 scale, float renderDepth)
{
	Transform* transform = new Transform(position, rotation, scale, renderDepth);
	std::shared_ptr<Transform> pointer{ transform };
	Root::addTransform(pointer);
	transform->self = pointer;
	return pointer;
}

void Transform::render(float parentRenderDepth, float renderDepthOffset)
{
	// Either use own renderdepth
	float usedRenderDepth{ renderDepth };

	// Or parent's
	if (renderDepth == -1.0f)
		usedRenderDepth = parentRenderDepth + renderDepthOffset;


	// Calling render() on each component attached to this Transform
	for (std::shared_ptr<Component>& component : getComponents())
	{
		renderDepthOffset -= 0.001f;
		component->render(usedRenderDepth + renderDepthOffset);
	}
	// Then rendering each child
	for (std::shared_ptr<Transform>& child : children)
	{
		renderDepthOffset -= 0.001f;
		child->render(usedRenderDepth, renderDepthOffset);
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
		this->parent->removeChild(this->self);

	// Setting new parent
	this->parent = parent;

	// Possibly adding child to new parent
	if (alsoAddChild && parent != NULL)
		parent->addChild(this->self, false);
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

			// and return true to indicate a child was removed
			return true;
		}
	}
	return false;
}

void Transform::removeAllChildren()
{
	children.clear();
}

void Transform::setRenderDepth(float renderDepth)
{
	if (renderDepth == -1.0f) {
		this->renderDepth = renderDepth;
		return;
	}
	this->renderDepth = glm::clamp(renderDepth, 0.0f, 10000.0f);
}

float Transform::getRenderDepth()
{
	return renderDepth;
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
	
	model = model * getTransformMatrix();

	/*
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

	//model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
	//model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
	*/
	return model;
}

glm::mat4 Transform::getTransformMatrix()
{
	updateTransformMatrices();

	return transform;
}

glm::mat4 Transform::getInverseTransformMatrix()
{
	updateTransformMatrices();

	return inverseTransform;
}

glm::vec2 Transform::worldPointToLocalPoint(glm::vec2 point)
{
	if (this->parent != NULL)
		point = this->parent->worldPointToLocalPoint(point);

	glm::vec4 transformedPoint =  this->getInverseTransformMatrix() * glm::vec4(point.x, point.y, 0.0f, 1.0f);
	glm::vec2 transformedPoint2D = glm::vec2(transformedPoint);

	return transformedPoint2D;
}

glm::vec2 Transform::localPointToWorldPoint(glm::vec2 point)
{
	glm::vec4 transformedPoint = this->getTransformMatrix() * glm::vec4(point.x, point.y, 0.0f, 1.0f);
	glm::vec2 transformedPoint2D = glm::vec2(transformedPoint);

	if (this->parent != NULL)
		transformedPoint2D = this->parent->localPointToWorldPoint(transformedPoint2D);

	return transformedPoint2D;
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

	glm::vec2 offset{ point - this->position };

	// Both zero are invalid atan2 inputs
	if (offset.x == 0.0f && offset.y == 0.0f)
		return 0.0f;

	return glm::degrees(glm::atan(offset.y, offset.x));
}

glm::vec2 Transform::getPosition()
{
	return position;
}
void Transform::setPosition(glm::vec2 position)
{
	// Update position and set updated flag if the position changed
	if (this->position != position)
	{
		transformUpdated = true;
		this->position = position;
	}
}
void Transform::movePosition(glm::vec2 offset)
{
	// Update position and set updated flag if the position changed
	if (offset != glm::vec2(0.0f))
	{
		this->position += offset;
		transformUpdated = true;
	}
}

float Transform::getRotation()
{
	return rotation;
}
void Transform::setRotation(float rotation)
{
	// Update rotation and set updated flag if the rotation changed
	if (this->rotation != rotation)
	{
		this->rotation = rotation;
		transformUpdated = true;
	}
}
void Transform::rotate(float angle)
{
	// Update rotation and set updated flag if the rotation changed
	if (angle != 0.0f)
	{
		this->rotation += angle;
		transformUpdated = true;
	}
}

glm::vec2 Transform::getScale()
{
	return scale;
}
void Transform::setScale(glm::vec2 scale)
{
	// Update scale and set updated flag if the scale changed
	if (this->scale != scale)
	{
		this->scale = scale;
		transformUpdated = true;
	}
}

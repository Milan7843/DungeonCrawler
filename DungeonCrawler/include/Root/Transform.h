#pragma once

#include "Component.h"

#include "Logger.h"

#include <glm/glm.hpp>

#include <vector>

/**
 * Class which holds values for a 2D transformation.
 */
class Transform
{
public:

	/**
	 * Create a new Transform.
	 * 
	 * \param position: the world position of this transform [optional: default = (0, 0)]
	 * \param rotation: the rotation of this transform [optional: default = 0]
	 * \param scale: the scale of this transform [optional: default = (1, 1)]
	 */
	Transform(
		glm::vec2 position = glm::vec2(0.0f), // Initialize position to (0, 0)
		float rotation = 0.0f, // Initialize rotation to no rotation
		glm::vec2 scale = glm::vec2(1.0f)); // Initialize scale to no scaling

	/**
	 * Destructor for the Transform class.
	 */
	~Transform();

	/**
	 * Get all components attached to this transform.
	 * 
	 * \returns all components attached to this transform.
	 */
	std::vector<std::shared_ptr<Component>>& getComponents();

	void addComponent(std::shared_ptr<Component> component);

private:

	std::vector<std::shared_ptr<Component>> components;

	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

};

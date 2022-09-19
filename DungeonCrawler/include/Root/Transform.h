#pragma once

#include "Root/Component.h"

#include "Root/Logger.h"
#include "Root/Root.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <typeinfo>
#include <typeindex>

#define TransformPointer std::shared_ptr<Transform>

/**
 * Class which holds values for a 2D transformation.
 */
class Transform
{
public:

	/**
	 * Create a new Transform. Will NOT automatically add this transform to the current scene.
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
	 * Set the parent transform of this transform.
	 * Having a parent will make the child transform's data in local space.
	 *
	 * \param parent: a shared_ptr to the transform that will be the parent.
	 * If this is NULL, the transform will have no parent
	 */
	void setParent(std::shared_ptr<Transform> parent);

	/**
	 * Get all components attached to this transform.
	 * 
	 * \returns all components attached to this transform.
	 */
	std::vector<std::shared_ptr<Component>>& getComponents();

	/**
	 * Get a matrix which correctly.
	 * 
	 * \return 
	 */
	glm::mat4 getModelMatrix();

	/**
	 * Get a component on this transform by type.
	 * 
	 * \returns the first components on this transform with the given type.
	 */
	std::shared_ptr<Component> getComponentOfType(const std::type_info& type);

	void addComponent(std::shared_ptr<Component> component);

	// Public variables
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	/**
	 * Create a new Transform. Will automatically add this transform to the current scene.
	 *
	 * \param position: the world position of this transform [optional: default = (0, 0)]
	 * \param rotation: the rotation of this transform [optional: default = 0]
	 * \param scale: the scale of this transform [optional: default = (1, 1)]
	 */
	static std::shared_ptr<Transform> create(
		glm::vec2 position = glm::vec2(0.0f), // Initialize position to (0, 0)
		float rotation = 0.0f, // Initialize rotation to no rotation
		glm::vec2 scale = glm::vec2(1.0f)); // Initialize scale to no scaling

private:

	std::vector<std::shared_ptr<Component>> components;

	std::shared_ptr<Transform> parent = NULL;
};

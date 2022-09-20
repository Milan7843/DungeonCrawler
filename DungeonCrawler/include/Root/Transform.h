#pragma once

#include "Root/Component.h"

#include "Root/Logger.h"
#include "Root/Root.h"

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

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
	 * Destructor for the Transform class.
	 */
	~Transform();

	/**
	 * Create a new Transform. Will automatically add this transform to the current scene.
	 *
	 * \param position: the world position of this transform [optional: default = (0, 0)]
	 * \param rotation: the rotation of this transform [optional: default = 0]
	 * \param scale: the scale of this transform [optional: default = (1, 1)]
	 * \param renderDepth: the depth at which this transform will be rendered.
	 * If this is not set or -1, the render depth of the parent will be used.
	 * The render depth is a scale from 0 (closest) to 10000 (furthest).
	 */
	static std::shared_ptr<Transform> create(
		glm::vec2 position = glm::vec2(0.0f), // Initialize position to (0, 0)
		float rotation = 0.0f, // Initialize rotation to no rotation
		glm::vec2 scale = glm::vec2(1.0f), // Initialize scale to no scaling
		float renderDepth = 0.0f); // Initialize render depth to 0

	/**
	 * Render this Transform.
	 * Should not be called by the user.
	 * 
	 * \param parentRenderDepth: render the depth of the parent of this transform.
	 * \param renderDepthOffset: the offset on top of the render depth.
	 */
	void render(float parentRenderDepth = 0.0f, float renderDepthOffset = 0.0f);

	/**
	 * Get a string representing this Transform.
	 *
	 * \returns this Transform in a human-readable format.
	 */
	std::string toString();

	/**
	 * Set the parent transform of this transform.
	 * Having a parent will make the child transform's data in local space.
	 * This will also add this transform as a child to the parent.
	 * Note that adding a child to a transform via Transform::addChild() 
	 * will also set the child's parent using setParent(), 
	 * and therefore does not have to be called manually.
	 *
	 * \param parent: a shared_ptr to the transform that will be the parent.
	 * If this is NULL, the transform will have no parent
	 */
	void setParent(std::shared_ptr<Transform> parent, bool alsoAddChild = true);

	/**
	 * Get the parent of this transform.
	 * 
	 * \returns the parent of this transform, or NULL if it does not have one.
	 */
	std::shared_ptr<Transform> getParent();

	/**
	 * Add a child to this transform.
	 * This will also set the child's parent pointer to this transform.
	 * Note that setting a transform's parent via Transform::setParent() 
	 * will also set the parent's child using addChild(), 
	 * and therefore does not have to be called manually.
	 *
	 * \param child: a TransformPointer to the child.
	 */
	void addChild(std::shared_ptr<Transform> child, bool alsoSetParent = true);

	/**
	 * Remove a child from this transform with the given shared_ptr.
	 * This will also set the child's parent pointer to NULL, indicating no parent.
	 *
	 * \param childToRemove: a TransformPointer to the child that should be removed.
	 * \returns whether a child was removed succesfully.
	 */
	bool removeChild(std::shared_ptr<Transform> childToRemove);

	/**
	 * Remove all children from this transform with the given shared_ptr.
	 */
	void removeAllChildren();

	/**
	 * Set this transform's render depth.
	 * The render depth is a scale from 0 (closest) to 10000 (furthest).
	 * 
	 * \param renderDepth: the new render depth.
	 * If this is -1, this transform will use its parent's render depth.
	 * If it additionally has no parent, it will use render depth 0 (front).
	 */
	void setRenderDepth(float renderDepth);

	/**
	 * Get this transform's render depth.
	 * 
	 * \returns this transform's render depth.
	 */
	float getRenderDepth();

	/**
	 * Get the children of this transform.
	 *
	 * \returns the children of this transform.
	 */
	std::vector<std::shared_ptr<Transform>>& getChildren();

	/**
	 * Get all components attached to this transform.
	 * 
	 * \returns all components attached to this transform.
	 */
	std::vector<std::shared_ptr<Component>>& getComponents();

	/**
	 * Get a matrix which correctly transforms points to local space.
	 * 
	 * \returns the model matrix.
	 */
	glm::mat4 getModelMatrix();

	/**
	 * Get a matrix which correctly transforms points to local space.
	 *
	 * \returns the model matrix.
	 */
	glm::mat4 getFullModelMatrix();

	/**
	 * Get a component on this transform of type T.
	 * 
	 * \returns the first components on this transform with the given type.
	 */
	template <class T>
	std::shared_ptr<Component> getComponent()
	{
		for (std::shared_ptr<Component>& component : components)
		{
			if (typeid(*component) == typeid(T))
			{
				return components[0];
			}
		}
		return NULL;
	}

	/**
	 * Add a component to this transform.
	 * 
	 * \param component: the component to add to this transform.
	 */
	void addComponent(std::shared_ptr<Component> component);

	/**
	 * Add a component of type T to this transform.
	 */
	template <class T>
	std::shared_ptr<T> addComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Cannot add a non-component to a transform.");
		std::shared_ptr<T> ptr = T::create();
		addComponent(ptr);
		return ptr;
	}

	/**
	 * Get the angle required for this transform to look at a point.
	 * Will NOT set the angle, only calculate it.
	 * Example of using this function to make an object look at the mouse:
	 * \code{.cpp}
	 * transform->rotation = transform->lookAt(Input::getMouseWorldPosition());
	 * \endcode
	 * 
	 * \param point: the point to look at.
	 * \returns the angle at which this transform would look at the point.
	 */
	float lookAt(glm::vec2 point);

	// Public variables
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

private:

	float renderDepth{ -1.0f };

	Transform(glm::vec2 position, float rotation, glm::vec2 scale, float renderDepth);

	std::vector<std::shared_ptr<Component>> components;

	std::shared_ptr<Transform> parent = NULL;
	std::vector<std::shared_ptr<Transform>> children;
	std::shared_ptr<Transform> self;
};

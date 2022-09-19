#pragma once

#define ComponentPointer std::shared_ptr<Component>

#include <string>

class Transform;

/**
 * Class which all components must inherit from.
 */
class Component
{
public:

	/**
	 * The start function of this component, gets called automatically at the start of the game.
	 */
	virtual void start() {}

	/**
	 * The update function of this component, gets called automatically every frame.
	 */
	virtual void update() {}

	/**
	 * The render function of this component, gets called automatically every frame.
	 * This function gets called after update().
	 */
	virtual void render() {}

	/**
	 * Set the point to the transform of this component.
	 * 
	 * \param transform: a pointer to the transform which this component belongs to.
	 */
	void setTransform(Transform* transform);

	/**
	 * Get a string representing this Component.
	 *
	 * \returns this Component in a human-readable format.
	 */
	virtual std::string toString() { return std::string{}; };

protected:

	// A pointer to the transform this component belongs to.
	Transform* transform;
};

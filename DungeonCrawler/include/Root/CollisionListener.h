#pragma once

#include <box2d/b2_world_callbacks.h>

/**
 * A class that should be the base class of your collision callback handler.
 * In order to use it:
 * - Create a subclass of this class
 * - Implement BeginContact() and EndContact() (optional)
 * - Create an instance of your new class
 * - Use Physics::setCollisionListener() with a pointer to the new instance
 * - Make sure the instance stays alive
 */
class CollisionListener : public b2ContactListener
{
public:

	virtual void BeginContact(b2Contact* contact) {}

	virtual void EndContact(b2Contact* contact) {}
};


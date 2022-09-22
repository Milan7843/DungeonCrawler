#pragma once

#include "Root/Component.h" // Base class
#include "Root/Transform.h"

#include <box2d/b2_body.h>
#include <glm/glm.hpp>

#include <memory>

class Rigidbody : public Component
{
public:

	~Rigidbody();

	/**
	 * Create a new rigidbody.
	 * Will automatically add this component to the given transform.
	 *
	 * \param transform:		the transform to add this component to.
	 * \param linearDamping:	linear damping is use to reduce the linear velocity. The damping parameter
	 * 							can be larger than 1.0f but the damping effect becomes sensitive to the
	 * 							time step when the damping parameter is large.
	 * 							Units are 1/time
	 * \param angularDamping:	angular damping is use to reduce the angular velocity. The damping parameter
	 * 							can be larger than 1.0f but the damping effect becomes sensitive to the
	 * 							time step when the damping parameter is large.
	 * 							Units are 1/time
	 * \param allowSleep:		set this flag to false if this body should never fall asleep. Note that
	 * 							this increases CPU usage.
	 * \param awake:			is this body initially awake or sleeping?
	 * \param fixedRotation:	should this body be prevented from rotating? Useful for characters.
	 * \param bullet:			Is this a fast moving body that should be prevented from tunneling through
	 * 							other moving bodies? Note that all bodies are prevented from tunneling through
	 * 							kinematic and static bodies. This setting is only considered on dynamic bodies.
	 *							Increases processing time.
	 * \param type:				the body type: static, kinematic, or dynamic (b2_staticBody, b2_kinematicBody, b2_dynamicBody).
	 * \param enabled:			does this body start out enabled?
	 * \param gravityScale:		scale the gravity applied to this body.
	 */
	static std::shared_ptr<Rigidbody> create(
		std::shared_ptr<Transform> transform,
		b2BodyType type = b2_staticBody,
		float linearDamping = 0.0f,
		float angularDamping = 0.0f,
		bool allowSleep = true,
		bool awake = true,
		bool fixedRotation = false,
		bool bullet = false,
		bool enabled = true,
		float gravityScale = 1.0f);


	void update() override;

private:

	Rigidbody(std::shared_ptr<Transform> transform, float linearDamping, float angularDamping, bool allowSleep, bool awake, bool fixedRotation, bool bullet, b2BodyType type, bool enabled, float gravityScale);

	b2Body* body;
};

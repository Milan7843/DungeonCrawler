#pragma once

#include "Root/Component.h" // Base class

#include <box2d/b2_body.h>
#include <glm/glm.hpp>

#include <memory>

#define RigidbodyPointer std::shared_ptr<Rigidbody>

class Transform;

class Rigidbody : public Component
{
public:

	~Rigidbody();

	/**
	 * Create a new rigidbody.
	 * Will automatically add this component to the given transform.
	 *
	 * \param transform:		the transform to add this component to.
	 * \param type:				the body type: static, kinematic, or dynamic (b2_staticBody, b2_kinematicBody, b2_dynamicBody).
	 * \param gravityScale:		scale the gravity applied to this body.
	 * \param fixedRotation:	should this body be prevented from rotating? Useful for characters.
	 * \param allowSleep:		set this flag to false if this body should never fall asleep. Note that
	 * 							this increases CPU usage.
	 * \param linearDamping:	linear damping is use to reduce the linear velocity. The damping parameter
	 * 							can be larger than 1.0f but the damping effect becomes sensitive to the
	 * 							time step when the damping parameter is large.
	 * 							Units are 1/time
	 * \param angularDamping:	angular damping is use to reduce the angular velocity. The damping parameter
	 * 							can be larger than 1.0f but the damping effect becomes sensitive to the
	 * 							time step when the damping parameter is large.
	 * 							Units are 1/time
	 * \param bullet:			Is this a fast moving body that should be prevented from tunneling through
	 * 							other moving bodies? Note that all bodies are prevented from tunneling through
	 * 							kinematic and static bodies. This setting is only considered on dynamic bodies.
	 *							Increases processing time.
	 * \param awake:			is this body initially awake or sleeping?
	 * \param enabled:			does this body start out enabled?
	 */
	static std::shared_ptr<Rigidbody> create(
		std::shared_ptr<Transform> transform,
		b2BodyType type = b2_staticBody,
		float gravityScale = 1.0f,
		bool fixedRotation = false,
		bool allowSleep = true,
		float linearDamping = 0.0f,
		float angularDamping = 0.0f,
		bool bullet = false,
		bool awake = true,
		bool enabled = true);


	void update() override;

	/**
	 * Set the position of this rigidbody.
	 * 
	 * \param position: the new position.
	 * \param alsoSetTransformPosition: whether to also set the transform's position. Do not change this.
	 */
	void setPosition(glm::vec2 position, bool alsoSetTransformPosition = true);

private:

	Rigidbody(std::shared_ptr<Transform> transform, float linearDamping, float angularDamping, bool allowSleep, bool awake, bool fixedRotation, bool bullet, b2BodyType type, bool enabled, float gravityScale);

	b2Body* body;
};

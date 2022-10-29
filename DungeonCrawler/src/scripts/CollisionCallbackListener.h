#pragma once

#include <Root/Logger.h>
#include <Root/CollisionListener.h>
#include <Root/components/Rigidbody.h>
#include <Root/Transform.h>


class CollisionCallbackListener : public CollisionListener
{
public:

	void BeginContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2) override;

	void EndContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2) override;
};


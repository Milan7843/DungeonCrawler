#pragma once

#include <Root/Logger.h>
#include <Root/CollisionListener.h>

#include <Root/components/Rigidbody.h>


class CollisionCallbackHandler : public CollisionListener
{
public:

	void BeginContact(b2Contact* contact) override;

	void EndContact(b2Contact* contact) override;
};


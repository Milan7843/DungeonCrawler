#include "CollisionCallbackHandler.h"

#include <Root/Transform.h>

void CollisionCallbackHandler::BeginContact(b2Contact* contact)
{
	std::string name1 = contact->GetFixtureA()->GetBody()->GetUserData().rigidbody->getTransform()->getName();
	std::string name2 = contact->GetFixtureB()->GetBody()->GetUserData().rigidbody->getTransform()->getName();

	Logger::log("Contact between " + name1 + " and " + name2);
}

void CollisionCallbackHandler::EndContact(b2Contact* contact)
{
}

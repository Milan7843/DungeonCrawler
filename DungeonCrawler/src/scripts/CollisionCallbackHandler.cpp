#include "CollisionCallbackHandler.h"

#include <Root/Transform.h>

void CollisionCallbackHandler::BeginContact(b2Contact* contact)
{
	//std::string name1 = contact->GetFixtureA()->GetBody()->GetUserData().rigidbody->getTransform()->getName();
	//std::string name2 = contact->GetFixtureB()->GetBody()->GetUserData().rigidbody->getTransform()->getName();


	FixtureData* fixtureData = reinterpret_cast<FixtureData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);

	Rigidbody* rb1{ reinterpret_cast<FixtureData*>(contact->GetFixtureA()->GetUserData().pointer)->rigidbody };
	Rigidbody* rb2{ reinterpret_cast<FixtureData*>(contact->GetFixtureB()->GetUserData().pointer)->rigidbody };

	std::string name1 = rb1->getTransform()->getName();
	std::string name2 = rb2->getTransform()->getName();

	Logger::log("Contact between " + name1 + " and " + name2);
}

void CollisionCallbackHandler::EndContact(b2Contact* contact)
{
}

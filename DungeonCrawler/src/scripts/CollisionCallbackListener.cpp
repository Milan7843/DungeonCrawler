#include "CollisionCallbackListener.h"

#include <Root/Transform.h>

void CollisionCallbackListener::BeginContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2)
{
	std::string name1 = rb1->getTransform()->getName();
	std::string name2 = rb2->getTransform()->getName();

	Logger::log("Contact between " + name1 + " and " + name2);

	if (name1 == "wall" && name2 == "bullet")
		rb2->getTransform()->destroy();
}

void CollisionCallbackListener::EndContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2)
{
}

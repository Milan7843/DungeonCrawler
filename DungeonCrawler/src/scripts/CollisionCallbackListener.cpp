#include "CollisionCallbackListener.h"

void CollisionCallbackListener::BeginContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2)
{
	std::string tag1 = rb1->getTransform()->getTag();
	std::string tag2 = rb2->getTransform()->getTag();

	Logger::log(
		"Contact between "
		+ rb1->getTransform()->getName()
		+ " and "
		+ rb2->getTransform()->getName());

	if (tag1 == "bullet" && tag2 == "wall")
	{
		rb1->getTransform()->destroy();
	}
	if (tag1 == "bullet" && tag2 == "enemy")
	{
		rb1->getTransform()->destroy();
	}
}

void CollisionCallbackListener::EndContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2)
{
}

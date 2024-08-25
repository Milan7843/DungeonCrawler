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
	if (strcmp(tag1.c_str(), "arrow") == 0 && (strcmp(tag2.c_str(), "enemy") == 0 || strcmp(tag2.c_str(), "wall") == 0))
	{
		//rb1->getTransform()->destroy();
		rb1->setEnabled(false);
		std::cout << "lp b: " << rb1->getTransform()->getLocalPosition().x << ", "
			<< rb1->getTransform()->getLocalPosition().y << std::endl;
		rb1->getTransform()->setParent(rb2->getTransform());
		std::cout << "lp a: " << rb1->getTransform()->getLocalPosition().x << ", "
			<< rb1->getTransform()->getLocalPosition().y << std::endl;
		//rb1->getTransform()->movePosition(rb2->getTransform()->getLocalPosition());
	}
}

void CollisionCallbackListener::EndContact(b2Contact* contact, Rigidbody* rb1, Rigidbody* rb2)
{
}

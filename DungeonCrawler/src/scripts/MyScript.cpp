#include "MyScript.h"

MyScript::MyScript()
{
}

MyScript::~MyScript()
{

}

void MyScript::start()
{
	// Adding an object to the scene
	std::shared_ptr<Transform> transform = std::shared_ptr<Transform>(new Transform());

	// Adding a script to this object
	std::shared_ptr<MyComponentScript> myComponentScript = std::shared_ptr<MyComponentScript>(new MyComponentScript());
	transform->addComponent(myComponentScript);

	// Adding the created object to the scene
	Root::addTransform(transform);

	Logger::log("We called the start function from a script!");
}

void MyScript::update()
{
	Logger::log("We called the update function from a script!");
}

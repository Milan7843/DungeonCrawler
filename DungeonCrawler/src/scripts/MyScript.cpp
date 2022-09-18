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

	// Adding a sprite renderer to the object
	std::shared_ptr<SpriteRenderer> spriteRenderer = std::shared_ptr<SpriteRenderer>(new SpriteRenderer());
	spriteRenderer->setSprite("src/sprites/cutie_cat.png");
	transform->addComponent(spriteRenderer);
	

	// Adding the created object to the scene
	Root::addTransform(transform);


	// Adding a camera to the scene
	std::shared_ptr<Transform> cameraTransform = std::shared_ptr<Transform>(new Transform());
	std::shared_ptr<Camera> camera = std::shared_ptr<Camera>(new Camera());
	cameraTransform->addComponent(camera);

	// Adding the created camera to the scene
	Root::addTransform(cameraTransform);
}

void MyScript::update()
{
}

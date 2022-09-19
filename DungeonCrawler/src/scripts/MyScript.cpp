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
	transform = Transform::create();

	// Adding a script to this object
	std::shared_ptr<MyComponentScript> myComponentScript = std::shared_ptr<MyComponentScript>(new MyComponentScript());
	transform->addComponent(myComponentScript);

	// Adding a sprite renderer to the object
	SpriteRendererPointer spriteRenderer = SpriteRenderer::create();
	spriteRenderer->setSprite("src/sprites/cutie_cat.png");
	transform->addComponent(spriteRenderer);


	TransformPointer child = Transform::create();

	// Adding a sprite renderer to the object
	SpriteRendererPointer childSpriteRenderer = SpriteRenderer::create();
	childSpriteRenderer->setSprite("src/sprites/cutie_cat.png");
	child->addComponent(childSpriteRenderer);
	child->position = glm::vec2(1.0f, 1.0f);
	child->scale = glm::vec2(0.5f);
	child->setParent(transform);
	

	// Adding the created object to the scene
	//Root::addTransform(transform);


	// Adding a camera to the scene
	TransformPointer cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(4.0f);
	cameraTransform->addComponent(camera);

	// Adding the created camera to the scene
	Root::addTransform(cameraTransform);
}

void MyScript::update()
{
	if (Input::getKey(KEY_W))
	{
		transform->position += glm::vec2(0.0f, 1.0f) * Time::getDeltaTime();
	}
	if (Input::getKey(KEY_S))
	{
		transform->position += glm::vec2(0.0f, -1.0f) * Time::getDeltaTime();
	}
	if (Input::getKey(KEY_A))
	{
		transform->position += glm::vec2(-1.0f, 0.0f) * Time::getDeltaTime();
	}
	if (Input::getKey(KEY_D))
	{
		transform->position += glm::vec2(1.0f, 0.0f) * Time::getDeltaTime();
	}
	if (Input::getKey(KEY_Q))
	{
		transform->rotation -= 30.0f * Time::getDeltaTime();
	}
	if (Input::getKey(KEY_E))
	{
		transform->rotation += 30.0f * Time::getDeltaTime();
	}
}

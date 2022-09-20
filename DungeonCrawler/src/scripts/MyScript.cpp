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

	
	weapon = Transform::create();

	// Adding a sprite renderer to the object
	SpriteRendererPointer weaponSpriteRenderer = SpriteRenderer::create();
	weaponSpriteRenderer->setSprite("src/sprites/weapon.png");
	weapon->addComponent(weaponSpriteRenderer);
	weapon->setParent(transform);
	
	// Adding a camera to the scene
	/*
	TransformPointer cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(4.0f);
	cameraTransform->addComponent(camera);
	*/
}

void MyScript::update()
{
	//weapon->rotation = weapon->lookAt(Input::getMouseWorldPosition());

	if (Input::getKeyPressed(KEY_F)) {

		std::cout << transform->toString() << std::endl;
		std::cout << weapon->toString()<< std::endl;
		/*
		std::cout << "Mouse position: "
			<< Input::getMousePosition().x << ", "
			<< Input::getMousePosition().y << std::endl;


		std::cout << "Mouse delta: "
			<< Input::getMouseDelta().x << ", "
			<< Input::getMouseDelta().y << std::endl;

		std::cout << "World mouse position: "
			<< Input::getMouseWorldPosition().x << ", "
			<< Input::getMouseWorldPosition().y << std::endl;

		std::cout << "World transform position: "
			<< transform->position.x << ", "
			<< transform->position.y << std::endl;
		*/
	}

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

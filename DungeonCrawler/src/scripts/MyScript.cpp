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
	SpriteRendererPointer spriteRenderer = transform->addComponent<SpriteRenderer>();
	spriteRenderer->setSprite("src/sprites/cutie_cat.png");
	transform->addComponent(spriteRenderer);
	transform->setRenderDepth(1.0f);

	
	weapon = Transform::create();

	// Adding a sprite renderer to the object
	SpriteRendererPointer weaponSpriteRenderer = weapon->addComponent<SpriteRenderer>();
	weaponSpriteRenderer->setSprite("src/sprites/weapon.png");
	weapon->setParent(transform);
	//weapon->setRenderDepth(0.0f);
	
	// Adding a camera to the scene
	TransformPointer cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(4.0f);
	cameraTransform->addComponent(camera);
}

void MyScript::update()
{
	weapon->setRotation(weapon->lookAt(Input::getMouseWorldPosition()));

	glm::mat4 r{ weapon->getTransformMatrix() * weapon->getInverseTransformMatrix() };
	std::cout
		<< r[0][0] << " " << r[0][1] << " " << r[0][2] << " " << r[0][3] << "\n"
		<< r[1][0] << " " << r[1][1] << " " << r[1][2] << " " << r[1][3] << "\n"
		<< r[2][0] << " " << r[2][1] << " " << r[2][2] << " " << r[2][3] << "\n"
		<< r[3][0] << " " << r[3][1] << " " << r[3][2] << " " << r[3][3] << std::endl;

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
		transform->movePosition(glm::vec2(0.0f, 1.0f) * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_S))
	{
		transform->movePosition(glm::vec2(0.0f, -1.0f) * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_A))
	{
		transform->movePosition(glm::vec2(-1.0f, 0.0f) * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_D))
	{
		transform->movePosition(glm::vec2(1.0f, 0.0f) * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_Q))
	{
		transform->rotate(-30.0f * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_E))
	{
		transform->rotate(30.0f * Time::getDeltaTime());
	}
}

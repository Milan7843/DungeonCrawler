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
	Rigidbody::create(transform, b2_dynamicBody, 0.0f, true);

	// Adding a sprite renderer to the object
	SpriteRendererPointer spriteRenderer = SpriteRenderer::create(transform, "src/sprites/cutie_cat.png");
	transform->setRenderDepth(1.0f);

	
	weapon = Transform::create();
	weapon->setScale(glm::vec2(0.8f, 0.4f));
	weapon->setParent(transform);

	// Adding a sprite renderer to the object
	SpriteRendererPointer weaponSpriteRenderer = SpriteRenderer::create(weapon, "src/sprites/weapon.png");

	cat = Transform::create(glm::vec2(2.0f, -1.0f), 90.0f, glm::vec2(0.1f));
	cat->setParent(weapon);

	// Adding a sprite renderer to the cat
	SpriteRendererPointer catSpriteRenderer = SpriteRenderer::create(cat, "src/sprites/cutie_cat.png");


	cat2 = Transform::create();
	cat2->setScale(glm::vec2(0.4f));

	// Adding a sprite renderer to the cat
	SpriteRendererPointer cat2SpriteRenderer = SpriteRenderer::create(cat2, "src/sprites/cutie_cat.png");
	Rigidbody::create(cat2, b2_dynamicBody, 1.0f, false, false);
	
	// Adding a camera to the scene
	TransformPointer cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(cameraTransform, 8.0f);


	// Creating a wall
	//TransformPointer wall = Transform::create(glm::vec2(5.0f, 0.0f), 0.0f, glm::vec2(1.0f, 5.0f));
	TransformPointer wall = Transform::create(glm::vec2(0.0f, -3.0f), 0.0f, glm::vec2(6.0f, 0.5f));
	SpriteRenderer::create(wall, "src/sprites/Wiskunde.png");
	Rigidbody::create(wall, b2_staticBody);
}

void MyScript::update()
{
	weapon->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	//transform->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	
	/*
	std::cout
		<< r[0][0] << " " << r[1][0] << " " << r[2][0] << " " << r[3][0] << "\n"
		<< r[0][1] << " " << r[1][1] << " " << r[2][1] << " " << r[3][1] << "\n"
		<< r[0][2] << " " << r[1][2] << " " << r[2][2] << " " << r[3][2] << "\n"
		<< r[0][3] << " " << r[1][3] << " " << r[2][3] << " " << r[3][3] << std::endl;
	*/

	if (Input::getKeyPressed(KEY_F)) {
		//cat2->setPosition(cat->localPointToWorldPoint(glm::vec2(0.0f, 0.0f)));
		//cat->setPosition(weapon->worldPointToLocalPoint(glm::vec2(1.0f, 0.0f)));
		//glm::vec2 r = cat->localPointToWorldPoint(glm::vec2(0.0f, 0.0f));
		//std::cout << cat2->getPosition().x << ", " << cat2->getPosition().y << std::endl;
		//std::cout << r.x << ", " << r.y << std::endl;
		/*
		std::cout << transform->toString() << std::endl;
		std::cout << weapon->toString()<< std::endl;
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

	//std::cout << transform->getLocalPosition().x << ", " << transform->getLocalPosition().y << std::endl;

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

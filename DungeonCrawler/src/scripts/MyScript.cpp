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
	weapon->setScale(glm::vec2(0.8f, 0.4f));
	weapon->setParent(transform);

	cat = Transform::create();

	// Adding a sprite renderer to the cat
	SpriteRendererPointer catSpriteRenderer = cat->addComponent<SpriteRenderer>();
	catSpriteRenderer->setSprite("src/sprites/cutie_cat.png");
	cat->setPosition(glm::vec2(2.0f, -1.0f));
	cat->setRotation(90.0f);
	cat->setScale(glm::vec2(0.1f));
	cat->setParent(weapon);

	cat2 = Transform::create();
	cat2->setScale(glm::vec2(0.2f));

	// Adding a sprite renderer to the cat
	SpriteRendererPointer cat2SpriteRenderer = cat2->addComponent<SpriteRenderer>();
	cat2SpriteRenderer->setSprite("src/sprites/cutie_cat.png");
	
	// Adding a camera to the scene
	TransformPointer cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(8.0f);
	cameraTransform->addComponent(camera);

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

#include "MyScript.h"

MyScript::MyScript()
	: collisionCallbackHandler()
{
	Physics::setCollisionListener(&collisionCallbackHandler);
}

MyScript::~MyScript()
{

}

void MyScript::start()
{
	// Adding an object to the scene
	transform = Transform::create();
	transform->setName("player");

	// Adding a script to this object
	std::shared_ptr<MyComponentScript> myComponentScript = std::shared_ptr<MyComponentScript>(new MyComponentScript());
	transform->addComponent(myComponentScript);
	Rigidbody::create(transform, b2_dynamicBody, 0.0f, true, false);

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
	cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(cameraTransform, 8.0f);


	// Creating a wall
	//TransformPointer wall = Transform::create(glm::vec2(5.0f, 0.0f), 0.0f, glm::vec2(1.0f, 5.0f));
	TransformPointer wall = Transform::create(glm::vec2(0.0f, -3.0f), 0.0f, glm::vec2(6.0f, 0.5f));
	wall->setName("Wall");
	SpriteRendererPointer wallSpriteRenderer = SpriteRenderer::create(wall, "src/sprites/Wiskunde.png");
	Rigidbody::create(wall, b2_staticBody);



	particleSystemTransform = Transform::create(glm::vec2(2.0f, 1.0f));
	particleSystem = ParticleSystem::create(particleSystemTransform);
	Gradient<glm::vec3> colorGradient = Gradient<glm::vec3>(std::vector<GradientPoint<glm::vec3>>{ 
		{ 0.0f, glm::vec3(1.0f) },
		{ 0.5f, glm::vec3(0.1f, 0.9f, 0.6f) },
		{ 0.9f, glm::vec3(0.9f, 0.2f, 0.8f) } });
	Gradient<glm::vec2> sizeGradient = Gradient<glm::vec2>(std::vector<GradientPoint<glm::vec2>>{
		{ 0.0f, glm::vec2(0.0f) },
		{ 0.1f, glm::vec2(1.0f) },
		{ 0.8f, glm::vec2(1.0f) },
		{ 1.0f, glm::vec2(0.0f) } 
	});
	particleSystem->setColorOverLifeTimeGradient(colorGradient);
	particleSystem->setSizeOverLifeTimeGradient(sizeGradient);
	particleSystem->setSprite("src/sprites/cutie_cat.png");
	particleSystem->setOnFinish(REPEAT);
	particleSystem->play();


	Renderer::addScreenSpaceEffect(ScreenSpaceEffect::create("src/shaders/screenSpaceFragment.shader"));
	Renderer::Bloom::setEnabled(true);
	Renderer::Bloom::setThreshold(0.7f);
	Renderer::Bloom::setIntensity(0.5f);
	Renderer::setMSAAQualityLevel(2);



	Gradient<glm::vec2> particleSystemMoveAnimationGradient = Gradient<glm::vec2>(std::vector<GradientPoint<glm::vec2>>{
		{ 0.0f, glm::vec2(2.0f, 1.0f) },
		{ 0.1f, glm::vec2(1.0f, 1.0f) },
		{ 0.8f, glm::vec2(2.0f, 2.0f) },
		{ 1.0f, glm::vec2(0.0f, 1.0f) },
		{ 1.5f, glm::vec2(2.0f, 1.0f) }
	});
	ValueAnimation<glm::vec2>* particleSystemMoveAnimation
		= ValueAnimation<glm::vec2>::create(&particleSystemAnimation, &particleSystemPosition, particleSystemMoveAnimationGradient);
	particleSystemMoveAnimation->setDuration(1.5f);
}

void MyScript::update()
{
	//weapon->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	float requestedRotation = transform->lookAt(Input::getMouseWorldPosition());
	weapon->setRotation(Math::smoothRotate(weapon->getRotation(), requestedRotation, 5.0f, 240.0f));
	//transform->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	
	particleSystemAnimation.update();
	particleSystemTransform->setPosition(particleSystemPosition);

	if (Input::getKeyPressed(KEY_B))
	{
		particleSystemAnimation.play();
	}

	/*
	std::cout
		<< r[0][0] << " " << r[1][0] << " " << r[2][0] << " " << r[3][0] << "\n"
		<< r[0][1] << " " << r[1][1] << " " << r[2][1] << " " << r[3][1] << "\n"
		<< r[0][2] << " " << r[1][2] << " " << r[2][2] << " " << r[3][2] << "\n"
		<< r[0][3] << " " << r[1][3] << " " << r[2][3] << " " << r[3][3] << std::endl;
	*/

	if (Input::getKey(KEY_F)) {
		cameraTransform->setPosition(
			Math::move(cameraTransform->getPosition(), transform->getPosition(), 4.0f));
	}
	if (Input::getKey(KEY_Z))
	{
		cameraTransform->rotate(-30.0f * Time::getDeltaTime());
	}
	if (Input::getKey(KEY_X))
	{
		cameraTransform->rotate(30.0f * Time::getDeltaTime());
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

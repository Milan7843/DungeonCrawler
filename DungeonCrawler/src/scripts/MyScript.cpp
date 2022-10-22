#include "MyScript.h"

#include <functional>

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
	playerSpriteRenderer = SpriteRenderer::create(transform, "src/sprites/test_sprite_sheet_directions.png", true, 4, 4);
	transform->setRenderDepth(1.0f);
	
	weapon = Transform::create(glm::vec2(1.0f, 0.0f));
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
	//Renderer::Bloom::setEnabled(true);
	Renderer::Bloom::setThreshold(0.7f);
	Renderer::Bloom::setIntensity(0.5f);
	Renderer::setMSAAQualityLevel(2);

	createPlayerAnimator();
}

void MyScript::update()
{
	//weapon->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	float requestedRotation = weapon->lookAt(weapon->worldPointToParentLocalPoint(Input::getMouseWorldPosition()));
	weapon->setRotation(Math::smoothRotate(weapon->getRotation(), requestedRotation, 5.0f, 240.0f));
	//transform->setRotation(transform->lookAt(Input::getMouseWorldPosition()));

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

	AnimationHandler::setAnimationWebParameter("player_sprite", "up", Input::getKey(KEY_W));
	AnimationHandler::setAnimationWebParameter("player_sprite", "down", Input::getKey(KEY_S));
	AnimationHandler::setAnimationWebParameter("player_sprite", "left", Input::getKey(KEY_A));
	AnimationHandler::setAnimationWebParameter("player_sprite", "right", Input::getKey(KEY_D));
}

void MyScript::createPlayerAnimator()
{
	float arrowAnimationDuration{ 1.0f };

	// Creating an animation for the up direction
	Animation playerMoveUpAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveUpSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveUpAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 3, arrowAnimationDuration));
	playerMoveUpSetColumnIndexAnimation->setDuration(arrowAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveUpSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveUpAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(3)); // Row index 3 for up
	playerMoveUpSetRowIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the up direction
	Animation playerMoveRightAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveRightSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveRightAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 3, arrowAnimationDuration));
	playerMoveRightSetColumnIndexAnimation->setDuration(arrowAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveRightSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveRightAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(2)); // Row index 2 for right
	playerMoveRightSetRowIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the down direction
	Animation playerMoveDownAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveDownSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveDownAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 3, arrowAnimationDuration));
	playerMoveDownSetColumnIndexAnimation->setDuration(arrowAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveDownSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveDownAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(1)); // Row index 1 for down
	playerMoveDownSetRowIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the left direction
	Animation playerMoveLeftAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveLeftSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveLeftAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 3, arrowAnimationDuration));
	playerMoveLeftSetColumnIndexAnimation->setDuration(arrowAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* playerMoveLeftSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&playerMoveLeftAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(0)); // Row index 0 for left
	playerMoveLeftSetRowIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation web to add the animations to
	AnimationWeb playerAnimationWeb;

	playerAnimationWeb.addAnimation(playerMoveUpAnimation, "up");
	playerAnimationWeb.addAnimation(playerMoveRightAnimation, "right", true);
	playerAnimationWeb.addAnimation(playerMoveDownAnimation, "down");
	playerAnimationWeb.addAnimation(playerMoveLeftAnimation, "left");

	// Creating links from up to the others
	playerAnimationWeb.createLink("up", "right", false);
	playerAnimationWeb.createLink("up", "down", false);
	playerAnimationWeb.createLink("up", "left", false);
	playerAnimationWeb.addConditionToLink("up", "left", "left", true);
	playerAnimationWeb.addConditionToLink("up", "right", "right", true);
	playerAnimationWeb.addConditionToLink("up", "down", "down", true);

	// Creating links from right to the others
	playerAnimationWeb.createLink("right", "up", false);
	playerAnimationWeb.createLink("right", "down", false);
	playerAnimationWeb.createLink("right", "left", false);
	playerAnimationWeb.addConditionToLink("right", "up", "up", true);
	playerAnimationWeb.addConditionToLink("right", "left", "left", true);
	playerAnimationWeb.addConditionToLink("right", "down", "down", true);

	// Creating links from down to the others
	playerAnimationWeb.createLink("down", "up", false);
	playerAnimationWeb.createLink("down", "right", false);
	playerAnimationWeb.createLink("down", "left", false);
	playerAnimationWeb.addConditionToLink("down", "up", "up", true);
	playerAnimationWeb.addConditionToLink("down", "right", "right", true);
	playerAnimationWeb.addConditionToLink("down", "left", "left", true);

	// Creating links from left to the others
	playerAnimationWeb.createLink("left", "up", false);
	playerAnimationWeb.createLink("left", "right", false);
	playerAnimationWeb.createLink("left", "down", false);
	playerAnimationWeb.addConditionToLink("left", "up", "up", true);
	playerAnimationWeb.addConditionToLink("left", "right", "right", true);
	playerAnimationWeb.addConditionToLink("left", "down", "down", true);

	playerAnimationWeb.addParameter("up", false);
	playerAnimationWeb.addParameter("right", true);
	playerAnimationWeb.addParameter("down", false);
	playerAnimationWeb.addParameter("left", false);

	AnimationHandler::addAnimationWeb(playerAnimationWeb, "player_sprite");
}

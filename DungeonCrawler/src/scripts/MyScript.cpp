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

	createPlayerAnimator();
}

void MyScript::update()
{
	//weapon->setRotation(transform->lookAt(Input::getMouseWorldPosition()));
	float requestedRotation = transform->lookAt(Input::getMouseWorldPosition());
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
}

void MyScript::createPlayerAnimator()
{
	float arrowAnimationDuration{ 2.0f };

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
			Gradient<unsigned int>(0)); // Row index 0 for up
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
			Gradient<unsigned int>(1)); // Row index 1 for right
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
			Gradient<unsigned int>(2)); // Row index 2 for down
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
			Gradient<unsigned int>(3)); // Row index 3 for left
	playerMoveLeftSetRowIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animator to add the animations to
	Animator playerAnimator;

	playerAnimator.addAnimation(playerMoveUpAnimation, "up");
	playerAnimator.addAnimation(playerMoveRightAnimation, "right", true);
	playerAnimator.addAnimation(playerMoveDownAnimation, "down");
	playerAnimator.addAnimation(playerMoveLeftAnimation, "left");

	// Creating links from up to the others
	playerAnimator.createLink("up", "right");
	playerAnimator.createLink("up", "down");
	playerAnimator.createLink("up", "left");
	playerAnimator.addConditionToLink("up", "left", "left", true);
	playerAnimator.addConditionToLink("up", "right", "right", true);
	playerAnimator.addConditionToLink("up", "down", "down", true);

	// Creating links from right to the others
	playerAnimator.createLink("right", "up");
	playerAnimator.createLink("right", "down");
	playerAnimator.createLink("right", "left");
	playerAnimator.addConditionToLink("right", "up", "up", true);
	playerAnimator.addConditionToLink("right", "left", "left", true);
	playerAnimator.addConditionToLink("right", "down", "down", true);

	// Creating links from down to the others
	playerAnimator.createLink("down", "up");
	playerAnimator.createLink("down", "right");
	playerAnimator.createLink("down", "left");
	playerAnimator.addConditionToLink("down", "up", "up", true);
	playerAnimator.addConditionToLink("down", "right", "right", true);
	playerAnimator.addConditionToLink("down", "left", "left", true);

	// Creating links from left to the others
	playerAnimator.createLink("left", "up");
	playerAnimator.createLink("left", "right");
	playerAnimator.createLink("left", "down");
	playerAnimator.addConditionToLink("left", "up", "up", true);
	playerAnimator.addConditionToLink("left", "right", "right", true);
	playerAnimator.addConditionToLink("left", "down", "down", true);

	playerAnimator.addParameter("up", false);
	playerAnimator.addParameter("right", true);
	playerAnimator.addParameter("down", false);
	playerAnimator.addParameter("left", false);

	AnimationHandler::addAnimator(playerAnimator, "player_sprite");
}

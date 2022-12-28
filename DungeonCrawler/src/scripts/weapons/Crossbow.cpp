#include "Crossbow.h"

Crossbow::Crossbow(TransformPointer parent)
{
	// Creating a weapon for the player to hold
	transform = Transform::create(glm::vec2(0.0f, -0.1f));
	transform->setScale(glm::vec2(1.6f, 0.8f));
	transform->setParent(parent);

	std::cout << "CHILDREN " << parent->getChildren().size() << std::endl;

	// Adding a sprite renderer to the object
	SpriteRendererPointer spriteRenderer = SpriteRenderer::create(transform, "src/sprites/crossbow.png", glm::vec2(0.2f, 0), true, 9, 1);

	// Creating an animation for the shooting
	Animation shootAnimation;

	float shootAnimationDuration{ 0.4f };

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* shootSubAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&shootAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 0), glm::ivec2(8, 0), shootAnimationDuration));
	shootSubAnimation->setDuration(shootAnimationDuration);

	// Creating an animation for the idle state
	Animation idleAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* idleSubAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&idleAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>(glm::ivec2(0, 0)));


	// Adding the shooting as part of the animation
	AnimationFunctionCallPointer shootArrowFunction = ClassAnimationFunction<Crossbow>::create(this, &Crossbow::spawnArrow);

	shootAnimation.addAnimationFunction(shootArrowFunction, 0.2f);
	
	// Creating an animation web to add the animations to
	AnimationWeb animationWeb;

	animationWeb.addAnimation(idleAnimation, "idle", true); // Default state
	animationWeb.addAnimation(shootAnimation, "shoot");

	animationWeb.createLink("idle", "shoot", false);
	animationWeb.createLink("shoot", "idle", true);

	animationWeb.addConditionToLink("idle", "shoot", "action_shoot", ConditionType::TRIGGER);

	//std::cout << animationWeb.toString() << std::endl;

	AnimationHandler::addAnimationWeb(animationWeb, "crossbow");


	bulletCollider = BoxCollider::create(0.1f, 0.1f, LAYER_1, LAYER_ALL - LAYER_1);


	firePoint = Transform::create(glm::vec2(0.6f, 0.0f));
	firePoint->setParent(transform);
}

Crossbow::~Crossbow()
{
}

void Crossbow::shoot()
{
	AnimationHandler::setAnimationWebParameter("crossbow", "action_shoot", true);
	//spawnArrow();
}

void Crossbow::spawnArrow()
{
	//Audio::playSound("shoot");

	Transform* bullet = Transform::create(transform->getPosition(), transform->getRotation(), glm::vec2(0.6f));
	bullet->setName("bullet");
	bullet->setTag("bullet");
	Rigidbody::create(bullet, bulletCollider, DYNAMIC, 0.0f, true);

	bullet->getComponent<Rigidbody>()->setLinearVelocity(bullet->getLocalRightVector() * 12.0f);

	SpriteRenderer::create(bullet, "src/sprites/arrow.png", glm::vec2(0.0f), true);
	float height{ 0.3f };
	bullet->setScale(glm::vec2(height * 11.0f / 3.0f, height));

	std::shared_ptr<Bullet> bulletScript = std::shared_ptr<Bullet>(new Bullet());
	bullet->addComponent(bulletScript);
}

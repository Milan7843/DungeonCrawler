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

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* shootSubAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&shootAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 0), glm::ivec2(8, 0), 0.35f));

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

	
	// Creating an animation web to add the animations to
	AnimationWeb animationWeb;

	animationWeb.addAnimation(idleAnimation, "idle", true); // Default state
	animationWeb.addAnimation(shootAnimation, "shoot");

	animationWeb.createLink("idle", "shoot", false);
	animationWeb.createLink("shoot", "idle", true);

	animationWeb.addConditionToLink("idle", "shoot", "action_shoot", ConditionType::TRIGGER);

	std::cout << animationWeb.toString() << std::endl;

	AnimationHandler::addAnimationWeb(animationWeb, "crossbow");
}

Crossbow::~Crossbow()
{
}

void Crossbow::shoot()
{
	AnimationHandler::setAnimationWebParameter("crossbow", "action_shoot", true);
}

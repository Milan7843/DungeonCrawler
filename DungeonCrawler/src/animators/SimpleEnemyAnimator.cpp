#include "SimpleEnemyAnimator.h"

AnimatorPointer SimpleEnemyAnimator::create(TransformPointer transform, std::string animationWebTag)
{
	AnimatorPointer animator{ Animator::createBase(transform, animationWebTag) };

	// Get the sprite renderer which will be animated
	SpriteRenderer* spriteRenderer{ transform->getComponent<SpriteRenderer>().get() };

	if (spriteRenderer == nullptr)
	{
		return animator;
	}

	// ======== Creating the animations ========

	float walkAnimationDuration{ 0.3f };

	// Creating an animation for the up right direction
	Animation moveUpRightAnimation;

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveUpRightSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveUpRightAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 2, walkAnimationDuration));
	moveUpRightSetColumnIndexAnimation->setDuration(walkAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveUpRightSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveUpRightAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(1)); // Row index 1 for up right
	moveUpRightSetRowIndexAnimation->setDuration(walkAnimationDuration);


	// Creating an animation for the up left direction
	Animation moveUpLeftAnimation;

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveUpLeftSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveUpLeftAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 2, walkAnimationDuration));
	moveUpLeftSetColumnIndexAnimation->setDuration(walkAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveUpLeftSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveUpLeftAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(0)); // Row index 0 for up left
	moveUpLeftSetRowIndexAnimation->setDuration(walkAnimationDuration);


	// Creating an animation for the down right direction
	Animation moveDownRightAnimation;

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveDownRightSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveDownRightAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 2, walkAnimationDuration));
	moveDownRightSetColumnIndexAnimation->setDuration(walkAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveDownRightSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveDownRightAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(3)); // Row index 3 for down right
	moveDownRightSetRowIndexAnimation->setDuration(walkAnimationDuration);


	// Creating an animation for the down left direction
	Animation moveDownLeftAnimation;

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveDownLeftSetColumnIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveDownLeftAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetColumnIndex,
			Gradient<unsigned int>::spriteIndexGradient(0, 2, walkAnimationDuration));
	moveDownLeftSetColumnIndexAnimation->setDuration(walkAnimationDuration);

	SetterValueAnimation<unsigned int, SpriteRenderer>* moveDownLeftSetRowIndexAnimation
		= SetterValueAnimation<unsigned int, SpriteRenderer>::create(
			&moveDownLeftAnimation,
			spriteRenderer,
			&SpriteRenderer::setSpriteSheetRowIndex,
			Gradient<unsigned int>(2)); // Row index 2 for down left
	moveDownLeftSetRowIndexAnimation->setDuration(walkAnimationDuration);


	// Creating an animation web to add the animations to
	AnimationWeb animationWeb;

	animationWeb.addAnimation(moveUpRightAnimation, "up_right");
	animationWeb.addAnimation(moveUpLeftAnimation, "up_left", true);
	animationWeb.addAnimation(moveDownRightAnimation, "down_right");
	animationWeb.addAnimation(moveDownLeftAnimation, "down_left");

	// Creating links from up right to the others
	animationWeb.createLink("up_right", "up_left", false);
	animationWeb.createLink("up_right", "down_right", false);
	animationWeb.createLink("up_right", "down_left", false);
	animationWeb.addConditionToLink("up_right", "up_left", "up_left");
	animationWeb.addConditionToLink("up_right", "down_right", "down_right");
	animationWeb.addConditionToLink("up_right", "down_left", "down_left");

	// Creating links from up left to the others
	animationWeb.createLink("up_left", "up_right", false);
	animationWeb.createLink("up_left", "down_right", false);
	animationWeb.createLink("up_left", "down_left", false);
	animationWeb.addConditionToLink("up_left", "up_right", "up_right");
	animationWeb.addConditionToLink("up_left", "down_right", "down_right");
	animationWeb.addConditionToLink("up_left", "down_left", "down_left");

	// Creating links from down right to the others
	animationWeb.createLink("down_right", "up_right", false);
	animationWeb.createLink("down_right", "up_left", false);
	animationWeb.createLink("down_right", "down_left", false);
	animationWeb.addConditionToLink("down_right", "up_right", "up_right");
	animationWeb.addConditionToLink("down_right", "up_left", "up_left");
	animationWeb.addConditionToLink("down_right", "down_left", "down_left");

	// Creating links from down left to the others
	animationWeb.createLink("down_left", "up_right", false);
	animationWeb.createLink("down_left", "up_left", false);
	animationWeb.createLink("down_left", "down_right", false);
	animationWeb.addConditionToLink("down_left", "up_right", "up_right");
	animationWeb.addConditionToLink("down_left", "up_left", "up_left");
	animationWeb.addConditionToLink("down_left", "down_right", "down_right");

	animationWeb.addParameter("up_right", false);
	animationWeb.addParameter("up_left", true); // Looking up-left by default
	animationWeb.addParameter("down_right", false);
	animationWeb.addParameter("down_left", false);

	AnimationHandler::addAnimationWeb(animationWeb, animationWebTag);

	std::cout << animationWeb.toString() << std::endl;

	return animator;
}

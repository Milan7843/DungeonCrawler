#include "PlayerAnimator.h"

AnimatorPointer PlayerAnimator::create(TransformPointer transform, std::string animationWebTag)
{
    AnimatorPointer animator{ Animator::createBase(transform, animationWebTag) };

	SpriteRenderer* playerSpriteRenderer{ transform->getComponent<SpriteRenderer>().get() };
	
	if (playerSpriteRenderer == nullptr)
	{
		return animator;
	}

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
	
	AnimationHandler::addAnimationWeb(playerAnimationWeb, animationWebTag);
	
	return animator;
}

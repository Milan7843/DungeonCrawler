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
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* playerMoveUpSetColumnIndexAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&playerMoveUpAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 3), glm::ivec2(3, 3), arrowAnimationDuration));
	playerMoveUpSetColumnIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the up direction
	Animation playerMoveRightAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* playerMoveRightSetColumnIndexAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&playerMoveRightAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 2), glm::ivec2(3, 2), arrowAnimationDuration)); // Row index 1 for down
	playerMoveRightSetColumnIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the down direction
	Animation playerMoveDownAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* playerMoveDownSetColumnIndexAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&playerMoveDownAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 1), glm::ivec2(3, 1), arrowAnimationDuration)); // Row index 1 for down
	playerMoveDownSetColumnIndexAnimation->setDuration(arrowAnimationDuration);


	// Creating an animation for the left direction
	Animation playerMoveLeftAnimation;

	// Creating a setter value animation (a sub-animation which sets a value via a setter),
	// which is added to the particle system animation
	SetterValueAnimation<glm::ivec2, SpriteRenderer>* playerMoveLeftSetColumnIndexAnimation
		= SetterValueAnimation<glm::ivec2, SpriteRenderer>::create(
			&playerMoveLeftAnimation,
			playerSpriteRenderer,
			&SpriteRenderer::setSpriteSheetIndex,
			Gradient<glm::ivec2>::sprite2DIndexGradient(glm::ivec2(0, 0), glm::ivec2(3, 0), arrowAnimationDuration));
	playerMoveLeftSetColumnIndexAnimation->setDuration(arrowAnimationDuration);


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
	playerAnimationWeb.addConditionToLink("up", "left", "left");
	playerAnimationWeb.addConditionToLink("up", "right", "right");
	playerAnimationWeb.addConditionToLink("up", "down", "down");

	// Creating links from right to the others
	playerAnimationWeb.createLink("right", "up", false);
	playerAnimationWeb.createLink("right", "down", false);
	playerAnimationWeb.createLink("right", "left", false);
	playerAnimationWeb.addConditionToLink("right", "up", "up");
	playerAnimationWeb.addConditionToLink("right", "left", "left");
	playerAnimationWeb.addConditionToLink("right", "down", "down");

	// Creating links from down to the others
	playerAnimationWeb.createLink("down", "up", false);
	playerAnimationWeb.createLink("down", "right", false);
	playerAnimationWeb.createLink("down", "left", false);
	playerAnimationWeb.addConditionToLink("down", "up", "up");
	playerAnimationWeb.addConditionToLink("down", "right", "right");
	playerAnimationWeb.addConditionToLink("down", "left", "left");

	// Creating links from left to the others
	playerAnimationWeb.createLink("left", "up", false);
	playerAnimationWeb.createLink("left", "right", false);
	playerAnimationWeb.createLink("left", "down", false);
	playerAnimationWeb.addConditionToLink("left", "up", "up");
	playerAnimationWeb.addConditionToLink("left", "right", "right");
	playerAnimationWeb.addConditionToLink("left", "down", "down");

	playerAnimationWeb.addParameter("up", false);
	playerAnimationWeb.addParameter("right", true);
	playerAnimationWeb.addParameter("down", false);
	playerAnimationWeb.addParameter("left", false);
	
	AnimationHandler::addAnimationWeb(playerAnimationWeb, animationWebTag);
	
	return animator;
}

#pragma once

#include <Root/components/Animator.h>
#include <Root/animation/SetterValueAnimation.h>
#include <Root/animation/AnimationWeb.h>

#include <Root/rendering/SpriteRenderer.h>

class SimpleEnemyAnimator : public Animator
{
public:

	/**
	 * Create a new simple enemy animator.
	 * Will automatically add this component to the given transform.
	 *
	 * \param transform:		the transform to add this component to.
	 * \param animationWebTag:	the tag of the animator.
	 */
	static AnimatorPointer create(
		TransformPointer transform,
		std::string animationWebTag);

private:

};

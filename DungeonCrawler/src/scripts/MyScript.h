#pragma once

#include "MyComponentScript.h"

#include "scripts/MyComponentScript.h"
#include "scripts/CollisionCallbackHandler.h"

#include <Root/Root.h>
#include <Root/Components.h>
#include <Root/Physics.h>
#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/Input.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/animation/ValueAnimation.h>
#include <Root/animation/SetterValueAnimation.h>

class MyScript : public Script
{
public:
	MyScript();
	~MyScript();

	void start() override;

	void update() override;

	void createPlayerAnimator();

private:
	TransformPointer transform;
	SpriteRendererPointer playerSpriteRenderer;
	TransformPointer weapon;
	TransformPointer cameraTransform;
	TransformPointer cat;
	TransformPointer cat2;
	ParticleSystemPointer particleSystem;
	TransformPointer particleSystemTransform;
	CollisionCallbackHandler collisionCallbackHandler;
};

#pragma once

#include "MyComponentScript.h"

#include "scripts/MyComponentScript.h"
#include "scripts/Player.h"
#include "scripts/CollisionCallbackHandler.h"
#include "animators/PlayerAnimator.h"

#include <Root/Root.h>
#include <Root/Components.h>
#include <Root/Physics.h>
#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/Input.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/animation/ValueAnimation.h>
#include <Root/animation/SetterValueAnimation.h>

class GameManager : public Script
{
public:
	GameManager();
	~GameManager();

	void start() override;

	void update() override;

private:

	void initialisePlayer();

	TransformPointer player;
	SpriteRendererPointer playerSpriteRenderer;
	TransformPointer cameraTransform;
	ParticleSystemPointer particleSystem;
	TransformPointer particleSystemTransform;
	CollisionCallbackHandler collisionCallbackHandler;
};

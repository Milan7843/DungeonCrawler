#pragma once

#include "animators/SimpleEnemyAnimator.h"
#include "scripts/enemies/SimpleEnemy.h"

#include <Root/Root.h>
#include <Root/Components.h>
#include <Root/Physics.h>
#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/Input.h>
#include <Root/animation/AnimationHandler.h>
#include <Root/animation/ValueAnimation.h>
#include <Root/animation/SetterValueAnimation.h>
#include <Root/Audio.h>

#include <Root/colliders/BoxCollider.h>

namespace EnemySpawner
{
	void spawnEnemy();
};


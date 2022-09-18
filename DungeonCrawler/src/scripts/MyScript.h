#pragma once

#include "MyComponentScript.h"

#include "scripts/MyComponentScript.h"

#include <Root/Root.h>
#include <Root/Script.h>
#include <Root/rendering/Camera.h>
#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/rendering/SpriteRenderer.h>

class MyScript : public Script
{
public:
	MyScript();
	~MyScript();

	void start() override;

	void update() override;

private:
};

#pragma once

#include "MyComponentScript.h"

#include "scripts/MyComponentScript.h"

#include <Root/Root.h>
#include <Root/Components.h>
#include <Root/Logger.h>
#include <Root/Transform.h>
#include <Root/Input.h>

class MyScript : public Script
{
public:
	MyScript();
	~MyScript();

	void start() override;

	void update() override;

private:
	TransformPointer transform;
	TransformPointer weapon;
	TransformPointer cat;
	TransformPointer cat2;
};

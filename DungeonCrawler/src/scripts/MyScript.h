#pragma once

#include "MyComponentScript.h"

#include "scripts/MyComponentScript.h"

#include <Root/Root.h>
#include <Root/Script.h>
#include <Root/Logger.h>
#include <Root/Transform.h>

class MyScript : public Script
{
public:
	MyScript();
	~MyScript();

	void start() override;

	void update() override;

private:
};

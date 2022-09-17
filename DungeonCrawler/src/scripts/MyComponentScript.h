#pragma once

#include <Root/Script.h>
#include <Root/Logger.h>
#include <Root/Transform.h>

class MyComponentScript : public Component
{
public:
	MyComponentScript();
	~MyComponentScript();

	void start() override;

	void update() override;

private:
};

#pragma once

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

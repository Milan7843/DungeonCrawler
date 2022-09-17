#pragma once

#include <Root/Script.h>
#include <Root/Logger.h>

class MyScript : public Script
{
public:
	MyScript();
	~MyScript();

	void start() override;

	void update() override;

private:
};

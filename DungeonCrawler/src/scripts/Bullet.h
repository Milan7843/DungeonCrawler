#pragma once

#include <Root/Transform.h>
#include <Root/Time.h>

class Bullet : public Component
{
public:
	Bullet();
	~Bullet();

	void start() override;

	void update() override;
};


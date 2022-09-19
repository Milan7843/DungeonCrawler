#pragma once

#include "Root/Component.h" // Base class
#include "Root/Logger.h"

#include <memory>

class Animator : public Component
{
public:

	Animator();
	~Animator();

	std::shared_ptr<Animator> create();

private:


};


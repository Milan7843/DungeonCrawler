#pragma once

#include "Root/components/Component.h" // Base class
#include "Root/Logger.h"

#include <memory>

#define AnimatorPointer std::shared_ptr<Animator>

class Animator : public Component
{
public:

	/**
	 * Create a new Animator component.
	 * Requires a SpriteRenderer component.
	 */
	Animator();
	~Animator();

	std::shared_ptr<Animator> create();

private:


};


#include "Animator.h"

Animator::~Animator()
{
	Logger::destructorMessage("Animator destroyed.");
}

std::shared_ptr<Animator> Animator::create()
{
	return std::shared_ptr<Animator>();
}

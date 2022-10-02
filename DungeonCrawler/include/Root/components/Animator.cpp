#include "Animator.h"

Animator::~Animator()
{
	Logger::destructorMessage("Animator");
}

std::shared_ptr<Animator> Animator::create()
{
	return std::shared_ptr<Animator>();
}

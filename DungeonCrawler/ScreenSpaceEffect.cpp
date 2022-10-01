#include "ScreenSpaceEffect.h"

ScreenSpaceEffect::~ScreenSpaceEffect()
{
	Logger::destructorMessage("Destroyed screen space effect.");
}

void ScreenSpaceEffect::run()
{

}

ScreenSpaceEffectPointer ScreenSpaceEffect::create(const std::string& shaderPath)
{
	ScreenSpaceEffect* screenSpaceEffect = new ScreenSpaceEffect();
	std::shared_ptr<ScreenSpaceEffect> pointer{ screenSpaceEffect };
	return pointer;
}

void ScreenSpaceEffect::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

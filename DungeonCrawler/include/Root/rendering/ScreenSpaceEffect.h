#pragma once

#include "Root/shaders/Shader.h"

#include <memory>
#include <string>

#define ScreenSpaceEffectPointer std::shared_ptr<ScreenSpaceEffect>

/**
 * Screen space effect shader template:



 */

/**
 * Class that encompasses a shader that will be run for every pixel on the screen,
 * allowing for full-screen post-processing effects.
 * Go to the class definition to see a template for a screen space effect shader.
 */
class ScreenSpaceEffect : public Shader
{
public:

	~ScreenSpaceEffect();

	void run();

	static ScreenSpaceEffectPointer create(const std::string& shaderPath);

	void setEnabled(bool enabled);

private:

	// Private constructor: use create()
	ScreenSpaceEffect(const std::string& shaderPath);

	ScreenSpaceEffectPointer self;

	const char* vertexShaderPath{"include/Root/shaders/default_shader_source/screenSpaceVertex.shader"};

	bool enabled{ true };

};


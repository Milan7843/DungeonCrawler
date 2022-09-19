#pragma once

#include "Root/Root.h"
#include "Root/Logger.h"
#include "Root/Component.h" // Base class
#include "Root/shaders/Shader.h"
#include "Root/rendering/Renderer.h"
#include "Root/rendering/Camera.h"

#include <stbi_utility/TextureData.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * Component for rendering sprites.
 */
class SpriteRenderer : public Component
{
public:

	SpriteRenderer();
	~SpriteRenderer();

	void render() override;

	/**
	 * Set the sprite used by this sprite renderer.
	 * 
	 * \param spritePath: the path to the sprite to set.
	 */
	void setSprite(const char* spritePath);

private:

	unsigned int textureID{ 0 };

};

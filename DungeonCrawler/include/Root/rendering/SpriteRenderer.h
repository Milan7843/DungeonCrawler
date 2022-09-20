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

#define SpriteRendererPointer std::shared_ptr<SpriteRenderer>

/**
 * Component for rendering sprites.
 */
class SpriteRenderer : public Component
{
public:
	~SpriteRenderer();

	/**
	 * Create a new sprite renderer.
	 */
	static std::shared_ptr<SpriteRenderer> create();

	/**
	 * Get a string representing this Component.
	 *
	 * \returns this Component in a human-readable format.
	 */
	std::string toString() override;

	void render(float renderDepth) override;

	/**
	 * Set the sprite used by this sprite renderer.
	 * 
	 * \param spritePath: the path to the sprite to set.
	 */
	void setSprite(const char* spritePath);

private:

	SpriteRenderer();

	unsigned int textureID{ 0 };

};

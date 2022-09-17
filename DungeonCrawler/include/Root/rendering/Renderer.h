#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer
{
	/**
	 * Initialise the renderer.
	 */
	void initialise();

	/**
	 * Get the index of a vertex array object which holds information to draw a square.
	 */
	unsigned int getSquareVAO();
};

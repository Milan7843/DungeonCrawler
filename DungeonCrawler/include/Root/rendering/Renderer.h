#pragma once

#include <Root/rendering/ScreenSpaceEffect.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>


namespace Renderer
{
	/**
	 * Initialise the renderer.
	 */
	void initialise(unsigned int width, unsigned int height);

	/**
	 * Terminate the renderer.
	 */
	void terminate();

	/**
	 * Start a new frame.
	 */
	void newFrame();

	/**
	 * Display the frame.
	 */
	void displayFrame();

	/**
	 * Add a new screen space effect.
	 */
	void addScreenSpaceEffect(ScreenSpaceEffectPointer screenSpaceEffect);

	void runScreenSpaceEffects();

	void runScreenSpaceEffect(ScreenSpaceEffectPointer screenSpaceEffect);

	void setFrameBufferTexture(unsigned int width, unsigned int height);

	/**
	 * Get the index of a vertex array object which holds information to draw a square.
	 */
	unsigned int getSquareVAO();

	/**
	 * Get the index of a vertex array object which holds information to draw a screen overlay rectangle.
	 */
	unsigned int getScreenRectVAO();
};

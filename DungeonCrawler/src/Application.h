#pragma once

#include "simpleprofiler/Profiler.h"

#include <simpletext/SimpleText.h>
#include <simplegui/SimpleGUI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Application
{
public:
	Application(unsigned int WIDTH, unsigned int HEIGHT);
	~Application();

	// Start up the application
	int Start();

private:

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	bool inRaytraceMode = false;

	unsigned int WINDOW_SIZE_X = 1200, WINDOW_SIZE_Y = 700;

	// Initiatialise GLFW
	void initialiseGLFW();

	// Draw the axes given by the VAO using the given shader from the given camera's perspective
	void drawAxes(unsigned int VAO, Shader& shader, Camera& camera);

	// Generate a VAO for the axes
	void generateAxesVAO();

	// Holds the vertices required for rendering the axes
	unsigned int axesVAO;

	// Hold the vertices required to render the skybox
	void processInput(GLFWwindow* window);
};

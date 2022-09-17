#pragma once

// Matrix math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Logger.h"

class Camera
{
	/* Public members */
public:
	Camera();
	Camera(glm::vec3 pos);
	Camera(glm::vec3 pos, float yaw, float pitch);
	Camera(glm::vec3 pos, float yaw, float pitch, float sensitivity, float fov, float cameraSpeed);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(int width, int height);

	virtual glm::vec3 getPosition();
	glm::vec3 getRotation();
	float getFov();

	// Don't use the current mouse offset, but start from where the cursor is
	void resetMouseOffset();

	// Process the input to the camera
	virtual void processInput(GLFWwindow* window, float deltaTime);

	// Callback for when the mouse is moved
	virtual void mouseCallback(GLFWwindow* window, double xpos, double ypos, float deltaTime);

	// Get important information of this camera (position, rotation)
	std::string getInformation();

	// Get the forward direction of the camera
	virtual glm::vec3 getForward();

	float* getCameraSpeedPointer();
	float* getFovPointer();
	float* getSensitivityPointer();

	/* Private members */
protected:

	void verifyVectors();

	glm::quat qRotation{ glm::identity<glm::quat>() };

	// Camera postion data
	glm::vec3 position = glm::vec3(4.0f, 3.5f, 1.5f);
	glm::vec3 up;
	glm::vec3 forward;
	float lastx = 400, lasty = 300;
	float yaw{ 200.0f }, pitch{ 0.0f }, roll{ 0.0f };
	bool firstMouse = true;
	unsigned int ssbo;

	float sensitivity = 1.0f;
	float fov = 60.0f;
	float cameraSpeed = 1.0f;
};
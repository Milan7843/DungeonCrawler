#include "Camera.h"

Camera::Camera()
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(direction);
}
Camera::Camera(glm::vec3 pos)
	: position(pos)
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(direction);
}
Camera::Camera(glm::vec3 pos, float yaw, float pitch)
	: position(pos)
	, yaw(yaw)
	, pitch(pitch)
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(direction);
}
Camera::Camera(glm::vec3 pos, float yaw, float pitch, float sensitivity, float fov, float cameraSpeed)
	: position(pos)
	, yaw(yaw)
	, pitch(pitch)
	, sensitivity(sensitivity)
	, fov(fov)
	, cameraSpeed(cameraSpeed)
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(direction);
}
Camera::~Camera()
{
	Logger::log("Camera destroyed");
}

glm::mat4 Camera::getViewMatrix()
{
	// Calculating the up vector, keeping the roll in mind
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(roll), forward);
	rotationMatrix = glm::toMat4(qRotation);
	glm::vec4 upVector = rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	//                           cam pos,  target,             up vector
	glm::mat4 view = glm::lookAt(position, position + forward, glm::vec3(upVector.x, upVector.y, upVector.z));
	return view;
}
glm::mat4 Camera::getProjectionMatrix(int width, int height)
{
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 1000.0f);
	return projection;
}

glm::vec3 Camera::getPosition()
{
	return glm::vec3(position.x, position.y, position.z);
}
glm::vec3 Camera::getRotation()
{
	return glm::vec3(0.0f, glm::radians(yaw), -glm::radians(pitch));
}

float Camera::getFov()
{
	return fov;
}


void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos, float deltaTime)
{
	// Sets the mouse offset by frame appropriately for the first frame
	if (firstMouse)
	{
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos; // reversed since y-coordinates range from bottom to top
	lastx = xpos;
	lasty = ypos;

	xoffset *= sensitivity * 0.1f;
	yoffset *= sensitivity * 0.1f;

	// Applying rotation
	yaw += xoffset;
	pitch += yoffset;

	// Making sure the pitch stays within bounds
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Making sure everything stays within bounds
	verifyVectors();
}

std::string Camera::getInformation()
{
	return "Camera position: ("
		+ std::to_string(getPosition().x) + ", "
		+ std::to_string(getPosition().y) + ", "
		+ std::to_string(getPosition().z) + 
		"), pitch: " + std::to_string(pitch)
		+ ", yaw: " + std::to_string(yaw);
}

glm::vec3 Camera::getForward()
{
	return forward;
}

float* Camera::getCameraSpeedPointer()
{
	return &cameraSpeed;
}

float* Camera::getFovPointer()
{
	return &fov;
}

float* Camera::getSensitivityPointer()
{
	return &sensitivity;
}

void Camera::verifyVectors()
{
	// Making sure the pitch stays within bounds
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Making sure the roll stays within bounds
	if (roll > 89.0f)
		roll = 89.0f;
	if (roll < -89.0f)
		roll = -89.0f;

	// Setting the new vectors
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(direction);
}

void Camera::resetMouseOffset()
{
	firstMouse = true;
}

// Processes the input
void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	float realSpeed = cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		realSpeed *= 3;

	// FORWARD/BACKWARD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += realSpeed * forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= realSpeed * forward;

	// SIDE/SIDE
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(forward, up)) * realSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(forward, up)) * realSpeed;

	// UP/DOWN
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		position += realSpeed * up;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		position -= realSpeed * up;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
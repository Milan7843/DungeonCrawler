#include "Camera.h"

Camera::Camera(float cameraHeight)
	: cameraHeight(cameraHeight)
{
	// If no camera was active, set this camera to be active
	if (RootEngine::getActiveCamera() == nullptr)
		setAsActiveCamera();
}

Camera::~Camera()
{
	// If this was the active camera, we must tell Root no camera is active.
	if (RootEngine::getActiveCamera() == this)
		RootEngine::setActiveCamera(nullptr);

	Logger::destructorMessage("Camera destroyed");
}

glm::mat4 Camera::getProjectionMatrix()
{
	float aspectRatio{ (float)RootEngine::getScreenWidth() / (float)RootEngine::getScreenHeight() };
	// The projection matrix maps [-aspectRatio, aspectRatio] to [-1, 1] horizontally,
	// and [-1, 1] to [-1, 1] vertically
	return glm::ortho(
		-aspectRatio * (cameraHeight / 2.0f), 
		aspectRatio * (cameraHeight / 2.0f),
		-1.0f * (cameraHeight / 2.0f), 
		1.0f * (cameraHeight / 2.0f), 
		-1.0f, 1.0f);
}

void Camera::setAsActiveCamera()
{
	RootEngine::setActiveCamera(this);
}

std::shared_ptr<Camera> Camera::create(float cameraHeight)
{
	Camera* transform = new Camera(cameraHeight);
	std::shared_ptr<Camera> pointer{ transform };
	return pointer;
}

glm::vec2 Camera::worldToScreenPosition(glm::vec2 worldPosition)
{
	return glm::vec2(
		glm::vec4(worldPosition.x, worldPosition.y, 0.0f, 1.0f)
		* RootEngine::getActiveCamera()->getProjectionMatrix());
}

glm::vec2 Camera::screenToWorldPosition(glm::vec2 screenPosition)
{
	// First converting screenPosition from [0, width], [0, height] to [-1, 1], [-1, 1]
	screenPosition = glm::vec2(
		(screenPosition.x / (float)RootEngine::getScreenWidth()) * 2.0f - 1.0f,
		(screenPosition.y / (float)RootEngine::getScreenHeight()) * 2.0f - 1.0f
	);

	// Invering vertically
	screenPosition.y *= -1;

	// Then convering to world position
	float aspectRatio{ (float)RootEngine::getScreenWidth() / (float)RootEngine::getScreenHeight() };
	screenPosition.x *= aspectRatio;
	glm::vec2 worldPosition = screenPosition * (cameraHeight / 2.0f);

	return worldPosition;
}

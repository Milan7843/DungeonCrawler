#include "Camera.h"

Camera::Camera(float cameraHeight)
	: cameraHeight(cameraHeight)
{
	// If no camera was active, set this camera to be active
	if (Root::getActiveCamera() == nullptr)
		setAsActiveCamera();
}

Camera::~Camera()
{
	// If this was the active camera, we must tell Root no camera is active.
	if (Root::getActiveCamera() == this)
		Root::setActiveCamera(nullptr);

	Logger::destructorMessage("Camera destroyed");
}

glm::mat4 Camera::getProjectionMatrix()
{
	float aspectRatio{ (float)Root::getScreenWidth() / (float)Root::getScreenHeight() };
	// The projection matrix maps [-aspectRatio, aspectRatio] to [-1, 1] horizontally,
	// and [-1, 1] to [-1, 1] vertically
	return glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
}

void Camera::setAsActiveCamera()
{
	Root::setActiveCamera(this);
}

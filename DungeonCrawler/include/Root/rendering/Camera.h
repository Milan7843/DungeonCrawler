#pragma once

#include "Root/Component.h" // Base class
#include "Root/Logger.h"
#include "Root/engine/RootEngine.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/**
 * Class that holds information about a camera in a component form.
 */
class Camera : public Component
{
public:

	/**
	 * Create a new Camera.
	 * Will automatically set the active camera to this if no camera was active.
	 *
	 * \param cameraHeight: the height of the camera [optional: default = 2]
	 */
	Camera(float cameraHeight = 2.0f); // Initialize cameraHeight to 2.0

	~Camera();

	/**
	 * Get the projection matrix which belongs to the values of this camera.
	 * 
	 * \return the projection matrix for this camera
	 */
	glm::mat4 getProjectionMatrix();

	/**
	 * Set this camera as the current active one used for rendering.
	 */
	void setAsActiveCamera();

	/**
	 * Create a new Camera.
	 * Will automatically set the active camera to this if no camera was active.
	 *
	 * \param cameraHeight: the height of the camera [optional: default = 2]
	 */
	static std::shared_ptr<Camera> create(float cameraHeight = 2.0f);

private:

	float cameraHeight;
};


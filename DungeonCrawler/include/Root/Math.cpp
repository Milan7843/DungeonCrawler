#include "Math.h"

namespace Math
{
	float move(float value, float target, float speed)
	{
		float diff = (target - value);
		// Check for too little distance
		if (glm::abs(diff) < 0.00001f) {
			return value;
		}

		float move = glm::sign(diff) * speed * Time::getDeltaTime();

		// Check for overshoot
		if (glm::abs(move) > glm::abs(diff)) {
			move = diff;
		}

		return value + move;
	}

	glm::vec2 move(glm::vec2 value, glm::vec2 target, float speed)
	{
		glm::vec2 diff = (target - value);
		// Check for too little distance
		if (glm::abs(diff.x) + glm::abs(diff.y) < 0.00001f) {
			return value;
		}
		glm::vec2 move = glm::normalize(diff) * speed * Time::getDeltaTime();

		// Check for overshoot
		if (glm::length(move) > glm::length(diff)) {
			move = diff;
		}

		return value + move;
	}

	float smoothMove(float value, float target, float speed, float maxVelocity)
	{
		float diff = (target - value);
		float move = diff * speed;

		// Check whether the computed speed stays under the maximum speed
		if (glm::abs(move) > maxVelocity) {
			// If it is, set it to the maximum velocity
			move = glm::sign(move) * maxVelocity;
		}

		return value + move * Time::getDeltaTime();
	}

	glm::vec2 smoothMove(glm::vec2 value, glm::vec2 target, float speed, float maxVelocity)
	{
		glm::vec2 diff = (target - value);
		glm::vec2 move = diff * speed;

		// Check whether the computed speed stays under the maximum speed
		if (glm::length(move) > maxVelocity) {
			// If it is, set it's length to the maximum velocity
			move = glm::normalize(move) * maxVelocity;
		}

		return value + move * Time::getDeltaTime();
	}
};

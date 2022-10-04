#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Math
{
	/**
	 * Lineraly interpolate between two values based on a third value between 0 and 1.
	 * 
	 * \param v1: the first value.
	 * \param v2: the second value.
	 * \param t: the float value between 0 and 1.
	 * \return a linear interpolation of the two values based on the t value.
	 */
	template <typename T>
	T lerp(T v1, T v2, float t)
	{
		if (t <= 0)
			return v1;
		if (t >= 1)
			return v2;

		return (1.0f - t) * v1 + t * v2;
	}

	/**
	 * Use cosine interpolation to interpolate between two values based on a third value between 0 and 1.
	 * http://paulbourke.net/miscellaneous/interpolation/
	 * 
	 * \param v1: the first value.
	 * \param v2: the second value.
	 * \param t: the float value between 0 and 1.
	 * \return a cosine interpolation of the two values based on the t value.
	 */
	template <typename T>
	T cerp(T v1, T v2, float t)
	{
		if (t <= 0)
			return v1;
		if (t >= 1)
			return v2;

		float t2{ (1.0f - glm::cos(t * glm::pi<float>())) / 2.0f };
		return(v1 * (1.0f - t2) + v2 * t2);
	}

	/**
	 * Map a value from [a1, a2] to [b1, b2].
	 * 
	 * \param value: the value to map.
	 * \param a1: the lower value of the input range.
	 * \param a2: the upper value of the input range.
	 * \param b1: the lower value of the output range.
	 * \param b2: the upper value of the output range.
	 * \return the input value mapped from [a1, a2] to [b1, b2].
	 */
	template <typename T>
	T map(T value, T a1, T a2, T b1, T b2)
	{
		return b1 + (value - a1) * (b2 - b1) / (a2 - a1);
	}
};
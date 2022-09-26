#pragma once

#include "Root/Logger.h"

#include <glm/gtc/constants.hpp>

#include <vector>
#include <algorithm>

/**
 * A struct that holds data for a gradient point.
 * 
 * point: the point at which evaluating the gradient will return the current value.
 * value: the value returned when evaluating the gradient at this point.
 */
template <class T>
struct GradientPoint
{
	float point;
	T value;
};

/**
 * A class for defining gradients.
 * 
 * Holds an array of 'GradientPoint's, 
 * where evaluating the gradient at the point of a specific GradientPoint will return its value, 
 * or an interpolated value if the evaluation value is not precisely on a GradientPoint.
 */
template <class T>
class Gradient
{
public:
	/**
	 * Create an empty gradient. Uses the default constructor of T to create one point.
	 */
	Gradient()
	{
		// Creating a single gradient point at 0, whose value will always be used.
		this->points = std::vector<GradientPoint<float>>({ 0.0f, T() });
	}
	/**
	 * Create an new gradient with just a single value which will always be returned when sampling.
	 *
	 * \param value: the single value.
	 */
	Gradient(T value)
	{
		// Creating a single gradient point at 0, whose value will always be used.
		this->points = std::vector<GradientPoint<T>>{ { 0.0f, value } };
	}
	/**
	 * Create a new gradient.
	 * 
	 * \param points a vector of gradient points.
	 */
	Gradient(std::vector<GradientPoint<T>> points)
		: points(points)
	{
		std::sort(points.begin(), points.end(), &Gradient::gradientSorter);
	}

	~Gradient()
	{
		Logger::destructorMessage("Gradient destroyed.");
	}

	/**
	 * Sample the gradient at a given point.
	 * 
	 * \param point the point at which to sample.
	 * \return the interpolated value at the given point.
	 */
	T sample(float samplePoint)
	{
		// If there are no points, return the value given by the default constructor of the type.
		if (points.size() == 0)
			return T();

		// If there is only one point, its value will always be returned.
		if (points.size() == 1)
			return points[0].value;

		unsigned int i{ 0 };
		for (GradientPoint& gradientPoint : points)
		{
			// Found the right side point
			if (samplePoint < gradientPoint.point)
			{
				// If this is the first point, simply returns its value
				if (&gradientPoint == &points.front())
					return gradientPoint.value;

				// Otherwise find the left side and interpolate
				float t = map(samplePoint, points[i].point, gradientPoint.point, 0.0f, 1.0f);
				return interpolate(points[i].value, gradientPoint.value, t);
			}

			i++;
		}

		// No right side was found: return the value of the right-most gradient point
		return points.back()->value;
	}

private:
	std::vector<GradientPoint<T>> points;

	// Helper functions
	float interpolate(float v1, float v2, float t)
	{
		float t2{ (1.0f - cos(t * glm::pi<float>())) / 2.0f };
		return(v1 * (1.0f - t2) + v2 * t2);
	}

	float map(float s, float a1, float a2, float b1, float b2)
	{
		return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
	}

	static bool gradientSorter(GradientPoint<T> const& lhs, GradientPoint<T> const& rhs)
	{
		return lhs.point < rhs.point;
	}
};

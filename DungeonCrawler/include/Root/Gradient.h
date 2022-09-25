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
	Gradient();
	/**
	 * Create an new gradient with just a single value which will always be returned when sampling.
	 *
	 * \param value: the single value.
	 */
	Gradient(T value);
	/**
	 * Create a new gradient.
	 * 
	 * \param points a vector of gradient points.
	 */
	Gradient(std::vector<GradientPoint<T>> points);

	~Gradient();

	/**
	 * Sample the gradient at a given point.
	 * 
	 * \param point the point at which to sample.
	 * \return the interpolated value at the given point.
	 */
	T sample(float samplePoint);

private:
	std::vector<GradientPoint<T>> points;
};

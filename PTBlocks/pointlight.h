#pragma once

#include "light.h"

// Represents a point light in 3-dimensional space
class PointLight : public Light {
public:
	Point	pos;	// Position

	// Returns true when this light intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	bool	Intersect(const Ray& ray, float& t) const;

	// Returns a ray from p to the point light
	Ray		GetRandomRayToLightFrom(const Point& p, RNG& rng) const;
};
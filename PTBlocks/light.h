#pragma once

#include "color.h"
#include "geometry.h"
#include "rng.h"

// The abstract base class for all lights
class Light {
public:
	Color			Le;	// Emitted light

	// Returns true when this light intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	virtual bool	Intersect(const Ray& ray, float& t) const = 0;
	
	// Returns a ray from p to a random point on the light
	virtual Ray		GetRandomRayToLightFrom(const Point& p, RNG& rng) const = 0;
};
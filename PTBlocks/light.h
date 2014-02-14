#pragma once

#include "color.h"
#include "geometry.h"
#include "rng.h"

// The abstract base class for all lights
class Light {
public:
	Color			c;	// Color of light
	float			i;	// Intensity of light
	float			kc;	// Constant attenuation factor
	float			kl; // Linear attenuation factor
	float			kq; // Quadratic attenunation factor

	// Returns true when this light intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	virtual bool	Intersect(const Ray& ray, float& t) const = 0;
	
	// Returns a ray from p to a random point on the light
	virtual Ray		GetRandomRayToLightFrom(const Point& p, RNG& rng) const = 0;

	// Returns the attenuation factor of the light, given the distance
	float	GetAttenuation(float d) const;

	// Returns the emitted light
	Color	Le() const;
};
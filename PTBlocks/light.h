#pragma once

#include "color.h"
#include "geometry.h"

// The abstract base class for all lights
class Light {
public:
	Color			c;	// Color emitted
	
	// Returns a ray from a random point on the light to p
	virtual Ray		GetRandomRayFromLightTo(const Point& p) const = 0;
};
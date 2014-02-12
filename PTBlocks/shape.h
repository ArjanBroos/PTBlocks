#pragma once

#include "geometry.h"
#include "rng.h"

// The abstract base class for all shapes
class Shape {
public:
	// Returns true when this shape intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	virtual bool	Intersect(const Ray& ray, float& t) const = 0;
	
	// Returns the normal of this shape at point p
	virtual Vector	GetNormal(const Point& p) const = 0;

	// Returns a random point on the surface of this shape
	virtual Point	GetRandomPointOnSurface(RNG& rng) const = 0;
};
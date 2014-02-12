#pragma once

#include "shape.h"

// Represents a sphere
class Sphere : public Shape {
public:
	Point c;	// Center
	float r;	// Radius

	// Initializes a sphere at (0, 0, 0) with radius 1
	Sphere();
	// Initializes a sphere at c with radius r
	Sphere(const Point& c, float r);

	// Returns true when this sphere intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	bool	Intersect(const Ray& ray, float& t) const;

	// Returns the normal of this sphere at point p
	Vector	GetNormal(const Point& p) const;

	// Returns a random point on the surface of this shape
	Point	GetRandomPointOnSurface(RNG& rng) const;
};
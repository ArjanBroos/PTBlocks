#pragma once

#include "point.h"
#include "vector.h"
#include "math.h"

// Represents a ray with an origin and direction through 3-dimensional space
class Ray {
public:
	Point		o;	// Origin
	Vector		d;	// Direction

	// The ray is clamped between o + mint * d and o + maxt * d
	// To prevent intersection with a surface that this ray originated from
	float		mint;	// Minimum distance along ray for intersection checks
	float		maxt; // Maximum distance along ray for intersection checks

	unsigned	depth; // Number of rays before this one on a light path

	// Initializes a ray with origin o and direction d. depth, mint and maxt are optional
	Ray(const Point& o, const Vector& d, unsigned depth = 0, float mint = 1.0e-9f, float maxt = INFINITY);

	// Returns o + t*d
	Point		operator()(float t) const;
};
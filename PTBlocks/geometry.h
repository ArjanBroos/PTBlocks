#pragma once

#include "point.h"
#include "vector.h"
#include "ray.h"

// Returns the dot product of two vectors
inline float Dot(const Vector& v1, const Vector& v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// Returns the cross product of two vectors
inline Vector Cross(const Vector& v1, const Vector& v2) {
	return Vector(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}

// Returns the unit vector with the same direction as v
inline Vector Normalize(const Vector& v) {
	float factor = 1.f / v.Length();
	return v * factor;
}
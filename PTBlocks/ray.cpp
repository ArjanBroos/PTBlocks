#include "ray.h"

// Initializes a ray with origin o and direction d, mint and maxt for intersection optional
Ray::Ray(const Point& o, const Vector& d, unsigned depth, float mint, float maxt) : o(o), d(d), depth(depth), mint(mint), maxt(maxt) {
}

// Returns o + t*d
Point Ray::operator()(float t) const {
	return o + d*t;
}
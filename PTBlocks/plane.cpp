#include "plane.h"

// Initializes a plane through (0, 0, 0) with normal (0, 1, 0)
Plane::Plane() : p(Point(0.f, 0.f, 0.f)), n(Vector(0.f, 1.f, 0.f)) {
}

// Initializes a plane through p with normal n
Plane::Plane(const Point& p, const Vector& n) : p(p), n(n) {
}

// Returns true when this shape intersects ray
// If so, output parameter t becomes the distance along ray to the closest intersection
bool Plane::Intersect(const Ray& ray, float& t) const {
	const float nDotD = Dot(n, ray.d);
	// If ray and plane are perpendicular
	if (fabsf(nDotD) < 1e-10f)
		return false;

	// Find intersection point between ray and plane
	t = Dot(p - ray.o, n) / nDotD;
	if (t < ray.mint || t > ray.maxt)
		return false; // Does not intersect with the right part of the ray

	return true;
}
	
// Returns the normal of this shape at point p
Vector Plane::GetNormal(const Point& p) const {
	return n;
}

// Returns a random point on the surface of this shape
// Since this shape is infinite, the points returned are at most 1 unit away from the reference point
// This way, the random points can be scaled as desired
Point Plane::GetRandomPointOnSurface(RNG& rng) const {
	const Vector u = Normalize(Vector(n.y, n.z - n.x, -n.y)); // A vector perpendicular to the normal
	const Vector v = Cross(u, n); // Another vector perpendicular to both u and the normal

	const float r1 = 1.f - 2.f * rng.Random();
	const float r2 = 1.f - 2.f * rng.Random();

	return p + r1 * u + r2 * v;
}
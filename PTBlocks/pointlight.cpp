#include "pointlight.h"

// Returns true when this light intersects ray
// If so, output parameter t becomes the distance along ray to the closest intersection
bool PointLight::Intersect(const Ray& ray, float& t) const {
	Vector v = pos - ray.o;
	if (Normalize(v) == ray.d) {
		t = v.Length();
		return true;
	}
	return false;
}

// Returns a ray from p to the point light
Ray	PointLight::GetRandomRayToLightFrom(const Point& p, RNG& rng) const {
	Vector v = pos - p;
	return Ray(p, Normalize(v), 1e-10f, v.Length() - 2e-10f);
}
#include "arealight.h"

// Initializes white area light with given shape (cannot be NULL)
AreaLight::AreaLight(Shape* shape) : shape(shape) {
	c = Color(1.f, 1.f, 1.f);
	i = 1.f;
	kc = 1.f;
	kl = 0.1f;
	kq = 0.05f;
}

// Initializes area light with given shape (cannot be NULL)
AreaLight::AreaLight(Shape* shape, Color color, float intensity) : shape(shape) {
	c = color;
	i = intensity;
	kc = 1.f;
	kl = 0.1f;
	kq = 0.05f;
}

// Returns true when this light intersects ray
// If so, output parameter t becomes the distance along ray to the closest intersection
bool AreaLight::Intersect(const Ray& ray, float& t) const {
	return shape->Intersect(ray, t);
}

// Returns a ray from p to a random point on the light
Ray	AreaLight::GetRandomRayToLightFrom(const Point& p, RNG& rng) const {
	Point o = shape->GetRandomPointOnSurface(rng);
	Vector v = o - p;
	return Ray(p, Normalize(v), 1e-3f, v.Length() - 2e-3f);
}
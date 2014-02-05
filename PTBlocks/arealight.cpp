#include "arealight.h"

// Returns a ray from a random point on the light to p
Ray	AreaLight::GetRandomRayFromLightTo(const Point& p) const {
	Point o = shape->GetRandomPointOnSurface();
	Vector d = Normalize(p - o);
	return Ray(o, d);
}
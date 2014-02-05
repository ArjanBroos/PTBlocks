#include "light.h"
#include "shape.h"

// Represents an area light (ie. with a surface/shape)
class AreaLight {
public:
	Shape*	shape;	// The shape of this area light

	// Returns a ray from a random point on the light to p
	Ray		GetRandomRayFromLightTo(const Point& p) const;
};
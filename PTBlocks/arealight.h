#include "light.h"
#include "shape.h"

// Represents an area light (ie. with a surface/shape)
class AreaLight : public Light {
public:
	Shape*	shape;	// The shape of this area light

	// Initializes area light with given shape (cannot be NULL)
	AreaLight(Shape* shape);

	// Returns true when this light intersects ray
	// If so, output parameter t becomes the distance along ray to the closest intersection
	bool	Intersect(const Ray& ray, float& t) const;

	// Returns a ray from p to a random point on the light
	Ray		GetRandomRayToLightFrom(const Point& p, RNG& rng) const;
};
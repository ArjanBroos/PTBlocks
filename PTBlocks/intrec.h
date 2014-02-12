#pragma once

#include "primitive.h"
#include "light.h"
#include "material.h"
#include "geometry.h"

// Holds all information required to handle a ray-object/light intersection
class IntRec {
public:
	float		t;		// Distance along ray, between ray origin and intersection
	Primitive*	prim;	// Primitive intersected, NULL if a light was intersected
	Light*		light;	// Light intersected, NULL if a primitive was intersected
	Material*	mat;	// Material of the primitive, if a primitive was intersected
	Vector		n;		// Normal of the primitive or light at the point of intersection
	Point		p;		// Point of intersection

	// Initializes the intersection record as empty
	IntRec() : t(0.f), prim(nullptr), light(nullptr), mat(nullptr), n(Vector()), p(Point()) {}
};
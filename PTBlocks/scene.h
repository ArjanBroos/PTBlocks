#pragma once

#include <vector>
#include "primitive.h"
#include "light.h"
#include "intrec.h"

// Represents the scene, a collection of objects and lights
class Scene {
public:
	// Adds a primitive to the scene
	void					AddPrimitive(const Primitive& primitive);
	// Adds a light to the scene
	void					AddLight(Light* light);

	// Returns the primitives in the scene
	const std::vector<Primitive>*	GetPrimivites() const;
	// Returns the lights in the scene
	const std::vector<Light*>*	GetLights() const;
	
	// Returns true if given ray intersects with the scene
	// If true, t will become the distance along the ray to the closest intersection
	// And *primitive will point to the closest intersected primitive or NULL
	// And *light will point to the closest intersected light or NULL
	// Depending on whether a light or a primitive is closest
	bool					Intersect(const Ray& ray, IntRec& intRec) const;
	// Returns true if given ray intersects with scene
	bool					ShadowRay(const Ray& ray) const;

private:
	std::vector<Primitive>	primitives;	// All the objects in the scene
	std::vector<Light*>		lights;		// All the lights in the scene
};
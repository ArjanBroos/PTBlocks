#pragma once

#include <vector>
#include "primitive.h"

// Represents the scene, a collection of objects and lights
class Scene {
public:
	// Adds a primitive to the scene
	void	AddPrimitive(const Primitive& primitive);
	
	// Returns true if given ray intersects with the scene
	// If true, t will become the distance along the ray to the closest intersection
	// And primitive will point to the closest intersected primitive
	bool	Intersect(const Ray& ray, float& t, Primitive** primitive);

private:
	std::vector<Primitive>	primitives;	// All the objects in the scene
};
#include "scene.h"

// Adds a primitive to the scene
void Scene::AddPrimitive(const Primitive& primitive) {
	primitives.push_back(primitive);
}
	
// Returns true if given ray intersects with the scene
// If true, t will become the distance along the ray to the closest intersection
// And primitive will point to the closest intersected primitive
bool Scene::Intersect(const Ray& ray, float& t, Primitive** primitive) {
	bool intersect = false;
	t = INFINITY;

	// Find closest intersection among primitives
	for (auto i = primitives.begin(); i != primitives.end(); i++) {
		float tt;
		if (i->GetShape()->Intersect(ray, tt) && tt < t) {
			t = tt;
			*primitive = &(*i);
			intersect = true;
		}
	}

	return intersect;
}
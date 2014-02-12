#include "scene.h"

// Adds a primitive to the scene
void Scene::AddPrimitive(const Primitive& primitive) {
	primitives.push_back(primitive);
}

// Adds a light to the scene
void Scene::AddLight(Light* light) {
	lights.push_back(light);
}

// Returns the primitives in the scene
std::vector<Primitive>* Scene::GetPrimivites() {
	return &primitives;
}

// Returns the lights in the scene
std::vector<Light*>* Scene::GetLights() {
	return &lights;
}
	
// Returns true if given ray intersects with the scene
// If true, t will become the distance along the ray to the closest intersection
// And *primitive will point to the closest intersected primitive or NULL
// And *light will point to the closest intersected light or NULL
// Depending on whether a light or a primitive is closest
bool Scene::Intersect(const Ray& ray, IntRec& intRec) {
	bool intersect = false;
	intRec.t = INFINITY;
	float tt;

	// Find closest intersection among primitives
	for (auto i = primitives.begin(); i != primitives.end(); i++) {
		if (i->GetShape()->Intersect(ray, tt) && tt < intRec.t) {
			intRec.t = tt;
			intRec.prim = &(*i);
			intRec.mat = intRec.prim->GetMaterial();
			intRec.p = ray(tt);
			intRec.n = i->GetShape()->GetNormal(intRec.p);
			intersect = true;
		}
	}

	// Find closest intersection among lights
	for (auto i = lights.begin(); i != lights.end(); i++) {
		if ((*i)->Intersect(ray, tt) && tt < intRec.t) {
			intRec.t = tt;
			intRec.prim = NULL;
			intRec.light = *i;
			intRec.p = ray(tt);
			intRec.n = Vector(0.f, 0.f, 0.f); // No normals needed for intersections with lights
			intersect = true;
		}
	}

	return intersect;
}

// Returns true if given ray intersects with scene
bool Scene::ShadowRay(const Ray& ray) {
	float tt;

	// Return true if it hits a primitive
	for (auto i = primitives.begin(); i != primitives.end(); i++) {
		if (i->GetShape()->Intersect(ray, tt))
			return true;
	}

	// Return true if it hits a light
	for (auto i = lights.begin(); i != lights.end(); i++) {
		if ((*i)->Intersect(ray, tt))
			return true;
	}

	return false;
}
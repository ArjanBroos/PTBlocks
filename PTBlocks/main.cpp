#include <iostream>
#include <string>
#include <sstream>
#include "application.h"
#include "sphere.h"
#include "geometry.h"
#include "camera.h"
#include "filter.h"
#include "scene.h"
#include "primitive.h"
#include "arealight.h"
#include "lambertmaterial.h"
#include "mirrormaterial.h"
#include "rng.h"
#include "plane.h"

void CastCameraRays(Camera& camera, Scene& scene, unsigned width, unsigned height, unsigned i, RNG& rng);
Color ComputeRadiance(IntRec& intRec, const Ray& ray, unsigned depth, Scene& scene, RNG& rng);
Color DirectIllumination(IntRec& intRec, const Ray& ray, Scene& scene, RNG& rng);
Color IndirectIllumination(IntRec& intRec, const Ray& ray, unsigned depth, Scene& scene, RNG& rng);
std::string GetTitle(unsigned nIterations);

int main() {
	RNG	rng;

	// Set up application
	const unsigned width = 1024;
	const unsigned height = 768;
	Application app(width, height, "PTBlocks");

	// Create three sphere primitives
	Sphere sphereShape1(Point(0.f, 0.5f, 0.f), 1.f);
	MirrorMaterial sphereMat1(Color(1.f, 1.f, 1.f), 1.f);
	Primitive spherePrim1(&sphereShape1, &sphereMat1);
	Sphere sphereShape2(Point(2.f, 2.f, 5.f), 3.f);
	LambertMaterial sphereMat2(Color(0.f, 1.f, 0.f), 1.f);
	Primitive spherePrim2(&sphereShape2, &sphereMat2);
	Sphere sphereShape3(Point(4.f, 2.f, -2.f), 0.5f);
	LambertMaterial sphereMat3(Color(1.f, 0.f, 0.f), 1.f);
	Primitive spherePrim3(&sphereShape3, &sphereMat3);
	Plane planeShape(Point(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f));
	LambertMaterial planeMat(Color(1.f, 1.f, 0.3f), 1.f);
	Primitive planePrim(&planeShape, &planeMat);

	// Create an area light
	Sphere lightShape(Point(3.f, 2.f, -1.f), 1.f);
	AreaLight light(&lightShape);
	light.Le = Color(1.f, 1.f, 1.f);

	// Set up the scene with the sphere primitives
	Scene scene;
	scene.AddPrimitive(spherePrim1);
	scene.AddPrimitive(spherePrim2);
	scene.AddPrimitive(spherePrim3);
	scene.AddPrimitive(planePrim);
	scene.AddLight(&light);

	// Set up the camera
	Camera camera(Point(0.f, 3.f, -10.f), Normalize(Vector(0.f, 0.f, 1.f)), Vector(0.f, 1.f, 0.f), width, height, 60.f);

	// Convert film into data usable by SFML
	Filter filter(*camera.GetFilm());

	// Handle events and draw
	unsigned nIterations = 0;
	while (app.IsRunning()) {
		app.HandleEvents();

		CastCameraRays(camera, scene, width, height, nIterations, rng);
		nIterations++;

		filter.Refilter(*camera.GetFilm(), nIterations);
		app.Draw(filter.GetPixels(), width, height);

		app.SetTitle(GetTitle(nIterations));
	}
}

// Casts the rays through the camera pixels and calculates incoming radiance along them
void CastCameraRays(Camera& camera, Scene& scene, unsigned width, unsigned height, unsigned i, RNG& rng) {
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			// Compute radiance coming through this pixel
			Ray ray = camera.GetJitteredRay(x, y, rng);
			IntRec intRec;
			Color c = ComputeRadiance(intRec, ray, 0, scene, rng);
			camera.GetFilm()->AddColor(c, x, y);
		}
	}
}

// Compute the radiance along from point x in direction dir
Color ComputeRadiance(IntRec& intRec, const Ray& ray, unsigned depth, Scene& scene, RNG& rng) {
	return IndirectIllumination(intRec, ray, depth, scene, rng);
}

// Compute the direct illumination reflected from point x in direction dir
Color DirectIllumination(IntRec& intRec, const Ray& ray, Scene& scene, RNG& rng) {
	// Terminate if ray left scene
	if (!scene.Intersect(ray, intRec))
		return Color(0.1f, 0.1f, 0.2f);

	// If a light was hit
	if (intRec.light)
		return intRec.light->Le;

	// Still in this function means that the ray hit a primitive

	Color di(0.f, 0.f, 0.f); // Direct illumination

	// Loop through all lights
	for (auto i = scene.GetLights()->begin(); i != scene.GetLights()->end(); i++) {
		// Check if ray from point to some point on the light is a shadow ray
		Ray shadowRay = (*i)->GetRandomRayToLightFrom(intRec.p, rng);
		if (!scene.ShadowRay(shadowRay)) {
			// If point is lit directly, light it
			const float brdf = intRec.mat->GetBRDF(ray.d, shadowRay.d, intRec.n);
			const float pdf = intRec.mat->GetPDF(ray.d, shadowRay.d, intRec.n);
			const Color matCol = intRec.mat->GetColor();
			di += (*i)->Le * brdf * Dot(shadowRay.d, intRec.n) / pdf * matCol;
		}
	}

	// Divide number of lights in the scene
	return di * (1 / (float)scene.GetLights()->size());
}

// Compute the indirect illumination reflected from point x in direction dir
Color IndirectIllumination(IntRec& intRec, const Ray& ray, unsigned depth, Scene& scene, RNG& rng) {
	// Terminate long paths
	const unsigned maxDepth = 4;
	if (depth >= maxDepth)
		return Color(0.f, 0.f, 0.f);

	// Terminate if ray left scene
	if (!scene.Intersect(ray, intRec))
		return Color(0.1f, 0.1f, 0.2f);

	// If a light was hit
	if (intRec.light)
		return intRec.light->Le;

	// Still in this function means that the ray hit a primitive

	// Sample a new direction
	Vector psi = intRec.mat->GetSample(ray.d, intRec.n, rng);
	Ray newRay(intRec.p, psi);

	// Calculate necessary information for radiance
	Color color = intRec.mat->GetColor();
	float multiplier = intRec.mat->GetMultiplier(ray.d, psi, intRec.n);

	// Compute incoming radiance along new ray and calculate amount reflected in our direction
	IntRec newIntRec;
	return ComputeRadiance(newIntRec, newRay, depth+1, scene, rng) * multiplier * color;
}

std::string GetTitle(unsigned nIterations) {
	std::stringstream ss;
	ss << "PTBlocks - Iterations: " << nIterations;
	return ss.str();
}
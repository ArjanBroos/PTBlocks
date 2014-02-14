#include "renderer.h"

// Casts the rays through the camera pixels and calculates incoming radiance along them
void Renderer::ComputeColors(Camera& camera, const Scene& scene, RNG& rng) {
	const unsigned width = camera.GetFilm()->GetWidth();
	const unsigned height = camera.GetFilm()->GetHeight();
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			// Compute radiance coming through this pixel
			Ray ray = camera.GetJitteredRay(x, y, rng);
			IntRec intRec;
			Color c = ComputeRadiance(intRec, ray, 0, scene, rng);
			camera.AddColor(c, x, y);
		}
	}
}

// Compute the radiance along from point x in direction dir
Color Renderer::ComputeRadiance(IntRec& intRec, const Ray& ray, unsigned depth, const Scene& scene, RNG& rng) {
	return IndirectIllumination(intRec, ray, depth, scene, rng);
}

// Compute the direct illumination reflected from point x in direction dir
Color Renderer::DirectIllumination(IntRec& intRec, const Ray& ray, const Scene& scene, RNG& rng) {
	// Terminate if ray left scene
	if (!scene.Intersect(ray, intRec))
		return Color(0.f, 0.f, 0.f);

	// If a light was hit
	if (intRec.light)
		return intRec.light->Le();

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
			// We are sampling lights directly, so we need to attenuate the light here
			const float attenuation = (*i)->GetAttenuation(intRec.t);
			di += (*i)->Le() * brdf * Dot(shadowRay.d, intRec.n) * attenuation / pdf * matCol;
		}
	}

	// Divide number of lights in the scene
	return di * (1 / (float)scene.GetLights()->size());
}

// Compute the indirect illumination reflected from point x in direction dir
Color Renderer::IndirectIllumination(IntRec& intRec, const Ray& ray, unsigned depth, const Scene& scene, RNG& rng) {
	// Terminate long paths
	const unsigned maxDepth = 4;
	if (depth >= maxDepth)
		return Color(0.f, 0.f, 0.f);

	// Terminate if ray left scene
	if (!scene.Intersect(ray, intRec))
		return Color(0.3f, 0.3f, 0.4f);

	// If a light was hit
	if (intRec.light)
		return intRec.light->Le();

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
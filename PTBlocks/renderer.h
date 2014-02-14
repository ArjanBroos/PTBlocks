#pragma once

#include "camera.h"
#include "color.h"
#include "scene.h"
#include "intrec.h"
#include "rng.h"

// Responsible for computing color of every pixel
class Renderer {
public:
	void	ComputeColors(Camera& camera, const Scene& scene, RNG& rng);

private:
	Color	ComputeRadiance(IntRec& intRec, const Ray& ray, unsigned depth, const Scene& scene, RNG& rng);
	Color	DirectIllumination(IntRec& intRec, const Ray& ray, const Scene& scene, RNG& rng);
	Color	IndirectIllumination(IntRec& intRec, const Ray& ray, unsigned depth, const Scene& scene, RNG& rng);
};
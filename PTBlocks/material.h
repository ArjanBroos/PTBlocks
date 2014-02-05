#pragma once

#include "color.h"

// Represents the base material
class Material {
public:
	Color c;	// Color

	// Initializes a white material
	Material();
	// Initializes a material with color c
	Material(const Color& c);

	// Add BRDF, BSDF or other properties
};
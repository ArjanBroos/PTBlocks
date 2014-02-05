#include "material.h"

// Initializes a white material
Material::Material() : c(Color(1.f, 1.f, 1.f)) {
}

// Initializes a material with color c
Material::Material(const Color& c) : c(c) {
}
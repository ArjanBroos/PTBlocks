#pragma once

#include "shape.h"
#include "material.h"

// Represents a physical object with a shape and material
class Primitive {
public:
	// Initializes this primitive with a shape and a material
	Primitive(Shape* shape, const Material& material);

	// Returns a pointer to the shape
	Shape*		GetShape();
	// Returns the material
	Material	GetMaterial();

private:
	Shape*		shape;		// Shape of the object
	Material	material;	// Material of the object
};
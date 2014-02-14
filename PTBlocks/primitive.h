#pragma once

#include "shape.h"
#include "material.h"

// Represents a physical object with a shape and material
class Primitive {
public:
	// Initializes this primitive with a shape and a material
	Primitive(Shape* shape, Material* material);

	// Returns a pointer to the shape
	const Shape*	GetShape() const;
	// Returns the material
	const Material*	GetMaterial() const;

private:
	Shape*			shape;		// Shape of the object
	Material*		material;	// Material of the object
};
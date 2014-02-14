#include "primitive.h"

// Initializes this primitive with a shape and a material
Primitive::Primitive(Shape* shape, Material* material) : shape(shape), material(material) {
}

// Returns a pointer to the shape
const Shape* Primitive::GetShape() const {
	return shape;
}

// Returns the material
const Material* Primitive::GetMaterial() const {
	return material;
}
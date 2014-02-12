#include "primitive.h"

// Initializes this primitive with a shape and a material
Primitive::Primitive(Shape* shape, Material* material) : shape(shape), material(material) {
}

// Returns a pointer to the shape
Shape* Primitive::GetShape() {
	return shape;
}

// Returns the material
Material* Primitive::GetMaterial() {
	return material;
}
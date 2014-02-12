#include "lambertmaterial.h"
#include "math.h"

// Initializes a white material with an albedo of 1
LambertMaterial::LambertMaterial() : color(Color(1.f, 1.f, 1.f)), albedo(1.f) {
}

// Initializes a material with given color and albedo
LambertMaterial::LambertMaterial(const Color& color, float albedo) : color(color), albedo(albedo) {
}

// Returns the color of this material
Color LambertMaterial::GetColor() const {
	return color;
}

// Bidirectional Reflectance Distribution Function
float LambertMaterial::GetBRDF(const Vector& in, const Vector& out, const Vector& normal) const {
	return albedo / PI;
}

// Probability Density Function for cosine-weighted hemisphere sampling
float LambertMaterial::GetPDF(const Vector& in, const Vector& out, const Vector& normal) const {
	return Dot(out, normal) / PI;
}

// Cosine weighted sampling on the unit hemisphere
Vector LambertMaterial::GetSample(const Vector& in, const Vector& normal, RNG& rng) const {
	const Vector u = Normalize(Vector(normal.y, normal.z - normal.x, -normal.y)); // A vector perpendicular to the normal
	const Vector v = Cross(u, normal); // Another vector perpendicular to both u and the normal

	const float u1 = rng.Random();
	const float u2 = rng.Random();

	const float r = sqrtf(u1);
	const float phi = u2 * 2.f * PI;

	const float x = r * cosf(phi);
	const float y = sqrtf(std::max(0.f, 1.f - u1));
	const float z = r * sinf(phi);

	return u * x + normal * y + v * z;
}

// Returns the factor between incoming and outgoing radiance along given rays
float LambertMaterial::GetMultiplier(const Vector& in, const Vector& out, const Vector& normal) const {
	return albedo;
}
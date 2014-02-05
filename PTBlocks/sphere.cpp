#include "sphere.h"
#include <random>
#include <ctime>

// Initializes a sphere at (0, 0, 0) with radius 1
Sphere::Sphere() : c(Point(0.f, 0.f, 0.f)), r(1.f) {
}

// Initializes a sphere at c with radius r
Sphere::Sphere(const Point& c, float r) : c(c), r(r) {
}

// Returns true when this sphere intersects ray
// If so, output parameter t becomes the distance along ray to the closest intersection
bool Sphere::Intersect(const Ray& ray, float& t) const {
	// Use abc-formula to solve for the two possible intersection points

	Vector v = ray.o - c;
	float a = Dot(ray.d, ray.d);
	float b = Dot(ray.d, v);
	float c = Dot(v, v) - r*r;
	float d = b*b - a*c;

	if (d < 0.f) return false; // No intersection

	float D = sqrtf(d);

	// s1 is always smaller than s2 and we want to return the closest valid intersection
	float s1 = (-b - D) / a;
	if (s1 >= ray.mint && s1 <= ray.maxt) {
		t = s1;
		return true;
	}
	float s2 = (-b + D) / a;
	if (s2 >= ray.mint && s2 <= ray.maxt) {
		t = s2;
		return true;
	}
	
	return false;
}

// Returns the normal of this sphere at point p
Vector Sphere::GetNormal(const Point& p) const {
	return Normalize(p - c);
}

// Returns a random point on the surface of this shape
Point Sphere::GetRandomPointOnSurface() const {
	// Keep generating random coordinates within cube around unit sphere
	// Reject any points outside the unit sphere
	std::mt19937 mt((unsigned)time(0));
	std::uniform_real_distribution<> urd(-1, 1);
	float x = (float)urd(mt);
	float y = (float)urd(mt);
	float z = (float)urd(mt);
	float length = x*x + y*y + z*z;
	// Expected number of iterations < 2
	while (length > 1.f) {
		x = (float)urd(mt);
		y = (float)urd(mt);
		z = (float)urd(mt);
		length = x*x + y*y + z*z;
	}

	// Point on surface of sphere
	float invLength = 1.f / length;
	Point p(x, y, z);
	return p * r * invLength;
}
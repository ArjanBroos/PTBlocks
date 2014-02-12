#include "camera.h"

// Initializes a camera at position, looking in direction, with up being the up direction for the camera
// and a film of filmWidth x filmHeight pixels.
// The camera will have given Field of View in degrees
Camera::Camera(const Point& position, const Vector& direction, const Vector& up,
	unsigned filmWidth, unsigned filmHeight, float FoV)
	: pos(position), film(filmWidth, filmHeight) {
		// Establish coordinate system with u, v and dir
		dir = Normalize(direction);
		v = Normalize(Cross(up, dir));
		u = Cross(v, dir);

		FoV *= 180.f / PI; // Convert FoV to radians
		float halfWidth = tanf(FoV/2.f);
		float aspectRatio = (float)filmWidth / (float)filmHeight;
		u *= halfWidth; // Make u's length half of the film's width
		v *= halfWidth * aspectRatio; // Make v's length half of the film's height

		dx = 2.f / (float)filmWidth;
		dy = 2.f / (float)filmHeight;
		xmin = -1.f + dx / 2.f;
		ymin = -1.f + dy / 2.f;
}

// Returns a ray from the viewpoint through pixel (x, y)
Ray	Camera::GetRay(unsigned x, unsigned y) const {
	Vector vx = (xmin + x*dx) * v;
	Vector vy = (ymin + y*dy) * u;
	return Ray(pos, Normalize(vx + vy + dir));
}

// Returns a ray through pixel (x, y), randomly jittered around its center
Ray	Camera::GetJitteredRay(unsigned x, unsigned y, RNG& rng) const {
	const float pxmin = -1.f + (float)x * dx;		// Pixel x mininum
	const float pymin = -1.f + (float)y * dy;		// Pixel y minimum

	const float px = pxmin + rng.Random() * dx;
	const float py = pymin + rng.Random() * dy;

	Vector vx = px * v;
	Vector vy = py * u;
	return Ray(pos, Normalize(vx + vy + dir));
}

// Returns a pointer to the camera's film
Film* Camera::GetFilm() {
	return &film;
}
#pragma once

#include "geometry.h"
#include "film.h"
#include "rng.h"

// Represents a pinhole camera
class Camera {
public:
	// Initializes a camera at position, looking in direction, with up being the up direction for the camera
	// and a film of filmWidth x filmHeight pixels.
	// The camera will have given Field of View in degrees
	Camera(const Point& position, const Vector& direction, const Vector& up,
		unsigned filmWidth, unsigned filmHeight, float FoV);

	// Returns a ray from the viewpoint through the center of pixel (x, y)
	Ray			GetRay(unsigned x, unsigned y) const;
	// Returns a ray through pixel (x, y), randomly jittered around its center
	Ray			GetJitteredRay(unsigned x, unsigned y, RNG& rng) const;

	// Returns a pointer to the camera's film
	const Film*	GetFilm() const;

	// Adds a color to the film
	void		AddColor(const Color& c, unsigned x, unsigned y);

	void Walk(float x);
	void Strafe(float x);
	void Elevate(float x);
	void Yaw(float r);
	void Pitch(float r);
	void Reset();
	void CalcUV();

private:
	Point		pos;	// Position
	Vector		dir;	// Direction camera is looking at
	Vector		u;		// Up direction of film plane
	Vector		up;		// Up direction of the world
	Vector		v;		// Right direction of film plane
	float		halfWidth;
	Film		film;	// Film to project light on

	float		xmin;	// Minimum normalized x-coordinate on film plane
	float		ymin;	// Minimum normalized y-coordinate on film plane
	float		dx;		// Difference in normalized x-coordinate of pixels on film plane
	float		dy;		// Difference in normalized y-coordinate of pixels on film plane
};
#include "camera.h"

// Initializes a camera at position, looking in direction, with up being the up direction for the camera
// and a film of filmWidth x filmHeight pixels.
// The camera will have given Field of View in degrees
Camera::Camera(const Point& position, const Vector& direction, const Vector& up,
			   unsigned filmWidth, unsigned filmHeight, float FoV)
			   : pos(position), film(filmWidth, filmHeight), up(up) {
				   // Establish coordinate system with u, v and dir
				   dir = Normalize(direction);
				   v = Normalize(Cross(dir, up));
				   u = Cross(dir, v);

				   FoV *= 180.f / PI; // Convert FoV to radians
				   halfWidth = tanf(FoV/2.f);
				   float aspectRatio = (float)filmWidth / (float)filmHeight;
				   u *= halfWidth; // Make u's length half of the film's width
				   v *= halfWidth * aspectRatio; // Make v's length half of the film's height

				   dx = 2.f / (float)filmWidth;
				   dy = 2.f / (float)filmHeight;
				   xmin = -1.f + dx / 2.f;
				   ymin = -1.f + dy / 2.f;
}

void Camera::Walk(float x)
{
	pos.x += x*dir.x;
	pos.z += x*dir.z;
}

void Camera::Strafe(float x)
{
	pos.x += x*v.x;
	pos.z += x*v.z;
}

void Camera::Elevate(float x)
{
	pos.y += x;
}

void Camera::Yaw(float r)
{
	//Rotate each vector around the y-axis
	float x = dir.x*cosf(r) + dir.z*sinf(r);
	float y = dir.y;
	float z = -dir.x*sinf(r) + dir.z*cosf(r);
	dir = Vector(x, y, z);

	CalcUV();
}

void Camera::Pitch(float r)
{
	//Calculate angle between dir and x axis
	float rx = -atan2(dir.z,dir.x);

	// Rotate dir axis-aligned
	float x = dir.x*cosf(-rx) + dir.z*sinf(-rx);
	float y = dir.y;
	float z = -dir.x*sinf(-rx) + dir.z*cosf(-rx);
	dir = Vector(x, y, z);

	// Pitch dir
	x = dir.x*cosf(r) + dir.z*sinf(r);
	y = -dir.x*sinf(r) + dir.y*cosf(r);
	z = dir.z;
	dir = Vector(x, y, z);

	// Rotate dir back to right angle
	x = dir.x*cosf(rx) + dir.z*sinf(rx);
	y = dir.y;
	z = -dir.x*sinf(rx) + dir.z*cosf(rx);
	dir = Vector(x, y, z);

	CalcUV();
}

void Camera::CalcUV() {
	dir = Normalize(dir);
	v = Normalize(Cross(dir, up));
	u = Cross(dir, v);
	u *= halfWidth; // Make u's length half of the film's width
	v *= halfWidth * film.GetAspectRatio(); // Make v's length half of the film's height
}

void Camera::Reset()
{
	film.Reset();
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
const Film* Camera::GetFilm() const {
	return &film;
}

// Adds a color to the film
void Camera::AddColor(const Color& c, unsigned x, unsigned y) {
	film.AddColor(c, x, y);
}
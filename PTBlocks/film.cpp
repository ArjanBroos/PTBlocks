#include "film.h"

// Initializes a width x height film with only black pixels
Film::Film(unsigned width, unsigned height) : width(width), height(height), aspectRatio((float) width / (float) height){
	pixels = new Color[width*height];
}

// Destroys the film
Film::~Film() {
	delete[] pixels;
}

// Returns the width of the film in pixels
unsigned Film::GetWidth() const {
	return width;
}

// Returns the height of the film in pixels
unsigned Film::GetHeight() const {
	return height;
}

// Returns the aspect ratio of the film
float Film::GetAspectRatio() const {
	return aspectRatio;
}

// Returns a read-only pointer to the pixels in the film
const Color* Film::GetPixels() const {
	return pixels;
}

// Adds color to the given pixel
void Film::AddColor(const Color& c, unsigned x, unsigned y) {
	pixels[x + y*width] += c;
}

// Divides all pixel colors by n
void Film::DivideAllColors(unsigned n) {
	float f = 1.f / (float)n;
	for (unsigned i = 0; i < width*height; i++) {
		pixels[i] *= f;
	}
}

// Multiplies all pixel colors by f
void Film::MultiplyAllColors(float f) {
	for (unsigned i = 0; i < width*height; i++) {
		pixels[i] *= f;
	}
}

// Resets all pixels
void Film::Reset() {
	delete[] pixels;
	pixels = new Color[width*height];
	for (unsigned i = 0; i < width*height; i++) {
		pixels[i] = Color(0,0,0);
	}
}
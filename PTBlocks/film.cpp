#include "film.h"

// Initializes a width x height film with only black pixels
Film::Film(unsigned width, unsigned height) : width(width), height(height) {
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
	for (unsigned i = 0; i < width*height; i++) {
		pixels[i] /= (float)n;
	}
}
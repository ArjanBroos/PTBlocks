#include "filter.h"

// Applies the filter to the given film
Filter::Filter(const Film& film) {
	unsigned filmSize = film.GetWidth() * film.GetHeight();
	unsigned size = 4 * filmSize; // Number of bytes (unsigned char's)
	pixels = new unsigned char[size];
	const Color* filmPixels = film.GetPixels();
	for (unsigned i = 0; i < filmSize; i++) {
		pixels[i*4]		= Clamp(filmPixels[i].r);
		pixels[i*4+1]	= Clamp(filmPixels[i].g);
		pixels[i*4+2]	= Clamp(filmPixels[i].b);
		pixels[i*4+3]	= 255;
	}
}

// Destroys the filter
Filter::~Filter() {
	delete[] pixels;
}

// Returns the filtered pixels
unsigned char* Filter::GetPixels() const {
	return pixels;
}

// Clamps [0, 1] of f into [0, 255]
unsigned char Filter::Clamp(float f) const {
	if (f < 0.f) return 0;
	if (f > 1.f) return 255;
	return (char)(f * 255);
}
#pragma once

#include "color.h"

// Represents a film, on which images are projected
class Film {
public:
	// Initializes a width x height film with only black pixels
	Film(unsigned width, unsigned height);
	// Destroys the film
	~Film();

	// Returns the width of the film in pixels
	unsigned		GetWidth() const;
	// Returns the height of the film in pixels
	unsigned		GetHeight() const;
	// Returns a read-only pointer to the pixels in the film
	const Color*	GetPixels() const;

	// Adds color to the given pixel
	void			AddColor(const Color& c, unsigned x, unsigned y);
	// Divides all pixel colors by n
	void			DivideAllColors(unsigned n);
	// Multiplies all colors by f
	void			MultiplyAllColors(float f);
	// Resets all pixels
	void			Reset();

private:
	unsigned		width;	// Width in pixels
	unsigned		height;	// Height in pixels
	Color*			pixels;	// Pixels on film
};
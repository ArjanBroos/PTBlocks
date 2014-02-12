#pragma once

#include "film.h"

// Represents a filter that converts a film into RGBA values that SFML understands
class Filter {
public:
	// Applies the filter to the given film
	Filter(const Film& film);
	// Destroys the filter
	~Filter();

	// Returns the filtered pixels
	unsigned char*	GetPixels() const;

	// Refilters the given film
	void			Refilter(const Film& film, unsigned nInterations);

private:
	unsigned char*	pixels;	// The filtered pixels
	unsigned		size;	// Number of pixels

	// Clamps [0, 1] of f into [0, 255]
	unsigned char	Clamp(float f) const;
};
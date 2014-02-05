#pragma once

// Represents a color
// Values for any of the components can be interpreted freely
// However, (0, 0, 0) is to be considered black
class Color {
public:
	float r, g, b;	// Color components for red, green and blue

	// Initializes color as black
	Color();
	// Initializes color as (r, g, b)
	Color(float r, float g, float b);

	Color operator+(const Color& c) const;
	Color& operator+=(const Color& c);
	Color operator*(float s) const;
	Color& operator*=(float s);
	Color operator/(float s) const;
	Color& operator/=(float s);
};
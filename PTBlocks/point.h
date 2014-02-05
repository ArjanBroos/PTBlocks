#pragma once

#include "vector.h"

// Represents a 3-dimensional point
class Point {
public:
	// Point coordinates
	float x, y, z;

	// Initialize point as (0, 0, 0)
	Point();
	// Initialize point as (x, y, z)
	Point(float x, float y, float z);

	// Arithmetic operators
	Vector operator-(const Point& p) const;
	Point operator+(const Vector& v) const;
	Point& operator+=(const Vector& v);
	Point operator-(const Vector& v) const;
	Point& operator-=(const Vector& v);
	Point operator+(const Point& p) const;
	Point& operator+=(const Point& p);
	Point operator*(float s) const;
	Point& operator*=(float s);
	Point operator/(float s) const;
	Point& operator/=(float s);
};
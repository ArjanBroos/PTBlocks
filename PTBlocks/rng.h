#pragma once
#include <random>
#include <ctime>

// Represents a random number generator
class RNG {
public:
	// Initializes the random number generator with a seed of the current time
	RNG();

	// Returns a random float between 0 and 1
	float								Random();

private:
	std::mt19937						mersenneTwister;
	std::uniform_real_distribution<>	urd;
};
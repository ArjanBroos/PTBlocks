#include "rng.h"

// Initializes the random number generator with a seed of the current time
RNG::RNG() : mersenneTwister((unsigned)time(0)) {
}

// Returns a random float between 0 and 1
float RNG::Random() {
	return (float)urd(mersenneTwister);
}
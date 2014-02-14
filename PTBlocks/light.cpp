#include "light.h"

// Returns the attenuation factor of the light, given the distance
float Light::GetAttenuation(float d) const {
	return 1.f / (kc + kl * d + kq * d*d);
}

// Returns the emitted light
Color Light::Le() const {
	return i * c;
}
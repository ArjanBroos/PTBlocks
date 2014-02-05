#pragma once

#define _USE_MATH_DEFINES // Include M_PI constant, and such, when including <cmath>
#include <cmath>
#include <cfloat>
#define INFINITY FLT_MAX
#define isinf(f) (!_finite((f)))
#define isnan _isnan // IS Not A Number
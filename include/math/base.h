#ifndef BASE_H
#define BASE_H

#include <cmath>

#ifdef USE_DOUBLE_PRECISION
using real_t = double;
constexpr size_t alignmentMultiplier = 8;
#else
using real_t = float;
constexpr size_t alignmentMultiplier = 4;
#endif

#endif

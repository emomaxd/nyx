#ifndef BASE_H
#define BASE_H

#ifdef USE_DOUBLE_PRECISION
using real_t = double;
constexpr size_t alignment_multiplier = 8;
#else
using real_t = float;
constexpr size_t alignment_multiplier = 4;
#endif

#endif

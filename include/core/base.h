#pragma once

#include <cstddef> // size_t

namespace nyx {

#ifdef USE_DOUBLE_PRECISION
using real_t = double;
constexpr size_t alignmentMultiplier = 8;
#else
using real_t = float;
constexpr size_t alignmentMultiplier = 4;
#endif

constexpr size_t kCacheLineSize = 64;
#define NYX_ALIGNAS_CACHE alignas(nyx::kCacheLineSize)

// Force inline macro
#if !defined(NYX_FORCEINLINE)
#define NYX_FORCEINLINE inline __attribute__((always_inline))
#endif

} // namespace nyx



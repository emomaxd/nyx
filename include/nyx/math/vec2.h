#pragma once

#ifdef NYX_USE_SSE4
#include "vec2_sse4.h"
#else
#include "vec2_naive.h"
#endif
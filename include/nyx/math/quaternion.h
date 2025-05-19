#pragma once

#ifdef NYX_USE_SSE4
#include "quaternion_sse4.h"
#else
#include "quaternion_naive.h"
#endif
#pragma once

#include <cmath>
#include <cstdint>

#include "core/base.h"

namespace nyx {
    NYX_FORCEINLINE real_t sqrt(real_t x)
    {
        #ifndef USE_CUSTOM_SQRT
        /* STL sqrt */
            return std::sqrt(x);
        #else
        /* Custom fast sqrt approximation */

        /* Edge case for both data types */
        if (x <= (real_t)0.0) return (real_t)0.0;

        #ifdef USE_DOUBLE_PRECISION
        /* DOUBLE implementation */
        const size_t magic = 0x5fe6eb50c7b537a9;
        #else
        /* FLOAT implementation*/
        const size_t magic = 0x5f3759df;
        #endif
        
        union {
            real_t F;
            uint32_t I;
        } u = { x };

        u.I = magic - (u.I >> 1);
        real_t y = u.F;
        
        real_t xhalf = 0.5f * x;
        y = y * (1.5f - xhalf * y * y);

        real_t sqrtX = x * y;

        /* OPTIONAL 
        * TODO: Test the performance and accuracy with and without this line.
        */
        sqrtX = sqrtX - ((sqrtX * sqrtX - x) / (2.0f * sqrtX));

        return sqrtX;
        #endif
    }
} // namespace nyx
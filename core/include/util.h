#pragma once

#include <string>

namespace core::util {

    /// @brief Initialize the random number generator.
    void init_random();

    /// @brief Generate a random integer between min and max.
    /// @param min The minimum value.
    /// @param max The maximum value.
    /// @return A random integer between min and max.
    int random_int(int min, int max);

    /// @brief Generate a random float between min and max.
    /// @param min The minimum value.
    /// @param max The maximum value.
    /// @return A random float between min and max.
    float random_float(float min, float max);

} // namespace core::util
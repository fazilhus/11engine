#pragma once

#include <string>

namespace core {

    /// @brief Enum class representing different states.
    enum class state_type {
        none,
        resting,
        working_at_construction,
        working_at_office,
        eating,
        drinking,
        partying,
        shopping,
        num_states
    };

    /// @brief Enum class representing different locations.
    enum class loc_type {
        none,
        home,
        construction,
        office,
        restaurant,
        bar,
        party,
        mall,
        num_locs
    };

    /// @brief Enum class representing different message types.
    enum class message_type {
        none,
        go_eating,
        go_drinking,
        go_partying,
        go_shopping,
        num_types
    };


    namespace util {

        /// @brief Convert state_type to string.
        /// @param state The state_type to convert.
        /// @return The string representation of the state_type.
        std::string str(state_type state);

        /// @brief Convert loc_type to string.
        /// @param location The loc_type to convert.
        /// @return The string representation of the loc_type.
        std::string str(loc_type location);

        /// @brief Convert message_type to string.
        /// @param type The message_type to convert.
        /// @return The string representation of the message_type.
        std::string str(message_type type);

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

        loc_type loc_by(state_type s);

    }

} // namespace core
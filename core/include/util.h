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
        travelling,
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
        road,
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

        /// @brief Location from State
        /// @param s State
        /// @return Location
        loc_type loc_by(state_type s);
        /// @brief Location from Message
        /// @param m Message
        /// @return Location
        loc_type loc_by(message_type m);
        /// @brief State from Location
        /// @param l Location
        /// @return State
        state_type state_by(loc_type l);
        /// @brief State from Message
        /// @param m Message
        /// @return State
        state_type state_by(message_type m);

    }

} // namespace core
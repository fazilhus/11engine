#pragma once

#include <cstdint>
#include <string>

namespace core {

    /// @brief Enum representing different states.
    enum state_type : uint8_t {
        state_type_none,
        state_type_resting,
        state_type_working_at_construction,
        state_type_working_at_office,
        state_type_eating,
        state_type_drinking,
        state_type_partying,
        state_type_shopping,
        state_type_travelling,
        state_type_num
    };

    /// @brief Enum representing different locations.
    enum loc_type : uint8_t {
        loc_type_none,
        loc_type_home,
        loc_type_construction,
        loc_type_office,
        loc_type_restaurant,
        loc_type_bar,
        loc_type_party,
        loc_type_mall,
        loc_type_road,
        loc_type_num
    };

    /// @brief Enum representing different message types.
    enum message_type : uint8_t {
        message_type_none,
        message_type_go_eating,
        message_type_go_drinking,
        message_type_go_partying,
        message_type_go_shopping,
        message_type_num
    };

    namespace util {

        /// @brief Convert state_type to string.
        /// @param state The state_type to convert.
        /// @return The string representation of the state_type.
        std::string state_to_str(uint8_t state);

        /// @brief Convert loc_type to string.
        /// @param location The loc_type to convert.
        /// @return The string representation of the loc_type.
        std::string loc_to_str(uint8_t location);

        /// @brief Convert message_type to string.
        /// @param type The message_type to convert.
        /// @return The string representation of the message_type.
        std::string msg_to_str(uint8_t type);

        /// @brief Location from State
        /// @param s State
        /// @return Location
        uint8_t loc_by_state(uint8_t s);
        /// @brief Location from Message
        /// @param m Message
        /// @return Location
        uint8_t loc_by_msg(uint8_t m);
        /// @brief State from Location
        /// @param l Location
        /// @return State
        uint8_t state_by_loc(uint8_t l);
        /// @brief State from Message
        /// @param m Message
        /// @return State
        uint8_t state_by_msg(uint8_t m);

    } // namespace util

} // namespace core
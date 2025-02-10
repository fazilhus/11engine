#pragma once

#include <cstdint>
#include <string>

namespace core {

    /// @brief Enum representing different states.
    enum state_type : uint8_t {
        state_type_none,
        state_type_at_start,
        state_type_at_finish,
        state_type_travelling,
        state_type_num
    };

    /// @brief Enum representing different locations.
    enum loc_type : uint8_t {
        loc_type_none,
        loc_type_start,
        loc_type_finish,
        loc_type_road,
        loc_type_num
    };

    /// @brief Enum representing different message types.
    enum message_type : uint8_t {
        message_type_none,
        message_type_num
    };

    enum tile_type : uint8_t {
        tile_type_none,
        tile_type_road,
        tile_type_rock,
        tile_type_start,
        tile_type_finish,
        tile_type_num
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
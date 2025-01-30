#pragma once

#include <array>

#include "util.h"

namespace core {

    /// Represents a link between two locations with a distance.
    struct link {
        loc_type m_from = loc_type::none; ///< The starting location.
        loc_type m_to = loc_type::none; ///< The destination location.
        int m_distance = 0; ///< The distance between the locations.
    };

    /// Contains data related to travel, including the distance travelled and the link.
    struct travel_data {
        int m_travelled = 0; ///< The distance travelled so far.
        link m_link; ///< The link representing the travel route.

        /// Starts travelling from one location to another.
        /// \param from The starting location.
        /// \param to The destination location.
        void start_travelling(loc_type from, loc_type to);

        /// Checks if the travel is finished.
        /// \return True if the travel is finished, false otherwise.
        bool finished() const { return m_travelled >= m_link.m_distance; }

        /// Gets the destination location.
        /// \return The destination location.
        loc_type dest() const { return m_link.m_to; }

        /// Gets the distance of the travel.
        /// \return The distance of the travel.
        int dist() const { return m_link.m_distance; }
    };

    /// Represents a map with distances between locations.
    class map {
    private:
        static map* s_instance; ///< The singleton instance of the map.

        std::array<std::array<int, static_cast<int>(loc_type::num_locs)>, static_cast<int>(loc_type::num_locs)> m_map; ///< The 2D array representing distances between locations.

    public:
        /// Constructs a map and initializes the singleton instance.
        map();
        ~map() = default;

        /// Gets the singleton instance of the map.
        /// \return The singleton instance.
        static map* instance() { return s_instance; }

        /// Gets the distance between two locations.
        /// \param from The starting location.
        /// \param to The destination location.
        /// \return The distance between the locations.
        int distance(loc_type from, loc_type to) const {
            return m_map[static_cast<int>(from)][static_cast<int>(to)];
        }
    };

} // namespace core
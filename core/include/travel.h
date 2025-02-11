#pragma once

#include <vector>

namespace core {

    /// Represents a link between two locations with a distance.
    struct link {
        uint8_t m_from = 0; ///< The starting location.
        uint8_t m_to = 0; ///< The destination location.
        int m_distance = 0; ///< The distance between the locations.
    };

    /// Contains data related to travel, including the distance travelled and the link.
    struct travel_data {
        int m_travelled = 0; ///< The distance travelled so far.
        link m_link; ///< The link representing the travel route.

        /// Starts travelling from one location to another.
        /// \param from The starting location.
        /// \param to The destination location.
        void start_travelling(uint8_t from, uint8_t to);

        /// Checks if the travel is finished.
        /// \return True if the travel is finished, false otherwise.
        bool finished() const { return m_travelled >= m_link.m_distance; }

        /// Gets the destination location.
        /// \return The destination location.
        uint8_t dest() const { return m_link.m_to; }

        /// Gets the distance of the travel.
        /// \return The distance of the travel.
        int dist() const { return m_link.m_distance; }
    };

    class map;

    /// Represents a graph with distances between locations.
    class graph {
    private:
        static graph* s_instance; ///< The singleton instance of the graph.

        std::vector<std::vector<uint8_t>> m_graph; ///< The 2D array representing distances between locations.

    public:
        /// Constructs a graph and initializes the singleton instance.
        graph(uint8_t num_locs);
        graph(const map& map);
        ~graph() = default;

        /// Gets the singleton instance of the graph.
        /// \return The singleton instance.
        static graph* instance() { return s_instance; }

        /// Gets the distance between two locations.
        /// \param from The starting location.
        /// \param to The destination location.
        /// \return The distance between the locations.
        int distance(uint8_t from, uint8_t to) const {
            return m_graph[from][to];
        }
    };

} // namespace core
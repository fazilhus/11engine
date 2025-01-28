#pragma once

#include <array>

#include "util.h"

namespace core {

    struct link {
        loc_type m_from = loc_type::none;
        loc_type m_to = loc_type::none;
        int m_distance = 0;
    };

    struct travel_data {
        int m_travelled = 0;
        link m_link;

        void start_travelling(loc_type from, loc_type to);
        bool finished() const { return m_travelled >= m_link.m_distance; }
        loc_type dest() const { return m_link.m_to; }
        int dist() const { return m_link.m_distance; }
    };

    class map {
    private:
        static map* s_instance;

        std::array<std::array<int, static_cast<int>(loc_type::num_locs)>, static_cast<int>(loc_type::num_locs)> m_map;

    public:
        map();
        ~map() = default;

        static map* instance() { return s_instance; }
        int distance(loc_type from, loc_type to) const {
            return m_map[static_cast<int>(from)][static_cast<int>(to)];
        }
    };

} // namespace core
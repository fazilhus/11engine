#include "travel.h"

namespace core {

    void travel_data::start_travelling(loc_type from, loc_type to) {
        m_travelled = 0;
        m_link = {from, to, map::instance()->distance(from, to)};
    }

    map* map::s_instance = nullptr;

    map::map() {
        s_instance = this;

    int n = static_cast<int>(loc_type::num_locs);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) {
                m_map[i][j] = 0;
            } else {
                int distance = util::random_int(1, 4);
                m_map[i][j] = distance;
                m_map[j][i] = distance;
            }
        }
    }
    }

} // namespace core
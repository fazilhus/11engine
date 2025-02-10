#include "travel.h"

namespace core {

    void travel_data::start_travelling(uint8_t from, uint8_t to) {
        m_travelled = 0;
        m_link = {from, to, graph::instance()->distance(from, to)};
    }

    graph* graph::s_instance = nullptr;

    graph::graph(uint8_t num_locs) {
        s_instance = this;

        m_map.resize(num_locs);
        for (auto& e : m_map) {
            e.resize(num_locs);
        }

        for (int i = 0; i < num_locs; ++i) {
            for (int j = i; j < num_locs; ++j) {
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
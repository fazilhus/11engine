#include "travel.h"

#include "map.h"
#include "util.h"

namespace core {

    void travel_data::start_travelling(uint8_t from, uint8_t to) {
        m_travelled = 0;
        m_link = {from, to, graph::instance()->distance(from, to)};
    }

    graph* graph::s_instance = nullptr;

    graph::graph(uint8_t num_locs) {
        s_instance = this;

        m_graph.resize(num_locs);
        for (auto& e : m_graph) {
            e.resize(num_locs);
        }

        for (int i = 0; i < num_locs; ++i) {
            for (int j = i; j < num_locs; ++j) {
                if (i == j) {
                    m_graph[i][j] = 0;
                } else {
                    int distance = util::random_int(1, 4);
                    m_graph[i][j] = distance;
                    m_graph[j][i] = distance;
                }
            }
        }
    }

    // graph::graph(const map& map) {
    //     
    // }
} // namespace core
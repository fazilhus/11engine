#pragma once

#include <cstdint>

namespace core {

    enum path_algo : uint8_t {
        path_algo_default,
        path_algo_dijkstra,
        path_algo_astar,
        path_algo_num
    };

} // namespace core
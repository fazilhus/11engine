#pragma once

#include <vector>
#include <memory>

#include "enum.h"
#include "game_config.h"

namespace core {

    struct tile {
        using value_type = std::weak_ptr<tile>;
        tile_type type;
        union {
            std::array<int, 2> pos;
            struct {
                int posx;
                int posy;
            };
        };
        int size;
        bool walkable;
        bool discovered;
        int contents;
        float speed_mod;
        
        int time;
        int dtime;

        std::vector<value_type> neighbours;

        tile(const config::tile_cfg& cfg, std::array<int, 2> p);
    };

    namespace util {

        std::array<int, 2> tile_to_pos(std::array<int, 2> pos);

    } // namespace util

} // namespace core
#pragma once

#include <vector>
#include <memory>

#include "enum.h"
#include "cfg.h"

namespace core {

    struct tile {
        using value_type = std::weak_ptr<tile>;
        tile_type type;
        int posx, posy;
        int size;
        bool walkable;
        bool discovered;
        int contents;
        float speed_mod;
        
        int time;
        int dtime;

        std::vector<value_type> neighbours;

        tile(const config::tile_cfg& cfg, int x, int y);
    };

} // namespace core
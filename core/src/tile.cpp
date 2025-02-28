#include "tile.h"

namespace core {

    tile::tile(const config::tile_cfg &cfg, std::array<int, 2> p) {
        type = cfg.name;
        pos = p;
        size = cfg.size;
        walkable = cfg.walkable;
        discovered = false;
        to_be_discovered = false;
        to_be_gathered = 0;
        contents = cfg.max_contents;
        max_contents = cfg.max_contents;
        speed_mod = cfg.speed_mod;
        building = building_type_none;

        time = static_cast<int>(static_cast<float>(size) * speed_mod);
        dtime = static_cast<int>(static_cast<float>(time) * 1.4f);
    }

    namespace util {

        std::array<int, 2> tile_to_pos(std::array<int, 2> pos) {
            const auto cfg = game_config::get();
            int size = cfg->tile_cfg[1].size;
            pos[0] = pos[0] * size + (size / 2);
            pos[1] = pos[1] * size + (size / 2);
            return pos;
        }

    } // namespace util

} // namespace core

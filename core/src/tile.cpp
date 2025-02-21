#include "tile.h"

namespace core {

    tile::tile(const config::tile_cfg &cfg, int x, int y) {
        type = cfg.name;
        posx = x;
        posy = y;
        size = cfg.size;
        walkable = cfg.walkable;
        discovered = false;
        contents = cfg.contents;
        speed_mod = cfg.speed_mod;

        time = static_cast<int>(static_cast<float>(size) * speed_mod);
        dtime = static_cast<int>(static_cast<float>(time) * 1.4f);
    }

} // namespace core
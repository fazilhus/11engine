#include "tile.h"

namespace core {

    tile::tile(const config::tile &cfg, int x, int y) {
        type = cfg.name;
        posx = x;
        posy = y;
        walkable = cfg.walkable;
        discovered = false;
        contents = cfg.contents;
        speed_mod = cfg.speed_mod;

        time = static_cast<int>(static_cast<float>(size) * speed_mod);
        dtime = static_cast<int>(static_cast<float>(time) * 1.4f);
    }

} // namespace core
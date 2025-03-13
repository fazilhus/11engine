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
        storage = {};

        time = static_cast<int>(static_cast<float>(size) * speed_mod);
        dtime = static_cast<int>(static_cast<float>(time) * 1.4f);
    }

    template <typename T>
    bool tile::has_resources_for(T type, std::array<int, resource_type_num>& res) {
        return false;
    }

    template <>
    bool tile::has_resources_for(resource_type type, std::array<int, resource_type_num>& res) {
        return false;
    }

    template <>
    bool tile::has_resources_for(building_type type, std::array<int, resource_type_num>& res) {
        const auto& required = game_config::get()->building_cfg[type].resources;
        bool flag = true;
        for (std::size_t i = 0; i < storage.size() && i < required.size(); ++i) {
            if (storage[i] < required[i]) {
                flag = false;
                res[i] = required[i] - storage[i];
            }
        }
        return flag;
    }

    namespace util {

        std::array<int, 2> tile_to_pos(std::array<int, 2> pos) {
            const auto cfg = game_config::get();
            int size = cfg->tile_cfg[0].size;
            pos[0] = pos[0] * size + (size / 2);
            pos[1] = pos[1] * size + (size / 2);
            return pos;
        }

    } // namespace util

} // namespace core

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
        bool to_be_discovered;
        int to_be_gathered;
        int contents;
        int max_contents;
        float speed_mod;
        building_type building;
        int building_used_by;
        std::array<int, resource_type_num> storage;
        
        int time;
        int dtime;

        std::vector<value_type> neighbours;

        tile(const config::tile_cfg& cfg, std::array<int, 2> p);

        int get_resource(resource_type type) { return storage[type]; }

        int put_resource(resource_type type, int num = 1) { return storage[type] += num; }

        int take_resource(resource_type type, int num = 1) { return storage[type] -= num; }

        template <typename T>
        bool has_resources_for(T type, std::array<int, resource_type_num>& res);
        template <>
        bool has_resources_for(resource_type type, std::array<int, resource_type_num>& res);
        template <>
        bool has_resources_for(building_type type, std::array<int, resource_type_num>& res);
    };

    namespace util {

        std::array<int, 2> tile_to_pos(std::array<int, 2> pos);

    } // namespace util

} // namespace core
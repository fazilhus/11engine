#pragma once

#include <array>

#include "nlohmann/json.hpp"

#include "enum.h"

namespace core {

    namespace config {

        struct map {
            int width;
            int height;
        };

        struct tile {
            int size;
            tile_type name;
            bool walkable;
            int contents;
            float speed_mod;
        };
        
        struct building {
            tile_type tile;
            building_type name;
            int builders;
            std::array<int, resource_type_num> resources;
            int time;
        };

        struct resource {
            resource_type name;
            std::array<int, resource_type_num> in;
            int out;
            int time;
        };

        struct unit {
            unit_type name;
            unit_type from;
            int carry;
            int upgrade_time;
        };

    } // namespace config

    struct game_config {

        config::map map_cfg;
        std::array<config::tile, tile_type_num> tile_cfg;
        std::array<config::building, building_type_num> building_cfg;
        std::array<config::resource, resource_type_num> resource_cfg;
        std::array<config::unit, unit_type_num> unit_cfg;
        
        game_config(const nlohmann::json& doc);
        
        static game_config* s_instance;
        static const game_config* get() { return s_instance; }
    };

} // namespace core
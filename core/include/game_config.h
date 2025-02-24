#pragma once

#include <array>

#include "nlohmann/json.hpp"

#include "enum.h"

namespace core {

    namespace config {

        struct map_cfg {
            int width;
            int height;
            std::array<int, 2> start;
        };

        struct tile_cfg {
            int size;
            tile_type name;
            bool walkable;
            int max_contents;
            float speed_mod;
        };
        
        struct building_cfg {
            tile_type tile;
            building_type name;
            int builders;
            std::array<int, resource_type_num> resources;
            int time;
        };

        struct resource_cfg {
            resource_type name;
            std::array<int, resource_type_num> in;
            int out;
            int time;
        };

        struct unit_cfg {
            unit_type name;
            unit_type from;
            int speed;
            int carry;
            int upgrade_time;
        };

    } // namespace config

    struct game_config {

        config::map_cfg map_cfg;
        std::array<config::tile_cfg, tile_type_num> tile_cfg;
        std::array<config::building_cfg, building_type_num> building_cfg;
        std::array<config::resource_cfg, resource_type_num> resource_cfg;
        std::array<config::unit_cfg, unit_type_num> unit_cfg;
        
        game_config(const nlohmann::json& doc);
        
        static game_config* s_instance;
        static const game_config* get() { return s_instance; }
    };

} // namespace core
#pragma once

#include <cstdint>
#include <string>

namespace core {

    enum path_algo : uint8_t {
        path_algo_default,
        path_algo_dijkstra,
        path_algo_astar,
        path_algo_num
    };

    enum tile_type : uint8_t {
        tile_type_none,
        tile_type_forest,
        tile_type_water,
        tile_type_swamp,
        tile_type_mountain,
        tile_type_grass,
        tile_type_num
    };

    enum building_type : uint8_t {
        building_type_none,
        building_type_coal_mine,
        building_type_num
    };

    enum resource_type : uint8_t {
        resource_type_none,
        resource_type_wood,
        resource_type_coal,
        resource_type_num
    };

    enum unit_type : uint8_t {
        unit_type_none,
        unit_type_worker,
        unit_type_scout,
        unit_type_builder,
        unit_type_miner,
        unit_type_num
    };

    namespace util {

        tile_type char_to_tile(char c);
        building_type str_to_building(const std::string& s);
        resource_type str_to_resource(const std::string& s);
        unit_type str_to_unit(const std::string& s);

    } // namespace util

} // namespace core
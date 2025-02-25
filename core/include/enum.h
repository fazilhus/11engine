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
        tile_type_forest,
        tile_type_water,
        tile_type_swamp,
        tile_type_mountain,
        tile_type_grass,
        tile_type_num,
        tile_type_none
    };

    enum building_type : uint8_t {
        building_type_coal_mine,
        building_type_num,
        building_type_none
    };

    enum resource_type : uint8_t {
        resource_type_wood,
        resource_type_coal,
        resource_type_num,
        resource_type_none
    };

    enum unit_type : uint8_t {
        unit_type_worker,
        unit_type_scout,
        unit_type_builder,
        unit_type_miner,
        unit_type_num,
        unit_type_none
    };

    enum scout_state_type : uint8_t {
        scout_state_wander,
        scout_state_num,
        scout_state_none
    };

    enum worker_state_type : uint8_t {
        worker_state_idle,
        worker_state_move_to_resource,
        worker_state_move_to_base,
        worker_state_gather_resource,
        worker_state_num,
        worker_state_none
    };

    enum message_type : uint8_t {};

    namespace util {

        tile_type char_to_tile(char c);
        building_type str_to_building(const std::string& s);
        resource_type str_to_resource(const std::string& s);
        unit_type str_to_unit(const std::string& s);

    } // namespace util

} // namespace core
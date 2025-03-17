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
        building_type_base,
        building_type_coal_mine,
        building_type_construction,
        building_type_num,
        building_type_none
    };

    enum target_type : uint8_t {
        target_type_forest,
        target_type_base,
        target_type_coal_mine,
        target_type_num,
        target_type_none
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
        scout_state_idle,
        scout_state_wander,
        scout_state_num,
        scout_state_none
    };

    enum worker_state_type : uint8_t {
        worker_state_idle,
        worker_state_move_to_resource,
        worker_state_move_to_target,
        worker_state_gather_resource,
        worker_state_store_resource,
        worker_state_upgrade_to_scout,
        worker_state_upgrade_to_builder,
        worker_state_upgrade_to_miner,
        worker_state_num,
        worker_state_none
    };

    enum builder_state_type : uint8_t {
        builder_state_idle,
        builder_state_move,
        builder_state_build,
        builder_state_num,
        builder_state_none
    };

    enum miner_state_type : uint8_t {
        miner_state_idle,
        miner_state_move,
        miner_state_produce_coal,
        miner_state_num,
        miner_state_none
    };

    enum job_type : uint8_t {
        job_type_collect_resource,
        job_type_create_scout,
        job_type_create_builder,
        job_type_create_miner,
        job_type_build_coal_mine,
        job_type_produce_coal,
        job_type_num,
        job_type_none
    };

    namespace util {

        tile_type char_to_tile(char c);
        building_type str_to_building(const std::string& s);
        resource_type str_to_resource(const std::string& s);
        unit_type str_to_unit(const std::string& s);

        target_type tile_to_target(tile_type t);
        target_type building_to_target(building_type b);

        std::string worker_state_to_str(worker_state_type t);

    } // namespace util

} // namespace core
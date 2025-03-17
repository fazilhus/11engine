#include "enum.h"

namespace core::util {

    tile_type char_to_tile(char c) {
        switch (c) {
        case 'T': return tile_type_forest;
        case 'V': return tile_type_water;
        case 'G': return tile_type_swamp;
        case 'B': return tile_type_mountain;
        case 'M': return tile_type_grass;
        default: return tile_type_none;
        }
    }

    building_type str_to_building(const std::string &s) {
        if (s == "base") return building_type_base;
        if (s == "coal_mine") return building_type_coal_mine;
        return building_type_none;
    }

    resource_type str_to_resource(const std::string &s) {
        if (s == "wood") return resource_type_wood;
        if (s == "coal") return resource_type_coal;
        return resource_type_none;
    }

    unit_type str_to_unit(const std::string &s) {
        if (s == "worker") return unit_type_worker;
        if (s == "scout") return unit_type_scout;
        if (s == "builder") return unit_type_builder;
        if (s == "miner") return unit_type_miner;
        return unit_type_none;
    }

    target_type tile_to_target(tile_type t) {
        switch (t) {
        case tile_type_forest: return target_type_forest;
        default: return target_type_none;
        }
    }

    target_type building_to_target(building_type b) {
        switch (b) {
        case building_type_base: return target_type_base;
        case building_type_coal_mine: return target_type_coal_mine;
        default: return target_type_none;
        }
    }

    std::string worker_state_to_str(worker_state_type t) {
        switch (t) {
        case worker_state_idle: return "idle";
        case worker_state_move_to_resource: return "move to res";
        case worker_state_move_to_target: return "move to target";
        case worker_state_gather_resource: return "gather";
        case worker_state_upgrade_to_scout: return "upgrade to scout";
        case worker_state_upgrade_to_builder: return "upgrade to builder";
        case worker_state_upgrade_to_miner: return "upgrade to miner";
        default: return "";
        }
    }

} // namespace core::util
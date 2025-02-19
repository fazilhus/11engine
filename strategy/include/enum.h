#pragma once

#include <cstdint>
#include <string>

namespace core {

    enum tile_type : uint8_t {
        tile_type_none,
        tile_type_forest,
        tile_type_water,
        tile_type_swamp,
        tile_type_mountain,
        tile_type_grass,
        tile_type_num
    };

} // namespace core
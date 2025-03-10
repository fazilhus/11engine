#pragma once

#include "enum.h"

namespace core {

    struct building {
        building_type type = building_type_none;
        int capacity = 0;
    };

} // namespace core
#pragma once

#include <string>

#include "enum.h"
#include "map.h"

namespace core {

    class map : public default_map<tile_type> {
    public:
        map(const std::string& path);
        ~map() override = default;
    };

} // namespace core
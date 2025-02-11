#pragma once

#include <filesystem>

#include "enum.h"
#include "map.h"

namespace core {

    class map : public default_map<tile_type> {
    public:
        map(const std::filesystem::path& path);
        ~map() override = default;
    };

} // namespace core
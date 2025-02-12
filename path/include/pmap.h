#pragma once

#include <filesystem>

#include "enum.h"
#include "map.h"

namespace core {

    class map : public default_map<tile_type> {
    public:
        map(const std::filesystem::path& path);
        ~map() override = default;

        path<tile_t> get_path(tile_type from, tile_type to, path_algo algo = path_algo_default) const override;
    };

} // namespace core
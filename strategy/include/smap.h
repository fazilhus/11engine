#pragma once

#include <filesystem>

#include "enum.h"
#include "map.h"

namespace core {

    class map : public default_map {
    private:
        static map* s_instance;

    public:
        map(const std::filesystem::path& path);
        ~map() override = default;

        static map* get() { return s_instance; }

        std::weak_ptr<tile_t> get_random_neighbour(std::weak_ptr<tile_t> t) const;

        path get_path(tile_type from, tile_type to, path_algo algo = path_algo_default) const override;

        void discover_around(std::weak_ptr<tile_t> t);
    };

} // namespace core
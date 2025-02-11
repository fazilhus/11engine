#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>

namespace core {

    template <typename tile_type>
    struct tile {
        using value_type = std::weak_ptr<tile>;
        tile_type type;
        std::vector<value_type> m_neighbours;
    };

    template <typename tile_type>
    struct path {
        using value_type = std::weak_ptr<tile<tile_type>>;
        std::vector<value_type> m_path;
    };

    template <typename tile_t>
    class default_map{
    public:
        using tile_type = tile<tile_t>;
        using value_type = std::shared_ptr<tile_type>;
        using reference = value_type&;
        using const_reference = const value_type&;

    protected:
        int m_xmax, m_ymax;
        std::vector<value_type> m_tiles;
        std::vector<std::weak_ptr<tile_type>> m_targets;

        default_map() = default;

    public:
        virtual ~default_map() = default;

        reference get(int i, int j) {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[i * m_xmax + j];
        }

        const_reference get(int i, int j) const {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[i * m_xmax + j];
        }

        const std::vector<std::weak_ptr<tile_type>>& get_targets() const { return m_targets; }
    };

} // namespace core
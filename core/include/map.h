#pragma once

#include <cstdint>
#include <vector>
#include <cassert>

namespace core {

    template <typename tile_type>
    struct tile {
        tile_type type;
        std::vector<tile> neighbours;
    };

    template <typename tile_type>
    class default_map{
    protected:
        std::size_t m_length, m_width;
        std::vector<tile<tile_type>> m_tiles;

        default_map() = default;

    public:
        virtual ~default_map() = default;

        tile<tile_type>& get(std::size_t i, std::size_t j) {
#ifdef DEBUG
            assert(i < m_length && j < m_width && "map index out of bounds");
#endif
            return m_tiles[i * m_length + j];
        }

        const tile<tile_type>& get(std::size_t i, std::size_t j) const {
#ifdef DEBUG
            assert(i < m_length && j < m_width && "map index out of bounds");
#endif
            return m_tiles[i * m_length + j];
        }
    };

} // namespace core
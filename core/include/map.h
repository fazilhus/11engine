#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <functional>

#include "enum.h"
#include "pqueue.h"
#include "tile.h"
#include "util.h"

namespace core {

    struct path {
        using value_type = std::weak_ptr<tile>;
        int m_i;
        value_type m_next;
        std::vector<value_type> m_path;

        void reverse() {
            std::reverse(m_path.begin(), m_path.end());
            m_i = 0;
            m_next = m_path.front();
        }
    };

    class map{
    private:
        static map* s_instance;

    public:
        using tile_t = tile;
        using value_t = std::shared_ptr<tile_t>;
        using reference = value_t&;
        using const_reference = const value_t&;

    private:
        int m_xmax, m_ymax;
        std::vector<value_t> m_tiles;
        std::vector<std::weak_ptr<tile_t>> m_targets;

        
    public:
        map(const std::filesystem::path& path);

        static map* get() { return s_instance; }

        std::pair<int, int> get_dim() const {
            return { m_xmax, m_ymax };
        }

        reference get_tile(std::pair<int, int> pos) {
            return get_tile(pos.first, pos.second);
        }
        reference get_tile(std::array<int, 2> pos) {
            return get_tile(pos[0], pos[1]);
        }
        reference get_tile(int i, int j) {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_xmax + i];
        }

        const_reference get_tile(std::pair<int, int> pos) const {
            return get_tile(pos.first, pos.second);
        }
        const_reference get_tile(std::array<int, 2> pos) const {
            return get_tile(pos[0], pos[1]);
        }
        const_reference get_tile(int i, int j) const {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_xmax + i];
        }

        const std::vector<std::weak_ptr<tile_t>>& get_targets() const { return m_targets; }

        const std::weak_ptr<tile_t>& find_target(tile_type tile) const {
            for (auto& target : m_targets) {
                if (target.lock()->type == tile) {
                    return target;
                }
            }
            return {};
        }

        std::weak_ptr<tile_t> get_random_neighbour(std::weak_ptr<tile_t> t) const;

        path get_path(tile_type from, tile_type to, path_algo algo = path_algo_default) const;

        path get_path_to_undiscovered(const_reference from) const;
        path get_path_to_tile_of(const_reference from, tile_type t) const;

        void discover_around(std::weak_ptr<tile_t> t);

        path get_path(const_reference from, const_reference to) const;
        path get_path_to_closest(const_reference from, std::function<bool(const_reference)> filter) const;
        path get_path_dijkstra(const_reference from, const_reference to) const;
        path get_path_astar(const_reference from, const_reference to) const;
        
    private:
        path _make_path(const std::vector<int>& costs, const_reference from, const_reference to, std::function<bool(const_reference)> filter) const;

    };
} // namespace core
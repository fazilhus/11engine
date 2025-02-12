#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cmath>

#include "enum.h"

namespace core {

    template <typename T>
    struct tile {
        using value_type = std::weak_ptr<tile>;
        T type;
        int posx, posy;
        std::vector<value_type> m_neighbours;
    };

    template <typename T>
    struct path {
        using value_type = std::weak_ptr<T>;
        std::vector<value_type> m_path;
    };

    template <typename T>
    class default_map{
    public:
        using tile_t = tile<T>;
        using value_t = std::shared_ptr<tile_t>;
        using reference = value_t&;
        using const_reference = const value_t&;

    protected:
        int m_xmax, m_ymax;
        std::vector<value_t> m_tiles;
        std::vector<std::weak_ptr<tile_t>> m_targets;

        default_map() = default;

    public:
        virtual ~default_map() = default;

        reference get(const std::pair<int, int>& pos) {
            return get(pos.first, pos.second);
        }
        reference get(int i, int j) {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_ymax + i];
        }

        const_reference get(const std::pair<int, int>& pos) const {
            return get(pos.first, pos.second);
        }
        const_reference get(int i, int j) const {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_ymax + i];
        }

        const std::vector<std::weak_ptr<tile_t>>& get_targets() const { return m_targets; }

        const std::weak_ptr<tile_t>& find_target(T tile) const {
            for (auto& target : m_targets) {
                if (target.lock()->type == tile) {
                    return target;
                }
            }
            return {};
        }

        virtual path<tile_t> get_path(T from, T to, path_algo algo = path_algo_default) const = 0;

    protected:
        path<tile_t> _get_path(const_reference from, const_reference to) const {
            std::vector<int> costs(m_tiles.size(), -1);
            costs[from->posy * m_ymax + from->posx] = 0;
            std::queue<std::pair<int, int>> q;
            q.push({from->posx, from->posy});

            while (!q.empty()) {
                auto coords = q.front();
                const auto& tile = get(coords);
                q.pop();

                for (auto i = 0; i < tile->m_neighbours.size(); i++) {
                    const auto& n_tile = tile->m_neighbours[i].lock();
                    int cost = 10;
                    if (abs(n_tile->posx - tile->posx) == 1 && abs(n_tile->posy - tile->posy) == 1 ) cost = 15;

                    int current_cost = costs[n_tile->posy * m_ymax + n_tile->posx];
                    int travel_cost = costs[tile->posy * m_ymax + tile->posx] + cost;
                    if (-1 != current_cost && current_cost < travel_cost) continue;
                    costs[n_tile->posy * m_ymax + n_tile->posx] = travel_cost;
                    q.push({n_tile->posx, n_tile->posy});
                }
            }

            path<tile_t> path;
            auto current = to;
            while (current != from) {
                path.m_path.push_back(current);
                int min_cost = costs[current->posy * m_ymax + current->posx];
                std::weak_ptr<tile_t> next_tile;

                for (const auto& neighbour : current->m_neighbours) {
                    auto n_tile = neighbour.lock();
                    int cost = costs[n_tile->posy * m_ymax + n_tile->posx];
                    if (cost >= 0 && cost < min_cost) {
                        min_cost = cost;
                        next_tile = n_tile;
                    }
                }

                current = next_tile.lock();
            }
            path.m_path.push_back(from);
            std::reverse(path.m_path.begin(), path.m_path.end());
            return path;
        }
        
        path<tile_t> _get_path_astar(const_reference from, const_reference to) const {
            path<tile_t> path;
            return path;
        }
        
        path<tile_t> _get_path_dijkstra(const_reference from, const_reference to) const {
            path<tile_t> path;
            return path;
        }
    };
} // namespace core
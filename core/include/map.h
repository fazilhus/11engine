#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cmath>
#include <algorithm>

#include "enum.h"
#include "pqueue.h"
#include "tile.h"

namespace core {

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

        std::pair<int, int> get_dim() const {
            return { m_xmax, m_ymax };
        }

        reference get(const std::pair<int, int>& pos) {
            return get(pos.first, pos.second);
        }
        reference get(int i, int j) {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_xmax + i];
        }

        const_reference get(const std::pair<int, int>& pos) const {
            return get(pos.first, pos.second);
        }
        const_reference get(int i, int j) const {
#ifdef DEBUG
            assert(i < m_xmax && j < m_ymax && "map index out of bounds");
#endif
            return m_tiles[j * m_xmax + i];
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
            costs[from->posy * m_xmax + from->posx] = 0;
            std::queue<std::pair<int, int>> q;
            q.emplace(from->posx, from->posy);

            while (!q.empty()) {
                auto coords = q.front();
                const auto& tile = get(coords);
                q.pop();

                for (auto i = 0; i < tile->neighbours.size(); i++) {
                    const auto& next_tile = tile->neighbours[i].lock();

                    if (!next_tile->walkable) continue;

                    int cost = 10;
                    if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = 15;

                    int current_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                    int travel_cost = costs[tile->posy * m_xmax + tile->posx] + cost;
                    if (-1 != current_cost && current_cost < travel_cost) continue;
                    costs[next_tile->posy * m_xmax + next_tile->posx] = travel_cost;
                    q.emplace(next_tile->posx, next_tile->posy);
                }
            }

            
            return _make_path(costs, from, to);
        }

        path<tile_t> _get_path_dijkstra(const_reference from, const_reference to) const {
            std::vector<int> costs(m_tiles.size(), INT_MAX);
            costs[from->posy * m_xmax + from->posx] = 0;

            struct connection {
                int dist;
                int posx;
                int posy;
            };
            auto comp = [](const connection& l, const connection& r) -> bool {
                return l.dist > r.dist;
            };
            container::pqueue<connection, decltype(comp)> pq(comp);
            pq.emplace(0, from->posx, from->posy);
            
            std::vector<bool> visited(m_tiles.size(), false);

            connection con = pq.top();
            auto tile = get(con.posx, con.posy);
            while (tile != to) {
                while (!pq.empty()) {
                    con = pq.top();
                    if (visited[con.posy * m_xmax + con.posx]) {
                        pq.pop();
                        continue;
                    }

                    tile = get(con.posx, con.posy);
                    pq.pop();
                    break;
                }

                for (auto i = 0; i < tile->neighbours.size(); i++) {
                    const auto& next_tile = tile->neighbours[i].lock();

                    if (!next_tile->walkable) continue;

                    if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;

                    int cost = 10;
                    if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = 15;
                    int old_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                    int new_cost = con.dist + cost;
                    if (old_cost > new_cost) {
                        costs[next_tile->posy * m_xmax + next_tile->posx] = new_cost;
                        pq.emplace(new_cost, next_tile->posx, next_tile->posy);
                    }
                }

                visited[con.posy * m_xmax + con.posx] = true;
            }
            
            return _make_path(costs, from, to);
        }
        
        path<tile_t> _get_path_astar(const_reference from, const_reference to) const {
            std::vector<int> costs(m_tiles.size(), INT_MAX);
            costs[from->posy * m_xmax + from->posx] = 0;

            auto dist = [](int x1, int y1, int x2, int y2) -> int {
                int dx = abs(x1 - x2);
                int dy = abs(y1 - y2);
                return std::min(dx, dy) * 15 + abs(dx - dy) * 10;
            };

            struct connection {
                int dist;
                int posx;
                int posy;
            };
            auto comp = [](const connection& l, const connection& r) -> bool {
                return l.dist > r.dist;
            };
            container::pqueue<connection, decltype(comp)> pq(comp);
            pq.emplace(dist(from->posx, from->posy, to->posx, to->posy), from->posx, from->posy);
            
            std::vector<bool> visited(m_tiles.size(), false);

            connection con = pq.top();
            auto tile = get(con.posx, con.posy);
            while (tile != to) {
                while (!pq.empty()) {
                    con = pq.top();
                    if (visited[con.posy * m_xmax + con.posx]) {
                        pq.pop();
                        continue;
                    }

                    tile = get(con.posx, con.posy);
                    pq.pop();
                    break;
                }

                for (auto i = 0; i < tile->neighbours.size(); i++) {
                    const auto& next_tile = tile->neighbours[i].lock();

                    if (!next_tile->walkable) continue;

                    if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;

                    int cost = 10;
                    if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = 15;
                    int old_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                    int new_cost = costs[tile->posy * m_xmax + tile->posx] + cost;
                    if (old_cost > new_cost) {
                        costs[next_tile->posy * m_xmax + next_tile->posx] = new_cost;
                        pq.emplace(new_cost + dist(next_tile->posx, next_tile->posy, to->posx, to->posy), next_tile->posx, next_tile->posy);
                    }
                }

                visited[con.posy * m_xmax + con.posx] = true;
            }
            
            return _make_path(costs, from, to);
        }
        
    private:
        path<tile_t> _make_path(const std::vector<int>& costs, const_reference from, const_reference to) const {
            path<tile_t> path;
            auto current = to;
            while (current != from) {
                path.m_path.push_back(current);
                int min_cost = costs[current->posy * m_xmax + current->posx];
                std::weak_ptr<tile_t> next_tile;

                for (const auto& neighbour : current->neighbours) {
                    auto n_tile = neighbour.lock();

                    if (!n_tile->walkable) continue;
                    
                    int cost = costs[n_tile->posy * m_xmax + n_tile->posx];
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
    };
} // namespace core
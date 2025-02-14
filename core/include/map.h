#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>

#include "enum.h"
#include "pqueue.h"

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

                for (auto i = 0; i < tile->m_neighbours.size(); i++) {
                    const auto& n_tile = tile->m_neighbours[i].lock();
                    int cost = 10;
                    if (abs(n_tile->posx - tile->posx) == 1 && abs(n_tile->posy - tile->posy) == 1 ) cost = 15;

                    int current_cost = costs[n_tile->posy * m_xmax + n_tile->posx];
                    int travel_cost = costs[tile->posy * m_xmax + tile->posx] + cost;
                    if (-1 != current_cost && current_cost < travel_cost) continue;
                    costs[n_tile->posy * m_xmax + n_tile->posx] = travel_cost;
                    q.emplace(n_tile->posx, n_tile->posy);
                }
            }

            
            return _make_path(costs, from, to);
        }

        path<tile_t> _get_path_dijkstra(const_reference from, const_reference to) const {
            std::vector<int> costs(m_tiles.size(), INT_MAX);
            costs[from->posy * m_xmax + from->posx] = 0;
            using connection = std::pair<int, std::pair<int, int>>;
            auto comp = [](const connection& l, const connection& r) {
                return l.first < r.first;
            };
            container::pqueue<connection, decltype(comp)> pq(comp);
            pq.push({0, {from->posx, from->posy}});
            std::vector<bool> visited(m_tiles.size(), false);

            while (!pq.empty()) {
                connection next = pq.top();
                const auto& tile = get(next.second);
                pq.pop();
                visited[tile->posy * m_xmax + tile->posx] = true;

                for (auto i = 0; i < tile->m_neighbours.size(); i++) {
                    const auto& next_tile = tile->m_neighbours[i].lock();
                    if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;
                    int cost = 10;
                    if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = 15;
                    int current_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                    int travel_cost = next.first + cost;
                    if (current_cost > travel_cost) {
                        costs[next_tile->posy * m_xmax + next_tile->posx] = travel_cost;
                        pq.push({travel_cost, {next_tile->posx, next_tile->posy}});
                    }
                }
            }
            
            return _make_path(costs, from, to);
        }
        
        path<tile_t> _get_path_astar(const_reference from, const_reference to) const {
            struct node_t {
                int f = INT_MAX;
                int g = 0;
                int h = 0;
                std::pair<int, int> parent;
            };
            std::vector<node_t> nodes(m_tiles.size());
            
            auto dist = [](int x1, int y1, int x2, int y2) -> int {
                int dx = abs(x1 - x2);
                int dy = abs(y1 - y2);
                return std::min(dx, dy) * 15 + abs(dx - dy) * 10;
            };
            int idx = from->posy * m_xmax + from->posx;
            nodes[idx].g = 0;
            nodes[idx].h = dist(from->posx, from->posy, to->posx, to->posy);
            nodes[idx].f = nodes[idx].h;
            
            using connection = std::pair<int, int>;
            auto comp = [this, &nodes](const connection& l, const connection& r) -> bool {
                const auto& node_l = nodes[l.second * m_xmax + l.first];
                const auto& node_r = nodes[r.second * m_xmax + r.first];

                if (node_l.f == node_r.f) return node_l.h < node_r.h;
                return node_l.f < node_r.f;
            };
            std::set<connection, decltype(comp)> not_visited(comp);
            not_visited.insert({from->posx, from->posy});

            std::vector<bool> visited(m_tiles.size(), false);

            while (!not_visited.empty()) {
                connection curr = *not_visited.begin();
                not_visited.erase(not_visited.begin());
                const auto& tile = get(curr);
                node_t& node = nodes[curr.second * m_xmax + curr.first];
                if (tile == to) break;

                for (auto i = 0; i < tile->m_neighbours.size(); i++) {
                    const auto& next_tile = tile->m_neighbours[i].lock();
                    if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;
                    int cost = 10;
                    if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = 15;

                    node_t& next_node = nodes[next_tile->posy * m_xmax + next_tile->posx]; 
                    int g = node.g + cost;
                    int h = dist(next_tile->posx, next_tile->posy, to->posx, to->posy);
                    int f = g + h;
                    if (next_node.f > f || !not_visited.contains({next_tile->posx, next_tile->posy})) {
                        next_node.f = f;
                        next_node.g = g;
                        next_node.h = h;
                        next_node.parent = {tile->posx, tile->posy};
                        if (!not_visited.contains({next_tile->posx, next_tile->posy})) {
                            not_visited.insert({next_tile->posx, next_tile->posy});
                        }
                    }
                }

                visited[tile->posy * m_xmax + tile->posx] = true;
            }
            
            path<tile_t> path;
            auto ctile = to;
            auto& cnode = nodes[ctile->posy * m_xmax + ctile->posx];
            while (ctile != from) {
                path.m_path.push_back(ctile);
                
                ctile = get(cnode.parent.first, cnode.parent.second);
                cnode = nodes[ctile->posy * m_xmax + ctile->posx];
            }
            path.m_path.push_back(from);
            std::reverse(path.m_path.begin(), path.m_path.end());
            return path;
        }
        
    private:
        path<tile_t> _make_path(const std::vector<int>& costs, const_reference from, const_reference to) const {
            path<tile_t> path;
            auto current = to;
            while (current != from) {
                path.m_path.push_back(current);
                int min_cost = costs[current->posy * m_xmax + current->posx];
                std::weak_ptr<tile_t> next_tile;

                for (const auto& neighbour : current->m_neighbours) {
                    auto n_tile = neighbour.lock();
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
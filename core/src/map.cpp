#include "map.h"

#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>

#include "tile.h"

namespace core {

    map* map::s_instance = nullptr;

    map::map(const std::filesystem::path& path) {
        s_instance = this;

        if (!std::filesystem::is_regular_file(path)) {
            std::cerr << "[ERROR] map file path invalid " << path << '\n';
            return;
        }
        
        std::ifstream file(path, std::ios::binary | std::ios::in);
        if (!file.is_open()) {
            std::cerr << "[ERROR] couldn't open map file " << path << '\n';
            return;
        }

        const auto cfg = game_config::get();

        std::string line;
        int n = 0, m = 0;
        while (std::getline(file, line) && m < cfg->map_cfg.height) {
            n = 0;
            for (char c : line) {
                if (n >= cfg->map_cfg.width) break;
                if (c == '\n' || c == '\r') continue;

                tile_type tt = util::char_to_tile(c);

                if (tt == tile_type_none) {
#ifdef DEBUG
                    assert(false && "invalid map tile type");
#endif
                    return;
                }

                m_tiles.emplace_back(std::make_shared<tile_t>(
                    tile(cfg->tile_cfg[tt], {n, m})
                ));

                n++;
            }
            m++;
        }
        m_xmax = n;
        m_ymax = m;

        file.close();

        std::array<std::pair<int, int>, 4> direct = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};
        std::array<std::pair<int, int>, 4> diag = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}};

        std::random_device rd;
        std::mt19937 g(rd());

        for (int i = 0; i < m_xmax; i++) {
            for (int j = 0; j < m_ymax; j++) {
                auto& tile = get_tile(i, j);
                if (!tile->walkable) continue;

                for (int k = 0; k < 4; k++) {
                    auto& dif = diag[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    
                    auto& dif_tile = get_tile(i + dif.first, j + dif.second);
                    
                    if (!dif_tile->walkable) continue;
                    
                    auto& dif_left = direct[k];
                    if (i + dif_left.first < 0 || i + dif_left.first >= m_xmax || j + dif_left.second < 0 || j + dif_left.second >= m_ymax) continue;
                    auto& tile_left = get_tile(i + dif_left.first, j + dif_left.second);
                    
                    auto& dif_right = direct[(k + 1) % 4];
                    if (i + dif_right.first < 0 || i + dif_right.first >= m_xmax || j + dif_right.second < 0 || j + dif_right.second >= m_ymax) continue;
                    auto& tile_right = get_tile(i + dif_right.first, j + dif_right.second);

                    if (tile_left->walkable && tile_right->walkable) {
                        tile->neighbours.push_back(dif_tile);
                    }
                }

                for (int k = 0; k < 4; k++) {
                    auto& dif = direct[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    auto& dif_tile = get_tile(i + dif.first, j + dif.second);

                    if (!dif_tile->walkable) continue;

                    tile->neighbours.push_back(dif_tile);
                }
                std::shuffle(tile->neighbours.begin(), tile->neighbours.end(), g);
            }
        }

        auto [i, j] = cfg->map_cfg.start;
        m_start = m_tiles[j * m_xmax + i];
        m_start.lock()->discovered = true;
        m_start.lock()->building = building_type_base;
        discover_around(m_start);
    }

    std::weak_ptr<map::tile_t> map::get_random_neighbour(std::weak_ptr<tile_t> t) const {
        auto t1 = t.lock();
        int idx;
        do {
            idx = util::random_int(0, t1->neighbours.size() - 1);
        } while (!t1->neighbours[idx].lock()->walkable);
        return t1->neighbours[idx];
    }

    path map::get_path_to_undiscovered(const_reference from) const {
        auto c = [](const_reference t) -> bool {
            return !t->discovered && !t->to_be_discovered;
        };
        auto f = [](const_reference t) -> bool {
            return t->walkable;
        };
        return get_path_to_closest(from, c, f);
    }

    path map::get_path_to_tile_of(const_reference from, tile_type t) const {
        auto c = [&t](const_reference tile) -> bool {
            return tile->type == t && tile->discovered && tile->to_be_gathered < tile->contents;
        };
        auto f = [&t](const_reference tile) -> bool {
            return tile->walkable && tile->discovered;
        };
        return get_path_to_closest(from, c, f);
    }

    void map::discover_around(std::weak_ptr<tile_t> t) {
        std::array<std::pair<int, int>, 8> difs = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}}};

        auto [i, j] = t.lock()->pos;

        for (auto [ii, jj] : difs) {
            if (i + ii < 0 || i + ii >= m_xmax || j + jj < 0 || j + jj >= m_ymax) continue;
            auto& dif_tile = get_tile(i + ii, j + jj);
            dif_tile->discovered = true;
            if (dif_tile->type == tile_type_forest) {
                m_targets[(j + jj) * m_xmax + (i + ii)] = dif_tile;
            }
        }
    }

    path map::get_path_to_closest(const_reference from, std::function<bool(const_reference)> condition, std::function<bool(const_reference)> filter) const {
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
        auto tile = get_tile(con.posx, con.posy);
        while (!condition(tile) && !pq.empty()) {
            while (!pq.empty()) {
                con = pq.top();
                if (visited[con.posy * m_xmax + con.posx]) {
                    pq.pop();
                    continue;
                }

                tile = get_tile(con.posx, con.posy);
                pq.pop();
                break;
            }

            for (auto i = 0; i < tile->neighbours.size(); i++) {
                const auto& next_tile = tile->neighbours[i].lock();

                if (!filter(next_tile)) continue;

                if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;

                int cost = next_tile->time;
                if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = next_tile->dtime;

                int old_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                int new_cost = con.dist + cost;
                if (old_cost > new_cost) {
                    costs[next_tile->posy * m_xmax + next_tile->posx] = new_cost;
                    pq.emplace(new_cost, next_tile->posx, next_tile->posy);
                }
            }

            visited[con.posy * m_xmax + con.posx] = true;
        }

        if (filter(tile)) {
            return _make_path(costs, from, tile, filter);
        }
        return {};
    }

    path map::get_path_from_to(const_reference from, const_reference to, std::function<bool(const_reference)> filter) const {
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
        auto tile = get_tile(con.posx, con.posy);
        while (tile != to) {
            while (!pq.empty()) {
                con = pq.top();
                if (visited[con.posy * m_xmax + con.posx]) {
                    pq.pop();
                    continue;
                }

                tile = get_tile(con.posx, con.posy);
                pq.pop();
                break;
            }

            for (auto i = 0; i < tile->neighbours.size(); i++) {
                const auto& next_tile = tile->neighbours[i].lock();

                if (!filter(next_tile)) continue;

                if (visited[next_tile->posy * m_xmax + next_tile->posx]) continue;

                int cost = next_tile->time;
                if (abs(next_tile->posx - tile->posx) == 1 && abs(next_tile->posy - tile->posy) == 1 ) cost = next_tile->dtime;

                int old_cost = costs[next_tile->posy * m_xmax + next_tile->posx];
                int new_cost = costs[tile->posy * m_xmax + tile->posx] + cost;
                if (old_cost > new_cost) {
                    costs[next_tile->posy * m_xmax + next_tile->posx] = new_cost;
                    pq.emplace(new_cost + dist(next_tile->posx, next_tile->posy, to->posx, to->posy), next_tile->posx, next_tile->posy);
                }
            }

            visited[con.posy * m_xmax + con.posx] = true;
        }
        
        return _make_path(costs, from, to, filter);
    }

    path map::_make_path(const std::vector<int> &costs, const_reference from, const_reference to, std::function<bool(const_reference)> filter) const {
        path path;
        auto current = to;
        while (current != from) {
            path.m_path.push_back(current);
            int min_cost = costs[current->posy * m_xmax + current->posx];
            std::weak_ptr<tile_t> next_tile;

            for (const auto& neighbour : current->neighbours) {
                auto n_tile = neighbour.lock();

                if (!filter(n_tile)) continue;
                
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
        if (path.m_path.size() > 1) {
            path.m_i = 1;
            path.m_next = path.m_path[path.m_i];
            return path;
        }
        
        path.m_next = path.m_path.front();
        path.m_i = 0;
        return path;
    }

} // namespace core
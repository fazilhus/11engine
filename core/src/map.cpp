#include "map.h"

#include <fstream>
#include <iostream>
#include <array>

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

        std::array<std::pair<int, int>, 4> direct = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};
        std::array<std::pair<int, int>, 4> diag = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}};

        for (int i = 0; i < m_xmax; i++) {
            for (int j = 0; j < m_ymax; j++) {
                auto& tile = get_tile(i, j);
                if (!tile->walkable) continue;

                for (int k = 0; k < 4; k++) {
                    auto& dif = diag[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    
                    auto& dif_tile = get_tile(i + dif.first, j + dif.second);
                    
                    // if (!dif_tile->walkable) continue;
                    
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

                    // if (!dif_tile->walkable) continue;

                    tile->neighbours.push_back(dif_tile);
                }
            }
        }

        auto [i, j] = cfg->map_cfg.start;
        auto& tile = m_tiles[j * m_xmax + i];
        tile->discovered = true;
        for (int k = 0; k < 4; k++) {
            auto& dif = diag[k];
            if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
            auto& dif_tile = get_tile(i + dif.first, j + dif.second);
            dif_tile->discovered = true;
        }

        for (int k = 0; k < 4; k++) {
            auto& dif = direct[k];
            if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
            auto& dif_tile = get_tile(i + dif.first, j + dif.second);
            dif_tile->discovered = true;
        }

        file.close();
    }

    std::weak_ptr<map::tile_t> map::get_random_neighbour(std::weak_ptr<tile_t> t) const {
        auto t1 = t.lock();
        int idx;
        do {
            idx = util::random_int(0, t1->neighbours.size() - 1);
        } while (!t1->neighbours[idx].lock()->walkable);
        return t1->neighbours[idx];
    }

    path map::get_path(tile_type from, tile_type to, path_algo algo) const {
        auto start = find_target(from);
        path null_path{};
        if (start.expired()) {
            std::cerr << "map::get_path: no target found\n";
            return null_path;
        }

        auto finish = find_target(to);
        if (finish.expired()) {
            std::cerr << "map::get_path: no target found\n";
            return null_path;
        }

        switch (algo) {
        case path_algo_default:
            return _get_path(start.lock(), finish.lock());
        case path_algo_dijkstra:
            return _get_path_dijkstra(start.lock(), finish.lock());
        case path_algo_astar:
            return _get_path_astar(start.lock(), finish.lock());
        default: {
#ifdef DEBUG
                assert(false && "invalid map path algorithm");
#endif
                return null_path;
        }
        }
    }

    void map::discover_around(std::weak_ptr<tile_t> t) {
        std::array<std::pair<int, int>, 4> direct = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};
        std::array<std::pair<int, int>, 4> diag = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}};

        auto [i, j] = t.lock()->pos;

        for (int k = 0; k < 4; k++) {
            auto& dif = diag[k];
            if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
            auto& dif_tile = get_tile(i + dif.first, j + dif.second);
            dif_tile->discovered = true;
        }

        for (int k = 0; k < 4; k++) {
            auto& dif = direct[k];
            if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
            auto& dif_tile = get_tile(i + dif.first, j + dif.second);
            dif_tile->discovered = true;
        }
    }

} // namespace core
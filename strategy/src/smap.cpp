#include "smap.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <array>

namespace core {

    map::map(const std::filesystem::path& path) {
        //auto validated_path = std::filesystem::absolute(path);
        if (!std::filesystem::is_regular_file(path)) {
            std::cerr << "[ERROR] map file path invalid " << path << '\n';
            return;
        }
        
        std::ifstream file(path, std::ios::binary | std::ios::in);
        if (!file.is_open()) {
            std::cerr << "[ERROR] couldn't open map file " << path << '\n';
            return;
        }

        std::string line;
        int n = 0, m = 0;
        while (std::getline(file, line)) {
            n = 0;
            for (char c : line) {
                const auto tp = tile_provider<tile_type>::instance();
                if (!tp->is_valid(c)) {
#ifdef DEBUG
                    assert(false && "invalid map tile type");
#endif
                    return;
                }

                auto t = tp->create(c);
                t.posx = n;
                t.posy = m;
                switch (c) {
                    case 'T': {
                        t.type = tile_type_forest;
                        break;
                    }
                    case 'V': {
                        t.type = tile_type_water;
                        break;
                    }
                    case 'G': {
                        t.type = tile_type_swamp;
                        break;
                    }
                    case 'B': {
                        t.type = tile_type_mountain;
                        break;
                    }
                    case 'M': {
                        t.type = tile_type_grass;
                        break;
                    }
                    default: {}
                }
                m_tiles.emplace_back(std::make_shared<tile_t>(t));

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
                auto& tile = get(i, j);
                if (!tile->walkable) continue;

                for (int k = 0; k < 4; k++) {
                    auto& dif = diag[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    
                    auto& dif_tile = get(i + dif.first, j + dif.second);
                    
                    // if (!dif_tile->walkable) continue;
                    
                    auto& dif_left = direct[k];
                    if (i + dif_left.first < 0 || i + dif_left.first >= m_xmax || j + dif_left.second < 0 || j + dif_left.second >= m_ymax) continue;
                    auto& tile_left = get(i + dif_left.first, j + dif_left.second);
                    
                    auto& dif_right = direct[(k + 1) % 4];
                    if (i + dif_right.first < 0 || i + dif_right.first >= m_xmax || j + dif_right.second < 0 || j + dif_right.second >= m_ymax) continue;
                    auto& tile_right = get(i + dif_right.first, j + dif_right.second);

                    if (tile_left->walkable && tile_right->walkable) {
                        tile->neighbours.push_back(dif_tile);
                    }
                }

                for (int k = 0; k < 4; k++) {
                    auto& dif = direct[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    auto& dif_tile = get(i + dif.first, j + dif.second);

                    // if (!dif_tile->walkable) continue;

                    tile->neighbours.push_back(dif_tile);
                }
            }
        }

        file.close();
    }

    path<default_map<tile_type>::tile_t> map::get_path(tile_type from, tile_type to, path_algo algo) const {
        auto start = find_target(from);
        path<tile_t> null_path{};
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
} // namespace core
#include "pmap.h"

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
            m++;
            n = 0;
            for (char c : line) {
                n++;
                switch (c) {
                    case 'X': {
                        m_tiles.emplace_back(std::make_shared<tile_type>(tile_type_rock));
                        break;
                    }
                    case '0': {
                        m_tiles.emplace_back(std::make_shared<tile_type>(tile_type_road));
                        break;
                    }
                    case 'S': {
                        m_tiles.emplace_back(std::make_shared<tile_type>(tile_type_start));
                        break;
                    }
                    case 'F': {
                        m_tiles.emplace_back(std::make_shared<tile_type>(tile_type_finish));
                        break;
                    }
                    case '\n':
                    case '\r': break;
                    default: {
#ifdef DEBUG
                        assert(false && "invalid map tile type");
#endif
                    }
                }
            }
        }
        m_xmax = n;
        m_ymax = m;

        std::array<std::pair<int, int>, 4> direct = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};
        std::array<std::pair<int, int>, 4> diag = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}};

        for (int i = 0; i < m_xmax; i++) {
            for (int j = 0; j < m_ymax; j++) {
                auto& tile = get(i, j);
                if (tile->type == tile_type_rock) continue;
                if (tile->type == tile_type_start || tile->type == tile_type_finish) {
                    m_targets.emplace_back(tile);
                }

                for (int k = 0; k < 4; k++) {
                    auto& dif = diag[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    
                    auto& dif_tile = get(i + dif.first, j + dif.second);
                    switch (dif_tile->type) {
                    case tile_type_rock: {
                            break;
                    }
                    case tile_type_start:
                    case tile_type_finish:
                    case tile_type_road: {
                            auto& dif_left = direct[k];
                            if (i + dif_left.first < 0 || i + dif_left.first >= m_xmax || j + dif_left.second < 0 || j + dif_left.second >= m_ymax) continue;
                            auto& tile_left = get(i + dif_left.first, j + dif_left.second);
                            
                            auto& dif_right = direct[(k + 1) % 4];
                            if (i + dif_right.first < 0 || i + dif_right.first >= m_xmax || j + dif_right.second < 0 || j + dif_right.second >= m_ymax) continue;
                            auto& tile_right = get(i + dif_right.first, j + dif_right.second);

                            if (tile_left->type != tile_type_rock && tile_right->type != tile_type_rock) {
                                tile->m_neighbours.push_back(dif_tile);
                            }
                            break;
                    }
                    default: {
                            break;
                    }
                    }
                }

                for (int k = 0; k < 4; k++) {
                    auto& dif = direct[k];
                    if (i + dif.first < 0 || i + dif.first >= m_xmax || j + dif.second < 0 || j + dif.second >= m_ymax) continue;
                    auto& dif_tile = get(i + dif.first, j + dif.second);
                    switch (dif_tile->type) {
                    case tile_type_rock: {
                            break;
                    }
                    case tile_type_start:
                    case tile_type_finish:
                    case tile_type_road: {
                            tile->m_neighbours.push_back(dif_tile);
                            break;
                    }
                    default: {
                            break;
                    }
                    }
                }
            }
        }

        file.close();
    }

} // namespace core
#include "pmap.h"

#include <fstream>
#include <iostream>

namespace core {

    map::map(const std::string& path) {
        std::ifstream file(path, std::ios::binary | std::ios::in);
        if (!file.is_open()) {
            std::cerr << "[ERROR] couldn't open map file " << path << '\n';
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            m_width++;
            for (char c : line) {
                m_length = line.size();
                switch (c) {
                    case 'X': {
                        m_tiles.emplace_back(tile_type_rock);
                        break;
                    }
                    case '0': {
                        m_tiles.emplace_back(tile_type_road);
                        break;
                    }
                    case 'S': {
                        m_tiles.emplace_back(tile_type_start);
                        break;
                    }
                    case 'F': {
                        m_tiles.emplace_back(tile_type_finish);
                        break;
                    }
                    case '\n': break;
                    default: {
#ifdef DEBUG
                        assert(false && "invalid map tile type");
#endif
                    }
                }
            }
        }

        file.close();
    }

} // namespace core
#pragma once

#include <vector>
#include <memory>

#include "../nlohmann/include/nlohmann/json.hpp"

namespace core {

    template <typename T>
    struct tile {
        using value_type = std::weak_ptr<tile>;
        T type;
        int posx, posy;
        int size;
        bool walkable;
        bool discovered;
        int contents;
        float speed_mod;
        
        int time;
        int dtime;

        std::vector<value_type> neighbours;

    public:
        tile() = default;
        tile(T type, int posx, int posy) : type(type), posx(posx), posy(posy), size(0), walkable(false), discovered(false), contents(0), speed_mod(0.0f), time(0), dtime(0) {}
        tile(int size, bool walkable, int contents, float speed_mod)
            : size(size), walkable(walkable), discovered(false), contents(contents), speed_mod(speed_mod) {
                time = static_cast<int>(static_cast<float>(size) * speed_mod);
                dtime = static_cast<int>(static_cast<float>(time) * 1.4f);
        }
    };

    template <typename T>
    class tile_provider {
    private:
        inline static tile_provider* s_instance;
        std::unordered_map<char, tile<T>> m_tiles;

    public:
        tile_provider() {
            s_instance = this;
        }

        static tile_provider* instance() {
            return s_instance;
        }

        void load_from_json(const nlohmann::json& doc) {
            int size = doc["size"].get<int>();
            for (auto it = doc.at("types").begin(); it != doc.at("types").end(); ++it) {
                auto& type = it.key()[0];
                auto& data = it.value();
                m_tiles[type] = tile<T>(size, data.at("walkable").get<bool>(), data.at("contents").get<int>(), data.at("speed_mod").get<float>());
            }
        }

        bool is_valid(char c) {
            return m_tiles.find(c) != m_tiles.end();
        }

        tile<T> create(char c) {
            return m_tiles[c];
        }
    };

} // namespace core
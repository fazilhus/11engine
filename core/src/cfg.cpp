#include "cfg.h"

#include "nlohmann/json.hpp"

#include "enum.h"

namespace core {

    game_config* game_config::s_instance = nullptr;

    game_config::game_config(const nlohmann::json& doc) {
        s_instance = this;

        map_cfg.width = doc.at("map").at("width");
        map_cfg.height = doc.at("map").at("height");

        {
            int size = doc.at("tile").at("size").get<int>();
            const auto& types = doc.at("tile").at("types");
            for (auto it = types.begin(); it != types.end(); ++it) {
                auto& data = it.value();
                tile_type type = util::char_to_tile(data.at("type").get<std::string>()[0]);
                tile_cfg[type] = {size, type, data.at("walkable").get<bool>(), data.at("contents").get<int>(), data.at("speed_mod").get<float>()};
            }
        }

        {
            tile_type t = util::char_to_tile(doc.at("buildings").at("tile").get<std::string>()[0]);
            const auto& types = doc.at("buildings").at("types");
            for (auto it = types.begin(); it != types.end(); ++it) {
                building_type type = util::str_to_building(it.key());
                auto& data = it.value();
                building_cfg[type] = {t, type, data.at("builders").get<int>(), {0, data.at("resources").at("wood").get<int>(), data.at("resources").at("coal").get<int>()}, data.at("time").get<int>()};
            }
        }

        {
            const auto& types = doc.at("resources");
            for (auto it = types.begin(); it != types.end(); ++it) {
                resource_type type = util::str_to_resource(it.key());
                auto& data = it.value();
                resource_cfg[type] = {type, {0, data.at("in").at("wood").get<int>(), data.at("in").at("coal").get<int>()}, data.at("out").get<int>(), data.at("time").get<int>()};
            }
        }

        {
            int speed = doc.at("units").at("speed").get<int>();
            const auto& types = doc.at("units").at("types");
            for (auto it = types.begin(); it != types.end(); ++it) {
                unit_type type = util::str_to_unit(it.key());
                auto& data = it.value();
                unit_cfg[type] = {type, util::str_to_unit(data.at("from").get<std::string>()), speed, data.at("carry").get<int>(), data.at("upgrade_time").get<int>()};
            }
        }
    }

} // namespace core
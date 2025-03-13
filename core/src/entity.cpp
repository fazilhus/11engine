#include "entity.h"

#include <cassert>
#include <iostream>

#include "message.h"
#include "util.h"
#include "game_config.h"
#include "tile.h"
#include "map.h"
#include "vec_math.h"

namespace core {

    entity::entity(int id)
        : m_id(id) {
            const auto cfg = game_config::get();
            m_tile = map::get()->get_tile(cfg->map_cfg.start);
            m_pos = util::tile_to_pos(m_tile.lock()->pos);
            m_speed = cfg->unit_cfg[0].speed;
            m_type = unit_type_none;
    }

    entity::entity(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type)
        : m_id(id) {
        m_tile = tile;
        m_pos = pos;
        m_speed = game_config::get()->unit_cfg[type].speed;
    }

    entity::~entity() {
    }

    void entity::move(int dt, bool discover) {
        if (get_path().m_path.empty()) {
            return;
        }

        auto t = get_path().m_next.lock();
        auto& path = get_path();
        std::array<int, 2> src = pos();
        auto dest = util::tile_to_pos(t->pos);
        auto dist = dest - src;
        auto dir = math::norm(dist);
        int tile_speed = static_cast<int>(static_cast<float>(speed()) / (get_tile().lock()->speed_mod));
        update_pos(dir * tile_speed * dt);

        auto p1 = t->pos * game_config::get()->tile_cfg[0].size;
        auto p2 = p1 + game_config::get()->tile_cfg[0].size;
        auto ep = pos();

        if (ep == util::tile_to_pos(t->pos)) {
            set_tile(t);
            if (discover) map::get()->discover_around(t);
            path.m_i++;
            if (path.m_i >= path.m_path.size()) return;
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void entity::accept_invite(uint8_t msg_type)
    {
        std::cout << m_id << " accepted invite to " << msg_type << std::endl;
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, long long timestamp, int delay) {
        std::cout << m_id << " sent invite to " << msg_type << " in " << timestamp << std::endl;
        message_dispatcher::get()->send_to_everyone(msg_type, sender_id, timestamp, delay);
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, int receiver_id, long long timestamp, int delay) {
        std::cout << m_id << " sent invite to " << msg_type << " in " << timestamp << " to " << receiver_id <<  std::endl;
        message_dispatcher::get()->send_to(msg_type, sender_id, receiver_id, timestamp, delay);
    }

} // namespace core
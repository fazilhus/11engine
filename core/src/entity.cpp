#include "entity.h"

#include <cassert>
#include <iostream>

#include "message.h"
#include "util.h"
#include "game_config.h"
#include "tile.h"
#include "map.h"

namespace core {

    entity::entity(int id, const std::string& name)
        : m_id(id), m_name(name) {
            const auto cfg = game_config::get();
            m_tile = map::get()->get_tile(cfg->map_cfg.start);
            m_pos = util::tile_to_pos(m_tile.lock()->pos);
            m_speed = cfg->unit_cfg[1].speed;
    }

    entity::~entity() {
    }

    void entity::accept_invite(uint8_t msg_type) {
        std::cout << m_name << " accepted invite to " << msg_type << std::endl;
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, long long timestamp, int delay) {
        std::cout << m_name << " sent invite to " << msg_type << " in " << timestamp << std::endl;
        message_dispatcher::get()->send_to_everyone(msg_type, sender_id, timestamp, delay);
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, int receiver_id, long long timestamp, int delay) {
        std::cout << m_name << " sent invite to " << msg_type << " in " << timestamp << " to " << receiver_id <<  std::endl;
        message_dispatcher::get()->send_to(msg_type, sender_id, receiver_id, timestamp, delay);
    }

} // namespace core
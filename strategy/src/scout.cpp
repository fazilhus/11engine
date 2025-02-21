#include "scout.h"

#include "game_config.h"
#include "wander.h"
#include "smap.h"

namespace core {

    scout::scout(int id, const std::string &name)
        : entity(id, name) {
        m_state = std::make_unique<wander>();
        m_link.m_to = map::get()->get_random_neighbour(m_tile);
    }

    scout::~scout() {
    }

    void scout::update(int dt) {
        if (m_state) {
            m_state->execute(this);
            m_state->make_decision(this);
            m_state->process_messages(this);
            m_state->change_state(this);
        }
    }

    void scout::change_state() {
        m_state->exit(this);
        m_link.m_to = map::get()->get_random_neighbour(m_tile);
        m_state->enter(this);
    }

} // namespace core
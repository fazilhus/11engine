#include "scout.h"

#include "game_config.h"
#include "scout_states.h"
#include "map.h"

namespace core {

    scout::scout(int id, const std::string &name)
        : entity(id, name) {
        m_state = std::make_unique<wander>();
        m_path = map::get()->get_path_to_undiscovered(m_tile.lock());
        if (m_path.m_path.size() > 1) {
            m_path.m_i = 1;
            m_path.m_next = m_path.m_path[m_path.m_i];
        }
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
        m_path = map::get()->get_path_to_undiscovered(m_tile.lock());
        if (m_path.m_path.size() > 1) {
            m_path.m_i = 1;
            m_path.m_next = m_path.m_path[m_path.m_i];
        }
        m_state->enter(this);
    }

} // namespace core
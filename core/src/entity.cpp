#include "entity.h"

#include <cassert>

#include "state.h"
#include "fsm.h"

namespace core {

    entity::entity(int id)
        : m_id(id) {
        set_id(id);
    }

    entity::~entity() {
    }

    human::human(int id)
        : entity(id) {
            m_fsm_state = fsm_state::resting;
            m_location = loc::home;
            m_current_state = fsm::instance()->get_state(m_fsm_state);
            m_money = stat(0, 0, 1000);
            m_cycles = 0;
    }

    human::~human() {
    }

    void human::update() {
        m_cycles++;
        if (m_current_state) {
            m_current_state->execute(this);
        }
    }

    void human::change_state(fsm_state new_state) {
        if (m_fsm_state == new_state) {
            return;
        }

        m_current_state->exit(this);
        m_current_state = fsm::instance()->get_state(new_state);
        m_current_state->enter(this);
    }

} // namespace core
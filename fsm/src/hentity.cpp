#include "hentity.h"

#include "state.h"
#include "state_provider.h"

namespace core {

    human::human(int id, const std::string& name)
        : entity(id, name) {
            m_location = loc_type_home;
            m_global_state = state_provider::instance()->get_global_state();
            m_state = state_provider::instance()->get_state();
            m_curr_state = state_type_resting;
            m_next_state = state_type_none;
            m_prev_state = state_type_none;
            m_money = need(util::random_int(25, 60), 0, 50, 100, 1000);
            m_hunger = need(util::random_int(10, 35), 0, 30, 60, 100);
            m_thirst = need(util::random_int(10, 35), 0, 30, 60, 100);
            m_fatigue = need(util::random_int(10, 35), 0, 20, 60, 100);
            m_loneliness = need(util::random_int(10, 35), 0, 35, 65, 100);
            m_chance = util::random_float(0.33f, 0.66f);
            m_cycles = 0;
    }

    human::~human() {
    }

    void human::update_stage1() {
        m_cycles++;
        if (m_global_state) {
            m_global_state->execute(this);
            m_global_state->make_decision(this);
        }

        if (m_state) {
            m_state->execute(this);
            m_state->make_decision(this);
        }
    }

    void human::update_stage2() {
        if (m_global_state) {
            m_global_state->process_messages(this);
            m_global_state->change_state(this);
        }
        if (m_state) {
            m_state->process_messages(this);
            m_state->change_state(this);
        }
        m_inbox.clear_messages();
    }

    void human::change_state() {
        if (m_curr_state == m_next_state || m_next_state == state_type_none) {
            return;
        }

        m_prev_state = m_curr_state;
        m_state->exit(this);
        m_curr_state = m_next_state;
        // m_state = state_provider::instance()->get_state();
        m_state->enter(this);
        m_next_state = state_type_none;
    }

} // namespace core
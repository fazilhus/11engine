#include "state_machine.h"

#include "state.h"

#include "scout.h"
#include "scout_states.h"

#include "worker.h"
#include "worker_states.h"

namespace core {

    state_machine<istate<scout>, scout_state_type>::state_machine(scout* ptr)
        : m_ptr(ptr) {
        for (int i = 0; i < m_states.size(); ++i) {
            switch (static_cast<scout_state_type>(i)) {
            case scout_state_wander: {
                m_states[i] = std::make_shared<wander>();
                break;
            }
            }
        }
    }

    void state_machine<istate<scout>, scout_state_type>::update(int dt) {
        if (!m_state_ref.expired()) {
            auto s = m_state_ref.lock();
            s->execute(m_ptr, dt);
            s->make_decision(m_ptr);
            s->process_messages(m_ptr);

            if (m_next_state != scout_state_none) {
                s->change_state(m_ptr);
            }
        }
    }

    void state_machine<istate<scout>, scout_state_type>::change_state() {
        m_state_ref.lock()->exit(m_ptr);

        m_state_ref = m_states[static_cast<std::size_t>(m_next_state)];
        m_prev_state = m_state;
        m_state = m_next_state;
        m_next_state = scout_state_none;

        m_state_ref.lock()->enter(m_ptr);
    }


    state_machine<istate<worker>, worker_state_type>::state_machine(worker* ptr)
        : m_ptr(ptr) {
        for (int i = 0; i < m_states.size(); ++i) {
            switch (static_cast<worker_state_type>(i)) {
            case worker_state_idle: {
                m_states[i] = std::make_shared<idle>();
                break;
            }
            case worker_state_move_to_resource: {
                m_states[i] = std::make_shared<move_to_resource>();
                break;
            }
            case worker_state_move_to_base: {
                m_states[i] = std::make_shared<move_to_base>();
                break;
            }
            case worker_state_gather_resource: {
                m_states[i] = std::make_shared<gather_resource>();
                break;
            }
            }
        }
    }

    void state_machine<istate<worker>, worker_state_type>::update(int dt) {
        if (!m_state_ref.expired()) {
            auto s = m_state_ref.lock();
            s->execute(m_ptr, dt);
            s->make_decision(m_ptr);
            s->process_messages(m_ptr);

            if (m_next_state != worker_state_none) {
                s->change_state(m_ptr);
            }
        }
    }

    void state_machine<istate<worker>, worker_state_type>::change_state() {
        m_state_ref.lock()->exit(m_ptr);

        m_state_ref = m_states[static_cast<std::size_t>(m_next_state)];
        m_prev_state = m_state;
        m_state = m_next_state;
        m_next_state = worker_state_none;

        m_state_ref.lock()->enter(m_ptr);
    }

} // namespace core
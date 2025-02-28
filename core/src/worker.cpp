#include "worker.h"

#include "game_config.h"
#include "worker_states.h"
#include "map.h"

namespace core {

    worker_state_machine::worker_state_machine(worker *ptr)
        : state_machine(ptr) {
        for (int i = 0; i < m_states.size(); ++i) {
            switch (static_cast<worker_state_type>(i)) {
            case worker_state_idle: {
                m_states[i] = std::make_shared<worker_idle>();
                break;
            }
            case worker_state_move_to_resource: {
                m_states[i] = std::make_shared<worker_move_to_resource>();
                break;
            }
            case worker_state_move_to_base: {
                m_states[i] = std::make_shared<worker_move_to_base>();
                break;
            }
            case worker_state_gather_resource: {
                m_states[i] = std::make_shared<worker_gather_resource>();
                break;
            }
            }
        }
    }

    void worker_state_machine::update(int dt) {
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

    void worker_state_machine::change_state() {
        m_state_ref.lock()->exit(m_ptr);

        m_state_ref = m_states[static_cast<std::size_t>(m_next_state)];
        m_prev_state = m_state;
        m_state = m_next_state;
        m_next_state = worker_state_none;

        m_state_ref.lock()->enter(m_ptr);
    }

    worker::worker(int id, const std::string &name)
        : entity(id, name), m_sm(this) {
    }

    void worker::update(int dt) {
        m_sm.update(dt);
    }


} // namespace core
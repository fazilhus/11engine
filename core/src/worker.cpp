#include "worker.h"

#include <iostream>

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
            case worker_state_move_to_target: {
                m_states[i] = std::make_shared<worker_move_to_target>();
                break;
            }
            case worker_state_gather_resource: {
                m_states[i] = std::make_shared<worker_gather_resource>();
                break;
            }
            case worker_state_upgrade_to_scout: {
                m_states[i] = std::make_shared<worker_upgrade_to_scout>();
                break;
            }
            case worker_state_upgrade_to_builder: {
                m_states[i] = std::make_shared<worker_upgrade_to_builder>();
                break;
            }
            case worker_state_upgrade_to_miner: {
                m_states[i] = std::make_shared<worker_upgrade_to_miner>();
                break;
            }
            }
        }

        m_state_ref = m_states[0];
        m_state = worker_state_idle;
        m_prev_state = worker_state_none;
        m_next_state = worker_state_none;
    }

    void worker_state_machine::update(int dt) {
        if (!m_state_ref.expired()) {
            auto s = m_state_ref.lock();
            s->execute(m_ptr, dt);
            s->make_decision(m_ptr);
            s->process_messages(m_ptr);
            s->change_state(m_ptr);
            std::cout << "worker " << m_ptr->id() << " is " << int(m_state) << '\n';

            if (m_next_state != worker_state_none) {
                change_state();
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

    worker::worker(int id)
        : entity(id), m_sm(this), m_carry(resource_type_none) {
        m_type = unit_type_worker;
    }

    void worker::update(int dt) {
        m_sm.update(dt);
    }


} // namespace core
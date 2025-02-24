#include "worker.h"

#include "game_config.h"
#include "worker_states.h"
#include "map.h"

namespace core {

    worker::worker(int id, const std::string &name)
        : entity(id, name) {
        m_state = std::make_unique<idle>();
        m_cur_state = worker_state_idle;
    }

    worker::~worker() {
    }

    void worker::update(int dt) {
        if (m_state) {
            m_state->execute(this);
            m_state->make_decision(this);
            m_state->process_messages(this);
            m_state->change_state(this);
        }
    }

    void worker::change_state() {

        if (m_next_state == worker_state_none) return;

        m_state->exit(this);

        m_cur_state = m_next_state;
        m_next_state = worker_state_none;

        switch (m_cur_state) {
        case worker_state_idle: {
            m_state = std::make_unique<idle>();
            if (m_carry != resource_type_none) {
                m_carry = resource_type_none;
            }
            break;
        }
        case worker_state_move_to_resource: {
            m_path = map::get()->get_path_to_tile_of(m_tile.lock(), tile_type_forest);
            if (m_path.m_path.empty()) {
                break;
            }

            m_state = std::make_unique<move_to_resource>();
            break;
        }
        case worker_state_move_to_base: {
            m_state = std::make_unique<move_to_base>();
            m_path = map::get()->get_path_dijkstra(m_tile.lock(), map::get()->get_start().lock());
        }
        case worker_state_gather_resource: {
            m_state = std::make_unique<gather_resource>();
            break;
        }
        }
        
        m_state->enter(this);
    }

} // namespace core
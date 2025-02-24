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
        m_state->exit(this);

        if (m_next_state != worker_state_none) {
            m_cur_state = m_next_state;
            m_next_state = worker_state_none;
        }
        
        switch (m_cur_state) {
        case worker_state_idle: {
            m_state = std::make_unique<move>();
            m_cur_state = worker_state_move;
            m_path = map::get()->get_path_to_tile_of(m_tile.lock(), tile_type_forest);
            if (m_carry != resource_type_none) {
                m_carry = resource_type_none;
            }
            break;
        }
        case worker_state_move: {
            if (m_carry == resource_type_none) {
                m_state = std::make_unique<gather_resource>();
                m_cur_state = worker_state_gather_resource;
            }
            else {
                m_state = std::make_unique<idle>();
                m_cur_state = worker_state_idle;
            }
            break;
        }
        case worker_state_gather_resource: {
            m_state = std::make_unique<move>();
            m_cur_state = worker_state_move;
            m_path.reverse();
            break;
        }
        }
        
        m_state->enter(this);
    }

} // namespace core
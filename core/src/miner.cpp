#include "miner.h"

#include "game_config.h"
#include "miner_states.h"
#include "map.h"

namespace core {

    miner_state_machine::miner_state_machine(miner *ptr)
        : state_machine(ptr) {
        for (int i = 0; i < m_states.size(); ++i) {
            switch (static_cast<miner_state_type>(i)) {
            case miner_state_idle: {
                m_states[i] = std::make_shared<miner_idle>();
                break;
            }
            case miner_state_move: {
                m_states[i] = std::make_shared<miner_move>();
                break;
            }
            case miner_state_produce_coal: {
                m_states[i] = std::make_shared<miner_produce_coal>();
                break;
            }
            }
        }

        m_state_ref = m_states[0];
        m_state = miner_state_idle;
        m_prev_state = miner_state_none;
        m_next_state = miner_state_none;
    }

    void miner_state_machine::update(int dt) {
        if (!m_state_ref.expired()) {
            auto s = m_state_ref.lock();
            s->execute(m_ptr, dt);
            s->make_decision(m_ptr);
            s->process_messages(m_ptr);
            s->change_state(m_ptr);

            if (m_next_state != miner_state_none) {
                change_state();
            }
        }
    }

    void miner_state_machine::change_state() {
        m_state_ref.lock()->exit(m_ptr);

        m_state_ref = m_states[static_cast<std::size_t>(m_next_state)];
        m_prev_state = m_state;
        m_state = m_next_state;
        m_next_state = miner_state_none;

        m_state_ref.lock()->enter(m_ptr);
    }

    miner::miner(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type)
        : entity(id, pos, tile, type), m_sm(this) {
        m_type = unit_type_miner;
    }

    void miner::update(int dt) {
        m_sm.update(dt);
    }

} // namespace core
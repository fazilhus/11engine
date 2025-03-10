#include "builder.h"

#include "game_config.h"
#include "builder_states.h"
#include "map.h"

namespace core {

    builder_state_machine::builder_state_machine(builder *ptr)
        : state_machine(ptr) {
        for (int i = 0; i < m_states.size(); ++i) {
            switch (static_cast<builder_state_type>(i)) {
            case builder_state_idle: {
                m_states[i] = std::make_shared<builder_idle>();
                break;
            }
            case builder_state_build: {
                m_states[i] = std::make_shared<builder_build>();
                break;
            }
            }
        }

        m_state_ref = m_states[0];
        m_state = builder_state_idle;
        m_prev_state = builder_state_none;
        m_next_state = builder_state_none;
    }

    void builder_state_machine::update(int dt) {
        if (!m_state_ref.expired()) {
            auto s = m_state_ref.lock();
            s->execute(m_ptr, dt);
            s->make_decision(m_ptr);
            s->process_messages(m_ptr);
            s->change_state(m_ptr);

            if (m_next_state != builder_state_none) {
                change_state();
            }
        }
    }

    void builder_state_machine::change_state() {
        m_state_ref.lock()->exit(m_ptr);

        m_state_ref = m_states[static_cast<std::size_t>(m_next_state)];
        m_prev_state = m_state;
        m_state = m_next_state;
        m_next_state = builder_state_none;

        m_state_ref.lock()->enter(m_ptr);
    }

    builder::builder(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type)
        : entity(id, pos, tile, type), m_sm(this) {
        m_type = unit_type_builder;
    }

    void builder::update(int dt) {
        m_sm.update(dt);
    }

} // namespace core
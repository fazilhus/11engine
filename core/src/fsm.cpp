#include "fsm.h"

#include "state.h"
#include "entity.h"

namespace core {

    fsm* fsm::s_instance = nullptr;

    fsm::fsm() {
        s_instance = this;

        for (int i = 0; i < static_cast<int>(state_type::num_states); ++i) {
            switch (static_cast<state_type>(i)) {
            case state_type::resting:
                m_states[i] = std::make_shared<resting>();
                break;
            case state_type::working_at_construction:
                m_states[i] = std::make_shared<working_at_construction>();
                break;
            case state_type::working_at_office:
                m_states[i] = std::make_shared<working_at_office>();
                break;
            case state_type::eating:
                m_states[i] = std::make_shared<eating>();
                break;
            case state_type::drinking:
                m_states[i] = std::make_shared<drinking>();
                break;
            case state_type::partying:
                m_states[i] = std::make_shared<partying>();
                break;
            case state_type::shopping:
                m_states[i] = std::make_shared<shopping>();
                break;
            }
        }
    }

    const std::shared_ptr<state<human>>& fsm::get_state(state_type state) {
        return m_states[static_cast<int>(state)];
    }

} // namespace core
#include "fsm.h"

#include "state.h"

namespace core {

    fsm* fsm::s_instance = nullptr;

    fsm::fsm() {
        s_instance = this;

        for (int i = 0; i < static_cast<int>(fsm_state::num_states); ++i) {
            switch (static_cast<fsm_state>(i)) {
            case fsm_state::resting:
                m_states[i] = std::make_shared<resting>();
                break;
            case fsm_state::working:
                m_states[i] = std::make_shared<working>();
                break;
            }
        }
    }

    const std::shared_ptr<state>& fsm::get_state(fsm_state state) {
        return m_states[static_cast<int>(state)];
    }

} // namespace core
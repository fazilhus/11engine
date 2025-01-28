#include "state_provider.h"

#include "state.h"
#include "entity.h"

namespace core {

    state_provider* state_provider::s_instance = nullptr;

    state_provider::state_provider() {
        s_instance = this;

        m_state = std::make_shared<state>();
    }

    const std::shared_ptr<istate<human>>& state_provider::get_state() {
        return m_state;
    }

} // namespace core
#include "state_provider.h"

#include "state.h"
#include "entity.h"

namespace core {

    state_provider* state_provider::s_instance = nullptr;

    state_provider::state_provider() {
        s_instance = this;

        m_global_state = std::make_shared<global_state>();
        m_state = std::make_shared<state>();
    }

} // namespace core
#pragma once

#include <array>
#include <memory>

#include "util.h"

namespace core {

    class state;

    class fsm {
    private:
        static fsm* s_instance;

        std::array<std::shared_ptr<state>, static_cast<int>(fsm_state::num_states)> m_states;

    public:
        fsm();
        ~fsm() = default;

        static fsm* instance() { return s_instance; }

        const std::shared_ptr<state>& get_state(fsm_state state);
    };

} // namespace core
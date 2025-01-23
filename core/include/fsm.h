#pragma once

#include <array>
#include <memory>

#include "util.h"

namespace core {

    template <typename entity_type>
    class state;

    class human;

    /// @brief Class representing a finite state machine (FSM).
    class fsm {
    private:
        static fsm* s_instance; ///< Singleton instance

        std::array<std::shared_ptr<state<human>>, static_cast<int>(state_type::num_states)> m_states; ///< Instances of all posible states

    public:
        /// @brief Constructor for the FSM class.
        fsm();
        ~fsm() = default;

        /// @brief Get the singleton instance of the FSM.
        /// @return Pointer to the singleton instance of the FSM.
        static fsm* instance() { return s_instance; }

        /// @brief 'getter' for state instances
        /// @param state controls instance of which state is going to be accessed
        /// @return shared_ptr to the state instance
        const std::shared_ptr<state<human>>& get_state(state_type state);
    };

} // namespace core
#pragma once

#include <array>
#include <memory>

#include "util.h"

namespace core {

    template <typename entity_type>
    class istate;

    class human;

    /// @brief Class providing state class instances (state_provider).
    class state_provider {
    private:
        static state_provider* s_instance; ///< Singleton instance

        std::shared_ptr<istate<human>> m_global_state;
        std::shared_ptr<istate<human>> m_state; ///< Instances of all posible states

    public:
        /// @brief Constructor for the state_provider class.
        state_provider();
        ~state_provider() = default;

        /// @brief Get the singleton instance of the state_provider.
        /// @return Pointer to the singleton instance of the state_provider.
        static state_provider* instance() { return s_instance; }

        /// @brief 'getter' for global_state instances
        /// @param state controls instance of which state is going to be accessed
        /// @return shared_ptr to the global_state instance
        const std::shared_ptr<istate<human>>& get_global_state() const {
            return m_global_state;
        }

        template <typename state_type>
        void set_global_state() {
            m_global_state = std::make_shared<state_type>();
        }

        /// @brief 'getter' for state instances
        /// @param state controls instance of which state is going to be accessed
        /// @return shared_ptr to the state instance
        const std::shared_ptr<istate<human>>& get_state() const {
            return m_state;
        }

        template <typename state_type>
        void set_state() {
            m_state = std::make_shared<state_type>();
        }
    };

} // namespace core
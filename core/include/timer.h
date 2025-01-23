#pragma once

#include <vector>

namespace core {

    /// @brief Class representing a timer.
    class timer {
    private:
        int m_cycles; ///< Current cycle count.
        int m_max_cycles; ///< Maximum cycle count.

        int m_listener_id; ///< Entity ID of the listener associated with the timer.

        bool m_done; ///< Flag indicating if the timer is done.

    public:
        /// @brief Constructor for the timer class.
        /// @param max_cycles Maximum cycle count.
        /// @param listener_id ID of the listener associated with the timer.
        timer(int max_cycles, int listener_id);

        /// @brief Default destructor for the timer class.
        ~timer() = default;

        /// @brief Update the timer.
        void update();

        /// @brief Check if the timer is done.
        /// @return True if the timer is done, false otherwise.
        bool is_done() const { return m_done; }

        /// @brief Get the Entity ID of the listener associated with the timer.
        /// @return ID of the listener.
        int listener_id() const { return m_listener_id; }
    };

    /// @brief Manager class for handling all timers.
    class timer_manager {
    private:
        static timer_manager* s_instance; ///< Singleton instance of the timer manager.

        std::vector<timer> m_timers; ///< List of all currently running timers.

    public:
        /// @brief Constructor for the timer manager class.
        timer_manager();

        /// @brief Default destructor for the timer manager class.
        ~timer_manager() = default;

        /// @brief Get the singleton instance of the timer manager.
        /// @return Singleton instance of the timer manager.
        static timer_manager* instance() { return s_instance; }

        /// @brief Update all timers managed by the timer manager.
        void update();

        /// @brief Add a new timer to the manager.
        /// @param max_cycles Maximum cycle count for the timer.
        /// @param listener_id ID of the listener associated with the timer.
        void add_timer(int max_cycles, int listener_id);
    };

} // namespace core
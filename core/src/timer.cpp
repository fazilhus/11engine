#include "timer.h"

#include <iostream>

namespace core {

    timer::timer(int max_cycles, int listener_id)
        : m_cycles(0), m_max_cycles(max_cycles), m_listener_id(listener_id), m_done(false) {
    }

    void timer::update() {
        m_cycles++;
        if (m_cycles >= m_max_cycles) {
            m_done = true;
        }
    }

    timer_manager* timer_manager::s_instance = nullptr;

    timer_manager::timer_manager() {
        s_instance = this;
    }

    void timer_manager::update() {
        for (auto& t : m_timers) {
            t.update();

            if (t.is_done()) {
                // Notify listener
                std::cout << "Timer " << t.listener_id() << " done" << std::endl;
            }
        }
    }

    void timer_manager::add_timer(int max_cycles, int listener_id) {
        m_timers.emplace_back(max_cycles, listener_id);
    }

} // namespace core
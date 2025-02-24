#include "timer.h"

#include <iostream>

namespace core {

    timer::timer(int max_cycles, int listener_id, std::function<void()> callback)
        : m_cycles(0), m_max_cycles(max_cycles), m_listener_id(listener_id), m_callback(callback), m_done(false) {
    }

    void timer::update(int dt) {
        m_cycles += dt;
        if (m_cycles >= m_max_cycles) {
            m_done = true;
        }
    }

    timer_manager* timer_manager::s_instance = nullptr;

    timer_manager::timer_manager() {
        s_instance = this;
    }

    void timer_manager::update(int dt) {
        for (int i = 0; i < m_timers.size(); ++i) {
            auto& t = m_timers[i];
            t.update(dt);

            if (t.is_done()) {
                // Notify listener
                if (t.callback()) {
                    t.callback()();
                }
                // std::cout << "Timer " << t.listener_id() << " done" << std::endl;
                m_queue_free.push(i);
            }
        }

        while (!m_queue_free.empty()) {
            m_timers.erase(m_queue_free.front());
            m_queue_free.pop();
        }
    }

    void timer_manager::add_timer(int max_cycles, int listener_id, std::function<void()> callback) {
        m_timers[m_timers.size()] = timer(max_cycles, listener_id, callback);
    }

} // namespace core
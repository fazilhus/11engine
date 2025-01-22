#pragma once

#include <vector>

namespace core {

    class timer {
    private:
        int m_cycles;
        int m_max_cycles;

        int m_listener_id;

        bool m_done;

    public:
        timer(int max_cycles, int listener_id);
        ~timer() = default;

        void update();

        bool is_done() const { return m_done; }

        int listener_id() const { return m_listener_id; }
    };

    class timer_manager {
    private:
        static timer_manager* s_instance;

        std::vector<timer> m_timers;

    public:
        timer_manager();
        ~timer_manager() = default;

        static timer_manager* instance() { return s_instance; }

        void update();

        void add_timer(int max_cycles, int listener_id);
    };

} // namespace core
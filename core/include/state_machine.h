#pragma once

#include <array>
#include <memory>

#include "enum.h"

namespace core {

    template<class state_type>
    struct state_machine_traits;

    template<>
    struct state_machine_traits<scout_state_type> {
        enum { size = scout_state_num };
    };

    template<>
    struct state_machine_traits<worker_state_type> {
        enum { size = worker_state_num };
    };

    template <typename entity_type, typename state_type>
    class state_machine {};

    template <typename entity_type>
    class istate;

    class scout;

    template<>
    class state_machine<istate<scout>, scout_state_type> {
    private:
        std::array<std::shared_ptr<istate<scout>>, state_machine_traits<scout_state_type>::size> m_states;

        std::weak_ptr<istate<scout>> m_state_ref;
        scout_state_type m_state;
        scout_state_type m_prev_state;
        scout_state_type m_next_state;

        scout* m_ptr;

    public:
        state_machine(scout* ptr);

        void update(int dt = 1);

        scout_state_type state() const { return m_state; }
        void set_state(scout_state_type state) { m_state = state; }
        scout_state_type prev_state() const { return m_prev_state; }
        void set_prev_state(scout_state_type state) { m_prev_state = state; }
        scout_state_type next_state() const { return m_next_state; }
        void set_next_state(scout_state_type state) { m_next_state = state; }

    private:
        void change_state();
    };

    class worker;

    template<>
    class state_machine<istate<worker>, worker_state_type> {
    private:
        std::array<std::shared_ptr<istate<worker>>, state_machine_traits<worker_state_type>::size> m_states;

    public:
        state_machine();
    };

} // namespace core
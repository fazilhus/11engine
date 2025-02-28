#pragma once

#include <array>
#include <memory>

#include "enum.h"

namespace core {

    template<class state_type>
    struct state_machine_traits {
        enum { size = 0 };
    };

    // template<>
    // struct state_machine_traits<scout_state_type> {
    //     enum { size = scout_state_num };
    // };

    // template<>
    // struct state_machine_traits<worker_state_type> {
    //     enum { size = worker_state_num };
    // };

    template <typename entity_type>
    class istate;

    template <typename entity_type, typename state_enum_type>
    class state_machine {
    protected:
        std::array<std::shared_ptr<istate<entity_type>>, state_machine_traits<state_enum_type>::size> m_states;

        std::weak_ptr<istate<entity_type>> m_state_ref;
        state_enum_type m_state;
        state_enum_type m_prev_state;
        state_enum_type m_next_state;

        entity_type* m_ptr;

        state_machine(entity_type* ptr) : m_ptr(ptr) {}

    public:
        virtual ~state_machine() = default;

        virtual void update(int dt = 1) = 0;

        state_enum_type state() const { return m_state; }
        void set_state(state_enum_type state) { m_state = state; }
        state_enum_type prev_state() const { return m_prev_state; }
        void set_prev_state(state_enum_type state) { m_prev_state = state; }
        state_enum_type next_state() const { return m_next_state; }
        void set_next_state(state_enum_type state) { m_next_state = state; }

    protected:
        virtual void change_state() = 0;
    };

} // namespace core
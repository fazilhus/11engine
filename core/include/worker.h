#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"
#include "map.h"

namespace core {

    class worker;

    template<>
    struct state_machine_traits<worker_state_type> {
        enum { size = worker_state_num };
    };

    class worker_state_machine : public state_machine<worker, worker_state_type> {
    public:
        worker_state_machine(worker* ptr);
        ~worker_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class worker : public entity {
    private:
        worker_state_machine m_sm;

        resource_type m_carry;

    public:
        worker(int id);
        ~worker() override = default;

        void update(int dt = 1) override;

        worker_state_machine& sm() { return m_sm; }
        resource_type carry() const { return m_carry; }
        void set_carry(resource_type t) { m_carry = t; }
    };

} // namespace core
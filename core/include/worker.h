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
    public:
        using state_type = std::unique_ptr<istate<worker>>;

    private:
        worker_state_machine m_sm;

    public:
        worker(int id, const std::string& name);
        ~worker() override = default;

        void update(int dt = 1) override;

        worker_state_machine& sm() { return m_sm; }
    };

} // namespace core
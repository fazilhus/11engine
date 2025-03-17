#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"

namespace core {

    class builder;

    template<>
    struct state_machine_traits<builder_state_type> {
        enum { size = builder_state_num };
    };

    class builder_state_machine : public state_machine<builder, builder_state_type> {
    public:
        builder_state_machine(builder* ptr);
        ~builder_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class builder : public entity {
    private:
        builder_state_machine m_sm;
        job m_job;

    public:
        builder(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type);
        ~builder() override = default;

        void update(int dt = 1) override;

        builder_state_machine& sm() { return m_sm; }

        const job& get_job() const { return m_job; }
        void set_job(job j) { m_job = j; }
        void reset_job() {
            m_job.type = job_type_none;
            m_job.prio = 10;
        }
    };

} // namespace core
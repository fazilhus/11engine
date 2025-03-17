#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"

namespace core {

    class miner;

    template<>
    struct state_machine_traits<miner_state_type> {
        enum { size = miner_state_num };
    };

    class miner_state_machine : public state_machine<miner, miner_state_type> {
    public:
        miner_state_machine(miner* ptr);
        ~miner_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class miner : public entity {
    private:
        miner_state_machine m_sm;
        job m_job;

    public:
        miner(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type);
        ~miner() override = default;

        void update(int dt = 1) override;

        miner_state_machine& sm() { return m_sm; }

        const job& get_job() const { return m_job; }
        void set_job(job j) { m_job = j; }
        void reset_job() {
            m_job.type = job_type_none;
            m_job.prio = 10;
        }
    };

} // namespace core
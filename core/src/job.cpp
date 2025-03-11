#include "job.h"

#include "tile.h"

#include <cassert>

namespace core {
    
    job_manager* job_manager::s_instance = nullptr;

    job_manager::job_manager() {
        s_instance = this;
    }

    bool job_manager::has_job(unit_type type) const {
        switch (type) {
        case unit_type_worker:
            return !m_worker_jobs.empty();
        case unit_type_builder:
            return !m_builder_jobs.empty();
        case unit_type_miner:
            return !m_miner_jobs.empty();
        default:
            assert(false && "unreachable");
            return false;
        }
    }

    job job_manager::dispatch_job(unit_type type) {
        switch (type) {
        case unit_type_worker: {
            auto j = m_worker_jobs.top();
            m_worker_jobs.pop();
            return j;
        }
        case unit_type_builder: {
            auto j = m_builder_jobs.top();
            m_builder_jobs.pop();
            return j;
        }
        case unit_type_miner: {
            auto j = m_miner_jobs.top();
            m_miner_jobs.pop();
            return j;
        }
        default:
            assert(false && "unreachable");
            return {};
        }
    }

    void job_manager::add_job(job j, int num) {
        switch (j.type) {
        case job_type_collect_wood:
        case job_type_create_scout:
        case job_type_create_builder:
        case job_type_create_miner: {
            for (int i = 0; i < num; ++i) m_worker_jobs.push(j);
            break;
        }
        case job_type_build_coal_mine: {
            for (int i = 0; i < num; ++i) m_builder_jobs.push(j);
            break;
        }
        case job_type_produce_coal: {
            for (int i = 0; i < num; ++i) m_miner_jobs.push(j);
            break;
        }
        default:
            assert(false && "unreachable");
        }
    }

} // namespace core
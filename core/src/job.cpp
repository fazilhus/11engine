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

    worker_job job_manager::dispatch_worker_job() {
        auto j = m_worker_jobs.top();
        m_worker_jobs.pop();
        return j;
    }

    job job_manager::dispatch_builder_job() {
        auto j = m_builder_jobs.top();
        m_builder_jobs.pop();
        return j;
    }

    job job_manager::dispatch_miner_job() {
        auto j = m_miner_jobs.top();
        m_miner_jobs.pop();
        return j;
    }

    void job_manager::add_worker_job(worker_job j, int num) {
        for (int i = 0; i < num; ++i) m_worker_jobs.push(j);
    }

    void job_manager::add_builder_job(job j, int num) {
        for (int i = 0; i < num; ++i) m_builder_jobs.push(j);
    }

    void job_manager::add_miner_job(job j, int num) {
        for (int i = 0; i < num; ++i) m_miner_jobs.push(j);
    }

} // namespace core
#include "job.h"

namespace core {
    
    job_manager* job_manager::s_instance = nullptr;

    job_manager::job_manager() {
        s_instance = this;
    }

    job_type job_manager::get_job() {
        if (has_jobs()) {
            auto job = m_jobs.front();
            m_jobs.pop();
            return job;
        }

        return job_type_none;
    }

    void job_manager::add_job(job_type type, int num) {
        for (int i = 0; i < num; ++i) {
            m_jobs.push(type);
        }
    }

} // namespace core
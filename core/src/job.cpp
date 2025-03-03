#include "job.h"

namespace core {
    
    job_manager* job_manager::s_instance = nullptr;

    job_manager::job_manager() {
        s_instance = this;
        for (int i = 0; i < job_type_num; ++i) {
            m_jobs[static_cast<job_type>(i)] = 0;
            m_active_jobs[static_cast<job_type>(i)] = 0;
        }
    }

    bool job_manager::has_job(job_type type) const {
        return m_jobs.at(type) > 0;
    }

    void job_manager::dispatch_job(job_type type)
    {
        if (has_job(type)) {
            m_jobs[type]--;
            m_active_jobs[type]++;
        }
    }

    void job_manager::add_job(job_type type, int num) {
        if (m_jobs.contains(type)) {
            m_jobs[type] += num;
        }
    }

    void job_manager::finish_job(job_type type, bool success) {
        if (m_active_jobs[type] > 0) {
            if (!success) {
                m_jobs[type]++;
            }
            m_active_jobs[type]--;
        }
    }

} // namespace core
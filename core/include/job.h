#pragma once

#include <queue>

#include "enum.h"

namespace core {

    class job_manager {
    private:
        static job_manager* s_instance;

        std::queue<job_type> m_jobs;

    public:
        job_manager();
        ~job_manager() = default;

        static job_manager* get() { return s_instance; }

        bool has_jobs() const { return !m_jobs.empty(); }
        job_type get_job();
        void add_job(job_type type, int num = 1);
    };

} // namespace core
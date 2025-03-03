#pragma once

#include <array>

#include "enum.h"

namespace core {

    class job_manager {
    private:
        static job_manager* s_instance;

        std::array<int, job_type_num> m_jobs;
        std::array<int, job_type_num> m_active_jobs;

    public:
        job_manager();
        ~job_manager() = default;

        static job_manager* get() { return s_instance; }

        bool has_job(job_type type) const;
        void dispatch_job(job_type type);
        void add_job(job_type type, int num = 1);
        void finish_job(job_type type, bool success = true);
    };

} // namespace core
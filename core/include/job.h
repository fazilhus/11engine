#pragma once

#include <memory>

#include "enum.h"
#include "pqueue.h"

namespace core {

    struct tile;

    struct job {
        job_type type;
        std::weak_ptr<tile> target;
    };

    struct job_comp {
        bool operator()(const job& a, const job& b) const {
            return a.type < b.type;
        }
    };

    class job_manager {
    private:
        static job_manager* s_instance;

        container::pqueue<job, job_comp> m_worker_jobs;
        container::pqueue<job, job_comp> m_builder_jobs;
        container::pqueue<job, job_comp> m_miner_jobs;

    public:
        job_manager();
        ~job_manager() = default;

        static job_manager* get() { return s_instance; }

        bool has_job(unit_type type) const;
        job dispatch_job(unit_type type);
        void add_job(job j, int num = 1);
    };

} // namespace core
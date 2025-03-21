#pragma once

#include <memory>

#include "enum.h"
#include "pqueue.h"

namespace core {

    struct tile;

    struct job {
        job_type type;
        int prio;

        job(job_type t, int p) : type(t), prio(p) {}
        job() : job(job_type_none, -1) {}
        job(const job& other) = default;
    };

    struct worker_job : public job {
        std::weak_ptr<tile> target;
        resource_type res_type;

        worker_job(job_type t, int p, std::weak_ptr<tile> tg, resource_type rt) : job(t, p) {
            target = tg;
            res_type = rt;
        }
        worker_job() : job() {
            target = {};
            res_type = resource_type_none;
        }
        worker_job(const worker_job& other) = default;
    };

    struct job_comp {
        bool operator()(const job& a, const job& b) const {
            if (a.type == b.type) return a.prio < b.prio;
            return a.type < b.type;
        }
    };

    class job_manager {
    private:
        static job_manager* s_instance;

        container::pqueue<worker_job, job_comp> m_worker_jobs;
        container::pqueue<job, job_comp> m_builder_jobs;
        container::pqueue<job, job_comp> m_miner_jobs;

    public:
        job_manager();
        ~job_manager() = default;

        static job_manager* get() { return s_instance; }

        bool has_job(unit_type type) const;
        worker_job dispatch_worker_job();
        job dispatch_builder_job();
        job dispatch_miner_job();
        void add_worker_job(worker_job j, int num = 1);
        void add_builder_job(job j, int num = 1);
        void add_miner_job(job j, int num = 1);
    };

} // namespace core
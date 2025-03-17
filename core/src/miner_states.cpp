#include "miner_states.h"

#include "miner.h"
#include "tile.h"
#include "timer.h"
#include "map.h"
#include "vec_math.h"

namespace core {

    void miner_idle::enter(miner *e) {
    }

    void miner_idle::execute(miner *e, int dt) {
        if (job_manager::get()->has_job(unit_type_miner) && map::get()->get_targets()[target_type_coal_mine] > 0) {
            e->set_job(job_manager::get()->dispatch_miner_job());
        }
    }

    void miner_idle::make_decision(miner *e) {
    }

    void miner_idle::process_messages(miner *e) {
    }

    void miner_idle::change_state(miner *e) {
        const auto& j = e->get_job();
        switch (j.type) {
        case job_type_produce_coal: {
            auto t = e->get_tile().lock();
            if (t->building == building_type_coal_mine && t->building_used_by == e->id()) {
                e->sm().set_next_state(miner_state_produce_coal);
            }
            else {
                e->sm().set_next_state(miner_state_move);
            }
        }
        }
    }

    void miner_idle::exit(miner *e) {
    }


    void miner_move::enter(miner *e) {
        e->set_path(map::get()->get_path_to_unused_mine(e->get_tile().lock()));
    }

    void miner_move::execute(miner *e, int dt) {
        e->move(dt);
    }

    void miner_move::make_decision(miner *e) {
    }

    void miner_move::process_messages(miner *e) {
    }

    void miner_move::change_state(miner *e) {
        auto& path = e->get_path();

        if (path.m_path.empty()) {
            e->sm().set_next_state(miner_state_idle);
            job_manager::get()->add_miner_job({job_type_produce_coal, 5});
            return;
        }
           
        if (path.m_i >= path.m_path.size()) {
            if (e->get_tile().lock()->building_used_by == -1)
                e->sm().set_next_state(miner_state_produce_coal);
            else {
                e->sm().set_next_state(miner_state_move);
            }
        }
    }

    void miner_move::exit(miner *e) {
        e->get_tile().lock()->building_used_by = e->id();
    }
    

    void miner_produce_coal::enter(miner *e) {
        std::array<int, resource_type_num> missing{};
        if (!e->get_tile().lock()->has_resources_for<resource_type>(resource_type_coal, missing)) {
            job_manager::get()->add_worker_job({job_type_collect_wood, 2, e->get_tile(), resource_type_wood}, missing[resource_type_wood]);
        }

        m_started = false;
        m_finished = false;
    }

    void miner_produce_coal::execute(miner *e, int dt) {
        std::array<int, resource_type_num> missing{};
        auto t = e->get_tile().lock();
        if (!m_started && t->has_resources_for<resource_type>(resource_type_coal, missing)) {
            m_started = true;
            timer_manager::get()->add_timer(
                game_config::get()->resource_cfg[resource_type_coal].time,
                e->id(),
                std::bind(&miner_produce_coal::finished, this)
            );
            const auto& req = game_config::get()->resource_cfg[resource_type_coal].in;
            for (int i = 0; i < req.size(); ++i) t->take_resource(static_cast<resource_type>(i), req[i]);
        }
    }

    void miner_produce_coal::make_decision(miner *e) {
    }

    void miner_produce_coal::process_messages(miner *e) {
    }

    void miner_produce_coal::change_state(miner *e) {
        if (m_finished) {
            e->sm().set_next_state(miner_state_idle);
        }
    }

    void miner_produce_coal::exit(miner *e) {
        auto t = e->get_tile().lock();
        t->put_resource(resource_type_coal);
        e->reset_job();
    }

} // namespace core
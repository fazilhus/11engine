#include "builder_states.h"

#include <array>

#include "builder.h"
#include "tile.h"
#include "timer.h"
#include "map.h"
#include "vec_math.h"

namespace core {

    void builder_idle::enter(builder *e) {
    }

    void builder_idle::execute(builder *e, int dt) {
        if (job_manager::get()->has_job(unit_type_builder)) {
            e->set_job(job_manager::get()->dispatch_builder_job());
        }
    }

    void builder_idle::make_decision(builder *e) {
    }

    void builder_idle::process_messages(builder *e) {
    }

    void builder_idle::change_state(builder *e) {
        const auto& j = e->get_job();
        switch (j.type) {
        case job_type_build_coal_mine: {
            e->sm().set_next_state(builder_state_move);
        }
        }
    }

    void builder_idle::exit(builder *e) {
    }


    void builder_move::enter(builder *e) {
        e->set_path(map::get()->get_path_to_empty_tile(e->get_tile().lock()));
    }

    void builder_move::execute(builder *e, int dt) {
        e->move(dt);
    }

    void builder_move::make_decision(builder *e) {
    }

    void builder_move::process_messages(builder *e) {
    }

    void builder_move::change_state(builder *e) {
        auto& path = e->get_path();
           
        if (path.m_i >= path.m_path.size()) {
            auto t = e->get_tile().lock();
            if (t->building == building_type_none && t->building_used_by == -1)
                e->sm().set_next_state(builder_state_build);
            else
                e->sm().set_next_state(builder_state_move);
        }
    }

    void builder_move::exit(builder *e) {
    }


    void builder_build::enter(builder *e) {
        std::array<int, resource_type_num> missing{};
        if (!e->get_tile().lock()->has_resources_for<building_type>(building_type_coal_mine, missing)) {
            job_manager::get()->add_worker_job({job_type_collect_resource, 5, e->get_tile(), resource_type_wood}, missing[resource_type_wood]);
        }

        auto t = e->get_tile().lock();
        if (t->building == building_type_construction && t->building_used_by != e->id()) {
            return;
        }
        t->building = building_type_construction;
        t->building_used_by = e->id();


        m_started = false;
        m_finished = false;
    }

    void builder_build::execute(builder *e, int dt) {
        std::array<int, resource_type_num> missing{};
        if (!m_started && e->get_tile().lock()->has_resources_for<building_type>(building_type_coal_mine, missing)) {
            m_started = true;
            timer_manager::get()->add_timer(
                game_config::get()->building_cfg[building_type_coal_mine].time,
                e->id(),
                std::bind(&builder_build::finished, this));
        }
    }

    void builder_build::make_decision(builder *e) {
    }

    void builder_build::process_messages(builder *e) {
    }

    void builder_build::change_state(builder *e) {
        auto t = e->get_tile().lock();
        if (t->building == building_type_construction && t->building_used_by != e->id()) {
            e->sm().set_next_state(builder_state_move);
            return;
        }

        if (m_finished) {
            e->sm().set_next_state(builder_state_idle);
        }
    }

    void builder_build::exit(builder *e) {
        auto t = e->get_tile().lock();
        t->building = building_type_coal_mine;
        e->get_tile().lock()->building_used_by = -1;
        const auto& req = game_config::get()->building_cfg[building_type_coal_mine].resources;
        for (int i = 0; i < req.size(); ++i) t->take_resource(static_cast<resource_type>(i), req[i]);
        map::get()->get_targets()[target_type_coal_mine]++;
        e->reset_job();
    }

} // namespace core
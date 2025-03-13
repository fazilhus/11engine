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
            e->set_job(job_manager::get()->dispatch_job(unit_type_builder));
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
            e->sm().set_next_state(builder_state_build);
        }
    }

    void builder_move::exit(builder *e) {
    }


    void builder_build::enter(builder *e) {
        std::array<int, resource_type_num> missing{};
        if (!e->get_tile().lock()->has_resources_for<building_type>(building_type_coal_mine, missing)) {
            job_manager::get()->add_job({job_type_collect_wood, e->get_tile()}, missing[resource_type_wood]);
            return;
        }

        m_finished = false;
        timer_manager::get()->add_timer(
            game_config::get()->building_cfg[building_type_coal_mine].time,
            e->id(),
            std::bind(&builder_build::finished, this));
    }

    void builder_build::execute(builder *e, int dt) {
    }

    void builder_build::make_decision(builder *e) {
    }

    void builder_build::process_messages(builder *e) {
    }

    void builder_build::change_state(builder *e) {
        if (m_finished) {
            e->sm().set_next_state(builder_state_idle);
        }
    }

    void builder_build::exit(builder *e) {
        e->get_tile().lock()->building = building_type_coal_mine;
        e->reset_job();
    }

} // namespace core
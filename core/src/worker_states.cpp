#include "worker_states.h"

#include "worker.h"
#include "scout.h"
#include "timer.h"
#include "vec_math.h"
#include "game_config.h"
#include "entity_manager.h"
#include "job.h"

namespace core {

    void worker_idle::enter(worker *e) {
    }

    void worker_idle::execute(worker *e, int dt) {
        if (job_manager::get()->has_job(job_type_create_scout)) {
            job_manager::get()->dispatch_job(job_type_create_scout);
            e->sm().set_next_state(worker_state_upgrade_to_scout);
        }
        else if (job_manager::get()->has_job(job_type_collect_wood)) {
            job_manager::get()->dispatch_job(job_type_collect_wood);
            e->sm().set_next_state(worker_state_move_to_resource);
        }
    }

    void worker_idle::make_decision(worker *e) {
    }

    void worker_idle::process_messages(worker *e) {
    }

    void worker_idle::change_state(worker *e) {
    }

    void worker_idle::exit(worker *e) {
    }


    void worker_move_to_resource::enter(worker *e) {
        e->set_path(map::get()->get_path_to_tile_of(e->get_tile().lock(), tile_type_forest));
    }

    void worker_move_to_resource::execute(worker *e, int dt) {
        if (e->get_path().m_path.empty()) {
            return;
        }

        auto l = e->get_path().m_next.lock();
        auto& path = e->get_path();
        std::array<int, 2> src = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        auto dist = dest - src;
        auto dir = math::norm(dist);
        int tile_speed = static_cast<int>(static_cast<float>(e->speed()) / (e->get_tile().lock()->speed_mod));
        e->update_pos(dir * tile_speed * dt);

        auto p1 = l->pos * game_config::get()->tile_cfg[0].size;
        auto p2 = p1 + game_config::get()->tile_cfg[0].size;
        auto ep = e->pos();

        if (ep == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            if (path.m_i >= path.m_path.size()) return;
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void worker_move_to_resource::make_decision(worker *e) {
    }

    void worker_move_to_resource::process_messages(worker *e) {
    }

    void worker_move_to_resource::change_state(worker *e) {
        if (e->get_path().m_path.empty()) {
            e->sm().set_next_state(worker_state_idle);
            job_manager::get()->finish_job(job_type_collect_wood, false);
            return;
        }

        auto& path = e->get_path();
        auto l = path.m_next.lock();
           
        if (path.m_i >= path.m_path.size()) {
            e->sm().set_next_state(worker_state_gather_resource);
        }
    }

    void worker_move_to_resource::exit(worker *e) {
    }


    void worker_move_to_base::enter(worker *e) {
        if (!e->get_path().m_path.empty() && e->get_path().m_path.front().lock() == map::get()->get_start().lock()) {
            e->get_path().reverse();
        }
        else {
            e->set_path(map::get()->get_path_astar(
                e->get_tile().lock(),
                map::get()->get_start().lock()
            ));
        }
    }

    void worker_move_to_base::execute(worker *e, int dt) {
        auto l = e->get_path().m_next.lock();
        auto& path = e->get_path();
        std::array<int, 2> src = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        auto dist = dest - src;
        auto dir = math::norm(dist);
        int tile_speed = static_cast<int>(static_cast<float>(e->speed()) / (e->get_tile().lock()->speed_mod));
        e->update_pos(dir * tile_speed * dt);

        auto p1 = l->pos * game_config::get()->tile_cfg[0].size;
        auto p2 = p1 + game_config::get()->tile_cfg[0].size;
        auto ep = e->pos();

        if (ep == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            if (path.m_i >= path.m_path.size()) return;
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void worker_move_to_base::make_decision(worker *e) {
    }

    void worker_move_to_base::process_messages(worker *e) {
    }

    void worker_move_to_base::change_state(worker *e) {
        auto& path = e->get_path();
        auto l = path.m_next.lock();
           
        if (path.m_i >= path.m_path.size()) {
            e->sm().set_next_state(worker_state_idle);
            e->set_carry(resource_type_none);
            job_manager::get()->finish_job(job_type_collect_wood, true);
        }
    }

    void worker_move_to_base::exit(worker *e) {
    }


    void worker_gather_resource::enter(worker *e) {
        auto t = e->get_tile().lock();
        if (t->to_be_gathered < t->contents) {
            t->to_be_gathered += 1;
            m_finished = false;
            timer_manager::get()->add_timer(
                game_config::get()->resource_cfg[resource_type_wood].time,
                e->id(),
                std::bind(&worker_gather_resource::finished, this));
        }
        else {
            e->sm().set_next_state(worker_state_move_to_resource);
        }
    }

    void worker_gather_resource::execute(worker *e, int dt) {
        if (m_finished) {
            auto t = e->get_tile().lock();
            t->contents -= 1;
            t->to_be_gathered -= 1;
            e->set_carry(resource_type_wood);
            if (t->contents == 0) {
                t->type = tile_type_grass;
                auto [x, _] = map::get()->get_dim();
                map::get()->get_targets().erase(t->posy * x + t->posx);
            }
        }
    }

    void worker_gather_resource::make_decision(worker *e) {
    }

    void worker_gather_resource::process_messages(worker *e) {
    }

    void worker_gather_resource::change_state(worker *e) {
        if (m_finished) {
            e->sm().set_next_state(worker_state_move_to_base);
        }
    }

    void worker_gather_resource::exit(worker *e) {
    }


    void worker_upgrade_to_scout::enter(worker *e) {
        m_finished = false;
        timer_manager::get()->add_timer(
            game_config::get()->unit_cfg[unit_type_scout].upgrade_time,
            e->id(),
            std::bind(&worker_upgrade_to_scout::finished, this));
    }

    void worker_upgrade_to_scout::execute(worker *e, int dt) {
        if (m_finished) {
            e->sm().set_next_state(worker_state_idle);
        }
    }

    void worker_upgrade_to_scout::make_decision(worker *e) {
    }

    void worker_upgrade_to_scout::process_messages(worker *e) {
    }

    void worker_upgrade_to_scout::change_state(worker *e) {
    }

    void worker_upgrade_to_scout::exit(worker *e) {
        entity_manager::get()->replace_entity<scout>(e->id(), unit_type_scout);
    }


    void worker_upgrade_to_builder::enter(worker *e) {
        m_finished = false;
    }

    void worker_upgrade_to_builder::execute(worker *e, int dt) {
    }

    void worker_upgrade_to_builder::make_decision(worker *e) {
    }

    void worker_upgrade_to_builder::process_messages(worker *e) {
    }

    void worker_upgrade_to_builder::change_state(worker *e) {
    }

    void worker_upgrade_to_builder::exit(worker *e) {
    }


    void worker_upgrade_to_miner::enter(worker *e) {
        m_finished = false;
    }

    void worker_upgrade_to_miner::execute(worker *e, int dt) {
    }

    void worker_upgrade_to_miner::make_decision(worker *e) {
    }

    void worker_upgrade_to_miner::process_messages(worker *e) {
    }

    void worker_upgrade_to_miner::change_state(worker *e) {
    }

    void worker_upgrade_to_miner::exit(worker *e) {
    }

} // namespace core
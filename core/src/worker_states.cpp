#include "worker_states.h"

#include "worker.h"
#include "scout.h"
#include "builder.h"
#include "miner.h"
#include "timer.h"
#include "game_config.h"
#include "entity_manager.h"
#include "job.h"

namespace core {

    void worker_idle::enter(worker *e) {
    }

    void worker_idle::execute(worker *e, int dt) {
        if (job_manager::get()->has_job(unit_type_worker)) {
            e->set_job(job_manager::get()->dispatch_worker_job());
        }
    }

    void worker_idle::make_decision(worker *e) {
    }

    void worker_idle::process_messages(worker *e) {
    }

    void worker_idle::change_state(worker *e) {
        const auto& j = e->get_job();
        switch (j.type) {
        case job_type_collect_resource: {
            e->sm().set_next_state(worker_state_move_to_resource);
            break;
        }
        case job_type_create_scout: {
            e->sm().set_next_state(worker_state_upgrade_to_scout);
            break;
        }
        case job_type_create_builder: {
            e->sm().set_next_state(worker_state_upgrade_to_builder);
            break;
        }
        case job_type_create_miner: {
            e->sm().set_next_state(worker_state_upgrade_to_miner);
            break;
        }
        }
    }

    void worker_idle::exit(worker *e) {
    }


    void worker_move_to_resource::enter(worker *e) {
        const auto j = e->get_job();
        if (j.res_type == resource_type_wood) {
            if (map::get()->get_start().lock()->storage[resource_type_wood] > 0)
                e->set_path(map::get()->get_path_from_to(e->get_tile().lock(), map::get()->get_start().lock()));
            else
                e->set_path(map::get()->get_path_to_tile_of(e->get_tile().lock(), tile_type_forest));
        }
        else {
            e->set_path(map::get()->get_path_from_to(e->get_tile().lock(), j.target.lock()));
        }
    }

    void worker_move_to_resource::execute(worker *e, int dt) {
        e->move(dt);
    }

    void worker_move_to_resource::make_decision(worker *e) {
    }

    void worker_move_to_resource::process_messages(worker *e) {
    }

    void worker_move_to_resource::change_state(worker *e) {
        auto t = e->get_tile().lock();
        
        if (e->get_path().m_path.empty()) {
            if (t->type == tile_type_forest && t->to_be_gathered < t->contents) {
                e->sm().set_next_state(worker_state_gather_resource);
                return;
            }
            e->sm().set_next_state(worker_state_idle);
            job_manager::get()->add_worker_job(e->get_job());
            e->reset_job();
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


    void worker_move_to_target::enter(worker *e) {
        if (e->get_job().res_type == resource_type_wood) {
            if (!e->get_job().target.expired()) {
                e->set_path(map::get()->get_path_from_to(
                    e->get_tile().lock(),
                    e->get_job().target.lock()
                ));
            }
            else {
                e->set_path(map::get()->get_path_from_to(
                    e->get_tile().lock(),
                    map::get()->get_start().lock()
                ));
            }
        }
        else {
            e->set_path(map::get()->get_path_from_to(
                e->get_tile().lock(),
                map::get()->get_start().lock()
            ));
        }
    }

    void worker_move_to_target::execute(worker *e, int dt) {
        e->move(dt);
    }

    void worker_move_to_target::make_decision(worker *e) {
    }

    void worker_move_to_target::process_messages(worker *e) {
    }

    void worker_move_to_target::change_state(worker *e) {
        auto& path = e->get_path();
        auto l = path.m_next.lock();
           
        if (path.m_i >= path.m_path.size()) {
            e->sm().set_next_state(worker_state_store_resource);
        }
    }

    void worker_move_to_target::exit(worker *e) {
    }


    void worker_gather_resource::enter(worker *e) {
        if (e->get_job().res_type == resource_type_wood) {
            auto t = e->get_tile().lock();
            m_started = false;
            m_finished = false;
            if (t->to_be_gathered < t->contents) {
                t->to_be_gathered += 1;
                m_started = true;
                timer_manager::get()->add_timer(
                    game_config::get()->resource_cfg[resource_type_wood].time,
                    e->id(),
                    std::bind(&worker_gather_resource::finished, this));
            }
        }
    }

    void worker_gather_resource::execute(worker *e, int dt) {
        auto t = e->get_tile().lock();
        if (e->get_job().res_type == resource_type_wood) {
            if (m_finished) {
                t->contents -= 1;
                t->to_be_gathered -= 1;
                e->set_carry(resource_type_wood);
                if (t->contents == 0) {
                    map::get()->get_targets()[static_cast<int>(target_type_forest)]--;
                    t->type = tile_type_grass;
                }
            }
        }
        else {
            e->set_carry(resource_type_coal);
            t->take_resource(resource_type_coal);
        }
    }

    void worker_gather_resource::make_decision(worker *e) {
    }

    void worker_gather_resource::process_messages(worker *e) {
    }

    void worker_gather_resource::change_state(worker *e) {
        auto t = e->get_tile().lock();
        if (e->get_job().res_type == resource_type_wood) {
            if (!m_started) {
                e->sm().set_next_state(worker_state_move_to_resource);
                return;
            }
            if (m_finished) {
                e->sm().set_next_state(worker_state_move_to_target);
            }
        }
        else {
            e->sm().set_next_state(worker_state_move_to_target);
        }
    }

    void worker_gather_resource::exit(worker *e) {
    }


    void worker_store_resource::enter(worker *e) {
    }

    void worker_store_resource::execute(worker *e, int dt) {
        e->get_tile().lock()->put_resource(e->carry());
        e->set_carry(resource_type_none);
    }

    void worker_store_resource::make_decision(worker *e) {
    }

    void worker_store_resource::process_messages(worker *e) {
    }

    void worker_store_resource::change_state(worker *e) {
        e->sm().set_next_state(worker_state_idle);
    }

    void worker_store_resource::exit(worker *e) {
        e->reset_job();
    }


    void worker_upgrade_to_scout::enter(worker *e) {
        m_finished = false;
        timer_manager::get()->add_timer(
            game_config::get()->unit_cfg[unit_type_scout].upgrade_time,
            e->id(),
            std::bind(&worker_upgrade_to_scout::finished, this));
    }

    void worker_upgrade_to_scout::execute(worker *e, int dt) {
    }

    void worker_upgrade_to_scout::make_decision(worker *e) {
    }

    void worker_upgrade_to_scout::process_messages(worker *e) {
    }

    void worker_upgrade_to_scout::change_state(worker *e) {
        if (m_finished) {
            e->sm().set_next_state(worker_state_idle);
        }
    }

    void worker_upgrade_to_scout::exit(worker *e) {
        entity_manager::get()->replace_entity<scout>(e->id(), unit_type_scout);
    }


    void worker_upgrade_to_builder::enter(worker *e) {
        m_finished = false;
        timer_manager::get()->add_timer(
            game_config::get()->unit_cfg[unit_type_builder].upgrade_time,
            e->id(),
            std::bind(&worker_upgrade_to_builder::finished, this));
    }

    void worker_upgrade_to_builder::execute(worker *e, int dt) {
        if (m_finished) {
            e->sm().set_next_state(worker_state_idle);
        }
    }

    void worker_upgrade_to_builder::make_decision(worker *e) {
    }

    void worker_upgrade_to_builder::process_messages(worker *e) {
    }

    void worker_upgrade_to_builder::change_state(worker *e) {
    }

    void worker_upgrade_to_builder::exit(worker *e) {
        entity_manager::get()->replace_entity<builder>(e->id(), unit_type_builder);
    }


    void worker_upgrade_to_miner::enter(worker *e) {
        m_finished = false;
        timer_manager::get()->add_timer(
            game_config::get()->unit_cfg[unit_type_miner].upgrade_time,
            e->id(),
            std::bind(&worker_upgrade_to_miner::finished, this));
    }

    void worker_upgrade_to_miner::execute(worker *e, int dt) {
        if (m_finished) {
            e->sm().set_next_state(worker_state_idle);
        }
    }

    void worker_upgrade_to_miner::make_decision(worker *e) {
    }

    void worker_upgrade_to_miner::process_messages(worker *e) {
    }

    void worker_upgrade_to_miner::change_state(worker *e) {
    }

    void worker_upgrade_to_miner::exit(worker *e) {
        entity_manager::get()->replace_entity<miner>(e->id(), unit_type_miner);
    }

} // namespace core
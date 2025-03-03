#include "worker_states.h"

#include "worker.h"
#include "scout.h"
#include "timer.h"
#include "game_config.h"
#include "entity_manager.h"
#include "job.h"

namespace core {

    void worker_idle::enter(worker *e) {
    }

    void worker_idle::execute(worker *e, int dt) {
        if (job_manager::get()->has_jobs()) {
            auto job = job_manager::get()->get_job();
            switch (job) {
            case job_type_create_scout: {
                e->sm().set_next_state(worker_state_upgrade_to_scout);
                return;
            }
            }
        }
        
        e->sm().set_next_state(worker_state_idle);
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
    }

    void worker_move_to_resource::execute(worker *e, int dt) {
    }

    void worker_move_to_resource::make_decision(worker *e) {
    }

    void worker_move_to_resource::process_messages(worker *e) {
    }

    void worker_move_to_resource::change_state(worker *e) {
    }

    void worker_move_to_resource::exit(worker *e) {
    }


    void worker_move_to_base::enter(worker *e) {
    }

    void worker_move_to_base::execute(worker *e, int dt) {
    }

    void worker_move_to_base::make_decision(worker *e) {
    }

    void worker_move_to_base::process_messages(worker *e) {
    }

    void worker_move_to_base::change_state(worker *e) {
    }

    void worker_move_to_base::exit(worker *e) {
    }


    void worker_gather_resource::enter(worker *e) {
    }

    void worker_gather_resource::execute(worker *e, int dt) {
    }

    void worker_gather_resource::make_decision(worker *e) {
    }

    void worker_gather_resource::process_messages(worker *e) {
    }

    void worker_gather_resource::change_state(worker *e) {
    }

    void worker_gather_resource::exit(worker *e) {
    }


    void worker_upgrade_to_scout::enter(worker *e) {
        timer_manager::get()->add_timer(
            game_config::get()->unit_cfg[util::str_to_unit("scout")].upgrade_time,
            e->id(),
            std::bind(&worker_upgrade_to_scout::finished, this));
    }

    void worker_upgrade_to_scout::execute(worker *e, int dt) {
        if (m_finished) {
            entity_manager::get()->replace_entity<scout>(e->id(), unit_type_scout);
        }
    }

    void worker_upgrade_to_scout::make_decision(worker *e) {
    }

    void worker_upgrade_to_scout::process_messages(worker *e) {
    }

    void worker_upgrade_to_scout::change_state(worker *e) {
    }

    void worker_upgrade_to_scout::exit(worker *e) {
    }


    void worker_upgrade_to_builder::enter(worker *e) {
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
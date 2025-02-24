#include "worker_states.h"

#include "worker.h"
#include "tile.h"
#include "map.h"
#include "timer.h"

namespace core {

    void idle::enter(worker *e) {
        e->set_state(worker_state_idle);
    }

    void idle::execute(worker *e, int dt) {
    }

    void idle::make_decision(worker *e) {
    }

    void idle::process_messages(worker *e) {
    }

    void idle::change_state(worker *e) {
        e->change_state();
    }

    void idle::exit(worker *e) {
    }


    void move::enter(worker *e) {
        e->set_state(worker_state_move);
    }

    void move::execute(worker *e, int dt) {
        auto l = e->path().m_next.lock();
        std::array<int, 2> dir = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        dir[0] = (dest[0] - dir[0]) / l->size * e->speed() * dt;
        dir[1] = (dest[1] - dir[1]) / l->size * e->speed() * dt;
        e->set_pos({dest[0] + dir[0], dest[1] + dir[1]});
    }

    void move::make_decision(worker *e) {
    }

    void move::process_messages(worker *e) {
    }

    void move::change_state(worker *e) {
        auto& path = e->path();
        auto l = path.m_next.lock();
        if (e->pos() == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            
            if (path.m_i >= path.m_path.size()) {
                e->change_state();
                return;
            }
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void move::exit(worker *e) {
    }


    void gather_resource::enter(worker *e) {
        e->set_state(worker_state_gather_resource);
        auto t = e->get_tile().lock();
        if (t->to_be_gathered < t->contents) {
            t->to_be_gathered += 1;
            timer_manager::get()->add_timer(game_config::get()->resource_cfg[resource_type_wood].time, e->id(), [=](){finished_gathering();});
        }
        else {
            e->set_next_state(worker_state_idle);
        }
    }

    void gather_resource::execute(worker *e, int dt) {
        if (m_finished) {
            auto t = e->get_tile().lock();
            t->contents -= 1;
            t->to_be_gathered -= 1;
            e->set_carry(resource_type_wood);
            if (t->contents == 0) {
                t->type = tile_type_grass;
            }
        }
    }

    void gather_resource::make_decision(worker *e) {
    }

    void gather_resource::process_messages(worker *e) {
    }

    void gather_resource::change_state(worker *e) {
        if (m_finished) {
            e->change_state();
        }
    }

    void gather_resource::exit(worker *e) {
    }

} // namespace core
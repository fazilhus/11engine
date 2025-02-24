#include "worker_states.h"

#include "worker.h"
#include "tile.h"
#include "map.h"
#include "timer.h"

namespace core {

    void idle::enter(worker *e) {
    }

    void idle::execute(worker *e, int dt) {
        if (!map::get()->get_targets().empty()) {
            e->set_next_state(worker_state_move_to_resource);
        }
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


    void move_to_resource::enter(worker *e) {
        if (e->path().m_path.empty()) {
            e->set_next_state(worker_state_idle);
        }
    }

    void move_to_resource::execute(worker *e, int dt) {
        if (e->path().m_path.empty()) return;

        auto l = e->path().m_next.lock();
        std::array<int, 2> dir = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        dir[0] = (dest[0] - dir[0]) / l->size * e->speed() * dt;
        dir[1] = (dest[1] - dir[1]) / l->size * e->speed() * dt;
        e->set_pos({dest[0] + dir[0], dest[1] + dir[1]});
    }

    void move_to_resource::make_decision(worker *e) {
    }

    void move_to_resource::process_messages(worker *e) {
    }

    void move_to_resource::change_state(worker *e) {
        auto& path = e->path();
        auto l = path.m_next.lock();
        if (e->pos() == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            
            if (path.m_i >= path.m_path.size()) {
                e->set_next_state(worker_state_gather_resource);
                e->change_state();
                return;
            }
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void move_to_resource::exit(worker *e) {
    }


    void move_to_base::enter(worker *e) {
    }

    void move_to_base::execute(worker *e, int dt) {
        auto l = e->path().m_next.lock();
        std::array<int, 2> dir = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        dir[0] = (dest[0] - dir[0]) / l->size * e->speed() * dt;
        dir[1] = (dest[1] - dir[1]) / l->size * e->speed() * dt;
        e->set_pos({dest[0] + dir[0], dest[1] + dir[1]});
    }

    void move_to_base::make_decision(worker *e) {
    }

    void move_to_base::process_messages(worker *e) {
    }

    void move_to_base::change_state(worker *e) {
        auto& path = e->path();
        auto l = path.m_next.lock();
        if (e->pos() == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            
            if (path.m_i >= path.m_path.size()) {
                e->set_next_state(worker_state_idle);
                e->change_state();
                return;
            }
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void move_to_base::exit(worker *e) {
    }


    void gather_resource::enter(worker *e) {
        auto t = e->get_tile().lock();
        if (t->to_be_gathered < t->contents) {
            t->to_be_gathered += 1;
            timer_manager::get()->add_timer(game_config::get()->resource_cfg[resource_type_wood].time, e->id(), [=](){finished_gathering();});
        }
        else {
            e->set_next_state(worker_state_move_to_resource);
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
                auto [x, _] = map::get()->get_dim();
                map::get()->get_targets().erase(t->posy * x + t->posx);
            }
        }
    }

    void gather_resource::make_decision(worker *e) {
    }

    void gather_resource::process_messages(worker *e) {
    }

    void gather_resource::change_state(worker *e) {
        if (m_finished) {
            e->set_next_state(worker_state_move_to_base);
        }
        e->change_state();
    }

    void gather_resource::exit(worker *e) {
    }

} // namespace core
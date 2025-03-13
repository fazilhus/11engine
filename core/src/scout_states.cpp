#include "scout_states.h"

#include "scout.h"
#include "tile.h"
#include "map.h"
#include "vec_math.h"

namespace core {

    void scout_idle::enter(scout *e) {
    }

    void scout_idle::execute(scout *e, int dt) {
    }

    void scout_idle::make_decision(scout *e) {
    }

    void scout_idle::process_messages(scout *e) {
    }

    void scout_idle::change_state(scout *e) {
        if (!map::get()->discovered()) {
            e->sm().set_next_state(scout_state_wander);
        }
    }

    void scout_idle::exit(scout *e) {
    }


    void scout_wander::enter(scout *e) {
        e->set_path(map::get()->get_path_to_undiscovered(e->get_tile().lock()));
        if (e->get_path().m_path.empty()) {
            map::get()->set_discovered(true);
            return;
        }
        e->get_path().m_path.back().lock()->to_be_discovered = true;
    }

    void scout_wander::execute(scout *e, int dt) {
        e->move(dt, true);
    }

    void scout_wander::make_decision(scout *e) {
    }

    void scout_wander::process_messages(scout *e) {
    }

    void scout_wander::change_state(scout *e) {
        auto& path = e->get_path();
        auto l = path.m_next.lock();
           
        if (path.m_path.empty() || path.m_i >= path.m_path.size()) {
            e->sm().set_next_state(scout_state_idle);
        }
    }

    void scout_wander::exit(scout *e) {
    }

} // namespace core
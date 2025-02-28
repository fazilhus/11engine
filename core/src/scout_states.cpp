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
        e->sm().set_next_state(scout_state_wander);
    }

    void scout_idle::exit(scout *e) {
    }


    void scout_wander::enter(scout *e) {
        e->set_path(map::get()->get_path_to_undiscovered(e->get_tile().lock()));
        e->get_path().m_path.back().lock()->to_be_discovered = true;
    }

    void scout_wander::execute(scout *e, int dt) {
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
            map::get()->discover_around(e->get_tile());
            path.m_i++;
            if (path.m_i >= path.m_path.size()) return;
            
            path.m_next = path.m_path[path.m_i];
        }
    }

    void scout_wander::make_decision(scout *e) {
    }

    void scout_wander::process_messages(scout *e) {
    }

    void scout_wander::change_state(scout *e) {
        auto& path = e->get_path();
        auto l = path.m_next.lock();
           
        if (path.m_i >= path.m_path.size()) {
            e->sm().set_next_state(scout_state_idle);
        }
    }

    void scout_wander::exit(scout *e) {
    }

} // namespace core
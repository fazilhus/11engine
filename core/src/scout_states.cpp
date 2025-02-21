#include "scout_states.h"

#include "scout.h"
#include "tile.h"
#include "map.h"

namespace core {

    void wander::enter(scout *e) {
    }

    void wander::execute(scout *e, int dt) {
        auto l = e->path().m_next.lock();
        std::array<int, 2> dir = e->pos();
        auto dest = util::tile_to_pos(l->pos);
        dir[0] = (dest[0] - dir[0]) / l->size * e->speed() * dt;
        dir[1] = (dest[1] - dir[1]) / l->size * e->speed() * dt;
        e->set_pos({dest[0] + dir[0], dest[1] + dir[1]});
    }

    void wander::make_decision(scout *e) {
    }

    void wander::process_messages(scout *e) {
    }

    void wander::change_state(scout *e) {
        auto& path = e->path();
        auto l = path.m_next.lock();
        if (e->pos() == util::tile_to_pos(l->pos)) {
            e->set_tile(l);
            path.m_i++;
            
            if (path.m_i >= path.m_path.size()) {
                e->change_state();
            }
            
            path.m_next = path.m_path[path.m_i];
            map::get()->discover_around(e->get_tile());
        }
    }

    void wander::exit(scout *e) {
    }

} // namespace core
#include "wander.h"

#include "scout.h"
#include "tile.h"
#include "smap.h"

namespace core {

    void wander::enter(scout *e) {
    }

    void wander::execute(scout *e, int dt) {
        auto l = e->link();
        std::array<int, 2> dir = e->pos();
        auto t = l.m_to.lock();
        auto dest = util::tile_to_pos(t->pos);
        dir[0] = (dest[0] - dir[0]) / t->size * e->speed() * dt;
        dir[1] = (dest[1] - dir[1]) / t->size * e->speed() * dt;
        e->set_pos({dest[0] + dir[0], dest[1] + dir[1]});
    }

    void wander::make_decision(scout *e) {
    }

    void wander::process_messages(scout *e) {
    }

    void wander::change_state(scout *e) {
        auto l = e->link();
        if (e->pos() == util::tile_to_pos(l.m_to.lock()->pos)) {
            e->set_tile(l.m_to);
            map::get()->discover_around(e->get_tile());
            e->change_state();
        }
    }

    void wander::exit(scout *e) {
    }

} // namespace core
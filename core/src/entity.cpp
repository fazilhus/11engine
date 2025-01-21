#include "entity.h"

#include <cassert>

#include "state.h"

namespace core {

    entity::entity(int id)
        : m_id(id) {
        set_id(id);
    }

    entity::~entity() {
    }

    human::human(int id)
        : entity(id) {
            m_current_state = new resting();
    }

    human::~human() {
        if (m_current_state) {
            delete m_current_state;
        }
    }

    void human::update() {
        if (m_current_state) {
            m_current_state->execute(this);
        }
    }

    void human::change_state(state* new_state) {
        assert(m_current_state && new_state);

        m_current_state->exit(this);
        m_current_state = new_state;
        m_current_state->enter(this);
    }

} // namespace core
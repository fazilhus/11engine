#include "state.h"

#include "entity.h"

namespace core {

    state::~state() {
    }

    void working::enter(human* e) {
        std::cout << "Entering working state" << std::endl;
        e->m_fsm_state = fsm_state::working;
        e->m_location = loc::work;
    }

    void working::execute(human* e) {
        std::cout << "Working..." << std::endl;
        e->m_money += 10;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue += 15;
        e->m_loneliness += 5;
    }

    void working::exit(human* e) {
        std::cout << "Exiting working state" << std::endl;
    }

    void resting::enter(human* e) {
        std::cout << "Entering resting state" << std::endl;
        e->m_fsm_state = fsm_state::resting;
        e->m_location = loc::home;
    }

    void resting::execute(human* e) {
        std::cout << "Resting..." << std::endl;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue -= 20;
        e->m_loneliness += 5;
    }

    void resting::exit(human* e) {
        std::cout << "Exiting resting state" << std::endl;
    }

} // namespace core
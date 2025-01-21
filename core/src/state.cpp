#include "state.h"

#include "entity.h"

namespace core {

    state::~state() {
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
        e->m_fatigue -= 25;
        e->m_loneliness += 5;

        if (e->is_tired()) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_lonely() && e->m_money >= 50) {
            e->change_state(fsm_state::partying);
        }
        else {
            e->change_state(fsm_state::working);
        }
    }

    void resting::exit(human* e) {
        std::cout << "Exiting resting state" << std::endl;
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

        if (e->is_hungry() && e->m_money >= 20) {
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 50) {
            e->change_state(fsm_state::partying);
        }
    }

    void working::exit(human* e) {
        std::cout << "Exiting working state" << std::endl;
    }

    void eating::enter(human* e) {
        std::cout << "Entering eating state" << std::endl;
        e->m_fsm_state = fsm_state::eating;
        e->m_location = loc::restaurant;
    }

    void eating::execute(human* e) {
        std::cout << "Eating..." << std::endl;
        e->m_money -= 20;
        e->m_hunger -= 20;
        e->m_thirst -= 5;
        e->m_fatigue += 5;
        e->m_loneliness -= 5;

        if (e->is_hungry()) return;

        if (e->is_thirsty() && e->m_money >= 15) {
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 50) {
            e->change_state(fsm_state::partying);
        }
        else {
            e->change_state(fsm_state::working);
        }
    }

    void eating::exit(human* e) {
        std::cout << "Exiting eating state" << std::endl;
    }

    void drinking::enter(human* e) {
        std::cout << "Entering drinking state" << std::endl;
        e->m_fsm_state = fsm_state::drinking;
        e->m_location = loc::bar;
    }

    void drinking::execute(human* e) {
        std::cout << "Drinking..." << std::endl;
        e->m_money -= 15;
        e->m_hunger -= 5;
        e->m_thirst -= 20;
        e->m_fatigue += 5;
        e->m_loneliness -= 10;

        if (e->is_thirsty()) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->change_state(fsm_state::eating);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 50) {
            e->change_state(fsm_state::partying);
        }
        else {
            e->change_state(fsm_state::working);
        }
    }

    void drinking::exit(human* e) {
        std::cout << "Exiting drinking state" << std::endl;
    }

    void partying::enter(human* e) {
        std::cout << "Entering partying state" << std::endl;
        e->m_fsm_state = fsm_state::partying;
        e->m_location = loc::party;
    }

    void partying::execute(human* e) {
        std::cout << "Partying..." << std::endl;
        e->m_money -= 50;
        e->m_hunger -= 10;
        e->m_thirst -= 20;
        e->m_fatigue += 20;
        e->m_loneliness -= 20;

        if (e->is_lonely()) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else {
            e->change_state(fsm_state::working);
        }
    }

    void partying::exit(human* e) {
        std::cout << "Exiting partying state" << std::endl;
    }

} // namespace core
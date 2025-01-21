#include "state.h"

#include "entity.h"

namespace core {

    state::~state() {
    }

    void working::enter(human* e) {
        std::cout << "Entering working state" << std::endl;
    }

    void working::execute(human* e) {
        std::cout << "Working..." << std::endl;
        e->m_money += 10;
    }

    void working::exit(human* e) {
        std::cout << "Exiting working state" << std::endl;
    }

    void resting::enter(human* e) {
        std::cout << "Entering resting state" << std::endl;
    }

    void resting::execute(human* e) {
        std::cout << "Resting..." << std::endl;
        e->m_fatigue -= 10;
    }

    void resting::exit(human* e) {
        std::cout << "Exiting resting state" << std::endl;
    }

} // namespace core
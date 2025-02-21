#include "clock.h"

namespace core {

    clock* clock::s_instance = nullptr;

    clock::clock() {
        s_instance = this;
        m_tick = 0;
    }

    void clock::update(int dt) {
        m_tick += dt;
    }

} // namespace core
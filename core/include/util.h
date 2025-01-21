#pragma once

#include <string>

namespace core {

    enum class fsm_state {
        resting,
        working,
        eating,
        drinking,
        num_states
    };

    enum class loc {
        home,
        work,
        restaurant,
        bar,
        num_locs
    };


    namespace util {

        std::string str(fsm_state state);
        std::string str(loc location);

    }

} // namespace core
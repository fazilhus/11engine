#pragma once

#include <string>

namespace core {

    enum class fsm_state {
        resting,
        working,
        eating,
        drinking,
        partying,
        num_states
    };

    enum class loc {
        home,
        work,
        restaurant,
        bar,
        party,
        num_locs
    };


    namespace util {

        std::string str(fsm_state state);
        std::string str(loc location);

    }

} // namespace core
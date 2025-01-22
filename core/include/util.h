#pragma once

#include <string>

namespace core {

    enum class fsm_state {
        resting,
        working_at_construction,
        working_at_office,
        eating,
        drinking,
        partying,
        num_states
    };

    enum class loc {
        home,
        construction,
        office,
        restaurant,
        bar,
        party,
        num_locs
    };


    namespace util {

        std::string str(fsm_state state);
        std::string str(loc location);

        void init_random();
        int random_int(int min, int max);

    }

} // namespace core
#pragma once

#include <string>

namespace core {

    enum class fsm_state {
        none,
        resting,
        working_at_construction,
        working_at_office,
        eating,
        drinking,
        partying,
        num_states
    };

    enum class loc {
        none,
        home,
        construction,
        office,
        restaurant,
        bar,
        party,
        num_locs
    };

    enum class message_type {
        none,
        go_eating,
        go_drinking,
        go_partying,
        num_types
    };


    namespace util {

        std::string str(fsm_state state);
        std::string str(loc location);
        std::string str(message_type type);

        void init_random();
        int random_int(int min, int max);

    }

} // namespace core